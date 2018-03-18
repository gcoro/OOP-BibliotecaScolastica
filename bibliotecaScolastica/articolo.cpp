#include "articolo.h"

//costruttore di Articolo (ovviamente non possiamo costruire oggetti di tipo Articolo,
//ma esso verrà usato per costruire gli oggetti delle classi derivate)
Articolo::Articolo(std::string id, std::string t, unsigned int y, bool disp)
    : id(id), titolo(t), annoPubblicazione(y), disponibilita(disp) {}

//getId restituisce l'ID dell' oggetto di una qualsiasi classe derivata di Articolo
std::string Articolo::getId() const
{
    return id;
}

//getTitolo() restituisce il titolo dell' oggetto di una qualsiasi classe derivata di Articolo
std::string Articolo::getTitolo() const
{
    return titolo;
}

//getAnnoPubblicazione restituisce l'anno di pubblicazione dell' oggetto di una qualsiasi classe derivata di Articolo
unsigned int Articolo::getAnnoPubblicazione() const
{
    return annoPubblicazione;
}

//getDisponibilita ritorna 1 se l'articolo è disponibile, opppure 0 se è stato prestato
bool Articolo::getDisponibilita() const
{
    return disponibilita;
}

//modifica la disponibilita da 0->1 oppure da 1->0
void Articolo::switchDisp()
{
    if(disponibilita == true)
        disponibilita = false;
    else
        disponibilita = true;
}



