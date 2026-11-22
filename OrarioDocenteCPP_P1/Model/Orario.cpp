#include "Orario.h"
#include <utility>
Orario::Orario() {
    for (int g = 0; g < 5; g++)
        for (int o = 0; o < 8; o++) celle[g][o] = nullptr;
}
Orario::~Orario() {
    for (int g = 0; g < 5; g++)
        for (int o = 0; o < 8; o++) delete celle[g][o];
}
Tessera* Orario::Get(Posizione p) {
    int g = p.GetGiorno(), o = p.GetOra();
    if (g < 0 || g >= 5 || o < 0 || o >= 8) return nullptr;
    return celle[g][o];
}
bool Orario::Set(Posizione p, Tessera* t) {
    int g = p.GetGiorno(), o = p.GetOra();
    if (g < 0 || g >= 5 || o < 0 || o >= 8 || t == nullptr || celle[g][o] != nullptr)
        return false;
    celle[g][o] = t;
    return true;
}
void Orario::ScambiaCelle(Posizione a, Posizione b) {
    int g1 = a.GetGiorno(), o1 = a.GetOra(), g2 = b.GetGiorno(), o2 = b.GetOra();
    if (g1 < 0 || g1 >= 5 || o1 < 0 || o1 >= 8 ||
        g2 < 0 || g2 >= 5 || o2 < 0 || o2 >= 8) return;
    std::swap(celle[g1][o1], celle[g2][o2]);
}
