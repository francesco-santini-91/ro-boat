#include "Arduino.h"
#include "SolarPanel.h"

SolarPanel::SolarPanel(short int number, short int pinInput, short int relay) {
    this->_number = number;
    this->_pinInput = pinInput;
    this->_relay = relay;
    pinMode(pinInput, INPUT);
    pinMode(relay, OUTPUT);
}

float SolarPanel::getVoltage() {
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

bool SolarPanel::isActive() {
    float value = 0;
    value = this->getVoltage();
    if(value >= 7.00)
        return true;
    else
        return false;
}

void SolarPanel::connect() {
    if(this->state == CONNECTED)
        return;
    digitalWrite(_relay, HIGH);
    state = CONNECTED;
}

bool SolarPanel::disconnect() {
    if(this->state == DISCONNECTED)
        return true;
    digitalWrite(_relay, LOW);
    float value = 0;
    value = this->getVoltage();
    if(value < 3.00) {
        return true;
        state = DISCONNECTED;
    }
    else
        return false;
}

short int SolarPanel::getNumber() {
    return _number;
}

String SolarPanel::createInfoCode() {
    String InfoCode = "";
    short int number = this->getNumber();
    float voltage = this->getVoltage();
    bool actived = this->isActive();
    bool connected = this->state;
    InfoCode = PARAMETER_CODE+number+'?'+voltage+'?'+actived+'?'+connected+'#';
    return InfoCode;
}
