const http = require('http');
const url = require('url');
const fileSys = require('fs');
const DB = require('./db');
const PORT = 5000;

let requestCount = 0;
let commitCount = 0;

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
            }
            else {
                response.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                response.end(data);
            }
        });
        return; 
    }
    else if (parsedUrl.pathname === '/api/db') {
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
                    body = body + chunk.toString(); 
                });

                request.on('end', function () {
                    try {
                        const newEntry = JSON.parse(body);
                        const entryWithId = DB.insert(newEntry); 

                        response.writeHead(201, { 'Content-Type': 'application/json; charset=utf-8' });
                        response.end(JSON.stringify(entryWithId)); 
                    } 
                    catch (error) {
                        response.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
                        response.end('Некорректный JSON');
                    }
                });    
                break;
            }
            case 'PUT': {
                const id = parseInt(parsedUrl.query.id); 
                let body = '';

                request.on('data', function (chunk) {
                    body = body + chunk.toString(); 
                });

                request.on('end', function () {
                    try {
                        const updatedEntry = JSON.parse(body);
                        const updatedRecord = DB.update(id, updatedEntry);

                        response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
                        response.end(JSON.stringify(updatedRecord)); 
                    } 
                    catch (error) {
                        response.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
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
                } 
                catch (error) {
                    response.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
                    response.end('Запись не найдена');
                }
                break;
            }
            case 'COMMIT': {
                DB.commit(); 
                commitCount++; 
                response.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
                response.end('Состояние БД зафиксировано');
                break;
            }
            default: {
                response.writeHead(405, { 'Content-Type': 'text/plain; charset=utf-8' });
                response.end('Метод не разрешен');
                break;
            }
        }
    }
    else if (parsedUrl.pathname === '/api/ss' && method === 'GET') {
        if (!isCollectingStats) {
            statsStartTime = new Date().toISOString();
            isCollectingStats = true;
            statsEndTime = null; 
        } else {
            statsEndTime = new Date().toISOString(); 
            isCollectingStats = false;
        }

        const stats = {
            start: statsStartTime,
            finish: statsEndTime,
            request: requestCount,
            commit: commitCount
        };

        response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
        response.end(JSON.stringify(stats));
    }
    else {
        response.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
        response.end('Страница не найдена');
    }

});

DB.on('GET', function(data) {
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

const commandLine = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

let shutdownTimeout;
let commitInterval;
let statsTimeout;

commandLine.on('line', function (input) {
    const args = input.split(' ');
    const command = args[0];
    const param = args[1];

    switch (command) {
        case 'sd': {
            if (param) {
                const seconds = parseInt(param);
                if (!isNaN(seconds)) {
                    clearTimeout(shutdownTimeout);
                    shutdownTimeout = setTimeout(function() {
                        console.log('Сервер остановлен через ' + seconds + ' секунд.');
                        server.close();
                        process.exit(0);
                    }, seconds * 1000);
                    shutdownTimeout.unref(); 
                }
            } 
            else {
                clearTimeout(shutdownTimeout);
                console.log('Остановка сервера отменена.');
            }
            break;
        }
        case 'sc': {
            if (param) {
                const seconds = parseInt(param);
                if (!isNaN(seconds)) {
                    clearInterval(commitInterval);
                    commitInterval = setInterval(function () {
                        DB.commit();
                        commitCount++;
                    }, seconds * 1000);
                    commitInterval.unref();
                    console.log('Функция фиксации запущена каждые ' + seconds + ' секунд.');
                }
            } 
            else {
                clearInterval(commitInterval);
                console.log('Функция фиксации остановлена.');
            }
            break;
        }
        case 'ss': {
            if (param) {
                const seconds = parseInt(param);
                if (!isNaN(seconds)) {
                    clearTimeout(statsInterval);
                    statsInterval = setTimeout(() => {
                        console.log(`Статистика: выполнено запросов ${requestCount}, фиксаций ${commitCount}`);
                    }, seconds * 1000);
                    statsTimeout.unref();
                    console.log('Сбор статистики запущен на ' + seconds + ' секунд.');
                }
            } else {
                clearTimeout(statsInterval);
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
    console.log('Для демонстрации задания запускать надо на http://localhost:5000/api/db');
});