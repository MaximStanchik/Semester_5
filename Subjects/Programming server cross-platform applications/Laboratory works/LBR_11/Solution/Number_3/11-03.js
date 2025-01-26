const websocket=require('ws');
const fs=require('fs');

const PORT = 4000;

const wsserver=new websocket.Server({port: PORT, host: 'localhost'});

let k=0;
wsserver.on('connection', (ws)=>{
    ws.on('pong', (data)=>{
        console.log('on pong: ',data.toString());
    });
    ws.on('message', (data)=>{
        console.log(`on message: ${data.toString()}`);
        ws.send(data);
    });
    setInterval(()=>{
        wsserver.clients.forEach((client)=>{
            if (client.readyState == ws.OPEN){
                client.send(`09-03-server: ${++k}`);
            }
        })
    }, 15000);
    setInterval(() => {
        console.log(`count of connections: ${wsserver.clients.size}`);
        ws.ping(`server ping ${wsserver.clients.size} clients`);
    }, 5000);
});

wsserver.on('listening', function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});

wsserver.on('error', function(error) {
    console.error('Ошибка WebSocket: ' + error);
});