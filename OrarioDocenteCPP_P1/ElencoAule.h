#pragma once
#include "Aula.h"
#include <vector>
#include <string>

class ElencoAule
{
private:
    vector<Aula> aule;

public:
    //Inserisce una copia dell'aula, se la sigla non è vuota e non è già presente;
    //restituisce true o false
    bool Aggiungi(const Aula& aula);

    //Cerca per sigla e restituisce l'indice; `-1` se assente 
    int Cerca(std::string sigla) const;
    //Restituisce il numero di elementi 
    int GetNumeroAule() const;
    //Restituisce un puntatore di sola lettura all'aula richiesta, 
    //oppure `nullptr` se l'indice non è valido 
    const Aula* Get(int indice) const;

};

