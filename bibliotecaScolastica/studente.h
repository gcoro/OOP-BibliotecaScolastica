#ifndef STUDENTE_H
#define STUDENTE_H

#include<string>
#include"utente.h"

class Studente: public Utente
{
public:
    Studente(const std::string&, const std::string&, const std::string&, const std::string&);
private:
    std::string getTipoUtente() const;
};

#endif // STUDENTE_H
