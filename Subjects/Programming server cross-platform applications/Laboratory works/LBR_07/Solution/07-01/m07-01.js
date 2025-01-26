const http = require('http');
const fileSystem = require('fs');
const path = require('path');

const serveStaticFiles = function (staticDir) {
    const mimeTypes = {
        '.html': 'text/html',
        '.css': 'text/css',
        '.js': 'text/javascript',
        '.png': 'image/png',
        '.docx': 'application/vnd.openxmlformats-officedocument.wordprocessingml.document',
        '.json': 'application/json',
        '.xml': 'application/xml',
        '.mp4': 'video/mp4'
    };

    const server = http.createServer(function (request, response) {
        if (request.method === 'GET') {
            const filePath = path.join(staticDir, request.url);
            fileSystem.stat(filePath, function (error, stats) {
                if (error || !stats.isFile()) {
                    response.writeHead(404, { 'Content-Type': 'text/plain; charset=utf8' });
                    response.end('Файл не найден!');
                    return;
                }
                const ext = path.extname(filePath);
                const contentType = mimeTypes[ext] || 'application/octet-stream';

                response.writeHead(200, { 'Content-Type': contentType });
                const readStream = fileSystem.createReadStream(filePath);
                readStream.pipe(response);
            });
        }
        else {
            response.writeHead(405, { 'Content-Type': 'text/plain; charset=utf8' });
            response.end('Поддерживается только метод GET');
        }
    });
    return server;
};

module.exports = serveStaticFiles;