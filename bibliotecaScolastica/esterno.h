#ifndef ESTERNO_H
#define ESTERNO_H

#include<string>
#include"utente.h"

class Esterno: public Utente
{
public:
    Esterno(const std::string&, const std::string&, const std::string&, const std::string&);
private:
    std::string getTipoUtente() const;
};

#endif // ESTERNO_H
