
const { send } = require('m0603lbr06'); 

async function testSendMail() {
    try {
        const message = 'Привет! Это тестовое сообщение.';
        const result = await send(message);
        console.log('Сообщение успешно отправлено:', result);
    } 
    catch (error) {
        console.error('Ошибка при отправке сообщения:', error);
    }
}

testSendMail(); 