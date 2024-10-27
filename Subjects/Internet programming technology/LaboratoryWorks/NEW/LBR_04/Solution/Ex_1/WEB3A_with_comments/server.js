const express = require('express');
const { Cookie } = require('express-session');
const session = require('express-session');

const server = express();
const PORT = 3000;

server.use(express.json());
server.use(session({
    secret: 'supersecret',            // (ОБЯЗАТЕЛЬНО) Секретная строка, используемая для шифрования идентификатора сессии
    name: 'sessionId',                // (НЕОБЯЗАТЕЛЬНО) имя cookie, которое будет использоваться для хранения идентификатора сессии
    cookie: {
        secure: false,
        httpOnly: true,
        maxAge: 1000 * 60 * 30
    },                                // (НЕОБЯЗАТЕЛЬНО) настройка куки сессии
    resave: false,                    // (НЕОБЯЗАТЕЛЬНО) сохранение сесси в хранилище, даже если сессия не была изменена
    saveUninitialized: true,          // (НЕОБЯЗАТЕЛЬНО) сохранение сессии
    rolling: true,                    // (НЕОБЯЗАТЕЛЬНО) обновление куки
    unset: 'destroy',                 // (НЕОБЯЗАТЕЛЬНО) указывает, как сессия должна быть сброшена
    store: null,                      // (НЕОБЯЗАТЕЛЬНО) хранилище для сессий (Redis, MongoDB и т.д.)
}));

server.post('', (request, response) => {
    request.session.data = request.body; 
    console.log('Сохраненные данные в сессии:', request.session.data);
    
    response.json({ message: 'Полученные данные:', data: request.session.data });
});

server.listen(PORT, function() {
    console.log(`Сервер запущен на http://localhost:` + PORT);
});