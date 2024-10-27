http = require('http');
const PORT = 5000;

const server = http.createServer(function(request, response) {
    response.setHeader('Access-Control-Allow-Origin', '*');
    response.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS');
    response.setHeader('Access-Control-Allow-Headers', 'X-Value-x, X-Value-y, X-Rand-N');
    
    const url = new URL(request.url, `http://${request.headers.host}`);
    if (url.pathname === '/fact' && url.searchParams.has('k')) {
        const k = parseInt(url.searchParams.get('k'));
        const factorial = calculateFactorial (k);
        if (factorial !== null) {
            response.writeHead(200, {'Content-Type': 'application/json'});
            response.end(JSON.stringify({k: k, fact: factorial}));
        }
        else {
            response.writeHead(400, {'Content-Type': 'text/plain'});
            response.end('Error: Factorial is not defined for negative numbers');
        }

    }
    else {
        response.writeHead(404, {'Content-Type': 'text/plain'});
        response.end('Error: not found');

    }
});

server.listen(PORT, function() {
    console.log('Server is running at http://localhost:' + PORT);
    console.log('Follow the link http://localhost:5000/fact?k=3');
});


function calculateFactorial (k) {
    if (k === 0) {
        return 1;
    }
    else if (k < 0) {
        return null;
    }
    else {
        return k * calculateFactorial(k-1);
    }
};