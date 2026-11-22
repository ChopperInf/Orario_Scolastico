#include "InterfacciaConsole.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include "ElencoAule.h"
using namespace std;

InterfacciaConsole::InterfacciaConsole(Orario& orario, ElencoAule& elencoAule) : orario(orario), elencoAule(elencoAule) {}

int InterfacciaConsole::LeggiIntero(string messaggio, int minimo, int massimo) {
    int valore;
    while (true) {
        cout << messaggio;
        if (cin >> valore && valore >= minimo && valore <= massimo) return valore;
        cout << "Valore non valido. Inserisci un numero tra " << minimo
             << " e " << massimo << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
Posizione InterfacciaConsole::LeggiPosizione() {
    int g = LeggiIntero("Giorno (1=Lun, 2=Mar, 3=Mer, 4=Gio, 5=Ven): ", 1, 5);
    int o = LeggiIntero("Ora (1-8): ", 1, 8);
    return Posizione(g - 1, o - 1);
}
void InterfacciaConsole::VisualizzaOrario() {
    string giorni[5] = {"Lun", "Mar", "Mer", "Gio", "Ven"};
    cout << "\nORARIO SETTIMANALE DELLA CLASSE\n" << left << setw(6) << "Ora";
    for (int g = 0; g < 5; g++) cout << setw(18) << giorni[g];
    cout << "\n";
    for (int o = 0; o < 8; o++) {
        cout << left << setw(6) << o + 1;
        for (int g = 0; g < 5; g++) {
            Tessera* t = orario.Get(Posizione(g, o));
            cout << setw(18) << (t == nullptr ? "---" : t->GetMateria());
        }
        cout << "\n";
    }
    cout << "\nPer visualizzare docente e aula, scegli l'opzione 2.\n";
}
void InterfacciaConsole::VisualizzaTessera() {
    cout << "\nCONSULTA UNA CELLA\n";
    Tessera* t = orario.Get(LeggiPosizione());
    if (t == nullptr) cout << "La cella e' vuota.\n";
    else {
        cout << "Materia: " << t->GetMateria() << "\n";
        cout << "Docente: " << t->GetDocente() << "\n";
        cout << "Aula: " << t->GetAula() << "\n";
    }
}
void InterfacciaConsole::RichiediScambio() {
    cout << "\nSCAMBIO DI DUE CELLE\nPrima posizione:\n";
    Posizione a = LeggiPosizione();
    cout << "Seconda posizione:\n";
    Posizione b = LeggiPosizione();
    if (a.GetGiorno() == b.GetGiorno() && a.GetOra() == b.GetOra()) {
        cout << "Hai selezionato due volte la stessa cella.\n";
        return;
    }
    if (motore.Scambia(orario, a, b)) cout << "Scambio autorizzato.\n";
    else cout << "Scambio rifiutato: si creerebbe un buco o l'orario non e' valido.\n";
}
void InterfacciaConsole::VerificaOrario() {
    cout << "\nVERIFICA DELL'ORARIO\n";
    if (validatore.SenzaBuchi(orario)) cout << "Orario valido: non ci sono buchi.\n";
    else cout << "Orario non valido: ci sono ore vuote prima di altre lezioni.\n";
}
void InterfacciaConsole::MostraMenu() {
    cout << "\n================================\n       ORARIO CLASSE\n"
        << "================================\n" << endl;
    cout << "1. Visualizza orario" << endl;
    cout << "2. Visualizza tessera" << endl;
    cout << "3. Scambia due tessere" << endl;
    cout << "4. Verifica validita' dell'orario" << endl;
    cout << "5. Visualizza elenco aule" << endl;
    cout << "6. Cerca aula" << endl;
    cout << "7. Aggiungi un'aula" << endl;
    cout << "0. Esci" << endl;
}
void InterfacciaConsole::visualizzaAule(){
    
    int numAule = elencoAule.GetNumeroAule();

    if (numAule == 0) {
        cout << "Nessuna aula presente nell'archivio "<< endl;
        return;
    }

    for (int i = 0; i < numAule; i++) {
        const Aula* aula = elencoAule.Get(i);
        if (aula != nullptr) {
            cout << "Sigla: " << aula->getSigla() << endl; 
            cout << "Tipologia: " << aula->getTipologia() << endl;
            cout << " Edigicio: " << aula->getEdificio() << endl;
        }
    }
}
void InterfacciaConsole::cercaAula()
{
    string sigla;
    cout << "Inserisci la sigla dell'aula da cercare: ";
    cin >> sigla;

    int indice = elencoAule.Cerca(sigla);
    if (indice == -1) {
        cout << "Aula non trovata ";
    }
    else {
        const Aula* aula = elencoAule.Get(indice);
        if (aula != nullptr) {
            cout << "Sigla: " << aula->getSigla() << endl;
            cout << "Tipologia: " << aula->getTipologia() << endl;
            cout << " Edificio: " << aula->getEdificio() << endl;
        }
    }
}
void InterfacciaConsole::aggiungiAula()
{
    string sigla;
    cout << "Inserisci la sigla della nuova aula: ";
    cin >> sigla;

    cout << "Scegli la tipologia: " << endl;
    cout << "1. Aula " << endl;
    cout << "2. Laboratorio" << endl;
    cout << "3. Aula DADA" <<endl;
    int sceltaTip = LeggiIntero("Scelta (1-3): ", 1, 3);

    string tipologia;
    if (sceltaTip == 1) 
    {
        tipologia = "Aula";
    }
    
    else if (sceltaTip == 2)
    {
        tipologia = "Laboratorio";
    }
    else 
    {
        tipologia = "Aula DADA";
    }

    cout << "Scegli l'edificio: " << endl;
    cout << "1. Lotto 1 " << endl;
    cout << "2. Lotto 2" << endl;
    cout << "3. Lotto 3 " << endl;
    int sceltaEd = LeggiIntero("Scelta (1-3): ", 1, 3);

    string edificio;
    if (sceltaEd == 1) 
    {
        edificio = "Lotto 1";
    }
    else if (sceltaEd == 2)
    {
        edificio = "Lotto 2";
    }
    else 
    {
        edificio = "Lotto 3";
    }

    Aula nuovaAula(sigla, tipologia, edificio);

    elencoAule.Aggiungi(nuovaAula);
    cout << "Nuova aula aggiunta" <<endl;
}
void InterfacciaConsole::Esegui() {
    int scelta;
    do {
        MostraMenu();
        scelta = LeggiIntero("Scelta: ", 0, 7);
        switch (scelta) {
        case 1: VisualizzaOrario(); break;
        case 2: VisualizzaTessera(); break;
        case 3: RichiediScambio(); break;
        case 4: VerificaOrario(); break;
        case 5: visualizzaAule(); break;
        case 6: cercaAula(); break;
        case 7: aggiungiAula(); break;

        case 0: cout << "Chiusura del programma.\n"; break;
        }
    } while (scelta != 0);
}
