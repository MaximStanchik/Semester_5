const websocket=require('ws');

const PORT = 4000;

const wsserver=new websocket.Server({port: PORT, host: 'localhost'});

wsserver.on('connection', (ws)=>{
    let k=0;
    ws.on('message', (data)=>{
        console.log('on message: ', JSON.parse(data));
        ws.send(JSON.stringify({server: ++k, client: JSON.parse(data).client, timestamp: new Date().toString()}))
    });
})

wsserver.on('listening', function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});

wsserver.on('error', function(error) {
    console.error('Ошибка WebSocket: ' + error);
});