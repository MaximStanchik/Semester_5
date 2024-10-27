const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = 5000;

const server = http.createServer(function(request, response) {
    if (request.url === '/xmlhttprequest' && request.method === 'GET') {
        const filePath = path.join(__dirname, 'xmlhttprequest.html');
        
        fs.readFile(filePath, 'utf8', function(err, data) {
            if (err) {
                response.writeHead(500, {'Content-Type': 'text/plain; charset=utf-8'});
                response.end('Ошибка сервера');
                return;
            }
            response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
            response.end(data);
        });
    } 
    else if (request.url === '/api/name' && request.method === 'GET') {
        response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('Станчик Максим Андреевич');
    } 
    else {
        response.writeHead(404, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('404 not found');
    }
});

server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});