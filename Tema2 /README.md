# TypeRacer - Arduino Game

Proiect realizat în cadrul cursului de Robotică

Acest proiect este un joc asemănător cu TypeRacer, creat folosind un microcontroller Arduino UNO, LED RGB, butoane și alte componente electronice. Scopul jocului este de a tasta corect cuvintele afișate în terminal, fiecare rundă având un timp limitat, iar dificultatea poate fi ajustată cu ajutorul butoanelor.

## Cerințele proiectului

1. **Descrierea task-ului / Cerințele:**  
   - **LED RGB**: Funcționează ca un indicator de stare. Culoarea LED-ului indică dacă utilizatorul a introdus cuvântul corect (verde), dacă a făcut o greșeală (roșu) sau dacă jocul este în repaus (alb).
   - **Butonul Start/Stop**: Pornește și oprește rundele de joc. La pornire, inițiază o numărătoare inversă de 3 secunde înainte de începerea rundei. În timpul jocului, o apăsare oprește imediat runda.
   - **Butonul de Dificultate**: Permite selecția dintre modurile Easy, Medium și Hard. Fiecare apăsare ciclică schimbă dificultatea și trimite un mesaj serial cu noul mod selectat.
   - **Generarea cuvintelor**: Un dicționar de cuvinte afișate aleatoriu în terminal. Dacă utilizatorul tastează corect, apare un nou cuvânt; dacă greșește, LED-ul devine roșu, iar un alt cuvânt este afișat după o perioadă.
   - **Durata rundei**: Fiecare rundă durează 30 de secunde, iar la final se afișează numărul de cuvinte corecte.

2. **Componentele utilizate:**
   - **1x LED RGB**: Indicator de stare (alb pentru repaus, verde pentru corect, roșu pentru greșeală).
   - **2x Butoane**:  
     - **Buton Start/Stop** pentru inițierea și oprirea rundelor.
     - **Buton Dificultate** pentru schimbarea modului de joc între Easy, Medium și Hard.
   - **5x Rezistoare**: 3 rezistoare de 220/330 ohm pentru LED RGB și 2 de 1K ohm pentru butoane.
   - **Breadboard**: Platformă pentru conectarea componentelor.
   - **Fire de conexiune**: Pentru conectarea circuitului.

3. **Imagini cu montajul fizic:**  
   Inserate imagini cu circuitul și setup-ul fizic.

   ![Setup fizic - imagine 1](https://github.com/user-attachments/assets/example_image1.png)
   ![Setup fizic - imagine 2](https://github.com/user-attachments/assets/example_image2.png)

4. **Link/Video cu funcționalitatea montajului fizic:**  
   [Video Funcționalitate](https://youtu.be/example_video_link)

5. **Schema electrică (realizată în Wokwi, TinkerCAD etc.):**  
   <img width="731" alt="image" src="https://github.com/user-attachments/assets/bc9af654-7275-4183-b234-75951467c43c">

Acest setup simulează un joc de tip TypeRacer, unde utilizatorul poate să selecteze dificultatea, să inițieze jocul și să fie ghidat de feedback-ul vizual al LED-ului RGB pentru a vedea dacă introduce cuvintele corect sau greșit.
