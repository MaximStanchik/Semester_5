const WebSocket = require('ws');

let socket;
let messageCount = 0;

function startWebSocket() {
    socket = new WebSocket('ws://localhost:4000');

    socket.on('open', function () {
        console.log('WebSocket connection established');
        setInterval(sendMessage, 3000); 
    });

    socket.on('message', function (data) {
        console.log('Message from server: ', data.toString());
    });

    socket.on('error', function (error) {
        console.error('WebSocket error: ', error);
    });

    socket.on('close', function () {
        console.log('WebSocket connection closed');
    });
}

function sendMessage() {
    messageCount += 1;
    const message = `10-01-client: ${messageCount}`;
    socket.send(message);
    console.log('Отправлено сообщение: "' + message.toString() + '"');
}

startWebSocket();