/* 
 * File:   main.cpp
 * Author: robert.kozak
 *
 * Created on 18 gennaio 2023, 08:42
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>                      // Include le opzioni setw e setfill per cout
#include <limits>

using namespace std;

const int nDadi = 5;                    // Dadi giocati 
const int nFacce = 6;                   // Facce dei dadi
const int CATEGORIE = 13;               // Categorie del gioco
typedef int Tdadi[nDadi];
typedef int Ttabella[CATEGORIE];
typedef bool Tverifica[CATEGORIE];
Tdadi lancio;
Ttabella risultatoTabella;
Tverifica verificaCategorie;            
bool cambioDado = false;
bool continuaProgramma = true;
int menu;
int tiri = 3;
bool secondoTiro = false;               // Cambio dadi
bool confermaInvio = false;
bool inputValido = false;
bool confermaTiro = false;
int sceltaCategoria;                    // Selezione categoria
int risultatoTiro;
bool selezioneCategoria = true;
int somma = 0;
int bonus = 0;
int sommaValoreDadi = 0;
bool turno = true;
int casoParteSuperiore, casoParteMedia, casoParteInferiore;

void lancia();                          // Lancio dei dati
void stampa();                          // Stampa valori dei dadi
void mainMenu();                        // Menu 
void tabella();

void regole();
void mostraDado();

void parteSuperioreDado();
void parteMediaDado();
void parteInferioreDado();
void cambiaDado();

void pulisciSchermo();                  // Funzione per pulire lo schermo
void attendiInvio();                    
void presentazioneGioco();

void gioco();
void opzioniGioco();

void selezionaCategoria();
void categoria();

void resetTabella();
void resetCategorie();

void sommaTabella();
void bonusTabella();
void categoriaUno();
void categoriaDue();
void categoriaTre();
void categoriaQuattro();
void categoriaCinque();
void categoriaSei();
bool sonoOccupateLePrimeSeiCategorie();
void categoriaTreDiUnTipo();
void categoriaQuattroDiUnTipo();
void categoriaFullHouse();
void categoriaScalaMinima();
void categoriaScalaMassima();
void categoriaChance();
void categoriaYahtzee();

void verificaFinePartita();
void calcolaPunteggioFinale();


int main() {
    gioco();
    return 0;
}
    
void opzioniGioco() {
    presentazioneGioco();
    cout << "\nBenvenuto nello Yahtzee!\n\nScegli cosa vuoi fare:\n";
    cout << "1. Inizia una nuova partita\n2. Mostra regole\n0. Esci dal programma\nOpzione n^: ";
    cin >> menu;
    pulisciSchermo();
}

void gioco() {
    char uscita;

    opzioniGioco();
    while (menu != 0) {
        if (menu == 1) {                        // Nuova partita
            presentazioneGioco();
            resetTabella();                     // Imposta a 0 tutti i valori della teblla
            resetCategorie();                   // Imposta al valore VERO tutte le categorie
            cout << "\nScegli tra le seguenti opzioni:\n";
            while (continuaProgramma) {
                mainMenu();
                if (menu == 1 || menu == 2) {
                    cout << "\nPremi INVIO per andare avanti ";
                    cout << "\n";
                    attendiInvio();
                    pulisciSchermo();
                    presentazioneGioco();
                    cout << "\nScegli tra le seguenti opzioni:\n";
                }
            }
        }
        else if (menu == 2) {                   // Regole
            pulisciSchermo();
            presentazioneGioco();
            regole();
            cout << "\nGiocare una nuova partita? S/N ";
            cin >> uscita;
            pulisciSchermo();
            if (uscita == 'S' || uscita == 's')
                menu = 1;
            else {
                pulisciSchermo();
                opzioniGioco();
            }
        }
        else if (menu == 3) {
            pulisciSchermo();
            continuaProgramma = true;
            opzioniGioco();
        }
        else if (menu == 4) {
            tabella();
            calcolaPunteggioFinale();
            cout << "Premi ENTER per tornare al menu principale ";
            attendiInvio();
            pulisciSchermo();
            opzioniGioco();
        }
        else {                                  // Uscita
            cout << "\nUscita...";
            menu = 0;
        }
    }
}

void mainMenu() {
    char scelta;
    char nuovaPartita;

    cout << "1. Lancia dadi\n";
    cout << "2. Mostra i dadi\n";
    cout << "3. Mostra tabella\n";
    cout << "4. Cambia dadi\n";
    cout << "5. Seleziona categoria\n";
    cout << "6. Torna al menu\n";
    cout << "0. Esci dal programma\n";
    cout << "Opzione n^: ";
    cin >> scelta;
    switch (scelta) {
        case '1':
            if (tiri > 0 && turno) {             // Lancia il dado finch� non termina i turni
                lancia();                            
                tiri--;
                cambioDado = false;
                cout << "\nHai " << tiri << " tiri rimanenti.\n";
            }
            else if (selezioneCategoria != false) {
                cout << "\nPrima di iniziare un nuovo turno devi selezionare una categoria\n";
            }       
            else {
                turno = true;
                cout << "Nuovo turno!";
                tiri = 3;
                lancia();                             
                tiri--;
                cambioDado = false;
                cout << "\nHai " << tiri << " tiri rimanenti.\n";
            }
            break;
        case '2':
            stampa();
            break;
        case '3':
            tabella();
            break;
        case '4':
            if (turno == false) 
                cout << "\nNon puoi cambiare i dadi, devi iniziare un nuovo turno.\n";
            else if (tiri == 0)
                cout << "\nNon puoi cambiare i dadi, devi selezionare una categoria.\n";
            else {
                cambiaDado();
                cambioDado = true;
            }
            break;
        case '5':
            if (!cambioDado)
                selezionaCategoria();
            else 
                cout << "\nPer selezionare la categoria devi tirare i dadi da cambiare\n";
            break;
        case '6':
            cout << "Tornando al menu perderai i tuoi progressi, sei sicuro di voler continuare? S/N ";
            cin >> nuovaPartita;
            if (nuovaPartita == 'S' || nuovaPartita == 's') {
                confermaTiro = false;
                continuaProgramma = false;
                tiri = 3;
                menu = 3;
                pulisciSchermo();
            }
            break;
        case '0':
            cout << "\nUscita...\n";
            continuaProgramma = false;
            menu = 0;
            break;
        default:
            cout << "Sbagliato\n";
    }
    sommaValoreDadi = 0;
    verificaFinePartita();
}

void regole() {
    cout << "\nRegole:\n1. Ogni partita di Yahtzee inizia con un totale di tre lanci di cinque dadi.\n"
        << "2. Il giocatore ha l'opzione di scegliere quali dadi tenere dopo ogni lancio e quali rigiocare.\n"
        << "3. Il giocatore ottiene punti per ogni dado con lo stesso valore, ad esempio cinque\n"
        << "   dadi con il valore di sei.\n"
        << "4. Il giocatore sceglie di inserire i punti ottenuti in una delle categorie della\n"
        << "   tabella dei punteggi, ad esempio 'cinque dadi uguali' per ottenere un punteggio massimo di 50 punti.\n"
        << "5. Se il giocatore ottiene un punteggio in una categoria, questa viene occupata \n"
        << "   per il resto della partita.\n"
        << "6. Il giocatore ha un totale di tredici turni per ottenere il punteggio finale.\n"
        << "7. Alla fine dei tredici turni, il giocatore ottiene un bonus di 35 punti se ha ottenuto\n"
        << "   almeno 63 punti nelle categorie obbligatorie.\n"
        << "\nNOTA: queste regole sono una semplificazione del gioco dello Yahtzee e potrebbero variare\n"
        << "      in base alle regole specifiche di una versione specifica del gioco.\n";
}

void lancia() {                        
    srand(time(NULL));
    for (int i = 0; i < nDadi; i++) {
        if (secondoTiro) {
            if (lancio[i] == 0) {
                lancio[i] = rand() % nFacce + 1;
            }
            
        }
        else
            lancio[i] = rand()%nFacce+1;    // Assegnazione faccia al dado 
    }
    confermaTiro = true;
    secondoTiro = false;
}

void stampa() {
    if (confermaTiro == true) {
        cout << "\n\n";
        mostraDado();
        for (int i = 0; i < nDadi; i++)
            sommaValoreDadi += lancio[i];
    }
    else 
        cout << "\nNon sono stati lanciati i dati!\n";
}

void tabella() { 
    somma = 0;
    bonus = 0;
    sommaTabella();
    bonusTabella();
    
    // * Nome linea + allineamento(setw) | valore(4 spazi dedicati) *
    cout << "\n" << string(28, '*');
    cout << "\n* Uno" << setw(17) << "|" << setw(4) << risultatoTabella[0] << " *";
    cout << "\n* Due" << setw(17) << "|" << setw(4) << risultatoTabella[1] << " *";
    cout << "\n* Tre" << setw(17) << "|" << setw(4) << risultatoTabella[2] << " *";
    cout << "\n* Quattro" << setw(13) << "|" << setw(4) << risultatoTabella[3] << " *";
    cout << "\n* Cinque" << setw(14) << "|" << setw(4) << risultatoTabella[4] << " *";
    cout << "\n* Sei" << setw(17) << "|" << setw(4) << risultatoTabella[5] << " *";

    cout << "\n" << string(28, '*');
 
    cout << "\n* Somma" << setw(15) << "|" << setw(4) << somma << " *";
    cout << "\n* Bonus" << setw(15) << "|" << setw(4) << bonus << " *";

    cout << "\n" << string(28, '*');
    
    cout << "\n* Tre di un tipo" << setw(6) << "|" << setw(4) << risultatoTabella[6] << " *";
    cout << "\n* Quattro di un tipo" << setw(2) << "|" << setw(4) << risultatoTabella[7] << " *";
    cout << "\n* Full House" << setw(10) << "|" << setw(4) << risultatoTabella[8] << " *";
    cout << "\n* Scala minima" << setw(8) << "|" << setw(4) << risultatoTabella[9] << " *";
    cout << "\n* Scala massima" << setw(7) << "|" << setw(4) << risultatoTabella[10] << " *";
    cout << "\n* Chance" << setw(14) << "|" << setw(4) << risultatoTabella[11] << " *";
    cout << "\n* YAHTZEE" << setw(13) << "|" << setw(4) << risultatoTabella[12] << " *";

    cout << "\n" << string(28, '*') << "\n";
    //cout << "\n* TOTAL SCORE" << setw(9) << "|" << setw(4) << 0 << " *";
    //cout << "\n" << string(28, '*') << "\n";
}
    
void mostraDado() {
    /* Costruzione di un dado :
     _______
    | o   o | <-- parteSuperioreDado()
    |   o   | <-- parteMediaDado()
    | o   o | <-- parteInferioreDado()
    |_______|
    questo � un esempio, nel programma ho tolto l'indentatura per ridurre spazio */
    cout << "Dado 1:     Dado 2:     Dado 3:     Dado 4:     Dado5:\n";
    cout << " _______     _______     _______     _______     _______\n";
    casoParteSuperiore = 0;
    for (int i = 0; i < nDadi; i++) {
        casoParteSuperiore = lancio[i];
        parteSuperioreDado();
    }
    cout << "\n";
    
    casoParteMedia = 0;
    for (int i = 0; i < nDadi; i++) {
        casoParteMedia = lancio[i];
        parteMediaDado();
    }
    cout << "\n";
    
    casoParteInferiore = 0;
    for (int i = 0; i < nDadi; i++) {
        casoParteInferiore = lancio[i];
        parteInferioreDado();
    }
    cout << "\n";
    cout << "|_______|   |_______|   |_______|   |_______|   |_______|\n";
}

