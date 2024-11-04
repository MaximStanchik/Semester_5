const express = require('express');
const { Cookie } = require('express-session');
const session = require('express-session');

const server = express();
const PORT = 3000;

server.use(express.json());
server.use(session({
    secret: 'supersecret',            
    name: 'sessionId',                
    cookie: {
        secure: false,
        httpOnly: true,
        maxAge: 1000 * 60 * 30
    },                                
    resave: false,                    
    saveUninitialized: true,          
    rolling: true,                    
    unset: 'destroy',                 
    store: null,                      
}));

server.post('', (request, response) => {
    const { x, y } = request.body;
    console.log('Данные сессии:', request.session);
    console.log(`Введенные значения: x = ${x}, y = ${y}`);
    if (Number.isInteger(x) && x > 0 && Number.isInteger(y) && y > 0) {
        if (!request.session.sx && !request.session.sy) {
            request.session.sx = x;
            request.session.sy = y;
            request.session.requestCount = 1; 
            return response.json({ sx: request.session.sx, sy: request.session.sy });
        } else {
            request.session.requestCount += 1;

            if (request.session.requestCount % 5 === 0) {
                const responseData = {
                    sx: request.session.sx,
                    sy: request.session.sy
                };
                request.session.sx = 0;
                request.session.sy = 0;
                response.json(responseData);
            } else {
                request.session.sx += x;
                request.session.sy += y;
                response.json({ sx: request.session.sx, sy: request.session.sy });
            }
        }
    } 
    else {
        response.status(400).json({ error: 'Ошибка: x и y должны быть положительными целыми числами.' });
    }
});

server.listen(PORT, function() {
    console.log(`Сервер запущен на http://localhost:` + PORT);
});