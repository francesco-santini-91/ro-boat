#include "Arduino.h"
#include "Battery.h"

Battery::Battery(short int cells, short int number, short int pinInput) {
    this->_cells = cells;
    this->_number = number;
    this->_pinInput = pinInput;
    pinMode(pinInput, INPUT);
}

float Battery::getVoltage() {
    int value = 0;
    float R = (this->R1 + this->R2) / this->R2;
    float voltage = 0;
    float values[10];
    for(int i=0;i<10;i++) {
        value = analogRead(this->_pinInput);
        voltage = map(value, 0, 1023, 0, 500);
        voltage = (voltage * R) / 100;
        values[i] = voltage;
        delay(50);
    }
    voltage = 0;
    for(int i=0;i<10;i++) {
        voltage = voltage + values[i];
    }
    voltage = voltage / 10;
    return voltage;
}

bool Battery::isConnected() {
    float value_1 = 0;
    float value_2 = 0;
    value_1 = this->getVoltage();
    delay(500);
    value_2 = this->getVoltage();
    if(value_1 > 0 && value_2 > 0) 
        return true;
    else 
        return false;
}

bool Battery::isCharged() {
    float value = 0;
    value = this->getVoltage();
    if(value >= ((V_MAX * _cells) * 0.95))
        return true;
    else
        return false;
}

bool Battery::isTooLow() {
    float value = 0;
    value = this->getVoltage();
    if(value <= (V_MIN * _cells))
        return true;
    else
        return false;    
}

bool Battery::isTooCharged() {
    float value = 0;
    value = this->getVoltage();
    if(value >= (V_MAX * _cells))
        return true;
    else
        return false;    
}

void Battery::setLimit(float voltageLimit) {
    this->_limit = voltageLimit;
}

bool alertLevel() {
    float value = 0;
    value = this->getVoltage();
    if(value > this->_limit)
        return false;
    else
        return true;
}

short int Battery::getNumber() {
    return this->_number;
}

String Battery::createInfoCode() {
    String InfoCode = "";
    short int number = this->getNumber();
    float voltage = this->getVoltage();
    bool isConnected = this->isConnected();
    bool isCharged = this->isCharged();
    bool isTooLow = this->isTooLow();
    bool isTooCharged = this->isTooCharged();
    InfoCode = PARAMETER_CODE+number+'?'+voltage+'?'+isConnected+'?'+isCharged+'?'+isTooLow+'?'+isTooCharged+'#';
    return InfoCode;
}