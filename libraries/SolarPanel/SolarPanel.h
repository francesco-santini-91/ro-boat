#ifndef SolarPanel_h
#define SolarPanel_h

#include "Arduino.h"

class SolarPanel {

    public:
        SolarPanel(short int number, short int pinInput, short int relay);
        float getVoltage();
        bool isActive();
        void connect();
        bool disconnect();
        short int getNumber();
        String createInfoCode();

    private:
        const int R1 = 10000;
        const int R2 = 10000;
        const bool DISCONNECTED = 0;
        const bool CONNECTED = 1;
        const String PARAMETER_CODE = "$SOLP$";
        short int _number;
        short int _pinInput;
        short int _relay;
        bool state;
};

#endif