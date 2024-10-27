const http = require('http');
const url = require('url');
const PORT = 3000;

const sessions = {};
const SESSION_TIMEOUT = 30 * 60 * 1000;

function generateSessionId() {
    return Math.random().toString(36).substring(2, 18);
};

const server = http.createServer(function (request, response) {

    for (const id in sessions) {
        if (Date.now() - sessions[id].lastAccess > SESSION_TIMEOUT) {
            delete sessions[id];
        }
    }

    const cookies = parseCookies(request.headers.cookie);
    let sessionId = cookies.sessionId;

    if (request.method === 'POST') {
        let body = '';

        request.on('data', function (chunk) {
            body = body + chunk.toString();
        });

        request.on('end', function () {
            if (!sessionId) {
                sessionId = generateSessionId();
                sessions[sessionId] = { lastAccess: Date.now(), data: {} };
                response.setHeader('Set-Cookie', `sessionId=${sessionId}; HttpOnly`);
            }

            sessions[sessionId].data = { ...sessions[sessionId].data, ...JSON.parse(body) };

            response.writeHead(200, { 'Content-Type': 'application/json' });
            response.end(JSON.stringify({ message: 'Данные получены', sessionId, data: sessions[sessionId].data }));
        });

    }
    else {
        response.writeHead(405, { 'Content-Type': 'text/plain; charset=utf-8' });
        response.end('Метод недоступен');
    }
});

function parseCookies(cookieHeader) {
    const cookies = {};
    if (cookieHeader) {
        cookieHeader.split(';').forEach(function (cookie) {
            const [name, value] = cookie.trim().split('=');
            cookies[name] = decodeURIComponent(value);
        });
    }
    return cookies;
}

server.listen(PORT, function () {
    console.log("Сервер запущен на http://localhost:" + PORT);
});