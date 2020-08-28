#include <Battery.h>

#define BAT_1 A0
#define BAT_2 A1
#define BAT_3 A2
#define BAT_4 A3

float voltage = 0;
bool _isConnected;
bool _isCharged;
bool _isTooLow;
bool _isTooCharged;
int number;

Battery Battery_1(2, 1, BAT_1);
Battery Battery_2(2, 2, BAT_2);
Battery Battery_3(2, 3, BAT_3);
Battery Battery_4(2, 4, BAT_4);

void setup() {
    Serial.begin(9600);
}

void loop() {
    delay(500);
    voltage = Battery_1.getVoltage();
    _isConnected = Battery_1.isConnected();
    _isCharged = Battery_1.isCharged();
    _isTooLow = Battery_1.isTooLow();
    _isTooCharged = Battery_1.isTooCharged();
    number = Battery_1.getNumber();
    Serial.print("Tensione: \t");
    Serial.print(voltage);
    Serial.println(" V");
    Serial.print("Connessione: \t\t");
    Serial.println(_isConnected);
    Serial.print("Carica: \t\t");
    Serial.println(_isCharged);
    Serial.print("Troppo scarica: \t");
    Serial.println(_isTooLow);
    Serial.print("Troppo carica: \t\t");
    Serial.println(_isTooCharged);
    Serial.print("Numero batteria: \t");
    Serial.println(number);
    Serial.println("");
    Serial.println("");
}