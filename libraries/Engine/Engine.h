#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine {
   
    public:
        Engine(short int number, short int pin1, short int pin2, short int pinEnable);         //Costruttore
        bool run(bool direction, short int speed);      //Pilota il motore in base ai parametri passati come argomenti.
        void start(bool direction);                     //Avvia il motore con partenza da fermo.
        void stop();                                    //Ferma il motore.
        bool increaseSpeed(short int increase);         //Incrementa la velocità. Restituisce TRUE se il valore è accettabile.
        bool decreaseSpeed(short int decrease);         //Decrementa la velocità. Restituisce TRUE se il valore è accettabile.
        void enable();                                  //Abilita il motore.
        void disable();                                 //Disabilita il motore.
        void test();                                    //Effettua un test di funzionamento del motore.
        bool getDirection();                            //Restituisce la direzione in cui sta girando il motore.
        short int getSpeed();                           //Restituisce la velocità alla quale sta girando il motore.
        short int getNumber();                          //Restituisce il numero di motore.
        String createInfoCode();                        //Crea e restituisce l' InfoCode.

    private:
        const bool REVERSE = 0;
        const bool FORWARD = 1;
        const bool DISABLED = 0;
        const bool ENABLED = 1;
        const short int MAX_SPEED = 255;                //Valore massimo di PWM.
        const String PARAMETER_CODE = "$ENGN$";
        short int _number;
        short int _pin1;
        short int _pin2;
        short int _pinEnable;
        bool engineDirection;
        short int engineSpeed;
        bool state;
};

#endif