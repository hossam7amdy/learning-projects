let readyPlayerCount = 0;

function listen(io) {
  const pongNamespace = io.of("/pong");

  let room;

  pongNamespace.on("connection", (socket) => {
    console.log("a user connected", socket.id);

    socket.on("ready", () => {
      room = Math.floor(readyPlayerCount / 2);
      console.log(`Player ${socket.id} is ready in room ${room}`);

      readyPlayerCount++;

      if (readyPlayerCount % 2 == 0) {
        pongNamespace.emit("startGame", socket.id);
      }
    });

    socket.on("paddleMove", (paddleData) => {
      socket.in(room).emit("paddleMove", paddleData);
    });

    socket.on("ballMove", (ballData) => {
      socket.in(room).emit("ballMove", ballData);
    });

    socket.on("disconnect", (reason) => {
      console.log(`Client ${socket.id} disconnected: ${reason}`);
      socket.leave(room);
    });
  });
}

module.exports = { listen };
