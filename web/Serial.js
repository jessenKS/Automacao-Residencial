const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
const sPort = new SerialPort('COM11' , {
  baudRate: 9600
});
const parser = new Readline();
sPort.pipe(parser);

parser.on('data', (recebido_arduino) => {
  console.log("==========================");	
  console.log("temperatura: " + recebido_arduino);
})