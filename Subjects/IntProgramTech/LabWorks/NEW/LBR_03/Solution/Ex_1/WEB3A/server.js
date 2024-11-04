const http = require('http');
const url = require('url');
const PORT = 3000;

const server = http.createServer(function(request, response) {
    if (request.method === 'POST') {
        let body = '';

        request.on('data', function(chunk) {
            body = body + chunk.toString();
        });

        request.on('end', function() {
            console.log('Полученные данные из POST-запроса:', body);
            response.setHeader('Set-Cookie', 'data=${}; HttpOnly; Path=/;');
            response.writeHead(200, {'Content-Type': 'application/json'});
            response.end(JSON.stringify({message: 'Data received', data: body}));
        });

    }
    else {
        response.writeHead(405, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('Метод недоступен');
    }
});

server.listen(PORT, function() {
    console.log("Сервер запущен на http://localhost:" + PORT);
});