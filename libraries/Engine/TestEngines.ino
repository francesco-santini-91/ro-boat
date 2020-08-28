/*
* - Nome:       Engines_Controller.ino
* - Autore:     Francesco Santini
* - Versione:   1.0
* - Progetto:   RoBoat
*
*   Software per la gestione dei 2 motori della barca mediante l' utilizzo del ponte H L298N.
*   ----------------------------------------------------------------------------------------------------------
*   FUNZIONE: run_Engine(bool engine, bool direction, int speed)
*   La funzione run_Engine riceve tre argomenti: - engine    -> Quale dei due motori si intende pilotare
*                                                - direction -> La direzione in cui dovrà ruotare
*                                                - speed     -> La velocità, in un range da 0 a 255 (Max)
*   Richiamando più volte la funzione è possibile gestire la velocità di rotazione.  
*   Ad ogni chiamata, viene effettuata una verifica e nel caso venga richiesto un cambio direzione, onde evitare picchi 
*   di corrente, i motori verranno prima fermati per 500 ms.
*   Nel caso invece si richieda una partenza da fermi, verranno attivati a piena potenza per 500 ms.
*   ----------------------------------------------------------------------------------------------------------
*   FUNZIONE: start_Engine(bool engine, bool direction)
*   La partenza da fermo di un motore potrebbe generare picchi di corrente, nel caso in cui la velocità di 
*   rotazione fosse troppo bassa, quindi la funzione start_Engine fornirà al  motore la massima potenza solo  
*   per i primi 500 millisecondi.
*   ----------------------------------------------------------------------------------------------------------
*   FUNZIONE: stop_Engine(bool engine)
*   La funzione stop_Engine ferma il motore passato come argomento.
*/

#define _INPUT_1 3  /* Definizione dei pin PWM */
#define _INPUT_2 5
#define _INPUT_3 6
#define _INPUT_4 9

const int MAX_SPEED = 255;
const bool REVERSE = 0;
const bool FORWARD = 1;
const bool ENGINE_1 = 0;
const bool ENGINE_2 = 1;

int _speed = 0;
int speed_ENG_1 = 0;
int speed_ENG_2 = 0;
bool direction_ENG_1 = null;
bool direction_ENG_2 = null;

void setup() {
    //Serial.begin(9600);
    pinMode(_INPUT_1, OUTPUT); 
    pinMode(_INPUT_2, OUTPUT);
    pinMode(_INPUT_3, OUTPUT);
    pinMode(_INPUT_4, OUTPUT);
}

void run_Engine(bool engine, bool direction, int speed) {
    if(engine == ENGINE_1) {
        if(direction == REVERSE) {
            if(direction != direction_ENG_1 && speed_ENG_1 > 0) {
                stop_Engine(ENGINE_1);
            }
            if(speed_ENG_1 == 0) {
                start_Engine(ENGINE_1, REVERSE);
            }
            analogWrite(_INPUT_1, speed);
            analogWrite(_INPUT_2, 0);
            direction_ENG_1 = REVERSE;
            speed_ENG_1 = speed;
        }
        else if(direction == FORWARD) {
            if(direction != direction_ENG_1 && speed_ENG_1 > 0) {
                stop_Engine(ENGINE_1);
            }
            if(speed_ENG_1 == 0) {
                start_Engine(ENGINE_1, FORWARD);
            }
            analogWrite(_INPUT_1, 0);
            analogWrite(_INPUT_2, speed);
            direction_ENG_1 = FORWARD;
            speed_ENG_1 = speed;
        }
    }
    else if(engine == ENGINE_2) {
        if(direction == REVERSE) {
            if(direction != direction_ENG_2 && speed_ENG_2 > 0) {
                stop_Engine(ENGINE_2);
            }
            if(speed_ENG_2 == 0) {
                start_Engine(ENGINE_2, REVERSE);
            }
            analogWrite(_INPUT_3, speed);
            analogWrite(_INPUT_4, 0);
            direction_ENG_2 = REVERSE;
            speed_ENG_2 = speed;
        }
        else if(direction == FORWARD) {
            if(direction != direction_ENG_2 && speed_ENG_2 > 0) {
                stop_Engine(ENGINE_2);
            }
            if(speed_ENG_2 == 0) {
                start_Engine(ENGINE_2, FORWARD);
            }
            analogWrite(_INPUT_3, 0);
            analogWrite(_INPUT_4, speed);
            direction_ENG_2 = FORWARD;
            speed_ENG_2 = speed;
        }
    }
    _speed = speed;
}

