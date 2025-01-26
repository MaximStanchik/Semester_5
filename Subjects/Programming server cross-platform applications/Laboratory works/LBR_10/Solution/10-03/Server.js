const WebSocket = require('ws');

// Создаем WebSocket-сервер на порту 4000
const wss = new WebSocket.Server({ port: 4000 });

const clients = new Set(); 

wss.on('connection', (ws) => {
    console.log('Новый клиент подключен');
    clients.add(ws);

    ws.on('message', (message) => {
        console.log(`Получено сообщение: ${message}`);
        clients.forEach(client => {
            if (client !== ws && client.readyState === WebSocket.OPEN) {
                client.send(message);
            }
        });
    });

    ws.on('close', () => {
        console.log('Клиент отключен');
        clients.delete(ws); 
    });

    ws.on('error', (error) => {
        console.error('Ошибка WebSocket: ', error);
    });
});

console.log('Широковещательный WebSocket-сервер запущен на ws://localhost:4000');