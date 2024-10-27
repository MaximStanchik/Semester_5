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
    if (Number.isInteger(x) && x > 0 && Number.isInteger(y) && y > 0) {
        request.session.data = { x, y }; 
        console.log('Сохраненные данные в сессии:', request.session.data);
        
        response.json({ message: 'Полученные данные:', data: request.session.data });
    } 
    else {
        response.status(400).json({ error: 'Ошибка: x и y должны быть положительными целыми числами.' });
    }
});

server.listen(PORT, function() {
    console.log(`Сервер запущен на http://localhost:` + PORT);
});