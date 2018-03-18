#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include<string>
#include<list>
#include<algorithm>
#include <cctype>
#include <functional>
#include"libronarrativa.h"
#include"libroscolastico.h"
#include"cdmusicale.h"
#include"rivista.h"

class Biblioteca
{
private:
    unsigned int totaleArt; //numero degli articoli in possesso della biblioteca
public:
    std::list<Articolo*> articoli; //uso un campo dati pubblico per averci piu facile accesso
    Biblioteca(unsigned int = 0);
    unsigned int getNumeroArt() const;

    //piuUno incrementa il numero di articoli in biblioteca di uno
    void piuUno();

    //checkAvaiableId restituisce true se l'id è disponibile (cioè mai usato), altrimenti false
    bool checkAvaiableId(std::string) const;

    //funzioni per Admin
    void rimuoviArticolo(std::string);  //rimuove, se esiste, l'articolo a dalla lista articoli
    bool cambiaDisponibilita(std::string);
    Articolo* findArticolo(std::string) const;

    //Funzioni per Utenti (di ricerca)  
    std::list<Articolo*> cercaLibroNarrativa(std::string, std::string, std::string, std::string, std::string, bool);
    std::list<Articolo*> cercaLibroScolastico(std::string, std::string, std::string, std::string, std::string, bool);
    std::list<Articolo*> cercaCdMusicale(std::string, std::string, std::string, bool);
    std::list<Articolo*> cercaRivista(std::string, std::string, std::string, bool);

};

#endif // BIBLIOTECA_H