void parteSuperioreDado() {
    switch (casoParteSuperiore) {
        case 0:
            cout << "| Dado  |   "; break;
        case 1:
            cout << "|       |   "; break;
        case 2:
            cout << "| o     |   "; break;
        case 3:
            cout << "| o     |   "; break;
        case 4:
            cout << "| o   o |   "; break;
        case 5:
            cout << "| o   o |   "; break;
        case 6:
            cout << "| o   o |   "; break;
    }       
}

void parteMediaDado() {
    switch (casoParteMedia) {
        case 0:
            cout << "| da    |   "; break;
        case 1:
            cout << "|   o   |   "; break;
        case 2:
            cout << "|       |   "; break;
        case 3:
            cout << "|   o   |   "; break;
        case 4:
            cout << "|       |   "; break;
        case 5:
            cout << "|   o   |   "; break;
        case 6:
            cout << "| o   o |   "; break;
    }
}

void parteInferioreDado() {
    switch (casoParteInferiore) {
        case 0:
            cout << "| camb. |   "; break;
        case 1:
            cout << "|       |   "; break;
        case 2:
            cout << "|     o |   "; break;
        case 3:
            cout << "|     o |   "; break;
        case 4:
            cout << "| o   o |   "; break;
        case 5:
            cout << "| o   o |   "; break;
        case 6:
            cout << "| o   o |   "; break;
    }
}

