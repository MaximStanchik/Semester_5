const http = require('http');

const server = http.createServer((req, res) => {
  if (req.method === 'POST' && req.url === '/json') {
    let body = '';

    req.on('data', (chunk) => {
      body += chunk;
    });

    req.on('end', () => {
      const parsedData = JSON.parse(body);
      const response = JSON.stringify({
        receivedUser: parsedData.user,
        message: `Привет, ${parsedData.user.name}`,
      });

      res.writeHead(200, { 'Content-Type': 'application/json' });
      res.end(response);
    });
  } 
  else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('Страница не найдена');
  }
});

server.listen(3000, () => {
  console.log('Сервер запущен на порту 3000');
});
