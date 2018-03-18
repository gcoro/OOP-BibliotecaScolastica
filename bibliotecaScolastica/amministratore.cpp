#include "amministratore.h"

Amministratore::Amministratore(const std::string& u, const std::string& p, const std::string& n,
                               const std::string& c): Utente(u,p,n,c) {}


std::string Amministratore::getTipoUtente() const
{
    return "Amministratore";
}
