#pragma once
#include "Tessera.h"
#include "Posizione.h"
class Orario {
    Tessera* celle[5][8];
public:
    Orario();
    ~Orario();
    Orario(const Orario&) = delete;
    Orario& operator=(const Orario&) = delete;
    Tessera* Get(Posizione posizione);
    // Se true, l'orario acquisisce la proprieta' della tessera.
    bool Set(Posizione posizione, Tessera* tessera);
    void ScambiaCelle(Posizione prima, Posizione seconda);
};
