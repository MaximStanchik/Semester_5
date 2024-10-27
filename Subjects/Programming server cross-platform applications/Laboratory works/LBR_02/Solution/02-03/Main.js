const http = require('http');
const PORT = 5000;

const server = http.createServer(function(request, response) {
    if (request.url == '/api/name' && request.method === 'GET') {
        response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('Станчик Максим Андреевич');
    }
    else {
        response.writeHead(404, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('404 not found');
    }

});

server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT + '/api/name');
});