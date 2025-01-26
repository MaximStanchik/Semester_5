const http = require('http');
const PORT = 5000;

const httpHandler = function(request, response) {
    if (request.method === 'GET') {
        const cssContent = `
            body {
                background-color: #f0f0f0;
                font-family: Arial, sans-serif;
            }
            h1 {
                color: #333;
            }
            p {
                font-size: 16px;
                color: #666;
            }
        `;

        response.writeHead(200, {
            'Content-Type': 'text/css',
            'Cache-Control': 'max-age=3600',
            'Last-Modified': new Date().toUTCString(),
            'ETag': '"12345"'
        });

        response.end(cssContent);
    } else {
        response.writeHead(400, {'Content-Type': 'text/plain; charset=utf8'});
        response.end('Другие методы не поддерживаются');
    }
};

const server = http.createServer(httpHandler);
server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});