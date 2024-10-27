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
    console.log('Данные сессии:', request.session);
    request.session.data = request.body; 
    console.log('Сохраненные данные в сессии:', request.session.data);
    
    response.json({ message: 'Полученные данные:', data: request.session.data });
});

server.listen(PORT, function() {
    console.log(`Сервер запущен на http://localhost:` + PORT);
});