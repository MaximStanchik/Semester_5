 // Задание 09: /formparameter
     else if (pathname === '/formparameter') { // проевряем uri
        if (req.method === 'GET') { // проверяем метод
            res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' }); // устанавливаме заголовок ответа
            res.end(` // передаем ответ от сервера клиенту
                <html>
                    <body>
                        <form action="/formparameter" method="post"> // отправка данных на localhost:3000/formparameter с помощью метода post
                            <input type="text" name="textInput" placeholder="Text Input" required><br>
                            <input type="number" name="numberInput" placeholder="Number Input" required><br>
                            <input type="date" name="dateInput" required><br>
                            <input type="checkbox" name="checkboxInput" value="checked"> Checkbox<br>
                            <input type="radio" name="radioInput" value="option1" checked> Option 1<br>
                            <input type="radio" name="radioInput" value="option2"> Option 2<br>
                            <textarea name="textareaInput" placeholder="Textarea Input"></textarea><br>
                            <input type="submit" name="submit" value="Submit">
                            <input type="submit" name="submit" value="Submit1">
                        </form>
                    </body>
                </html>
            `);
        } 
        else if (req.method === 'POST') {
            let body = '';
            req.on('data', chunk => {
                body += chunk.toString();
            });

            req.on('end', () => {
                const params = querystring.parse(body);
                res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
                res.end(`Полученные параметры:\n${JSON.stringify(params, null, 2)}`);
                console.log('Полученные параметры: ', params);
            });
        }
    }

    // Задание 10: /json
    else if (pathname === '/json') {
        if (req.method === 'POST') {
            let body = '';
            req.on('data', chunk => {
                body += chunk.toString();
            });

            req.on('end', () => {
                const data = JSON.parse(body);
                const response = {
                    'x+y': data.x + data.y,
                    'Concatination_s_o': data.s + data.o.name + data.o.pass,
                    'Length_m': data.m.length
                };
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify(response));
            });
        }
    }

    // Задание 11: /xml
    else if (pathname === '/xml') {
        if (req.method === 'POST') {
            let body = '';
            req.on('data', chunk => {
                body += chunk.toString();
            });
    
            req.on('end', () => {
                const parser = new (require('xml2js')).Parser();
                parser.parseString(body, (err, result) => {
                    if (err) {
                        res.writeHead(400, { 'Content-Type': 'text/plain' });
                        res.end('Ошибка при разборе XML');
                        return;
                    }
    
                    const requestId = result.request.$.id;
                    const xValues = result.request.x.map(x => parseFloat(x.$.value));
                    const mValues = result.request.m.map(m => m.$.value);
                    const sumX = xValues.reduce((acc, curr) => acc + curr, 0);
                    const concatM = mValues.join('');
    
                    const responseXml = `
                        <response id="${requestId + 5}" request="${requestId}">
                            <sum element="x" result="${sumX}" />
                            <concat element="m" result="${concatM}" />
                        </response>
                    `;
                    res.writeHead(200, { 'Content-Type': 'application/xml' });
                    res.end(responseXml);
                });
            });
        } 
        else {
            res.writeHead(404, { 'Content-Type': 'text/plain' });
            res.end('Метод не поддерживается');
        }
    }
    // Задание 12: /files
    else if (pathname === '/files') {
        fs.readdir('./static', (err, files) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain; charset=utf-8' });
                res.end('Ошибка при чтении директории');
            }
            else {
                res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8', 'X-static-files-count': files.length });
                res.end(`Количество файлов: ${files.length}`);
            }
        });
    }

    // Задание 13: /files/filename
    else if (pathname.startsWith('/files/')) { // Проверяем, начинается ли путь с '/files/'
        const filename = pathname.replace('/files/', ''); // Извлекаем имя файла из пути, убирая '/files/'
        const filepath = path.join(__dirname, 'static', filename); // Формируем полный путь к файлу, соединяя директорию 'static' и имя файла

        // Проверяем, существует ли файл по указанному пути
        fs.access(filepath, fs.constants.F_OK, (err) => {
            if (err) { // Если файл не существует, err будет содержать информацию об ошибке
                res.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' }); // Устанавливаем статус 404 (Не найдено) и заголовок типа контента
                res.end('Файл не найден');
                return;
            }
            res.writeHead(200, { 'Content-Type': 'application/octet-stream' }); 
            const readStream = fs.createReadStream(filepath); // Создаем поток для чтения файла
            readStream.pipe(res); // Передаем данные из потока файла в ответ клиента
        });
    }

    // Задание 14: /upload (загрузка файла)
    else if (pathname === '/upload') {
        if (req.method === 'GET') {
            res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
            res.end(`
                <html>
                    <body>
                        <form action="/upload" method="post" enctype="multipart/form-data">
                            <input type="file" name="file" />
                            <button type="submit">Загрузить файл</button>
                        </form>
                    </body>
                </html>
            `);
        } 
        else if (req.method === 'POST') {
            const boundary = req.headers['content-type'].split('; ')[1].replace('boundary=', '');
            let body = '';

            req.on('data', chunk => {
                body += chunk.toString();
            });

            req.on('end', () => {
                const parts = body.split(`--${boundary}`).filter(part => part.includes('filename='));

                if (parts.length > 0) {
                    const filePart = parts[0];
                    const fileContent = filePart.split('\r\n\r\n')[1].split('\r\n--')[0];
                    const filename = filePart.match(/filename="(.+)"/)[1].replace(/"/g, '');

                    const filePath = path.join(__dirname, 'static', filename);

                    fs.writeFile(filePath, fileContent, 'binary', err => {
                        if (err) {
                            res.writeHead(500, { 'Content-Type': 'text/plain; charset=utf-8' });
                            res.end('Ошибка при сохранении файла');
                        } 
                        else {
                            res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
                            res.end('Файл успешно загружен');
                        }
                    });
                } 
                else {
                    res.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
                    res.end('Файл не загружен');
                }
            });
        } 
        else {
            res.writeHead(405, { 'Content-Type': 'text/plain; charset=utf-8' });
            res.end('Метод не поддерживается');
        }
    } 
    else {
        res.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
        res.end('Не найдено');
    }