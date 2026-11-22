#pragma once
#include <vector>
#include <stack>
#include <string>
#include "../Model/Orario.h"
#include "Vincolo.h"
#include "Modifica.h"

class MotoreScambi {
private:
    std::vector<Vincolo*> vincoli; // Puntatori non proprietari.
    std::stack<Modifica> cronologia;
    Orario* orarioCronologia = nullptr; // Un motore gestisce un solo orario.
    bool VerificaVincoli(Orario& orario, std::string& messaggio);
    bool EseguiScambio(Orario& orario, Posizione prima, Posizione seconda,
                       std::string& messaggio, bool verificaIniziale);
public:
    void AggiungiVincolo(Vincolo* vincolo);
    bool Scambia(Orario& orario, Posizione prima, Posizione seconda, std::string& messaggio);
    bool Annulla(Orario& orario, std::string& messaggio);
};
