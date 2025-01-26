const express = require("express");
const { parseString } = require("xml2js");
const xmlBuilder = require("xmlbuilder");
const fs = require('fs');
const path = require('path');
const multer = require('multer');
const server = express();
const PORT = 5000;

const serverListen = server.listen(PORT, () => {
  console.log(`Сервер запущен на http://localhost:${PORT}`);
});

server.get("/connection", (req, res) => {
  res.send(
    `Текущее состояние KeepAliveTimeout: ${serverListen.keepAliveTimeout}`
  );
});

server.get("/connection/set=:set", (req, res) => {
  const newTimeout = parseInt(req.params.set, 10);

  if (!isNaN(newTimeout)) {
    serverListen.keepAliveTimeout = newTimeout;
    res.send(
      `Текущее состояние KeepAliveTimeout изменено на: ${serverListen.keepAliveTimeout}`
    );
    return;
  }

  res.status(400).send("Некорректное значение параметра");
});

server.get("/headers", (req, res) => {
  const requestHeaders = Object.entries(req.headers);
  res.setHeader("Content-Type", "text/html; charset=utf-8");
  res.setHeader("test", "test");
  const responseHeaders = Object.entries(res.getHeaders());

  let html = "<h1>Заголовки запроса и ответа</h1>";

  html += "<h2>Заголовки запроса:</h2><ol>";

  requestHeaders.forEach(([key, value]) => {
    html += `<li>${key}: ${value}</li>`;
  });
  html += "</ol>";

  html += "<h2>Заголовки ответа:</h2><ol>";

  responseHeaders.forEach(([key, value]) => {
    html += `<li>${key}: ${value}</li>`;
  });
  html += "</ol>";

  res.send(html);
});

server.get("/parametr", (req, res) => {
  const x = parseFloat(req.query.x);
  const y = parseFloat(req.query.y);

  if (!isNaN(x) && !isNaN(y)) {
    const sum = x + y;
    const diff = x - y;
    const prod = x * y;
    const quot = y !== 0 ? (x / y).toFixed(2) : "Деление на ноль невозможно";

    res.send(`
      <h1>Результаты для параметров x=${x} и y=${y}</h1>
      <ul>
          <li>Сумма: ${sum}</li>
          <li>Разность: ${diff}</li>
          <li>Произведение: ${prod}</li>
          <li>Частное: ${quot}</li>
      </ul>
  `);
    return;
  }

  res
    .status(400)
    .send("<h1>Ошибка: параметры должны быть числовыми значениями.</h1>");
});

server.get("/parametr/:x/:y", (req, res) => {
  const x = parseFloat(req.query.x);
  const y = parseFloat(req.query.y);

  if (!isNaN(x) && !isNaN(y)) {
    const sum = x + y;
    const diff = x - y;
    const prod = x * y;
    const quot = y !== 0 ? (x / y).toFixed(2) : "Деление на ноль невозможно";

    res.send(`
      <h1>Результаты для параметров x=${x} и y=${y}</h1>
      <ul>
          <li>Сумма: ${sum}</li>
          <li>Разность: ${diff}</li>
          <li>Произведение: ${prod}</li>
          <li>Частное: ${quot}</li>
      </ul>
  `);
    return;
  }

  res
    .status(400)
    .send("<h1>Ошибка: параметры должны быть числовыми значениями.</h1>");
});

server.get("/close", (req, res) => {
  res.send("<h1>Сервер будет закрыт через 10 секунд...</h1>");

  setTimeout(() => {
    console.log("Сервер закрывается...");
    server.close(() => {
      console.log("Сервер успешно остановлен.");
    });
  }, 10000);
});

server.get("/socket", (req, res) => {
  const clientIp = req.socket.remoteAddress;
  const clientPort = req.socket.remotePort;

  const serverIp = req.socket.localAddress;
  const serverPort = req.socket.localPort;

  res.send(`
      <h1>Информация о сокете</h1>
      <ul>
          <li>IP-адрес клиента: ${clientIp}</li>
          <li>Порт клиента: ${clientPort}</li>
          <li>IP-адрес сервера: ${serverIp}</li>
          <li>Порт сервера: ${serverPort}</li>
      </ul>
  `);
});

server.get("/req-data", (req, res) => {
  let html = "<ul>";
  let data = "";

  req.on("data", (chunk) => {
    data += chunk;
    //console.log(`Получено ${chunk.length} байт данных...`);
    html += `<li>Получено ${chunk.length} байт данных...</li>`;
  });

  req.on("end", () => {
    //console.log('Получение данных завершено.');
    html += "</ul>";
    html += "<br/>Получение данных завершено.";
    html += `<br/><h2>Данные успешно получены. Размер данных: ${data.length} байт.</h2>`;
    res.send(html);
  });

  req.on("error", (err) => {
    //console.error('Ошибка при получении данных:', err);
    res.status(500).send("<h1>Ошибка при получении данных</h1>");
  });
});

