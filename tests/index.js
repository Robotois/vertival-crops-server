const IOModule = require('../IOModule');
const ioModule = new IOModule();
ioModule.enableEvents();

ioModule.motorOn();
ioModule.waterPumpOff();

ioModule.on('sensor-value', (state) => {
  if(state){
    ioModule.motorOff();
    ioModule.waterPumpOn();
  } else {
    ioModule.motorOn();
    ioModule.waterPumpOff();
  }
});

process.on('SIGINT', () => {
  process.exit();
});

process.on('SIGTERM', () => {
  process.exit();
});
