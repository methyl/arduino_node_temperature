class HttpServer
  http = require('http')
  fs = require('fs')

  constructor: (@port) ->
    @app = http.createServer(@handler)
    @app.listen(@port)

  handler: (req, res) =>
    fs.readFile __dirname + '/index.html', (err, data) ->
      res.writeHead(200)
      res.end(data)

  getApp: ->
    @app

class IoServer
  constructor: (@app, onConnection) ->
    @io = require('socket.io').listen(@app)

  emit: (name, data) ->
    @io.sockets.emit(name, data)

  onConnection: (fn) ->
    @io.sockets.on 'connection', fn

class ArduinoHandler
  serialport = require('serialport')

  constructor: (@device) ->
    @serialPort = new serialport.SerialPort @device,
      baudrate: 115200,
      dataBits: 8,
      parity: 'none',
      stopBits: 1,
      flowControl: false,
      parser: serialport.parsers.readline("\n")

  listen: (onData) ->
    @serialPort.on "open", => @serialPort.on('data', onData)

  send: (data) ->
    @serialPort.write("P#{data}")

class Temperature
  history: []

  constructor: (@ioServer, @arduinoHandler) ->
    @arduinoHandler.listen(@update)
    @ioServer.onConnection(@pushHistory)

  update: (data) =>
    [device, temp] = data.split(':')
    @history.push
      device: parseInt(device)
      temp: temp
      date: new Date()
    @pushHistory()

  pushHistory: =>
    @ioServer.emit('change-temp', @history)

class Pwm
  constructor: (@ioServer, @arduinoHandler) ->
    @ioServer.onConnection(@addEventListener)

  addEventListener: (socket) =>
    socket.on('change-pwm', @onChange)

  onChange: (pwm) =>
    @arduinoHandler.send(pwm)

class App
  constructor: (@port, @device) ->
    @httpServer = new HttpServer(@port)
    @ioServer = new IoServer(@httpServer.getApp())
    @arduinoHandler = new ArduinoHandler(@device)

    @temperature = new Temperature(@ioServer, @arduinoHandler)
    @pwm = new Pwm(@ioServer, @arduinoHandler)


app = new App(3334, "/dev/tty.usbmodem14141")