//resp-status?code=404&mess=Page+not+found
server.get("/resp-status", (req, res) => {
  const code = parseInt(req.query.code);
  const message = req.query.mess || "Нет сообщения";

  if (isNaN(code) || code < 100 || code > 599) {
    res.status(400).send("<h1>Ошибка: некорректный код статуса</h1>");
    return;
  }

  res.status(code).send(`
      <h1>Ответ с кодом статуса ${code}</h1>
      <p>Сообщение: ${message}</p>
  `);
});

const bodyParser = require("body-parser");
server.use(bodyParser.urlencoded({ extended: true }));

server.post("/formparameter", (req, res) => {
  const text = req.body.text || "";
  const number = req.body.number || "";
  const date = req.body.date || "";
  const checkbox = req.body.checkbox ? "Согласен" : "Не согласен";
  const radio = req.body.radio || "";
  const textarea = req.body.textarea || "";
  const submit = req.body.submit || "";

  res.send(`
      <h1>Значения полученные от формы:</h1>
      <p><strong>Текст:</strong> ${text}</p>
      <p><strong>Число:</strong> ${number}</p>
      <p><strong>Дата:</strong> ${date}</p>
      <p><strong>Согласие:</strong> ${checkbox}</p>
      <p><strong>Выбранная опция:</strong> ${radio}</p>
      <p><strong>Текстовая область:</strong> ${textarea}</p>
      <p><strong>Кнопка отправки:</strong> ${submit}</p>
  `);
});

server.use(bodyParser.json());
server.post("/json", (req, res) => {
  const requestData = req.body;

  const x_plus_y = requestData.x + requestData.y;
  const concat_s_o = `${requestData.s}: ${requestData.o.surname}, ${requestData.o.name}`;
  const length_m = requestData.m.length;

  const responseData = {
    __comment: "Ответ.Лабораторная работа 8/10",
    x_plus_y: x_plus_y,
    Concatination_s_o: concat_s_o,
    Length_m: length_m,
  };

  res.json(responseData);
});

// {
//   "__comment": "Запрос.Лабораторная работа 8/10",
//   "x": 1,
//   "y": 2,
//   "s": "Сообщение",
//   "m": ["a", "b", "c", "d"],
//   "o": {
//     "surname": "Иванов",
//     "name": "Иван"
//   }
// }

server.use(express.text({ type: "application/xml" }));

server.post("/xml", (req, res) => {
  let xmlString = req.body;

  parseString(xmlString, (err, result) => {
    if (err) {
      res.status(400).send(`<result>Ошибка парсинга: ${err.message}</result>`);
      return;
    }

    let sum = 0;
    let mess = "";

    if (result.request && result.request.x) {
      const xElements = Array.isArray(result.request.x)
        ? result.request.x
        : [result.request.x];
      xElements.forEach((el) => {
        sum += Number.parseInt(el.$.value, 10) || 0;
      });
    }

    if (result.request && result.request.m) {
      const mElements = Array.isArray(result.request.m)
        ? result.request.m
        : [result.request.m];
      mElements.forEach((el) => {
        mess += el.$.value || "";
      });
    }

    let xmlDoc = xmlBuilder
      .create("response")
      .att("id", +result.request.$.id + 10)
      .att("request", result.request.$.id);

    xmlDoc.ele("sum", { element: "x", result: `${sum}` });
    xmlDoc.ele("concat", { element: "m", result: `${mess}` });

    const rc = xmlDoc.end({ pretty: true });

    res.status(200).type("xml").send(rc);
  });
});

server.get('/files', (req, res) => {
  const staticDirPath = path.join(__dirname, 'static');

  fs.readdir(staticDirPath, (err, files) => {
    if (err) {
      res.status(500).send('Ошибка при чтении директории');
      return;
    }

    const fileCount = files.filter(file => fs.statSync(path.join(staticDirPath, file)).isFile()).length;

    res.set('X-static-files-count', fileCount);
    res.send(`<h1>Количество файлов в директории static: ${fileCount}</h1>`);
  });
});

server.get('/files/:filename', async (req, res) => {
  const fileName = req.params.filename;
  const filePath = path.join(__dirname, 'static', fileName);

  try {
    await fs.promises.access(filePath, fs.constants.F_OK);

    res.sendFile(filePath, (err) => {
      if (err) {
        res.status(500).send('Ошибка при отправке файла');
      }
    });
  } catch (err) {
    res.status(404).send('Файл не найден');
  }
});

const staticDir = path.join(__dirname, 'static');
if (!fs.existsSync(staticDir)) {
    fs.mkdirSync(staticDir);
}

const storage = multer.diskStorage({
  destination: function (req, file, cb) {
      cb(null, staticDir);
  },
  filename: function (req, file, cb) {
      cb(null, file.originalname);
  }
});

const upload = multer({ storage: storage });

server.get('/upload', (req, res) => {
    res.send(`
        <form action="/upload" method="POST" enctype="multipart/form-data">
            <input type="file" name="file" required />
            <button type="submit">Загрузить файл</button>
        </form>
    `);
});

server.post('/upload', upload.single('file'), (req, res) => {
    if (!req.file) {
        return res.status(400).send('Файл не был загружен');
    }

    res.send(`Файл ${req.file.originalname} был успешно загружен!`);
});