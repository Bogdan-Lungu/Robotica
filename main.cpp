// Definim pinii
const int led1 = 10;  // LED 25%
const int led2 = 9;   // LED 50%
const int led3 = 8;   // LED 75%
const int led4 = 7;   // LED 100%
const int ledRGB_R = 6;  // LED RGB rosu
const int ledRGB_G = 5;  // LED RGB verde
const int buttonStart = 3; // buton start
const int buttonStop = 2;  // buton stop

// variabile pentru temporizare si starea de incarcare
unsigned long lastUpdate = 0;      // timpul ultimei actualizari a ledurilor
unsigned long interval = 500;      // intervalul de clipire (500ms)
int nivel = 1;                     // nivelul curent de incarcare (1 = LED 25%)
bool isCharging = false;           // indicator daca incarcarea este in desfasurare
int blinkCount = 0;                // contor pentru cate ori a clipit ledul curent
bool finalBlink = false;           // indicator pentru faza finala de clipire a tuturor ledurilor
unsigned long buttonStopPressedTime = 0; // momentul cand butonul stop a fost apasat
bool stopButtonHeld = false;       // indicator pentru apasarea lunga a butonului stop

void setup() {
  // setam pinii ledurilor ca iesiri
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(ledRGB_R, OUTPUT);
  pinMode(ledRGB_G, OUTPUT);
  pinMode(buttonStart, INPUT);  // setam pinul butonului start ca intrare
  pinMode(buttonStop, INPUT);   // setam pinul butonului stop ca intrare

  // station incepe libera (led verde aprins)
  digitalWrite(ledRGB_G, HIGH);
  digitalWrite(ledRGB_R, LOW);

  // toate ledurile sunt stinse initial
  resetAllLEDs();
}

void loop() {
  // citim starea butoanelor
  int buttonStateStart = digitalRead(buttonStart);  // citim butonul start
  int buttonStateStop = digitalRead(buttonStop);    // citim butonul stop
  unsigned long currentMillis = millis();           // timpul curent

  // daca butonul start este apasat si nu se incarca deja, incepem incarcarea
  if (buttonStateStart == LOW && !isCharging) {
    startCharging();
  }

  // verificam daca butonul stop este apasat si se incarca sistemul
  if (buttonStateStop == LOW && isCharging) {
    if (!stopButtonHeld) {
      // daca nu este deja apasat, memoram timpul apasarii
      buttonStopPressedTime = currentMillis;
      stopButtonHeld = true;
    } else if (currentMillis - buttonStopPressedTime >= 1000) {
      // daca butonul este tinut apasat mai mult de 1 secunda, declansam oprirea de urgenta
      emergencyStop();
      stopButtonHeld = false;  // resetam indicatorul de apasare
    }
  } else {
    // daca butonul nu este apasat, resetam starea butonului stop
    stopButtonHeld = false;
  }

  // gestionam procesul de clipire si aprindere a ledurilor daca incarcarea a inceput
  if (isCharging) {
    if (currentMillis - lastUpdate >= interval) {
      lastUpdate = currentMillis;  // actualizam timpul curent

      if (!finalBlink) {
        if (blinkCount < 4) {  // ledul curent clipeste de doua ori (4 schimbari de stare)
          blinkLED(nivel);
          blinkCount++;
        } else {
          // dupa ce ledul a clipit de doua ori, ramane aprins si trecem la urmatorul led
          setLEDOn(nivel);
          nivel++;
          blinkCount = 0;

          // daca toate ledurile au fost aprinse, trecem la faza finala
          if (nivel > 4) {
            finalBlink = true;
            blinkCount = 0;  // resetam pentru faza finala
          }
        }
      } else {
        // faza finala: toate ledurile clipesc de 3 ori
        if (blinkCount < 6) {  // 6 schimbari de stare pentru 3 clipiri
          blinkAllLEDs();
          blinkCount++;
        } else {
          // dupa ce toate ledurile au clipit de 3 ori, le stingem si terminam procesul
          resetAllLEDs();
          digitalWrite(ledRGB_G, HIGH);  // station devine libera (led verde aprins)
          digitalWrite(ledRGB_R, LOW);   // stingem ledul rosu
          isCharging = false;            // incarcarea s-a terminat
          finalBlink = false;
          blinkCount = 0;
        }
      }
    }
  }
}

void startCharging() {
  // pornim incarcarea
  isCharging = true;            // setam flag-ul de incarcare
  nivel = 1;                    // incepem cu primul led
  lastUpdate = millis();         // initializam timpul curent
  digitalWrite(ledRGB_G, LOW);   // stingem ledul verde (station ocupata)
  digitalWrite(ledRGB_R, HIGH);  // aprindem ledul rosu (station ocupata)
}

void blinkLED(int level) {
  // functie pentru a face ledul curent sa clipeasca
  switch (level) {
    case 1:
      toggleLED(led1);  // comutam starea led1
      break;
    case 2:
      toggleLED(led2);  // comutam starea led2
      break;
    case 3:
      toggleLED(led3);  // comutam starea led3
      break;
    case 4:
      toggleLED(led4);  // comutam starea led4
      break;
  }
}

void blinkAllLEDs() {
  // functie pentru a face toate ledurile sa clipeasca
  toggleLED(led1);
  toggleLED(led2);
  toggleLED(led3);
  toggleLED(led4);
}

void toggleLED(int ledPin) {
  // inversam starea ledului curent (aprindere/stingere)
  int state = digitalRead(ledPin);
  digitalWrite(ledPin, !state);  // comutam starea ledului
}

void setLEDOn(int level) {
  // functie pentru a aprinde ledul curent dupa ce a clipit de 2 ori
  switch (level) {
    case 1:
      digitalWrite(led1, HIGH);  // aprindem led1
      break;
    case 2:
      digitalWrite(led2, HIGH);  // aprindem led2
      break;
    case 3:
      digitalWrite(led3, HIGH);  // aprindem led3
      break;
    case 4:
      digitalWrite(led4, HIGH);  // aprindem led4
      break;
  }
}

void resetAllLEDs() {
  // stingem toate ledurile normale
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  // resetam variabilele pentru o noua incarcare
  nivel = 1;           // revenim la primul led
  blinkCount = 0;      // resetam contorul de clipiri
  isCharging = false;  // oprirea procesului de incarcare
  finalBlink = false;  // iesirea din faza finala de clipire
}

void emergencyStop() {
  // functie care opreste totul si reseteaza sistemul
  isCharging = false;          // oprirea procesului de incarcare
  blinkCount = 0;              // resetam contorul de clipiri
  finalBlink = false;          // resetam faza finala
  nivel = 1;                   // resetam nivelul de incarcare
  resetAllLEDs();              // stingem toate ledurile

  // facem ledurile sa clipeasca de 3 ori
  for (int i = 0; i < 6; i++) {  // 6 schimbari de stare pentru 3 clipiri
    blinkAllLEDs();
    delay(500);  // pauza intre clipiri
  }

  resetAllLEDs();              // stingem toate ledurile
  digitalWrite(ledRGB_G, HIGH); // led verde aprins (station libera)
  digitalWrite(ledRGB_R, LOW);  // led rosu stins (station libera)
}