void start_Engine(bool engine, bool direction) {
    if(engine == ENGINE_1) {
        if(direction == REVERSE) {
            analogWrite(_INPUT_1, MAX_SPEED);
            analogWrite(_INPUT_2, 0);
            direction_ENG_1 = REVERSE;
            speed_ENG_1 = MAX_SPEED;
        }
        else if(direction == FORWARD) {
            analogWrite(_INPUT_1, 0);
            analogWrite(_INPUT_2, MAX_SPEED);
            direction_ENG_1 = FORWARD;
            speed_ENG_1 = MAX_SPEED;
        }
    }
    else if(engine == ENGINE_2) {
        if(direction == REVERSE) {
            analogWrite(_INPUT_3, MAX_SPEED);
            analogWrite(_INPUT_4, 0);
            direction_ENG_2 = REVERSE;
            speed_ENG_2 = MAX_SPEED;
        }
        else if(direction == FORWARD) {
            analogWrite(_INPUT_3, 0);
            analogWrite(_INPUT_4, MAX_SPEED);
            direction_ENG_2 = FORWARD;
            speed_ENG_2 = MAX_SPEED;
        }
    }
    _speed = MAX_SPEED;
    delay(500);
}

void stop_Engine(bool engine) {
    if(engine == ENGINE_1) {
        analogWrite(_INPUT_1, 0);
        analogWrite(_INPUT_2, 0);
        speed_ENG_1 = 0;
    }
    else if(engine == ENGINE_2) {
        analogWrite(_INPUT_3, 0);
        analogWrite(_INPUT_4, 0);
        speed_ENG_2 = 0;
    }
    delay(500);
}

void turn_RIGHT() {
    if(_speed > 200) {
        int turning_Speed = _speed - 55;
        run_Engine(ENGINE_2, FORWARD, turning_Speed);
    }
    else if(_speed <= 200) {
        int turning_Speed = _speed + 55;
        run_Engine(ENGINE_1, FORWARD, turning_Speed);
    }
}

void turn_LEFT() {
    if(_speed > 200) {
        int turning_Speed = _speed - 55;
        run_Engine(ENGINE_1, FORWARD, turning_Speed);
    }
    else if(_speed <=200) {
        int turning_Speed = _speed + 55;
        run_Engine(ENGINE_2, FORWARD, turning_Speed);
    }
}

void engine_TEST() {
    run_Engine(ENGINE_1, REVERSE, MAX_SPEED);
    delay(2500);
    stop_Engine(ENGINE_1);
    delay(5000);
    run_Engine(ENGINE_2, REVERSE, MAX_SPEED);
    delay(2500);
    stop_Engine(ENGINE_2);
    delay(5000);
    for(int testSpeed=250;testSpeed>100;testSpeed=testSpeed-10) {
        run_Engine(ENGINE_1, FORWARD, testSpeed);
        run_Engine(ENGINE_2, FORWARD, testSpeed);
        delay(500);
    }
    stop_Engine(ENGINE_1);
    stop_Engine(ENGINE_2);
}

void loop() {
    //test1();
    //test2();
    //test3();

}

void test1() {
    delay(5000);
    start_Engine(ENGINE_1, REVERSE);
    delay(1500);
    stop_Engine(ENGINE_1);
    delay(2500);
    start_Engine(ENGINE_2, REVERSE);
    delay(1500);
    stop_Engine(ENGINE_2);
    delay(2500);
    start_Engine(ENGINE_1, FORWARD);
    start_Engine(ENGINE_2, FORWARD);
    run_Engine(ENGINE_1, FORWARD, 140);
    run_Engine(ENGINE_2, FORWARD, 140);
    delay(15000);
    stop_Engine(ENGINE_1);
    stop_Engine(ENGINE_2);
    delay(2500);
}

void test2() {
    delay(5000);
    start_Engine(ENGINE_1, FORWARD);
    start_Engine(ENGINE_2, FORWARD);
    run_Engine(ENGINE_1, FORWARD, 205);
    run_Engine(ENGINE_2, FORWARD, 205);
    delay(3000);
    turn_RIGHT();
    delay(5000);
}

void test3() {
    delay(5000);
    start_Engine(ENGINE_1, FORWARD);
    start_Engine(ENGINE_2, FORWARD);
    for(int downspeed=150;downspeed>0;downspeed--) {
        run_Engine(ENGINE_1, FORWARD, downspeed);
        run_Engine(ENGINE_2, FORWARD, downspeed);
        Serial.println(downspeed);
        delay(2000);
    }
}