#pragma once
#include "Model/Orario.h"
#include "Engine/MotoreScambi.h"
#include "Engine/ValidatoreOrario.h"
#include <string>
#include "ElencoAule.h"

class InterfacciaConsole {
    Orario& orario;
    ElencoAule& elencoAule;
    MotoreScambi motore;
    ValidatoreOrario validatore;
    int LeggiIntero(std::string messaggio, int minimo, int massimo);
    Posizione LeggiPosizione();
    void VisualizzaOrario();
    void VisualizzaTessera();
    void RichiediScambio();
    void VerificaOrario();
    void MostraMenu();

    void visualizzaAule();
    void cercaAula();
    void aggiungiAula();
public:
    InterfacciaConsole(Orario& orario, ElencoAule& elencoAule);
    void Esegui();
};
