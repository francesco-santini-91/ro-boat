#include "Arduino.h"
#include "Engine.h"

Engine::Engine(short int number, short int pin1, short int pin2, short int pinEnable) {
    this->_number = number;
    this->_pin1 = pin1;
    this->_pin2 = pin2;   
    this->_pinEnable = pinEnable;
    this->engineDirection = FORWARD;
    this->engineSpeed = 0;
    this->state = DISABLED;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pinEnable, OUTPUT);
}

bool Engine::run(bool direction, short int speed) {
    if(speed < 0 || speed > 255 || this->state == DISABLED) {
        return false;
    }
    if(direction == REVERSE) {
        if(direction != this->getDirection() && this->getSpeed() > 0) {
            this->stop();
        }
        if(this->getSpeed() == 0) {
            this->start(direction);
        }
        analogWrite(this->_pin1, speed);
        analogWrite(this->_pin2, 0);
        this->engineDirection = direction;
        this->engineSpeed = speed;
    }
    else if(direction == FORWARD) {
        if(direction != this->getDirection() && this->getSpeed() > 0) {
            this->stop();
        }
        if(this->getSpeed() == 0) {
            this->start(direction);
        }
        analogWrite(this->_pin1, 0);
        analogWrite(this->_pin2, speed);
        this->engineDirection = direction;
        this->engineSpeed = speed;
    }
    return true;
}

void Engine::start(bool direction) {
    if(this->getDirection != direction && this->getSpeed > 0) {
        this->stop();
    }
    if(direction == REVERSE) {
        analogWrite(this->_pin1, MAX_SPEED);
        analogWrite(this->_pin2, 0);
        this->engineDirection = direction;
        this->engineSpeed = MAX_SPEED;
    }
    else if(direction == FORWARD) {
        analogWrite(this->_pin1, 0);
        analogWrite(this->_pin2, MAX_SPEED);
        this->engineDirection = direction;
        this->engineSpeed = MAX_SPEED;
    }
    delay(500);
}

void Engine::stop() {
    analogWrite(this->_pin1, 0);
    analogWrite(this->_pin2, 0);
    this->engineSpeed = 0;
    delay(500);
}

bool Engine::increaseSpeed(short int increase) {
    if((this->getSpeed() + increase) > MAX_SPEED) {
        return false;
    }
    else {
        this->run(this->getDirection(), this->getSpeed()+increase);
        return true;
    }
}

bool Engine::decreaseSpeed(short int decrease) {
    if((this->getSpeed() - decrease) < 100) {
        return false;
    }
    else {
        this->run(this->getDirection(), this->getSpeed()-decrease);
        return true;
    }
}

void Engine::enable() {
    digitalWrite(this->_pinEnable, HIGH);
    this->state = ENABLED;
}

void Engine::disable() {
    digitalWrite(this->_pinEnable, LOW);
    this->state = DISABLED;
}

void Engine::test() {
    this->run(REVERSE, MAX_SPEED);
    delay(2500);
    this->stop();
    delay(3000);
    this->run(FORWARD, MAX_SPEED);
    delay(2500);
    this->stop();
}

bool Engine::getDirection() {
    return this->engineDirection;
}

short int Engine::getSpeed() {
    return this->engineSpeed;
}   

bool Engine::getState() {
    return this->state;
}

short int Engine::getNumber() {
    return this->_number;
}

String Engine::createInfoCode() {
    String InfoCode = "";
    short int number = this->getNumber();
    short int speed = this->getSpeed();
    bool direction = this->getDirection();
    bool state = this->getState();
    InfoCode = PARAMETER_CODE+number+'?'+speed+'?'+direction+'?'+state+'#';
    return InfoCode;    
}