const http = require('http');
const { Builder, parseStringPromise } = require('xml2js');

const builder = new Builder();
const xmlData = builder.buildObject({
  user: {
    id: 2,
    name: 'Мария',
    email: 'maria@example.com'
  }
});

const options = {
  hostname: 'localhost',
  port: 3000,
  path: '/user-xml',
  method: 'POST',
  headers: {
    'Content-Type': 'application/xml',
    'Content-Length': Buffer.byteLength(xmlData)
  }
};

const req = http.request(options, (res) => {
  let data = '';
  
  res.on('data', (chunk) => {
    data += chunk;
  });

  res.on('end', async () => {
    const result = await parseStringPromise(data);
    console.log('Данные в теле ответа:', result); // привести result к строке чтобы вывести нормально к xml
  });
});

req.on('error', (error) => {
  console.error(`Ошибка: ${error.message}`);
});

req.write(xmlData);
req.end();
