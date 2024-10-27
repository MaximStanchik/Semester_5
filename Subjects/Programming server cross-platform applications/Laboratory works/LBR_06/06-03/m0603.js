const sendmail = require('sendmail')();

const FIXED_EMAIL_ADDRESS = 'xedow13837@advitize.com';

function send(message) { 
    return new Promise((resolve, reject) => {
        sendmail({
            from: 'xtnya@mailto.plus',
            to: FIXED_EMAIL_ADDRESS,
            subject: 'Новое сообщение',
            text: message,
        }, function(err, reply) {
            if (err) {
                reject(err);
            } 
            else {
                resolve(reply);
            }
        });
    });
};

module.exports = { send };