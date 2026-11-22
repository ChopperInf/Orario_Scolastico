#pragma once
#include <string>
class Tessera {
    std::string materia, docente, aula;
public:
    Tessera(std::string materia, std::string docente, std::string aula);
    std::string GetMateria();
    std::string GetDocente();
    std::string GetAula();
};
