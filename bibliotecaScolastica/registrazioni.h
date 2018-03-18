#ifndef REGISTRAZIONI_H
#define REGISTRAZIONI_H

#include<string>
#include<list>
#include"utente.h"
#include"studente.h"
#include"esterno.h"
#include"contribuente.h"
#include"amministratore.h"

class Registrazioni
{
public:
    std::list<Utente*> registrati; //la metto pubblica per avere più facile accesso
private:
    unsigned int numUtenti;
public:
    Registrazioni(unsigned int= 0);
    unsigned int getNumUtenti() const;

    //inserisciUtente inserisce l'utente nei registrati, e ritorna l'utente aggiunto
    Utente* inserisciUtente(std::string,std::string,std::string,std::string,std::string);

    void rimuoviUtente(std::string);

    //controlla se l'username è avaiable: ritorna true se non ci sono già inseriti utenti con lo stesso username,
    //altrimenti false
    bool checkAvaiableUsername(std::string) const;

    //elimina l'utente e restituisce un nuovo utente del nuovo tipo
    void cambiaTipoUtente(std::string, std::string);

};

#endif // REGISTRAZIONI_H
