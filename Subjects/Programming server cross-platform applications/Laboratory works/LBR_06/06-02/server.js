const http = require('http');
const fs = require('fs');
const path = require('path');
const sendmail = require('sendmail')();

const PORT = 3000;

const server = http.createServer(function(req, res) {
    if (req.method === 'GET' && req.url === '/') {
        fs.readFile(path.join(__dirname, 'public', 'main.html'), function (err, data) {
            if (err) {
                res.writeHead(500);
                return res.end('Ошибка загрузки страницы');
            }
            res.writeHead(200, { 'Content-Type': 'text/html' });
            res.end(data);
        });
    }
    else if (req.method === 'POST' && req.url === '/send') {
        let body = '';
        req.on('data', function (chunk) {
            body =  body + chunk.toString();
        });
        req.on('end', function () {
            const { from, to, message } = JSON.parse(body);

            sendmail({
                from: from,
                to: to,
                subject: 'Новое сообщение',
                text: message,
            }, function (err, reply) {
                if (err) {
                    res.writeHead(500);
                    return res.end(JSON.stringify({ message: 'Ошибка при отправке письма' }));
                }
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ message: 'Письмо успешно отправлено!' }));
            });
        });
    }
    else {
        res.writeHead(404);
        res.end('404: Страница не найдена');
    }
});

server.listen(PORT, () => {
    console.log(`Сервер запущен на http://localhost:${PORT}`);
});