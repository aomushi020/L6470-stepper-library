/*
    L6470 Stepper driver library for Arduino
    by aomushi020
*/

#include"Arduino.h"
#include"L6470.h"
#include<SPI.h>

SPISettings _spiSettings(1000000,MSBFIRST,SPI_MODE3);

// public members
L6470::L6470(unsigned short _SPI_SS){
  _L6470_SPI_SS = _SPI_SS;
  _L6470_SIG_BS = -1;
  _L6470_SIG_SR = -1;
}
L6470::L6470(unsigned short _SPI_SS,short _L6470_BS,short _L6470_SR){
  _L6470_SPI_SS = _SPI_SS;
  _L6470_SIG_BS = _L6470_BS;
  _L6470_SIG_SR = _L6470_SR;
}

void L6470::begin(void){
  if(!_L6470_SPI_SETUP){
    _L6470_SPI_SETUP=1;
    pinMode(L6470_SPI_MOSI, OUTPUT);
    pinMode(L6470_SPI_MISO, INPUT);
    pinMode(L6470_SPI_SCK, OUTPUT);
  }
  pinMode(_L6470_SPI_SS, OUTPUT);
  digitalWrite(_L6470_SPI_SS, HIGH);
  if(!_L6470_SPI_BEGIN){
    _L6470_SPI_BEGIN=1;
    SPI.begin();
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
  }
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_CMD_SETPARAM);// & B11100000);
  _spiwrite(0x00);
  _spiwrite(0x00);
  _spiwrite(0x00);
  _spiwrite(L6470_CMD_RESETDEVICE);
  SPI.endTransaction();
}

void L6470::setMaxSpeed(unsigned int _L6470_payload){
  _L6470_payload = constrain(_L6470_payload,0x0000,0x03FF);
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_ADD_MAX_SPEED);
  _spiwrite(_L6470_payload>>8);
  _spiwrite(_L6470_payload);
  SPI.endTransaction();
}
void L6470::setHoldVoltage(unsigned char _L6470_payload){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_ADD_KVAL_HOLD);
  _spiwrite(_L6470_payload);
  SPI.endTransaction();
}
void L6470::setRunVoltage(unsigned char _L6470_payload){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_ADD_KVAL_RUN);
  _spiwrite(_L6470_payload);
  SPI.endTransaction();
}
void L6470::setAccelVoltage(unsigned char _L6470_payload){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_ADD_KVAL_ACC);
  _spiwrite(_L6470_payload);
  SPI.endTransaction();
}  
void L6470::setDecelVoltage(unsigned char _L6470_payload){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_ADD_KVAL_DEC);
  _spiwrite(_L6470_payload);
  SPI.endTransaction();
}
void L6470::setSteps(unsigned char _L6470_payload){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_ADD_STEP_MODE);
  _spiwrite(_L6470_payload);
  SPI.endTransaction();
}

// Rotate commands
void L6470::run(unsigned char _dir,unsigned long _spd){
  _dir=constrain(_dir,0x00,0x01);
  _spd=constrain(_spd,0x000000,0x0FFFFF);
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_CMD_RUN | _dir);
  _spiwrite(_spd>>16);
  _spiwrite(_spd>>8);
  _spiwrite(_spd);
  SPI.endTransaction();
}
void L6470::move(unsigned char _dir,unsigned long _steps){
  _dir=constrain(_dir,0x00,0x01);
  _steps=constrain(_steps,0x000000,0x5FFFFF);
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_CMD_MOVE | _dir);
  _spiwrite(_steps>>16);
  _spiwrite(_steps>>8);
  _spiwrite(_steps);
  SPI.endTransaction();
}

// Stop commands
void L6470::hardStop(void){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_CMD_HARDSTOP);
  SPI.endTransaction();
}
void L6470::softStop(void){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_CMD_SOFTSTOP);
  SPI.endTransaction();
}
void L6470::goHome(void){
  SPI.beginTransaction(_spiSettings);
  _spiwrite(L6470_CMD_GOHOME);
  SPI.endTransaction();
}

// private member
void L6470::_spiwrite(unsigned char _L6470_payload){
//  Serial.println(_L6470_payload);
  digitalWrite(_L6470_SPI_SS, LOW); 
  SPI.transfer(_L6470_payload);
  digitalWrite(_L6470_SPI_SS, HIGH); 
}
// static menber variables
boolean L6470::_L6470_SPI_SETUP=0;
boolean L6470::_L6470_SPI_BEGIN=0;
