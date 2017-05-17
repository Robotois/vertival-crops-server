const io_module = require('bindings')('IOModule');
const EventEmitter = require('events').EventEmitter;
const inherits = require('util').inherits;

function IOModule() {
  EventEmitter.call(this);
  this.eventsInterval = false;

  this.ioModule = new io_module();

  let prevState = this.ioModule.readSensor1();

  process.on('SIGINT', () => {
    this.ioModule.release();
  });

  process.on('SIGTERM', () => {
    this.ioModule.release();
  });
}

IOModule.prototype.readSensor1 = function readSensor1() {
  return this.ioModule.readSensor1();
}

IOModule.prototype.readSensor2 = function readSensor2() {
  return this.ioModule.readSensor2();
}

IOModule.prototype.setMotor1 = function setMotor1(state) {
  return this.ioModule.setMotor1(state);
}

IOModule.prototype.setMotor2 = function setMotor2(state) {
  return this.ioModule.setMotor2(state);
}

IOModule.prototype.motorOn = function motorOn() {
  return this.ioModule.setMotor1(1);
}

IOModule.prototype.motorOff = function motorOff() {
  return this.ioModule.setMotor1(0);
}

IOModule.prototype.waterPumpOn = function waterPumpOn() {
  return this.ioModule.setMotor2(1);
}

IOModule.prototype.waterPumpOff = function waterPumpOff() {
  return this.ioModule.setMotor2(0);
}

IOModule.prototype.enableEvents = function enableEvents() {
  if(!this.eventsInterval){
    this.eventsInterval = setInterval(() => {
      const state = this.ioModule.readSensor1();
      this.emit('sensor-value', state);
    }, 200);
  }
}

IOModule.prototype.onChange = function onChange(callback) {
  this.on('sensor-value', (sensorState) => {
    if(this.prevState != sensorState){
      callback(sensorState);
      // this.emit('sensor-change', sensorState);
      this.prevState = sensorState;
    }
  });
}

IOModule.prototype.when = function when(state, callback) {
  this.enableEvents();
  this.on('sensor-value', (sensorState) => {
    if(sensorState == state){
      callback();
    }
  });
}

IOModule.prototype.release = function release() {
  clearInterval(this.eventsInterval);
  this.ioModule.release();
}

inherits(IOModule, EventEmitter);
module.exports = IOModule;