void cambiaDado() {
    bool dado = true;
    secondoTiro = true;
    char risposta;
    char cambio;
    int sostituisci;

    if (confermaTiro == true) {
        stampa();
        cout << "\nSei sicuro di voler cambiare i dadi? S/N ";
        cin >> cambio;
        if (cambio == 'S' || cambio == 's') {
            while(dado) {
                cout << "\nQuale dado vuoi cambiare?\nIl dado numero: ";
                cin >> sostituisci;
                lancio[sostituisci - 1] = 0;                     // Imposta a 0 il dado che si cambia
                cout << "Vuoi cambiare un'altro dado? S/N ";
                cin >> risposta;
                if (risposta == 'N' || risposta == 'n') 
                    dado = false;
            }
        }
       
    }
    else
        cout << "\nNon sono stati lanciati i dati!\n";
}

void pulisciSchermo() {                 
    system("cls||clear");
}

void attendiInvio() {              
    //cin.ignore() permette di ignorare tutti i caratteri presenti nello stream
    //fino a quando non viene trovato un '\n'
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char invio;
    //invio = getchar();
    invio = getchar();
    while (invio != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        invio = getchar();
    }
}

void presentazioneGioco() {
    cout << string(70, '*') << "\n";
    cout << string(24, '*') << " GIOCO DELLO YAHTZEE " << string(25, '*') << "\n";
    cout << string(70, '*') << "\n";
}

