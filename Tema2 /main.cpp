#include <Arduino.h>

// defineste pinii led-ului
const int red_pin = 6;          // pin pentru led rosu
const int green_pin = 5;        // pin pentru led verde
const int blue_pin = 4;         // pin pentru led albastru

// defineste pinii pentru butoane
const int button_start_pin = 3;         // pin pentru butonul de start
const int button_difficulty_pin = 2;    // pin pentru butonul de dificultate

// variabile pentru starea jocului si timpi
int difficulty = 0;                    // nivelul de dificultate: 0 - usor, 1 - mediu, 2 - greu
unsigned long previous_millis = 0;      // momentul ultimei afisari a unui cuvant nou
unsigned long round_start_millis = 0;   // momentul de inceput al rundei
const unsigned long round_duration = 30000;  // durata rundei in milisecunde (30 secunde)
unsigned long word_interval;            // intervalul dintre cuvinte in functie de dificultate
bool is_round_active = false;           // indica daca runda este activa
bool is_countdown_active = false;       // indica daca este activa numaratoarea inversa
bool was_round_stopped = true;          // permite pornirea numaratorii daca runda anterioara a fost oprita
int countdown_step = 3;                 // numaratoarea inversa de la 3 la 0
unsigned long countdown_millis = 0;     // momentul ultimei actualizari a numaratorii
int words_correct = 0;                  // contor pentru cuvintele tastate corect
String current_word = "";               // cuvantul curent de tastat
String input_word = "";                 // cuvantul introdus de jucator

// variabile pentru debouncing la butoane
unsigned long last_debounce_start = 0;       // temporizator debounce pentru butonul de start
unsigned long last_debounce_difficulty = 0;  // temporizator debounce pentru butonul de dificultate
const int debounce_delay = 50;               // intarzierea pentru debounce in milisecunde

// starea butoanelor
bool start_button_pressed = false;           // indica daca butonul de start este apasat
bool difficulty_button_pressed = false;      // indica daca butonul de dificultate este apasat

// dicționar de cuvinte pentru joc
String words[] = {
    "creeper", "diamond", "pickaxe", "nether", "zombie", "skeleton", 
    "crafting", "potion", "enderman", "emerald", "villager", "redstone", 
    "biome", "portal", "enchantment", "obsidian", "armor", "bedrock", 
    "mob", "spawn", "wither", "dragon", "torch", "sword", "shovel", 
    "furnace", "mineshaft", "anvil", "elytra", "piston"
};
const int words_count = sizeof(words) / sizeof(words[0]);  // numarul total de cuvinte

// seteaza culoarea led-ului rgb
void set_led_color(int red, int green, int blue) {
    analogWrite(red_pin, red);
    analogWrite(green_pin, green);
    analogWrite(blue_pin, blue);
}

// actualizeaza intervalul dintre cuvinte in functie de dificultate
void update_word_interval() {
    switch (difficulty) {
        case 0:
            word_interval = 5000; // usor: 5 secunde
            break;
        case 1:
            word_interval = 1500; // mediu: 1.5 secunde
            break;
        case 2:
            word_interval = 1000; // greu: 1 secunda
            break;
    }
}

void setup() {
    Serial.begin(9600);
    
    // configureaza pinii pentru led si butoane
    pinMode(red_pin, OUTPUT);
    pinMode(green_pin, OUTPUT);
    pinMode(blue_pin, OUTPUT);
    pinMode(button_start_pin, INPUT_PULLUP);
    pinMode(button_difficulty_pin, INPUT_PULLUP);

    // seteaza led-ul alb ca stare de asteptare
    set_led_color(255, 255, 255);
    update_word_interval();                       // seteaza intervalul initial al cuvintelor
    Serial.println("difficulty is preset to easy");
}

// incepe numaratoarea inversa pentru startul jocului
void start_countdown() {
    is_countdown_active = true;                   // activeaza numaratoarea
    countdown_step = 3;                           // porneste de la 3
    countdown_millis = millis();                  // seteaza timpul initial al numaratorii
}

// afiseaza un cuvant nou pentru jucator
void display_new_word() {
    input_word = "";                              // reseteaza cuvantul introdus de jucator

    // sterge linia anterioara din serial monitor
    Serial.write(27);                             // cod de escape pentru stergere
    Serial.print("[2K");                          // sterge linia curenta
    Serial.write(13);                             // muta cursorul la inceputul liniei

    while (Serial.available() > 0) {
        Serial.read();                            // goleste buffer-ul serial
    }

    // alege un cuvant nou aleatoriu din lista
    current_word = words[random(0, words_count)];
    Serial.print("type the word: ");
    Serial.println(current_word);
}

// incepe o noua runda
void start_round() {
    is_round_active = true;                       // activeaza runda
    words_correct = 0;                            // reseteaza scorul
    previous_millis = millis();                   // seteaza timpul pentru cuvantul urmator
    round_start_millis = millis();                // seteaza timpul de start al rundei
    display_new_word();                           // afiseaza primul cuvant
}

