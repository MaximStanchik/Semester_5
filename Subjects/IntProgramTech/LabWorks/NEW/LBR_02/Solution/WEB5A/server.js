const http = require('http');

const port = 3000;

const requestListener = (req, res) => {
    res.setHeader('Access-Control-Allow-Origin', '*'); 
    res.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS'); 
    res.setHeader('Access-Control-Allow-Headers', 'X-Value-x, X-Value-y');

    if (req.method === 'OPTIONS') {
        res.writeHead(204); 
        res.end();
        return;
    }

    if (req.method === 'POST' && req.url === '/submitXY') {
        const valueX = parseInt(req.headers['x-value-x'], 10);
        const valueY = parseInt(req.headers['x-value-y'], 10);

        if (isNaN(valueX) || isNaN(valueY)) {
            res.writeHead(400, { 'Content-Type': 'text/plain' });
            res.end('Ошибка: значения должны быть целыми числами.');
            return;
        }

        const resultZ = valueX + valueY;

        res.setHeader('X-Value-z', resultZ);
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ z: resultZ }));
    } else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('404 Not Found');
    }
};

const server = http.createServer(requestListener);

server.listen(port, () => {
    console.log(`Сервер запущен на http://localhost:${port}`);
});