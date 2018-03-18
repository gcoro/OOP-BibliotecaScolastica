#ifndef RIVISTA_H
#define RIVISTA_H

#include<string>
#include"articolo.h"

class Rivista: public Articolo
{
private:
    unsigned int numero;
    std::string periodicita;
    std::string argomento;
    unsigned int numPagine;

public:
    Rivista(std::string, std::string, unsigned int=0, bool = true, unsigned int=1, std::string="", std::string = "", unsigned int = 0);
    unsigned int getNumero() const;
    std::string getPeriodicita() const;
    std::string getArgomento() const;
    unsigned int getNumeroPagine()const;
    std::string getDynamicType() const;
    Rivista* clone() const;
};

#endif // RIVISTA_H
