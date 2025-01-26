const websocket= require('ws');
const fs=require('fs');

const PORT = 4000;

const wsserver=new websocket.Server({port: PORT, host: 'localhost'});

wsserver.on('connection', function(ws) {
    const duplex=websocket.createWebSocketStream(ws);
    let wfile=fs.createWriteStream(`./upload/newfile.txt`);
    duplex.pipe(wfile);
});

wsserver.on('listening', () => {
    console.log(`Сервер запущен на ws://localhost:${PORT}`);
});