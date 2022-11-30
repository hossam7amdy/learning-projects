const http = require("http");
const io = require("socket.io");

const apiServer = require("./api");
const httpServer = http.createServer(apiServer);
const socketServer = io(httpServer);

const PORT = 3000;
httpServer.listen(PORT, () => {
  console.log(`server is running on port ${PORT}`);
});

const sockets = require("./sockets");
sockets.listen(socketServer);
