#include "studente.h"

Studente::Studente(const std::string& u, const std::string& pass, const std::string& n, const std::string& c)
    : Utente(u,pass,n,c) {}

std::string Studente::getTipoUtente() const
{
    return "Studente";
}
