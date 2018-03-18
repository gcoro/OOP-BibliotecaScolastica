#include "esterno.h"

Esterno::Esterno(const std::string& u, const std::string& pass, const std::string& n, const std::string& c)
    : Utente(u,pass,n,c) {}

std::string Esterno::getTipoUtente() const
{
    return "Esterno";
}
