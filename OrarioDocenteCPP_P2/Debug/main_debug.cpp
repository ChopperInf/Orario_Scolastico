#include <iostream>
#include "../Model/Tessera.h"
#include "../Model/TesseraAula.h"
#include "../Model/TesseraLaboratorio.h"
#include "../Engine/Vincolo.h"
#include "../Engine/VincoloSenzaBuchi.h"
#include "../Engine/VincoloMaxOreGiornaliere.h"
#include "../Model/Orario.h"

int main() {
    std::cout << "=== PARTE A: MATRICE 2x2 DI TESSERE ===\n";
    Tessera* matrice[2][2] = { {nullptr, nullptr}, {nullptr, nullptr} };

    std::cout << "\nCreazione delle tessere:\n";
    matrice[0][0] = new Tessera("Matematica", "4AI", "A1");
    matrice[0][1] = new TesseraAula("Italiano", "4AI", "A2");
    matrice[1][0] = new TesseraLaboratorio("Informatica", "4AI", "LAB-1",
                                          "Informatica", "Rossi", nullptr);
    matrice[1][1] = new TesseraLaboratorio("Informatica", "4BI", "LAB-2",
                                          "Informatica", "Bianchi",
                                          new DotazioneLabInformatica(
                                              {"PC docente", "PC studenti"}, true));

    std::cout << "\nDescrizioni attraverso Tessera*:\n";
    for (int riga = 0; riga < 2; riga++)
        for (int colonna = 0; colonna < 2; colonna++)
            std::cout << "[" << riga << "][" << colonna << "] "
                      << matrice[riga][colonna]->GetDescrizione() << "\n";

    std::cout << "\nDistruzione delle tessere:\n";
    for (int riga = 0; riga < 2; riga++)
        for (int colonna = 0; colonna < 2; colonna++) {
            delete matrice[riga][colonna];
            matrice[riga][colonna] = nullptr;
        }

    std::cout << "\n=== PARTE B: VETTORE DI VINCOLI ===\n";
    Orario orario; // Vuoto: rispetta entrambi i vincoli.
    Vincolo* vincoli[2];
    std::cout << "\nCreazione dei vincoli:\n";
    vincoli[0] = new VincoloSenzaBuchi();
    vincoli[1] = new VincoloMaxOreGiornaliere(4);

    std::cout << "\nVerifica attraverso Vincolo*:\n";
    for (int i = 0; i < 2; i++)
        std::cout << vincoli[i]->GetMessaggio() << ": "
                  << (vincoli[i]->Verifica(orario) ? "rispettato" : "violato") << "\n";

    std::cout << "\nDistruzione dei vincoli:\n";
    for (int i = 0; i < 2; i++) {
        delete vincoli[i];
        vincoli[i] = nullptr;
    }
    std::cout << "\nFine esercitazione.\n";
    return 0;
}
