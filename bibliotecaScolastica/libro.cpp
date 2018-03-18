#include "libro.h"

//costruttore di Libro
Libro::Libro(std::string id, std::string titolo, unsigned int anno, bool disp, std::string author,
             std::string casaed, unsigned int pag )
    : Articolo(id, titolo, anno, disp), autore(author), casaEditrice(casaed), pagine(pag) {}

//getAutore ritorna l'autore di un oggetto di tipo Libro o tipo derivato
std::string Libro::getAutore() const
{
    return autore;
}

//getCasaEditrice ritorna la casa editrice di un oggetto di tipo Libro o tipo derivato
std::string Libro::getCasaEditrice() const
{
    return casaEditrice;
}

//getPagine ritorna il numero di pagine di un oggetto di tipo Libro o tipo derivato
unsigned int Libro::getPagine() const
{
    return pagine;
}
