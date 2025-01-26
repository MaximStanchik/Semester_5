const websocket=require('ws');
const fs=require('fs');

const ws=new websocket('ws://localhost:4000');

ws.on('open', ()=>{
    const duplex=websocket.createWebSocketStream(ws);
    let wfile=fs.createWriteStream(`./download/accepted.txt`);
    duplex.pipe(wfile);

    wfile.on('end', function() {
        console.log('Файл принят успешно');
    });
});

ws.on('error', function(error) {
    console.error('Ошибка WebSocket:', error);
});