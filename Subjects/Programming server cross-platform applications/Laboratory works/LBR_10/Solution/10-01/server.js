const http = require('http');
const WebSocket = require('ws');
const fs = require('fs');
const path = require('path');

const httpServerPort = 3000;
const wsServerPort = 4000;

const server = http.createServer(function (request, response) {
    if (request.method === 'GET' && request.url === '/start') {
        fs.readFile(path.join(__dirname, 'main.html'), 'utf8', function (err, data) {
            if (err) {
                response.writeHead(500, {'Content-Type': 'text/plain; charset=utf-8'});
                response.end('Ошибка сервера');
                return;
            }
            response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
            response.end(data);
        });
    } 
    else {
        response.writeHead(400, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('Неправильный запрос');
    }
});

server.listen(httpServerPort, function() {
    console.log('HTTP-сервер запущен на http://localhost:' + httpServerPort);
});

const webSocketServer = new WebSocket.Server({ port: wsServerPort });

webSocketServer.on('connection', function (ws) {
    console.log('Установлено новое WebSocket-соединение');
    let messageCount = 0;

    ws.on('message', function (message) {
        const textMessage = message.toString();
        console.log('Получено сообщение от клиента: ', textMessage);
        const lastMessageNumber = parseInt(textMessage.split(':')[1], 10);
        
        const intervalId = setInterval( function() {
            messageCount++;
            const serverMessage = `10-01-server: ${lastMessageNumber}->${messageCount}`;
            ws.send(serverMessage);
            console.log('Отправлено сообщение клиенту: ', serverMessage);
        }, 5000);

        setTimeout(() => {
            clearInterval(intervalId);
            ws.close();
            console.log('WebSocket-соединение закрыто через 25 секунд');
        }, 25000);
    });

    ws.on('close', function() {
        console.log('WebSocket-соединение закрыто');
    });
});

console.log('WebSocket-сервер запущен на ws://localhost:' + wsServerPort);