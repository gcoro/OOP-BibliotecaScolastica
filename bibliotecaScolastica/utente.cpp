#include "utente.h"

Utente::Utente(const std::string& u, const std::string& pass, const std::string& n, const std::string& c)
    : username(u), password(pass), nome(n), cognome(c) {}

std::string Utente::getUsername() const
{
    return username;
}

std::string Utente::getPassword() const
{
    return password;
}

std::string Utente::getNome() const
{
    return nome;
}

std::string Utente::getCognome() const
{
    return cognome;
}
