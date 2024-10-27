const http = require('http');
const fileSystem = require('fs');
const path = require('path');
const PORT = 5000;

const server = http.createServer(function(request, response) {
    if (request.url == '/png') {
        const filePath = path.join(__dirname, 'pic.png');

        fileSystem.readFile(filePath, function(fileSystemError, data) {
            if (fileSystemError == true) {
                response.writeHead(500, {'Content-Type' : 'text/plain'});
                response.end('Ошибка сервера');
                return;
            }
            else {
                response.writeHead(200, {'Content-Type' : 'image/png'});
                response.end(data);
            }
        });
    }
    else {
        response.writeHead(404, {'Content-Type': 'text/plain'});
        response.end('404 not found');
    }
});

server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT + '/png');
});