#include "Aula.h"

Aula::Aula(string sigla, string tip, string edificio)
{
	this->sigla = sigla;
	this->tipologia = tip;
	this->edificio = edificio;
}

string Aula::getSigla() const
{
	return this->sigla;
}

string Aula::getTipologia() const
{
	return this->tipologia;
}

string Aula::getEdificio() const
{
	return this->edificio;
}
