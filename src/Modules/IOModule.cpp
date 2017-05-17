/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOModule.cpp
 * Author: yovany
 * 
 * Created on May 16, 2017, 12:00 PM
 */

#include <cstdio>

#include "IOModule.h"

IOModule::IOModule(uint8_t addr) {
    mcp  = new MCP23008(addr);
    initialize();
}

IOModule::IOModule(const IOModule& orig) {
}

IOModule::~IOModule() {
}

void IOModule::initialize(){
    mcp->setDir(SENSOR1,MCP23008_INPUT);
    mcp->setDir(SENSOR2,MCP23008_INPUT);
    mcp->setPullUp(SENSOR1,MCP23008_PULL_UP_EN);
    mcp->setPullUp(SENSOR2,MCP23008_PULL_UP_EN);
    
    mcp->setDir(MOTOR1,MCP23008_OUTPUT);
    mcp->setDir(MOTOR2,MCP23008_OUTPUT);
}

uint8_t IOModule::readSensor1(){
    return mcp->digitalRead(SENSOR1) ^ 0x01;
}

uint8_t IOModule::readSensor2(){
    return mcp->digitalRead(SENSOR2) ^ 0x01;
}

void IOModule::setMotor1(uint8_t state){
    mcp->digitalWrite(MOTOR1,state);
}

void IOModule::setMotor2(uint8_t state){
    mcp->digitalWrite(MOTOR2,state);
}

void IOModule::release() {
    mcp->digitalWrite(MOTOR1,0);
    mcp->digitalWrite(MOTOR2,0);
//    delete mcp;
    printf("[IOModule] => Released!!\n");
}
