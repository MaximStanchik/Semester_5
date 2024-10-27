const http = require('http');
const fs = require('fs'); 
const PORT = 5000;

function calculateFactorial(k) {
    if (k === 0) {
        return 1;
    } else if (k < 0) {
        return null;
    } else {
        return k * calculateFactorial(k - 1);
    }
}

const server = http.createServer((request, response) => {
    response.setHeader('Access-Control-Allow-Origin', '*');

    const url = new URL(request.url, `http://${request.headers.host}`);

    if (url.pathname === '/fact' && url.searchParams.has('k')) {
        const k = parseInt(url.searchParams.get('k'), 10);
        const factorial = calculateFactorial(k);
        
        if (factorial !== null) {
            response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
            response.end(JSON.stringify({ k: k, fact: factorial }));
        } else {
            response.writeHead(400, { 'Content-Type': 'text/plain' });
            response.end('Error: Factorial is not defined for negative numbers');
        }
    } else if (url.pathname === '/') {
        fs.readFile('03-03.html', (err, data) => {
            if (err) {
                response.writeHead(500, { 'Content-Type': 'text/plain' });
                response.end('Error: could not read the HTML file');
            } else {
                response.writeHead(200, { 'Content-Type': 'text/html' });
                response.end(data);
            }
        });
    } else {
        response.writeHead(404, { 'Content-Type': 'text/plain' });
        response.end('Error: not found');
    }
});

server.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}`);
});
