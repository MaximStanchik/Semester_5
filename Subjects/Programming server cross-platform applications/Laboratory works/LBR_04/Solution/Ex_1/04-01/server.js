const http = require('http');
const url = require('url');
const DB = require('./db');
const PORT = 5000;

const server = http.createServer(function (request, response) {
    const parsedUrl = url.parse(request.url, true);
    const method = request.method;

    if (parsedUrl.pathname === '/api/db') {
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
            default: {
                response.writeHead(405, { 'Content-Type': 'text/plain; charset=utf-8' });
                response.end('Метод не разрешен');
                break;
            }
        }
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

server.listen(PORT, function () {
    console.log('Сервер запущен на http://localhost:' + PORT);
    console.log('Для демонстрации задания запускать надо на http://localhost:5000/api/db');
});