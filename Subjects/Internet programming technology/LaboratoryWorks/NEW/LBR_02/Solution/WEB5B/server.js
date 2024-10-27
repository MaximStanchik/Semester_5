const http = require('http');

const PORT = 3000;

const server = http.createServer((request, response) => {
    response.setHeader('Access-Control-Allow-Origin', '*');
    response.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS'); 
    response.setHeader('Access-Control-Allow-Headers', 'X-Rand-N'); 

    if (request.method === 'OPTIONS') {
        response.writeHead(204); 
        response.end();
        return;
    }
    if (request.method === 'POST' && request.url === '/submit') {
        const n = parseInt(request.headers['x-rand-n'], 10);

        if (!isNaN(n)) {
            const count = Math.floor(Math.random() * 6) + 5; 
            const randomNumbers = Array.from({ length: count }, () => {
                return Math.floor(Math.random() * (2 * n + 1)) - n;
            });

            response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
            response.end(JSON.stringify(randomNumbers));
        } else {
            response.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
            response.end('Ошибка: заголовок X-Rand-N должен содержать целочисленное значение');
        }
    } else {
        response.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
        response.end('Не найдено');
    }
});

server.listen(PORT, () => {
    console.log(`Сервер запущен на http://localhost:${PORT}`);
});