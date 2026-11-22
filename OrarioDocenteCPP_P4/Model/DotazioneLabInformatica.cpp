#include "DotazioneLabInformatica.h"
#include "../DebugP2.h"
DotazioneLabInformatica::DotazioneLabInformatica(std::vector<std::string> postazioni, bool presenzaLIM)
    : postazioni(postazioni), presenzaLIM(presenzaLIM) {
    LOG_CTOR("DotazioneLabInformatica this=" << this);
}
DotazioneLabInformatica::~DotazioneLabInformatica() {
    LOG_DTOR("DotazioneLabInformatica this=" << this);
}
int DotazioneLabInformatica::GetNumeroPostazioni() {
    return static_cast<int>(postazioni.size());
}
std::string DotazioneLabInformatica::GetDescrizionePostazione(int indice) {
    if (indice < 0 || indice >= GetNumeroPostazioni()) return "";
    return postazioni[indice];
}
bool DotazioneLabInformatica::GetPresenzaLIM() { return presenzaLIM; }
