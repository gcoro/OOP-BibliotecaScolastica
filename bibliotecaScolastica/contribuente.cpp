#include "contribuente.h"

Contribuente::Contribuente(const std::string& u, const std::string& pass, const std::string& n, const std::string& c)
    : Utente(u,pass,n,c) {}

std::string Contribuente::getTipoUtente() const
{
    return "Contribuente";
}
