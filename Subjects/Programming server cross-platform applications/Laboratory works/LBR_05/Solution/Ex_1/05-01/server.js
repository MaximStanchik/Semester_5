const http = require('http');
const url = require('url');
const fileSys = require('fs');
const DB = require('./db');
const PORT = 5000;

let requestCount = 0;
let commitCount = 0;
let isCollectingStats = false;
let statsInterval = null;
let statsStartTime = null;
let finishStatisticsDate = null;

const server = http.createServer(function (request, response) {
    requestCount++;
    const parsedUrl = url.parse(request.url, true);
    const method = request.method;

    if (parsedUrl.pathname === '/') {
        fileSys.readFile('main.html', 'utf8', function (error, data) {
            if (error) {
                response.writeHead(500, { 'Content-Type': 'text/plain; charset=utf-8' });
                response.end('Ошибка при загрузке страницы');
                return;
            } else {
                response.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                response.end(data);
            }
        });
        return;
    } else if (parsedUrl.pathname === '/api/db') {
        switch (method) {
            case 'GET': {
                const data = DB.select();
                response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
                response.end(JSON.stringify(data));
                break;
            }
            case 'POST': {
                let body = '';
                request.on('data', function (chunk) {
                    body += chunk.toString();
                });
                request.on('end', function () {
                    try {
                        const newEntry = JSON.parse(body);
                        if (newEntry.action === 'commit') {
                            DB.commit();
                            commitCount++;
                            response.writeHead(200, { 'Content-Type': 'text/plain' });
                            response.end('Состояние БД зафиксировано');
                        } else {
                            const entryWithId = DB.insert(newEntry);
                            response.writeHead(201, { 'Content-Type': 'application/json' });
                            response.end(JSON.stringify(entryWithId));
                        }
                    } catch (error) {
                        response.writeHead(400, { 'Content-Type': 'text/plain' });
                        response.end('Некорректный JSON');
                    }
                });
                break;
            }
            case 'PUT': {
                const id = parseInt(parsedUrl.query.id);
                let body = '';
                request.on('data', function (chunk) {
                    body += chunk.toString();
                });
                request.on('end', function () {
                    try {
                        const updatedEntry = JSON.parse(body);
                        const updatedRecord = DB.update(id, updatedEntry);
                        response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
                        response.end(JSON.stringify(updatedRecord));
                    } catch (error) {
                        response.writeHead(400, { 'Content-Type': 'text/plain' });
                        response.end('Некорректный JSON');
                    }
                });
                break;
            }
            case 'DELETE': {
                const id = parseInt(parsedUrl.query.id);
                try {
                    const deletedEntry = DB.delete(id);
                    response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
                    response.end(JSON.stringify(deletedEntry));
                } catch (error) {
                    response.writeHead(404, { 'Content-Type': 'text/plain' });
                    response.end('Запись не найдена');
                }
                break;
            }
            default: {
                response.writeHead(405, { 'Content-Type': 'text/plain' });
                response.end('Метод не разрешен');
                break;
            }
        }
    } else if (parsedUrl.pathname === '/api/ss' && method === 'GET') {
        const stats = {
            start: statsStartTime || null,
            finish: isCollectingStats ? null : finishStatisticsDate,
            request: requestCount,
            commit: commitCount
        };
        response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
        response.end(JSON.stringify(stats));
    } else {
        response.writeHead(404, { 'Content-Type': 'text/plain' });
        response.end('Страница не найдена');
    }
});

DB.on('GET', function (data) {
    console.log('Полученные данные:', JSON.stringify(data, null, 2));
});
DB.on('POST', (newEntry) => {
    console.log('Добавлена новая запись:', JSON.stringify(newEntry, null, 2));
});
DB.on('PUT', (updatedEntry) => {
    console.log('Обновлена запись:', JSON.stringify(updatedEntry, null, 2));
});
DB.on('DELETE', (deletedEntry) => {
    console.log('Удалена запись:', JSON.stringify(deletedEntry, null, 2));
});
DB.on('COMMIT', function () {
    console.log('Состояние БД зафиксировано через событие COMMIT');
});

const commandLine = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

function collectStatistics(duration) {
    let elapsedTime = 0;

    statsStartTime = new Date().toISOString();
    isCollectingStats = true;
    finishStatisticsDate = null; 

    statsInterval = setInterval(() => {
        elapsedTime += 1;
        if (elapsedTime >= duration) {
            clearInterval(statsInterval);
            isCollectingStats = false;
            finishStatisticsDate = new Date().toISOString();
            console.log('Сбор статистики завершен.');
            console.log(`Запросы: ${requestCount}, Фиксации: ${commitCount}`);
            return;
        }
    }, 1000);
    statsInterval.unref();
}

let shutdownTimer = null;
let periodicCommitInterval = null;

function shutdownServer(seconds) {
    shutdownTimer = setTimeout(function () {
        server.close(() => {
            console.log('Сервер остановлен.');
        });
    }, seconds * 1000);
    shutdownTimer.unref();
}

commandLine.on('line', function (input) {
    const args = input.split(' ');
    const command = args[0];
    const param = args[1];

    switch (command) {
        case 'sd': {
            if (param) {
                const seconds = parseInt(param);
                if (isNaN(seconds)) {
                    console.log('Пожалуйста, укажите корректное число секунд.');
                } else {
                    console.log('Сервер будет остановлен через ' + seconds + ' секунд');
                    clearTimeout(shutdownTimer);
                    shutdownServer(seconds);
                }
            } else {
                clearTimeout(shutdownTimer);
                console.log('Остановка сервера отменена');
            }
            break;
        }
        case 'sc': {
            if (param) {
                const seconds = parseInt(param);
                if (isNaN(seconds) || seconds <= 0) {
                    console.log('Пожалуйста, укажите корректное число секунд.');
                } else {
                    if (periodicCommitInterval) {
                        clearInterval(periodicCommitInterval);
                    }
                    periodicCommitInterval = setInterval(() => {
                        DB.commit();
                        commitCount++;
                    }, seconds * 1000);
                    periodicCommitInterval.unref(); 
                    console.log(`Периодическая фиксация запущена каждые ${seconds} секунд.`);
                }
            } else {
                if (periodicCommitInterval) {
                    clearInterval(periodicCommitInterval);
                    periodicCommitInterval = null;
                    console.log('Периодическая фиксация остановлена.');
                } else {
                    console.log('Периодическая фиксация не была запущена.');
                }
            }
            break;
        }
        case 'ss': {
            if (param) {
                const seconds = parseInt(param);
                if (!isNaN(seconds) && seconds > 0) {
                    collectStatistics(seconds);
                    console.log(`Сбор статистики запущен на ${seconds} секунд.`);
                } else {
                    console.log('Пожалуйста, введите корректное число секунд.');
                }
            } else {
                clearInterval(statsInterval);
                isCollectingStats = false;
                console.log('Сбор статистики остановлен.');
            }
            break;
        }
        default: {
            console.log('Неизвестная команда.');
            break;
        }
    }
});

server.listen(PORT, function () {
    console.log('Сервер запущен на http://localhost:' + PORT);
    console.log('Для демонстрации задания запускать надо на http://localhost:5000/api/ss');
});