// opreste runda si reseteaza led-ul la alb
void stop_round() {
    is_round_active = false;                      // dezactiveaza runda
    Serial.print("final score: ");
    Serial.println(words_correct);                // afiseaza scorul
    set_led_color(255, 255, 255);                 // led alb pentru stare de asteptare
}

// gestioneaza numaratoarea inversa
void run_countdown() {
    if (millis() - countdown_millis >= 1000) {    // verifica daca a trecut o secunda
        switch (countdown_step) {
            case 3:
                Serial.println("3");
                set_led_color(255, 0, 0);         // rosu pentru 3
                break;
            case 2:
                Serial.println("2");
                set_led_color(255, 75, 0);        // portocaliu pentru 2
                break;
            case 1:
                Serial.println("1");
                set_led_color(255, 255, 0);       // galben pentru 1
                break;
            case 0:
                Serial.println("start");
                set_led_color(0, 255, 0);         // verde pentru start
                start_round();                    // incepe runda
                is_countdown_active = false;      // opreste numaratoarea
                return;
        }
        countdown_step--;                         // scade numaratoarea
        countdown_millis = millis();              // reseteaza timpul pentru urmatorul pas
    }
}

// schimba nivelul de dificultate
void change_difficulty() {
    difficulty = (difficulty + 1) % 3;            // ciclare intre 0, 1, 2
    update_word_interval();                       // actualizeaza intervalul in functie de dificultate
    switch (difficulty) {
        case 0:
            Serial.println("easy mode on");
            break;
        case 1:
            Serial.println("medium mode on");
            break;
        case 2:
            Serial.println("hard mode on");
            break;
    }
}

// verifica starea butoanelor cu debounce
void check_buttons() {
    // verifica apasarea butonului de start
    if (digitalRead(button_start_pin) == LOW && !start_button_pressed && millis() - last_debounce_start > debounce_delay) {
        start_button_pressed = true;

        if (is_round_active) {
            stop_round();                         // opreste runda daca este activa
            was_round_stopped = true;
        } else if (!is_countdown_active && was_round_stopped) {
            start_countdown();                    // incepe numaratoarea daca runda a fost oprita
            was_round_stopped = false;
        }

        last_debounce_start = millis();           // reseteaza temporizatorul de debounce
    } else if (digitalRead(button_start_pin) == HIGH) {
        start_button_pressed = false;
    }

    // verifica apasarea butonului de dificultate
    if (digitalRead(button_difficulty_pin) == LOW && !difficulty_button_pressed && millis() - last_debounce_difficulty > debounce_delay) {
        difficulty_button_pressed = true;

        if (!is_round_active && !is_countdown_active) {
            change_difficulty();                  // schimba dificultatea daca nu e in runda
        }
        last_debounce_difficulty = millis();
    } else if (digitalRead(button_difficulty_pin) == HIGH) {
        difficulty_button_pressed = false;
    }
}

// verifica daca cuvantul introdus e corect
bool check_word(const String& word) {
    return word.equals(current_word);
}

// verifica daca cuvantul introdus e prefix al cuvantului curent
bool check_partial_word(const String& word) {
    return current_word.startsWith(word);
}

void loop() {
    check_buttons();                              // verifica butoanele

    if (is_countdown_active) {
        run_countdown();                          // gestioneaza numaratoarea inversa
    } else if (is_round_active) {
        unsigned long current_millis = millis();
        
        // verifica daca runda s-a incheiat
        if (current_millis - round_start_millis >= round_duration) {
            stop_round();
            was_round_stopped = true;
        } else {
            // verifica daca e timpul pentru un cuvant nou
            if (current_millis - previous_millis >= word_interval) {
                display_new_word();
                set_led_color(0, 255, 0);         // verde pentru cuvant nou
                previous_millis = current_millis;
            }

            // gestioneaza intrarile din serial
            if (Serial.available() > 0) {
                char input_char = Serial.read();
                
                // sterge ultimul caracter la backspace
                if (input_char == '\b' && input_word.length() > 0) {
                    input_word.remove(input_word.length() - 1);
                    Serial.print("\b \b");
                } else if (input_char == '\n') { // verifica la apasare enter
                    input_word.trim();
                    if (check_word(input_word)) {
                        Serial.println("corect");
                        words_correct++;
                        display_new_word();
                        set_led_color(0, 255, 0); // verde pentru corect
                        previous_millis = millis();
                    } else {
                        Serial.println("gresit");
                        set_led_color(255, 0, 0); // rosu pentru gresit
                    }
                    input_word = "";  
                } else {
                    input_word += input_char;
                    Serial.print(input_char);

                    // seteaza culoarea led-ului in functie de potrivire
                    if (check_partial_word(input_word)) {
                        set_led_color(0, 255, 0); // verde daca e prefix
                    } else {
                        set_led_color(255, 0, 0); // rosu daca nu e prefix
                    }
                }
            }
        }
    }
}
