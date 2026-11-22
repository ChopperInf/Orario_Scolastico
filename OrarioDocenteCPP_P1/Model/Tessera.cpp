#include "Tessera.h"
Tessera::Tessera(std::string materia, std::string docente, std::string aula)
    : materia(materia), docente(docente), aula(aula) {}
std::string Tessera::GetMateria() { return materia; }
std::string Tessera::GetDocente() { return docente; }
std::string Tessera::GetAula() { return aula; }
