#include "registrazioni.h"

Registrazioni:: Registrazioni(unsigned int n)
    : numUtenti(n) {}


unsigned int Registrazioni::getNumUtenti() const
{
    return numUtenti;
}

//inserisciUtente crea e inserisce l'utente
Utente* Registrazioni::inserisciUtente(std::string user,std::string pass ,std::string nome ,std::string cognome, std::string tipo)
{
    Utente* ut ; //creo un nuovo puntatore polimorfo ad utente

    //e lo costruisco con un diverso tipo dinamico, a seconda del tipo di utente che voglio andare a creare
    if(tipo == "Amministratore")
    {
        ut= new Amministratore(user,pass,nome,cognome);
    }
    else if(tipo == "Studente")
    {
        ut= new Studente(user,pass,nome,cognome);
    }
    else if(tipo == "Contribuente")
    {
        ut= new Contribuente(user,pass,nome,cognome);
    }
    else //if(tipo == "Esterno")
    {
        ut= new Esterno(user,pass,nome,cognome);
    }

    //faccio la push di questo nuovo utente all'interno della lista degli utenti registrati
    //incrementando anche il contatore degli utenti
    registrati.push_back(ut);
    numUtenti++;
    //ritorno infine l'utente
    return ut;
}

//rimuoviUtente rimuove dalla lista di utenti registrati l'utente con username corrispondente, e diminuisce quindi il numUtenti
void Registrazioni::rimuoviUtente(std::string username)
{
    for(auto it = registrati.begin(); it!=registrati.end(); it++)
    {
        if((*it)->getUsername() == username)
        {
            delete(*it); //distrugge l'oggetto (ma non il puntatore ad esso)
            it = registrati.erase(it);
            it--;
            numUtenti--;
        }
    }
}


//checkAvaiableUsername controlla che l'username non sia già usato per un altro utente
bool Registrazioni::checkAvaiableUsername(std::string user) const
{
    if(numUtenti>0)  //se ancora non c'è nessun utente, l'username so già che è avaiable quindi torno true
    {
        bool trovato= false;
        for(auto it = registrati.begin(); it != registrati.end() && !trovato; it++)
        {
            if(user == (*it)->getUsername())
                trovato=true;
        }
        if(trovato) //se trovo l'username ritorno false
            return false;
        else //altrimenti non l'ho trovato quindi è avaiable, torno true
            return true;
    }
    else
        return true;

}

//trasforma l'utente con username u e tipo != t, in un utente di tipo t
void Registrazioni::cambiaTipoUtente(std::string u, std::string t)
{
    bool trovato = false;
    for(auto it = registrati.begin(); it!=registrati.end() && !trovato; it++)
    {
        if((*it)->getUsername() == u)
        {
            //mi salvo i dati mancanti dell'utente
            std::string uPass = (*it)->getPassword();
            std::string uNome = (*it)->getNome();
            std::string uCognome = (*it)->getCognome();
            //lo rimuovo dalla lista degli utenti registrati
            it = registrati.erase(it);
            it--;
            trovato = true; //cosi interrompo il ciclo subito
            numUtenti--; //mi ricordo di decrementare il numero degli utenti, dato che poi lo incrementa
            //e infine faccio lo inserisco come nuovo utente
            Utente* nuovo = inserisciUtente(u,uPass,uNome,uCognome,t);
            // Utente* nuovo è una variabile che alla fine non viene usata, perchè non serve.
            //Serve però in altri casi che la funzione inserisciUtente ritorni un Utente*
        }
    }
}



