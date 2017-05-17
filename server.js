const logger = require('koa-logger');
const route = require('koa-route');
const parse = require('co-body');
const koa = require('koa');

const WateringModule = require('./WateringModule');

const app = koa();
const port = 8082;
let INTERVAL = null;

const DB = {
  interval: 0,
  duration: 0,
};

app.use(logger());
/* eslint-disable require-yield */

/**
 * Renders the home layout
 * @returns {HTML} returns html body.
 */
function* home() {
  this.body = 'VERTICAL CROPS API';
}

function stopWatering(duracion) {
  console.log('stop watering');
  // ioModule.waterPumpOff();
}

function startWatering(duracion) {
  console.log('start watering');
  // ioModule.waterPumpOn();
  setTimeout(
    () => {
      stopWatering();
      // ioModule.waterPumpOff();
    },
    duracion * 1000
  );
}

function runTimeout(intervalo, duracion, delta) {
  setTimeout(
    () => {
      startWatering(duracion);
      runTimeout(intervalo, duracion, duracion);
    },
    intervalo * 60 * 1000 + delta * 1000
  );
}
/**
 * Renders the home layout
 * @returns {JSON} returns JSON.
 */
function* post() {
  const data = yield parse(this);
  let reps = 0;
  let delta = 0;
  const intervalo = parseInt(data.intervalo);
  const duracion = parseInt(data.duracion);
  let counter = 1;

  console.log(data);

  // setInterval(function () {
  //   console.log(counter++);
  // }, 1000);

  if (intervalo && duracion) {
    // runTimeout(intervalo, duracion, 0);
    this.body = {
      success: true,
      message: 'Configuración lista!',
    };
  } else {
    this.body = {
      success: false,
      message: 'Error de datos',
    };
  }

  if(intervalo != 0 && duracion != 0){
    WateringModule.setConfig({ intervalo, duracion });
  }else{
    WateringModule.stop();
  }
  return this.body;
}

app.use(route.get('/', home));
app.use(route.post('/post', post));

console.log(`Application is up and running at port ${port}`);
// listen
app.listen(port);
