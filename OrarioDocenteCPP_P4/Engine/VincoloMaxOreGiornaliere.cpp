#include "VincoloMaxOreGiornaliere.h"

VincoloMaxOreGiornaliere::VincoloMaxOreGiornaliere(int massimoOre)
    : massimoOre(massimoOre) {
    LOG_CTOR("VincoloMaxOreGiornaliere this=" << this << " massimo=" << massimoOre);
}
VincoloMaxOreGiornaliere::~VincoloMaxOreGiornaliere() {
    LOG_DTOR("VincoloMaxOreGiornaliere this=" << this);
}

bool VincoloMaxOreGiornaliere::Verifica(Orario& orario) {
    if (massimoOre < 0 || massimoOre > 8) return false;

    for (int giorno = 0; giorno < 5; giorno++) {
        int numeroOre = 0;
        for (int ora = 0; ora < 8; ora++) {
            if (orario.Get(Posizione(giorno, ora)) != nullptr)
                numeroOre++;
        }
        if (numeroOre > massimoOre) return false;
    }
    return true;
}

int VincoloMaxOreGiornaliere::GetMassimoOre() {
    return massimoOre;
}

void VincoloMaxOreGiornaliere::SetMassimoOre(int nuovoMassimo) {
    if (nuovoMassimo >= 1 && nuovoMassimo <= 8)
        massimoOre = nuovoMassimo;
}

std::string VincoloMaxOreGiornaliere::GetMessaggio() {
    return "superato il numero massimo di " + std::to_string(massimoOre) + " ore giornaliere";
}
