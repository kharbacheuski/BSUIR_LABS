const net = require('net');

const getServerTimeLive = (startServerTime) => {
    const uptimeMilliseconds = new Date() - startServerTime;

    return `${uptimeMilliseconds / 1000}s`;
} 

const server = net.createServer((socket) => {
    const serverStartTime = new Date();

    console.log('Client connected');

    socket.write(`You connect to server\r\n`);
    socket.write(`Current server time: ${new Date().toLocaleTimeString()}\r\n`);

    socket.on('data', (data) => {
        const args = data.toString().trim().split(" ");

        console.log("Command: " + `"${args[0]}"`);

        switch (args[0]) {
            case "ECHO": {
                socket.write(`${args.filter((arg, index) => index != 0).toString().replaceAll(",", " ")}\r\n`)
            }; break;

            case "TIME": {
                socket.write(`Server live time: ${getServerTimeLive(serverStartTime)}\r\n`);
            }; break;

            case "CLOSE": {
                socket.write('Goodbye!\r\n');
                socket.destroy();
            }; break;

            default: {
                socket.write('Unknown command\r\n');
            }; break;
        }
    });

    socket.on('close', () => {
        console.log('Client disconnected');
    });
});

const port = 9000;

server.listen(port, () => {
    console.log("Server listening on port", port);
});
