const http = require('http');
const PORT = 3000;

const server = http.createServer((request, response) => {
    response.setHeader('Access-Control-Allow-Origin', '*');
    response.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS');
    response.setHeader('Access-Control-Allow-Headers', 'X-Value-x, X-Value-y, X-Rand-N');

    if (request.method === 'OPTIONS') {
        response.writeHead(204);
        response.end();
        return;
    }

    if (request.method === 'POST' && request.url === '/submitXY') {
        const x = parseFloat(request.headers['x-value-x']);
        const y = parseFloat(request.headers['x-value-y']);
        if (!isNaN(x) && !isNaN(y)) {
            setTimeout(() => {
                const z = x + y;
                response.writeHead(200, { 'Content-Type': 'application/json' });
                response.end(JSON.stringify({ z })); 
            }, 10000); 
            return;
        }
    }

    if (request.method === 'POST' && request.url === '/submitN') {
        const n = parseInt(request.headers['x-rand-n'], 10);
        if (!isNaN(n)) {
            setTimeout(() => {
                const count = Math.floor(Math.random() * 6) + 5;
                const randomNumbers = Array.from({ length: count }, () => {
                    return Math.floor(Math.random() * (2 * n + 1)) - n;
                });
                response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
                response.end(JSON.stringify(randomNumbers));
            }, 1000); 
            return;
        }
    }

    response.writeHead(404, { 'Content-Type': 'text/plain' });
    response.end('Не найдено');
});

server.listen(PORT, () => {
    console.log(`Сервер запущен на http://localhost:${PORT}`);
});