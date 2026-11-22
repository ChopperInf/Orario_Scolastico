#include "ElencoAule.h"



int ElencoAule::GetNumeroAule() const
{
    return static_cast<int>(aule.size());
}

int ElencoAule::Cerca(std::string sigla) const
{   
    for (int i = 0; i < GetNumeroAule(); i++) {
        if(aule[i].getSigla() == sigla){
            return i;
        }
    }
    return -1;
}

bool ElencoAule::Aggiungi(const Aula& aula)
{
    if (aula.getSigla().empty()) {
        return false;
    }
    if (Cerca(aula.getSigla()) != -1) {
        return false;
    }

    aule.push_back(aula);
    return true;
}


const Aula* ElencoAule::Get(int indice) const
{
    if (indice < 0 || indice >= GetNumeroAule()) {
        return nullptr;
    }
    return &aule[indice];
}
