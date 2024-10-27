const http = require('http');
const fs = require('fs');
const PORT = 5000;

const server = http.createServer(function(request, response) {
    response.setHeader('Access-Control-Allow-Origin', '*');
    response.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS');
    response.setHeader('Access-Control-Allow-Headers', 'X-Value-x, X-Value-y, X-Rand-N');
    
    const url = new URL(request.url, `http://${request.headers.host}`);

    if (url.pathname === '/') {
        fs.readFile('main.html', (err, data) => {
            if (err) {
                response.writeHead(500, { 'Content-Type': 'text/plain' });
                response.end('Error: could not read the HTML file');
            } else {
                response.writeHead(200, { 'Content-Type': 'text/html' });
                response.end(data);
            }
        });
    }
    else if (url.pathname === '/fact' && url.searchParams.has('k')) {
        const k = parseInt(url.searchParams.get('k'));
        calculateFactorial(k, function(err, factorial) {
            if (err) {
                response.writeHead(400, {'Content-Type': 'text/plain'});
                response.end('Error: Factorial is not defined for negative numbers');
            } else {
                response.writeHead(200, {'Content-Type': 'application/json'});
                response.end(JSON.stringify({ k: k, fact: factorial }));
            }
        });
    } else {
        response.writeHead(404, {'Content-Type': 'text/plain'});
        response.end('Error: not found');
    }
});

server.listen(PORT, function() {
    console.log('Server is running at http://localhost:' + PORT);
});

function calculateFactorial(k, callback) {
    if (k < 0) {
        return callback(new Error('Факториал не определен для отрицательных чисел'), null);
    }

    let result = 1;
    function compute(num) {
        if (num > 1) {
            result *= num;
            setImmediate(() => {
                compute(num - 1);
            });
        } else {
            callback(null, result);
        }
    }
    compute(k);
}
