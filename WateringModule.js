const IOModule = require('./IOModule');

function WateringModule() {
  this.ioModule = new IOModule();
  // this.ioModule.enableEvents();

  this.motorTimeout = false;
  this.waterTimeout = false;

  this.config = {
    intervalo: 0,
    duracion: 0
  };
  this.status = false;
}

WateringModule.prototype.run = function run() {
  this.motorTimeout = setTimeout(() => {
    this.runCycle();
  }, this.config.intervalo);
}

WateringModule.prototype.runCycle = function runCycle() {
  this.ioModule.motorOn();
  // ---
  let prevState = this.ioModule.readSensor1();
  const onChange = () => {
    const currentState = this.ioModule.readSensor1();
    // console.log(`CurrentState: ${currentState}`);
    if(prevState != currentState && currentState){
      this.ioModule.motorOff();
      setTimeout(() => {
        this.watering();
      }, 500);
    }else {
      setTimeout(onChange, 100);
      prevState = currentState;
    }
  }
  onChange();
  // ---

  // this.ioModule.onChange((sensorState) => {
  //   if(sensorState){
  //     this.ioModule.motorOff();
  //     setTimeout(() => {
  //       this.watering();
  //     }, 500);
  //   }
  // });
}

WateringModule.prototype.watering = function watering() {
  this.ioModule.waterPumpOn();
  this.waterTimeout = setTimeout(() => {
    this.ioModule.waterPumpOff();
    this.run();
  }, this.config.duracion);
}

WateringModule.prototype.stop = function stop() {
  clearTimeout(this.motorTimeout);
  clearTimeout(this.waterTimeout);
  this.motorTimeout = false;
  this.waterTimeout = false;
  this.ioModule.motorOff();
  this.ioModule.waterPumpOff();
  console.log("Watering process stopped!!");
};

WateringModule.prototype.setConfig = function setConfig(new_config) {
  this.stop();
  this.config.intervalo = new_config.intervalo * 1000;
  this.config.duracion = new_config.duracion * 1000;
  console.log(this.config);
  if(this.config.intervalo != 0 && this.config.duracion != 0){
    this.run();
  }
};

module.exports = new WateringModule();