void resetTabella() {
    for(int i = 0; i < CATEGORIE; i++) 
        risultatoTabella[i] = 0;
}

void resetCategorie() {         // Se la categoria ha valore FALSO non può ricevere più valori
    for(int i = 0; i < CATEGORIE; i++)
        verificaCategorie[i] = true;
}
        
void selezionaCategoria() {
    char domanda;
    if (confermaTiro) {
        if (turno) {
            selezioneCategoria = true;
            stampa();
            cout << "\nQuesti sono i tuoi dadi, sei sicuro di questa scelta? S/N ";
            cin >> domanda;
            if (domanda == 'S' || domanda == 's') {
                cout << "\nSeleziona una categoria:\n";
                cout << "1. Uno\n" << "2. Due\n" << "3. Tre\n" << "4. Quattro\n";
                cout << "5. Cinque\n" << "6. Sei\n" << "7. Tre di un tipo\n";
                cout << "8. Quattro di un tipo\n" << "9. Full House\n";
                cout << "10. Scala minima\n" << "11. Scala Massima\n";
                cout << "12. Chance\n" << "13. YAHTZEE\n" << "0. Esci\n";
                while(selezioneCategoria) {
                    cout << "Opzione n^: ";
                    cin >> sceltaCategoria;
                    categoria();
                }
            }
        }
        else 
            cout << "Categoria occupata devi tirare di nuovo per iniziare un nuovo turno\n";

    }
}

void categoria() {
    risultatoTiro = 0;
    switch(sceltaCategoria) {
        case 0:
            selezioneCategoria = false; break;
        case 1:
            categoriaUno(); break;
        case 2:
            categoriaDue(); break;
        case 3: 
            categoriaTre(); break;
        case 4:
            categoriaQuattro(); break;
        case 5:
            categoriaCinque(); break;
        case 6:
            categoriaSei(); break;
        case 7:
            categoriaTreDiUnTipo(); break;
        case 8:
            categoriaQuattroDiUnTipo(); break;
        case 9:
            categoriaFullHouse(); break;
        case 10:
            categoriaScalaMinima(); break;
        case 11:
            categoriaScalaMassima(); break;
        case 12:
            categoriaChance(); break;
        case 13:
            categoriaYahtzee(); break;
        default:
            cout << "Sbagliato\n";
    }
}

