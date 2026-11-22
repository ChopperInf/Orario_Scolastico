#pragma once
#include <string>
using namespace std;

class Aula
{	
private:
	string sigla;
	string tipologia;
	string edificio;
public:

	Aula(string sigla, string tip, string edificio);
	string getSigla() const;
	string getTipologia() const;
	string getEdificio() const;
};

