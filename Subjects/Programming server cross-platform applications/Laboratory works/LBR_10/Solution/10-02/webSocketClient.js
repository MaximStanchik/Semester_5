const WebSocket = require('ws');

let socket;
let messageCount = 0;
let intervalId;

function startWebSocket() {
    socket = new WebSocket('ws://localhost:4000');

    socket.on('open', function () {
        console.log('WebSocket connection established');
        intervalId = setInterval(sendMessage, 3000);
    });

    socket.on('message', function (data) {
        console.log('Сообщение от сервера: ', data.toString());
    });

    socket.on('error', function (error) {
        console.error('Ошибка сокета: ', error);
    });

    socket.on('close', function () {
        console.log('Подключение сокета закрыто');
        clearInterval(intervalId);
    });
}

function sendMessage() {
    messageCount += 1;
    const message = `10-01-client: ${messageCount}`;
    socket.send(message);
    console.log('Отправлено сообщение: "' + message.toString() + '"');
}

startWebSocket();