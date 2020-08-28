#ifndef InfoCode_h
#define InfoCode_h

#include "Arduino.h"

class InfoCode {

    public:
        InfoCode(string InfoCode);
        bool verify();
        String getParameter();
        short int getEngineNumber();
        short int getEngineSpeed();
        bool getEngineDirection();
        bool getEngineState();
        short int getBatteryNumber();
        float getBatteryVoltage();
        bool isBatteryConnected();
        bool isBatteryCharged();
        bool isBatteryTooLow();
        bool isBatteryTooCharged();
        short int getSolarPanelNumber();
        float getSolarPanelVoltage();
        bool isSolarPanelActived();
        bool isSolarPanelConnected();

    private:
        String InfoCode = "";

};

#endif