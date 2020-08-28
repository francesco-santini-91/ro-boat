#include <SolarPanel.h>

#define SP_1 A0
#define SP_2 A1
#define rel_1 2
#define rel_2 3

float voltage = 0;
bool _isActive;
bool _disconnect;
int number;

SolarPanel Panel_1(1, SP_1, rel_1);
SolarPanel Panel_2(2, SP_2, rel_2);

void setup() {
    Serial.begin(9600);
}

void loop() {
    delay(500);
    Panel_1.connect();
    voltage = Panel_1.getVoltage();
    _disconnect = Panel_1.disconnect();
    number = Panel_1.getNumber();
    Serial.print("Tensione: ");
    Serial.print(voltage);
    Serial.println(" V");
    Serial.print("Attivazione: ");
    Serial.println(_isActive);
    Serial.print("Disconnesso: ");
    Serial.println(_isActive);
    Serial.print("Numero: ");
    Serial.println(number);
    delay(1000);
    Panel_1.disconnect();
    Panel_1.connect();
    voltage = Panel_1.getVoltage();
    _disconnect = Panel_1.disconnect();
    number = Panel_1.getNumber();
    Serial.print("Tensione: ");
    Serial.print(voltage);
    Serial.println(" V");
    Serial.print("Attivazione: ");
    Serial.println(_isActive);
    Serial.print("Disconnesso: ");
    Serial.println(_isActive);
    Serial.print("Numero: ");
    Serial.println(number);
}
    
}