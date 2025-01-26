const http = require('http');
const { parseStringPromise, Builder } = require('xml2js');

const server = http.createServer((req, res) => {
  if (req.method === 'POST' && req.url === '/user-xml') {
    let data = '';

    req.on('data', chunk => {
      data += chunk;
    });

    req.on('end', async () => {
      const user = await parseStringPromise(data);
      console.log('Полученные данные пользователя:', user);

      const builder = new Builder();
      const responseXml = builder.buildObject({
        message: 'Данные пользователя получены',
        receivedUser: user.user
      });

      res.writeHead(200, { 'Content-Type': 'application/xml' });
      res.end(responseXml);
    });
  }
});

server.listen(3000, () => {
  console.log('Сервер запущен на http://localhost:3000');
});
