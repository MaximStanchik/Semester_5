const http = require('http');
const fileSystem = require('fs');
const path = require('path');

const PORT = 5000;

const server = http.createServer(function(request, response) {
    if (request.url === '/html') 
    {
       const filepath = path.join(__dirname, 'index.html');
       fileSystem.readFile(filepath, 'utf8', function(readFileError, fileData) {
        if (readFileError) {
            response.writeHead(500, {'Content-Type': 'text/plain'});
            response.end('Ошибка сервера');
            return;
        }
        else {
         response.writeHead(200, {'Content-Type': 'text/html'});
         response.end(fileData);
        }
       });
       
    }
    else 
    {
        response.writeHead(404, {'Content-Type': 'text/plain'});
        response.end('404 not found');
    }
});

server.listen(PORT, function() {
    console.log(`Сервер запущен на http://localhost:${PORT}/html`);
});