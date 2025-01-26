const http = require('http');
const fs = require('fs');
const PORT = 5000;

const httpHandler = function(request, response) {
    if (request.method === 'GET') {
        const imagePath = 'D:\\User\\Desktop\\StudyAtBSTU\\Course_3\\Semester5\\Subjects\\InterProgTech\\LabWorks\\NEW\\LBR_05\\Solution\\1\\image.png';
        fs.readFile(imagePath, function(error, data) {
            if (error) {
                console.error('Ошибка при открытии файла:', error);
                response.writeHead(404, {'Content-Type': 'text/plain; charset=utf8'});
                response.end('Ошибка при открытии файла');
            } else {
                response.writeHead(200, {
                    'Content-Type': 'image/png',
                    'Content-Length': data.length
                });
                response.end(data);
            }
        });
    } else {
        response.writeHead(400, {'Content-Type': 'text/plain; charset=utf8'});
        response.end('Другие методы не поддерживаются');
    }
}

const server = http.createServer(httpHandler);
server.listen(PORT, function() {
    console.log('Сервер запущен на http://localhost:' + PORT);
});