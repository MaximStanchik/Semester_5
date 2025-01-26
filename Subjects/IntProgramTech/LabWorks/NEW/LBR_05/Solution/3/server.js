const http = require('http');
const PORT = 5000;

const httpHandler = function(request, response) {
    if (request.method === 'GET') {
        const scriptContent = `
            console.log('Script is loaded and done!');
            alert('Hello from JavaScript!');
        `;

        response.writeHead(200, {
            'Content-Type': 'application/javascript',
            'Cache-Control': 'no-cache', 
            'Last-Modified': new Date().toUTCString(),
            'ETag': '"12345"' 
        });

        response.end(scriptContent);
    } 
    else {
        response.writeHead(400, {'Content-Type': 'text/plain; charset=utf8'});
        response.end('Other methods are not supported!');
    }
};

const server = http.createServer(httpHandler);
server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});