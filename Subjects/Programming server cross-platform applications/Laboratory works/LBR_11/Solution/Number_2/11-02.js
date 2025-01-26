const websocket=require('ws');
const fs=require('fs');
const PORT = 4000;

const wsserver=new websocket.Server({port: PORT, host: 'localhost'});

let parm2=process.argv[2];
wsserver.on('connection', function (ws) {
    const duplex=websocket.createWebSocketStream(ws);
    let rfile=fs.createReadStream(`./download/${parm2}`);
    rfile.pipe(duplex);
});

wsserver.on('listening', function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});

wsserver.on('error', function(error) {
    console.error('Ошибка WebSocket: ' + error);
});