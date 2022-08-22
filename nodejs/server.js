const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);

server.listen(7000,(req, res)=>{
    console.log("Listening on 7000");
  });

app.get('/public/index.html',function(req,res){
    res.sendFile(__dirname + '/index.html');
}); 

app.use(express.static("public"));

io.on('connection', (socket) => {
    
    socket.on('server', () => {
        console.log('Server Connected');
    });
    socket.on('client', () => {
        console.log('Client Connected');
    });
    socket.on('json', (data) => {
        io.emit("update", data);
    });
    
  socket.on('disconnect', () => {
    console.log('Disconnected');
  });
});









