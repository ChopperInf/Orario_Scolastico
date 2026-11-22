#include "MotoreScambi.h"
bool MotoreScambi::Scambia(Orario& orario, Posizione a, Posizione b) {
    int g1 = a.GetGiorno(), o1 = a.GetOra(), g2 = b.GetGiorno(), o2 = b.GetOra();
    if (g1 < 0 || g1 >= 5 || o1 < 0 || o1 >= 8 ||
        g2 < 0 || g2 >= 5 || o2 < 0 || o2 >= 8 ||
        (g1 == g2 && o1 == o2) || !validatore.SenzaBuchi(orario)) return false;
    orario.ScambiaCelle(a, b);
    if (validatore.SenzaBuchi(orario)) return true;
    orario.ScambiaCelle(a, b); // Ripristino.
    return false;
}
