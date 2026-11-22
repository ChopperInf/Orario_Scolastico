#pragma once
#include <string>
#include "Model/Orario.h"
#include "Model/ElencoClassi.h"
#include "Engine/MotoreScambi.h"
#include "Engine/GestoreRichieste.h"
#include "Engine/VincoloSenzaBuchi.h"
#include "Engine/VincoloMaxOreGiornaliere.h"

class InterfacciaConsole {
private:
    Orario& orario; // Riferimento non proprietario.
    ElencoClassi& elencoClassi; // Riferimento non proprietario.
    VincoloSenzaBuchi vincoloSenzaBuchi;
    VincoloMaxOreGiornaliere vincoloMaxOre;
    MotoreScambi motore;
    GestoreRichieste gestoreRichieste;

    int LeggiIntero(std::string messaggio, int minimo, int massimo);
    Posizione LeggiPosizione();
    void VisualizzaOrario();
    void VisualizzaTessera();
    void RichiediScambio();
    void RichiediAnnullamento();
    void AccodaRichiesta();
    void ElaboraRichiesta();
    void MostraCoda();
    void VerificaOrario();
    void MostraMenu();
    void VisualizzaClassi();
    void CercaClasse();
    void AggiungiClasse();
    void ModificaMassimoOre();
public:
    InterfacciaConsole(Orario& orario, ElencoClassi& elencoClassi);
    void Esegui();
};
