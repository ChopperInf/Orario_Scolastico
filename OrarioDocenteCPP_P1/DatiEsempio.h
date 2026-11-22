#pragma once
#include "Model/Orario.h"
#include "ElencoAule.h"

class DatiEsempio {
public:
    static bool Carica(Orario& orario);
    static bool CaricaAule(ElencoAule& elenco);
};
