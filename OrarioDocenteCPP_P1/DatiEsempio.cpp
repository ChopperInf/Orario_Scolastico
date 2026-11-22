#include "DatiEsempio.h"
#include <string>
bool DatiEsempio::Carica(Orario& orario) {
    std::string materie[7] = {"Matematica", "Informatica", "Italiano", "Inglese",
                              "Sistemi", "TPS", "Storia"};
    std::string docenti[7] = {"Rossi", "Bianchi", "Verdi", "Neri",
                              "Gialli", "Conti", "Riva"};
    for (int g = 0; g < 5; g++) {
        int n = (g == 4) ? 6 : 7;
        for (int o = 0; o < n; o++) {
            int i = (g + o) % 7;
            Tessera* t = new Tessera(materie[i], docenti[i], "A" + std::to_string(o + 1));
            if (!orario.Set(Posizione(g, o), t)) {
                delete t; // Set non ha acquisito la tessera.
                return false;
            }
        }
    }
    return true;
}

bool DatiEsempio::CaricaAule(ElencoAule& elenco)
{
    if (!elenco.Aggiungi(Aula("INF1", "Laboratorio", "Lotto 2"))) {
        return false;
    }

    if (!elenco.Aggiungi(Aula("A1", "Aula", "Lotto 1"))) {
        return false;
    }

    if (!elenco.Aggiungi(Aula("A5", "Laboratorio", "Lotto 3"))) {
        return false;
    }

    return true;
}
