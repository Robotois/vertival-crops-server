#include <cstdio>
#include <bcm2835.h>

#include "../Modules/IOModule.h"
#include "../Libraries/Timer/AccurateTiming.h"

void i2c_init();
void i2c_end();

int main(int argc, char const *argv[]){
  i2c_init();

  IOModule *io = new IOModule();
    io->setMotor1(1);
    uint8_t state = 0x00;
  while(true){
      state = io->readSensor1();
      printf("Sensor State: %d\n", state);
    if(!state){
        io->setMotor1(1);
        io->setMotor2(0);        
    }else {
        io->setMotor1(0);
        io->setMotor2(1);
//        mDelay(250);
    }
    mDelay(100);
  }

  i2c_end();
}

void i2c_init(){
  uint16_t clockDiv = BCM2835_I2C_CLOCK_DIVIDER_626;

  if(!bcm2835_init()){
    printf("BCM2835 Error!!\n");
  }

  bcm2835_i2c_begin();
  bcm2835_i2c_setClockDivider(clockDiv);
}

void i2c_end(){
  bcm2835_i2c_end();
  bcm2835_close();
}
