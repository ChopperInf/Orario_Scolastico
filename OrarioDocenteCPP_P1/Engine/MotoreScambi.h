#pragma once
#include "../Model/Orario.h"
#include "ValidatoreOrario.h"
class MotoreScambi {
    ValidatoreOrario validatore;
public:
    bool Scambia(Orario& orario, Posizione prima, Posizione seconda);
};
