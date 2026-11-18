#include "TesseraAula.h"
#include "../DebugP2.h"
TesseraAula::TesseraAula(std::string materia, std::string classe, std::string aula)
    : Tessera(materia, classe, aula) {
    LOG_CTOR("TesseraAula this=" << this);
}
TesseraAula::~TesseraAula() {
    LOG_DTOR("TesseraAula this=" << this);
}
std::string TesseraAula::GetDescrizione() {
    return "AULA - " + Tessera::GetDescrizione();
}
