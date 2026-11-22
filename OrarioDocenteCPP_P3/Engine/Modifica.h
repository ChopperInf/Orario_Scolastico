#pragma once
#include "../Model/Posizione.h"

// Ripetere lo scambio delle stesse posizioni annulla la modifica.
class Modifica {
private:
    Posizione prima;
    Posizione seconda;
public:
    Modifica(Posizione prima, Posizione seconda) : prima(prima), seconda(seconda) {}
    Posizione GetPrima() { return prima; }
    Posizione GetSeconda() { return seconda; }
};
