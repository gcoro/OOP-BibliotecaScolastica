#ifndef UTENTE_H
#define UTENTE_H

#include<string>

class Utente
{
private:
    std::string username; //l'username distingue univocamente un utente
    std::string password;
    std::string nome;
    std::string cognome;

public:
    Utente(const std::string&, const std::string&, const std::string&, const std::string&);
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getNome() const;
    std::string getCognome() const;
    virtual ~Utente() = default;
    virtual std::string getTipoUtente() const = 0;
};

#endif // UTENTE_H
