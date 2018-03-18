#ifndef AMMINISTRATORE_H
#define AMMINISTRATORE_H

#include<string>
#include"utente.h"


class Amministratore: public Utente
{
public:
    Amministratore(const std::string&, const std::string&, const std::string&, const std::string&);
private:
    std::string getTipoUtente() const;
};

#endif // AMMINISTRATORE_H
