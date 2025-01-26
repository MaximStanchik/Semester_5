const websocket=require('ws');
const fs=require('fs');

const ws=new websocket('ws://localhost:4000');

ws.on('open', function() {
    const duplex=websocket.createWebSocketStream(ws);
    let rfile=fs.createReadStream('./myfile.txt');
    rfile.pipe(duplex);

    rfile.on('end', function() {
        console.log('Файл отправлен успешно.');
    });
})

ws.on('error', function(error) {
    console.error('Ошибка WebSocket:', error);
});