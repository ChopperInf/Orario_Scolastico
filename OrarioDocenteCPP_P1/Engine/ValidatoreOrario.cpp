#include "ValidatoreOrario.h"
bool ValidatoreOrario::SenzaBuchi(Orario& orario) {
    for (int g = 0; g < 5; g++) {
        bool vuota = false;
        for (int o = 0; o < 8; o++) {
            if (orario.Get(Posizione(g, o)) == nullptr) vuota = true;
            else if (vuota) return false;
        }
    }
    return true;
}
