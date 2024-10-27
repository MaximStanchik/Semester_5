http = require('http');
const PORT = 5000;

let currentState = "norm";

const server = http.createServer(function(request, response) {
    response.writeHead(200, {'Content-Type': 'text/html'});
    response.end(`<h1>${currentState}</h1>`);
});

server.listen(PORT, function() {
    console.log('Server is running at http://localhost:' + PORT);
})

process.stdin.setEncoding('utf8');
process.stdout.write(currentState + "->");
process.stdin.on('readable', () => {
    let chunk = null;
    while((chunk = process.stdin.read()) !== null) {
        switch (chunk.trim()) {
            case "exit":
                process.exit(0);
                break;
            case "norm":
            case "idle":
            case "stop":
            case "test":
                process.stdout.write("reg = " + currentState + " --> " + chunk);
                currentState = chunk.trim();
                break;
            default:
                process.stdout.write(chunk);
        }
        process.stdout.write(currentState + "->");
    }
});