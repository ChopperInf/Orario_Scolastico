#pragma once
#include "Vincolo.h"

class VincoloMaxOreGiornaliere : public Vincolo {
private:
    int massimoOre;
public:
    VincoloMaxOreGiornaliere(int massimoOre);
    ~VincoloMaxOreGiornaliere() override;
    int GetMassimoOre();
    void SetMassimoOre(int nuovoMassimo);
    bool Verifica(Orario& orario) override;
    std::string GetMessaggio() override;
};
