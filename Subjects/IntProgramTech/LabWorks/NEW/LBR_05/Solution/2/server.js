const http = require('http');
const fs = require('fs');
const path = require('path');
const PORT = 5000;

const httpHandler = function(request, response) {
    const cacheParam = new URL(request.url, `http://localhost:${PORT}`).searchParams.get('cache_param');
    const imagePath = 'D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\InterProgTech\\LabWorks\\NEW\\LBR_05\\Solution\\2\\image.png';
    
    fs.stat(imagePath, (error, stats) => {
        if (error) {
            response.writeHead(404, {'Content-Type': 'text/plain; charset=utf8'});
            response.end('Ошибка при открытии файла');
            return;
        }

        const lastModified = stats.mtime.toUTCString();
        const etag = `"${stats.size}-${stats.mtime.getTime()}"`;

        if (cacheParam === 'max-age') {
            response.setHeader('Cache-Control', 'max-age=3600'); 
            response.setHeader('Last-Modified', lastModified);
            response.setHeader('ETag', etag);
        } 
        else if (cacheParam === 'no-store') {
            response.setHeader('Cache-Control', 'no-store');
            response.setHeader('Last-Modified', lastModified);
            response.setHeader('ETag', etag);
        } 
        else if (cacheParam === 'expire') {
            const expireDate = new Date();
            expireDate.setMinutes(expireDate.getMinutes() + 60); 
            response.setHeader('Expires', expireDate.toUTCString());
            response.setHeader('Last-Modified', lastModified);
            response.setHeader('ETag', etag);
        } 
        else {
            response.setHeader('Cache-Control', 'no-cache');
        }

        fs.readFile(imagePath, (error, data) => {
            if (error) {
                response.writeHead(404, {'Content-Type': 'text/plain; charset=utf8'});
                response.end('Ошибка при открытии файла');
            } 
            else {
                response.writeHead(200, {
                    'Content-Type': 'image/png',
                    'Content-Length': data.length
                });
                response.end(data);
            }
        });
    });
};

const server = http.createServer(httpHandler);
server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});