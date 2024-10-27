const http = require('http');

http.createServer (function (request, responce) {
    responce.writeHead(200, {'Content-Type' : 'text/html'});
    responce.end('<h1>Hello World</h1>');
}).listen(3000, () => {console.log('Server running at http://localhost:3000/')});

