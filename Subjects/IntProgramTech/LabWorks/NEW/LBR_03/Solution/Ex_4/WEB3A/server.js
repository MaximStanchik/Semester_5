const http = require('http');
const url = require('url');
const PORT = 3000;

let accumulatedAmountX = 0;
let accumulatedAmountY = 0;
let responseData = 0;

const server = http.createServer(function(request, response) {
    if (request.method === 'POST') {
        let body = '';

        request.on('data', function(chunk) {
            body = body + chunk.toString();
        });

        request.on('end', function() {
            console.log('Полученные данные из POST-запроса:', body);
            try {
                const data = JSON.parse(body);

                if (data.x !== undefined && data.y !== undefined) {
                    if (Number.isInteger(data.x) && Number.isInteger(data.y)) {

                        accumulatedAmountX = accumulatedAmountX + data.x;
                        accumulatedAmountY = accumulatedAmountY + data.y;
                        responseData = { sx: accumulatedAmountX, sy: accumulatedAmountY };

                        response.setHeader('Set-Cookie', [
                            `cookie_sx=${accumulatedAmountX}; HttpOnly; Path=/;`,
                            `cookie_sy=${accumulatedAmountY}; HttpOnly; Path=/;`
                        ]);

                        response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8'});
                        response.end(JSON.stringify(responseData));
                    }
                    else {
                        response.writeHead(400, {'Content-Type': 'text/plain; charset=utf-8'});
                        response.end('Неверный запрос: x и y должны быть целочисленными значениями');
                    }

                }
                else {
                    response.writeHead(400, {'Content-Type': 'text/plain; charset=utf-8'});
                    response.end('Неверный запрос: отсутствует x или y или и то и другое');
                }

            }
            catch (error) {
                response.writeHead(400, {'Content-Type': 'text/plain; charset=utf-8'});
                response.end('Неверный запрос: неправильный JSON');
            }
        });

    }
    else {
        response.writeHead(405, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end('Метод недоступен');
    }
});

server.listen(PORT, function() {
    console.log("Сервер запущен на http://localhost:" + PORT);
});