void categoriaUno() {
    if (verificaCategorie[0]) {
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == 1)
                risultatoTiro++;
        }
        if (risultatoTiro > 0) {
            verificaCategorie[0] = false;
            risultatoTabella[0] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Uno' con il valore " << risultatoTiro << "\n";
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaDue() {
    if (verificaCategorie[1]) {
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == 2)
                risultatoTiro += 2;
        }
        if (risultatoTiro > 0) {
            verificaCategorie[1] = false;
            risultatoTabella[1] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Due' con il valore " << risultatoTiro << "\n";
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaTre() {
    if (verificaCategorie[2]) {
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == 3)
                risultatoTiro += 3;
        }
        if (risultatoTiro > 0) {
            verificaCategorie[2] = false;
            risultatoTabella[2] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Tre' con il valore " << risultatoTiro << "\n";
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaQuattro() {
    if (verificaCategorie[3]) {
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == 4)
                risultatoTiro += 4;
        }
        if (risultatoTiro > 0) {
            verificaCategorie[3] = false;
            risultatoTabella[3] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Quattro' con il valore " << risultatoTiro << "\n";
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaCinque() {
    if (verificaCategorie[4]) {
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == 5)
                risultatoTiro += 5;
        }
        if (risultatoTiro > 0) {
            verificaCategorie[4] = false;
            risultatoTabella[4] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Cinque' con il valore " << risultatoTiro << "\n";
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaSei() {
    if (verificaCategorie[5]) {
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == 6)
                risultatoTiro += 6;
        }
        if (risultatoTiro > 0) {
            verificaCategorie[5] = false;
            risultatoTabella[5] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Sei' con il valore " << risultatoTiro << "\n";
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

bool sonoOccupateLePrimeSeiCategorie() {
    if (verificaCategorie[0] == false && verificaCategorie[1] == false && verificaCategorie[2] == false
        && verificaCategorie[3] == false && verificaCategorie[4] == false && verificaCategorie[5] == false)
        return true;
    else
        return false;
}

void categoriaTreDiUnTipo() {
    if (verificaCategorie[6]) {
        for (int i = 1; i <= 6; i++) {
            int k = 0;
            for (int j = 0; j < nDadi; j++) {
                if (lancio[j] == i) 
                    k++;
            }
            if (k >= 3) {
                risultatoTiro = i * 3;
            }
        }
        if (risultatoTiro > 0) {
            risultatoTiro = risultatoTiro + (sommaValoreDadi - risultatoTiro);
            verificaCategorie[6] = false;
            risultatoTabella[6] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Tre di un tipo' con il valore " << risultatoTiro << "\n";
        }
        else if (sonoOccupateLePrimeSeiCategorie()) {
            cout << "Le prime sei categorie sono occupate e non hai una combinazione giusta quindi il valore viene impostato a 0\n";
            verificaCategorie[6] = false;
            selezioneCategoria = false;
            turno = false;
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaQuattroDiUnTipo() {
    if (verificaCategorie[7]) {
        for (int i = 1; i <= 6; i++) {
            int k = 0;
            for (int j = 0; j < nDadi; j++) {
                if (lancio[j] == i)
                    k++;
            }
            if (k >= 4) {
                risultatoTiro = i * 4;
            }
        }
        if (risultatoTiro > 0) {
            risultatoTiro = risultatoTiro + (sommaValoreDadi - risultatoTiro);
            verificaCategorie[7] = false;
            risultatoTabella[7] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Quattro di un tipo' con il valore " << risultatoTiro << "\n";
        }
        else if (sonoOccupateLePrimeSeiCategorie()) {
            cout << "Le prime sei categorie sono occupate e non hai una combinazione giusta quindi il valore viene impostato a 0\n";
            verificaCategorie[7] = false;
            selezioneCategoria = false;
            turno = false;
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaFullHouse() {
    if (verificaCategorie[8]) {
        int nDue = 0, nTre = 0;
        for (int i = 1; i <= 6; i++) {
            int k = 0;
            for (int j = 0; j < nDadi; j++) {
                if (lancio[j] == i)
                    k++;
            }
            if (k == 2) {
                nDue = i;
            }
            if (k == 3) {
                nTre = i;
            }
        }
        if (nDue > 0 && nTre > 0) {
            risultatoTiro = 25;
            verificaCategorie[8] = false;
            risultatoTabella[8] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Full House' con il valore " << risultatoTiro << "\n";
        }
        else if (sonoOccupateLePrimeSeiCategorie()) {
            cout << "Le prime sei categorie sono occupate e non hai una combinazione giusta quindi il valore viene impostato a 0\n";
            verificaCategorie[8] = false;
            selezioneCategoria = false;
            turno = false;
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaScalaMinima() {
    if (verificaCategorie[9]) {
        int nSequenza = 0;
        for (int i = 1; i <= 3; i++) {
            nSequenza = 0;
            for (int j = i; j < i + 4; j++) {
                int k = 0;
                for (int l = 0; l < nDadi; l++) {
                    if (lancio[l] == j)
                        k++;
                }
                if (k >= 1)
                    nSequenza++;
            }
            if (nSequenza == 4) {
                risultatoTiro = 30;
            }
        }
        if (risultatoTiro > 0) {
            verificaCategorie[9] = false;
            risultatoTabella[9] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Scala minima' con il valore " << risultatoTiro << "\n";
        }
        else if (sonoOccupateLePrimeSeiCategorie()) {
            cout << "Le prime sei categorie sono occupate e non hai una combinazione giusta quindi il valore viene impostato a 0\n";
            verificaCategorie[9] = false;
            selezioneCategoria = false;
            turno = false;
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaScalaMassima() {
    if (verificaCategorie[10]) {
        for (int i = 0; i <= nDadi - 5; i++) {
            int k = 1;
            for (int j = i; j < i + 5; j++) {
                if (lancio[j] == lancio[j + 1] - 1)
                    k++;
            }
            if (k == 5) {
                risultatoTiro = 40;
            }
        }
        if (risultatoTiro > 0) {
            verificaCategorie[10] = false;
            risultatoTabella[10] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Scala massima' con il valore " << risultatoTiro << "\n";
        }
        else if (sonoOccupateLePrimeSeiCategorie()) {
            cout << "Le prime sei categorie sono occupate e non hai una combinazione giusta quindi il valore viene impostato a 0\n";
            verificaCategorie[10] = false;
            selezioneCategoria = false;
            turno = false;
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaChance() {
    if (verificaCategorie[11]) {
        for (int i = 0; i < nDadi; i++) {
            risultatoTiro += lancio[i];
        }
        verificaCategorie[11] = false;
        risultatoTabella[11] = risultatoTiro;
        selezioneCategoria = false;
        turno = false;
        cout << "Hai occupato la categoria 'Chance' con il valore " << risultatoTiro << "\n";
    }
    else
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
}

void categoriaYahtzee() {
    if (verificaCategorie[12]) {
        int k = 0;
        for (int i = 0; i < nDadi; i++) {
            if (lancio[i] == lancio[0])
                k++;
        }
        if (k == nDadi) {
            risultatoTiro = 50;
            verificaCategorie[12] = false;
            risultatoTabella[12] = risultatoTiro;
            selezioneCategoria = false;
            turno = false;
            cout << "Hai occupato la categoria 'Yahtzee' con il valore " << risultatoTiro << "\n";
        }
        else if (sonoOccupateLePrimeSeiCategorie()) {
            cout << "Le prime sei categorie sono occupate e non hai una combinazione giusta quindi il valore viene impostato a 0\n";
            verificaCategorie[12] = false;
            selezioneCategoria = false;
            turno = false;
        }
        else
            cout << "Non hai i valori adatti per questa categoria, scegline un'altra\n";
    }
    else {
        cout << "\nLa categoria contiene già un valore, scegline un'altra\n\n";
    }
}

void verificaFinePartita() {
    int verifica = 0;
    for (int i = 0; i < 13; i++) {
        if (!verificaCategorie[i])
            verifica++;
    }
    if (verifica == 13) {
        cout << "\nHai occupato tutte le categorie!\n";
        cout << "Complimenti hai finito il gioco!\n";
        menu = 4;
        continuaProgramma = false;
    }
}

void calcolaPunteggioFinale() {
    int sommaCategorie = 0;
    for (int i = 0; i < 13; i++) {
        sommaCategorie += risultatoTabella[i];
    }

    cout << "Punteggio finale: " << sommaCategorie + bonus << "\n";
}

void sommaTabella() {
    for (int i = 0; i < 6; i++)
        somma += risultatoTabella[i];
}

void bonusTabella() {
    int totale = 0;
    for(int i = 0; i <= 5; i++)
        totale += risultatoTabella[i];
    if (totale >= 63) {
        bonus = 35;
    }
    else
        bonus = 0;
}
