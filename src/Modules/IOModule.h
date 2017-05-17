/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOModule.h
 * Author: yovany
 *
 * Created on May 16, 2017, 12:00 PM
 */

#ifndef IOMODULE_H
#define IOMODULE_H

#include <cstdint>

#include "../Libraries/MCP23008/MCP23008.h"

#define SENSOR1 0x00
#define SENSOR2 0x01
#define MOTOR1 0x04
#define MOTOR2 0x05

class IOModule {
public:
    IOModule(uint8_t addr = 0x04);
    IOModule(const IOModule& orig);
    virtual ~IOModule();
    
    uint8_t readSensor1();
    uint8_t readSensor2();
    
    void setMotor1(uint8_t state);
    void setMotor2(uint8_t state);
    
    void release();
private:
    MCP23008 *mcp;
    
    void initialize();
};

#endif /* IOMODULE_H */

