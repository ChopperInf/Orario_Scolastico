#pragma once
#include "../Model/Posizione.h"

// Una richiesta in attesa non e' ancora una modifica dell'orario.
class RichiestaScambio {
private:
    Posizione prima;
    Posizione seconda;
public:
    RichiestaScambio(Posizione prima, Posizione seconda)
        : prima(prima), seconda(seconda) {}
    Posizione GetPrima() const { return prima; }
    Posizione GetSeconda() const { return seconda; }
};
