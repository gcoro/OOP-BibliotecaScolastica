#ifndef CONTRIBUENTE_H
#define CONTRIBUENTE_H

#include<string>
#include"utente.h"

class Contribuente: public Utente
{
public:
    Contribuente(const std::string&, const std::string&, const std::string&, const std::string&);
private:
    std::string getTipoUtente() const;
};

#endif // CONTRIBUENTE_H
