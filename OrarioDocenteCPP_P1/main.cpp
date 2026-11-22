#include <iostream>
#include "Model/Orario.h"
#include "DatiEsempio.h"
#include "InterfacciaConsole.h"
#include "ElencoAule.h"
int main() {

    Orario orario;
    if (!DatiEsempio::Carica(orario)) return 1;

    ElencoAule elencoAule;
    if (!DatiEsempio::CaricaAule(elencoAule)) return 1;

    InterfacciaConsole interfaccia(orario, elencoAule);
    interfaccia.Esegui();

    return 0;
}
