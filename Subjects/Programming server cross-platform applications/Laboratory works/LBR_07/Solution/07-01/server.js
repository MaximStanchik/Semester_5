const http = require('http');
const fileSystem = require('fs');
const path = require('path');
const serveStaticFiles = require('./m07-01');

const PORT = 5000;
const STATIC_DIR = path.join(__dirname, 'static');

const server = serveStaticFiles(STATIC_DIR);

server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
    console.log('Для скачинвания файла (например index.html) запускать на http://localhost:5000//index.html');
});