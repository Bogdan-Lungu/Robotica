# Quicktime - Joc de Reflexe cu Arduino

Proiect realizat în cadrul cursului de Robotică

Acest proiect este un joc de reflexe competitiv pentru doi jucători, creat folosind microcontrollere Arduino UNO, LED-uri RGB, butoane, un ecran LCD, și alte componente electronice. Scopul jocului este ca fiecare jucător să reacționeze cât mai rapid la semnalele luminoase și să apese butonul corect pentru a obține puncte. Jucătorul cu cel mai mare punctaj la finalul jocului este declarat câștigător.

## Cerințele proiectului

1. **Descrierea task-ului / Cerințele:**  
   - **Joc de Reflexe Competitiv:** Fiecare jucător are trei butoane, fiecare asociat unui LED de o culoare diferită. În plus, fiecare jucător are un LED RGB care afișează culoarea pe care trebuie să o recunoască și să apese rapid butonul corespunzător.
   - **SPI și Control Dual-Arduino:** Proiectul necesită două plăci Arduino UNO care comunică prin SPI. Arduino-ul Master gestionează ecranul LCD, servomotorul și starea jocului, în timp ce Arduino-ul Slave controlează LED-urile și butoanele.
   - **Buton de Start:** Există mai multe opțiuni pentru pornirea jocului: prin apăsarea oricărui buton, prin desemnarea unui buton anume, sau prin adăugarea unui buton suplimentar.
   - **LED-uri RGB și LED-uri Individuale:** LED-urile RGB afișează culoarea pe care jucătorul trebuie să o recunoască și să apese. LED-urile individuale luminează permanent pentru a indica ce culoare corespunde fiecărui buton.
   - **Punctaj:** Jocul calculează punctajul fiecărui jucător în funcție de rapiditatea cu care apasă butonul corect. Ecranul LCD afișează scorul actualizat în timp real.
   - **Servomotor pentru Timp:** Servomotorul indică progresul jocului printr-o rotație completă care marchează sfârșitul jocului. Viteza de rotație poate fi ajustată pentru a controla durata totală a jocului.
   - **Finalizarea Jocului:** La sfârșit, ecranul LCD afișează numele câștigătorului și scorul final.

2. **Componentele utilizate:**
   - **6x LED-uri Individuale:** Grupate în câte 3 pentru fiecare jucător, fiecare LED având o culoare diferită.
   - **2x LED RGB:** Un LED pentru fiecare jucător, utilizat pentru afișarea semnalelor de culoare pe parcursul rundelor.
   - **1x LCD:** Ecran pentru afișarea punctajelor și a mesajelor jocului.
   - **1x Buzzer:** Pentru semnalizarea răspunsurilor corecte/greșite și alte sunete de joc.
   - **1x Potențiometru:** Pentru ajustarea contrastului LCD-ului.
   - **6x Butoane:** 3 butoane pentru fiecare jucător, fiecare asociat unui LED de o anumită culoare.
   - **1x Buton de Start:** Dedicat pentru inițierea jocului.
   - **1x Servomotor:** Indică progresul jocului prin rotație.
   - **2x Arduino UNO:** Pentru gestionarea componentelor și logica jocului.
   - **2x Breadboard:** Unul mare și unul mic pentru montarea componentelor electronice.
   - **8x Rezistoare de 1k Ohmi:** Pentru butoane.
   - **1x Rezistor de 100 Ohmi:** Pentru buzzer.
   - **13x Rezistoare de 220 Ohmi:** 6 pentru LED-urile normale, 6 pentru LED-urile RGB și 1 pentru LCD.
   - **Fire de legătură:** Pentru conexiunile necesare între componente.


3. **Imagini cu montajul fizic:**  
   (Inserați imagini ale setup-ului fizic cu detalii clare ale componentelor conectate)

   ![Imagine 1](https://github.com/user-attachments/assets/example1)
   ![Imagine 2](https://github.com/user-attachments/assets/example2)

4. **Link/Video cu funcționalitatea montajului fizic:**  
   (Adăugați link-ul către un video care arată cum funcționează montajul)

   https://youtu.be/exemplu-video

5. **Schema electrică (realizată în Wokwi, TinkerCAD etc.):**  
   ![Schema Electrică](https://github.com/user-attachments/assets/example-schema)

   **Descriere schemă:** Schema electrică ilustrează conexiunile dintre componente: LED-urile, butoanele, LCD-ul, servomotorul și cele două plăci Arduino UNO.

## Funcționalități Extra (Bonus)

- **Animație pe LCD:** Jocul poate începe cu o animație de bun venit afișată pe ecranul LCD.
- **Buzzer pentru Sunete:** Buzzerul poate semnaliza răspunsurile corecte sau greșite, începutul și finalul jocului sau poate reda un theme song.
- **Personalizare Jucători:** Jucătorii pot introduce numele folosind o interfață simplă bazată pe butoane sau prin comunicare serială.

Această documentație oferă toate informațiile esențiale pentru înțelegerea și reproducerea proiectului.

