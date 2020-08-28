#ifndef Battery_h
#define Battery_h

#include "Arduino.h"

class Battery {

    public:
        Battery(short int cells, short int number, short int pinInput);         //Costruttore
        float getVoltage();                //Restituisce la tensione media di 10 letture effettuate a distanza di 50 ms.
        bool isConnected();                //Restituisce TRUE se la batteria è connessa al circuito.
        bool isCharged();                  //Restituisce TRUE se la percentuale di ricarica raggiunge il 95%.
        bool isTooLow();                   //Restituisce TRUE se la batteria raggiunge il livello minimo di tensione.
        bool isTooCharged();               //Restituisce TRUE se la batteria raggiunge il livello massimo di tensione.
        void setLimit(float voltageLimit); //Imposta il limite di tensione sotto la quale verrà attivato un alert.
        bool alertLevel();                 //Restituisce TRUE quando la tensione è inferiore o uguale al limite impostato
        short int getNumber();             //Restituisce il numero della batteria.
        String createInfoCode();           //Crea e restituisce l' InfoCode.

    private:
        const int R1 = 10000;           //Valore della resistenza R1
        const int R2 = 10000;           //Valore della resistenza R2
        const float V_NOMINAL = 3.7;    //Tensione nominale di una cella LiPO
        const float V_MAX = 4.2;        //Tensione massima di sicurezza di una cella LiPO
        const float V_MIN = 3.0;        //Tensione minima di sicurezza di una cella LiPO
        const String PARAMETER_CODE = "$BATT$";
        short int _number;
        short int _pinInput;
        short int _cells;
        float _limit;

};

#endif