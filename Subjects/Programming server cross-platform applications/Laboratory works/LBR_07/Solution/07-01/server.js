const http = require('http');
const fileSystem = require('fs');
const PORT = 5000;

const server = http.createServer(function(request, response) {
    if (request.method === 'GET') {
        response.writeHead(405, {'Content-Type': 'text/plain; charset=utf8'});
        response.end('Обработан метод GET');
    }
    else {
        response.writeHead(405, {'Content-Type': 'text/plain; charset=utf8'});
        response.end('Поддерживается только метод GET');
    }
});

server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});