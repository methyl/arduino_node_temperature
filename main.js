
var app = require('http').createServer(handler)
  , io = require('socket.io').listen(app)
  , fs = require('fs')

app.listen(3334);

function handler (req, res) {
  fs.readFile(__dirname + '/index.html',
  function (err, data) {
    if (err) {
      res.writeHead(500);
      return res.end('Error loading index.html');
    }

    res.writeHead(200);
    res.end(data);
  });
}

var currentTemperature;

function setCurrentTemperature(temperature) {
  currentTemperature = temperature;
  io.sockets.emit('change', { temperature: temperature });
}

io.sockets.on('connection', function(socket){
  socket.emit('change', { temperature: currentTemperature })
});

var serialport = require('serialport');

var serialPort = new serialport.SerialPort("/dev/tty.usbmodem1421", {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});

serialPort.on("open", function () {
  serialPort.on('data', setCurrentTemperature);
});
