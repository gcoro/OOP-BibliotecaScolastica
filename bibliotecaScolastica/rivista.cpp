#include "rivista.h"

//costruttore di Rivista
Rivista::Rivista(std::string id, std::string titolo, unsigned int anno, bool disp, unsigned int num,
                 std::string per, std::string arg, unsigned int pag)
    : Articolo(id, titolo, anno, disp), numero(num), periodicita(per), argomento(arg), numPagine(pag) {}


unsigned int Rivista::getNumero() const
{
    return numero;
}
std::string Rivista::getPeriodicita() const
{
    return periodicita;
}
std::string Rivista::getArgomento() const
{
    return argomento;
}
unsigned int Rivista::getNumeroPagine() const
{
    return numPagine;
}
std::string Rivista::getDynamicType() const
{
    return "Rivista";
}

Rivista* Rivista::clone() const
{
    return new Rivista(*this);
}
