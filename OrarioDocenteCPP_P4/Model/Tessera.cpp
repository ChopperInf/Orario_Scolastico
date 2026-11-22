#include "Tessera.h"
#include "../DebugP2.h"

Tessera::Tessera(std::string materia, std::string classe, std::string aula)
    : materia(materia), classe(classe), aula(aula) {
    LOG_CTOR("Tessera this=" << this << " materia=" << this->materia);
}

std::string Tessera::GetMateria() { return materia; }
std::string Tessera::GetClasse() { return classe; }
std::string Tessera::GetAula() { return aula; }

std::string Tessera::GetDescrizione() {
    return materia + " - " + classe + " - " + aula;
}
Tessera::~Tessera() {
    LOG_DTOR("Tessera this=" << this << " materia=" << materia);
}
