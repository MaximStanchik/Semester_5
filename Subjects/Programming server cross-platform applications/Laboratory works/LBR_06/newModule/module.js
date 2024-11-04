const http = require('http');
const PORT = 3001;

const server = http.createServer(function (request, responce) {
    if (request.method === 'GET') {
        responce.end('HELLO!');
    }
    else {
        responce.end("Another method!");
    }
});

server.listen(3001, function() {
    console.log("Сервер будет на localhost:" , PORT);
});