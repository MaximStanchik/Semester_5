const http = require('http');

const data = JSON.stringify({
  user: { id: 1, name: "John Doe" },
  message: "Hello, server!",
});

const options = {
  hostname: 'localhost',
  port: 3000,
  path: '/json',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    'Content-Length': data.length,
  },
};

const req = http.request(options, (res) => {
  console.log(`Статус ответа: ${res.statusCode}`);

  res.setEncoding('utf8');
  res.on('data', (chunk) => {
    console.log(`Данные: ${chunk}`);
  });
});

req.on('error', (e) => {
  console.error(`Проблема с запросом: ${e.message}`);
});

req.write(data);
req.end();
