#ifndef LIBRO_H
#define LIBRO_H

#include<string>
#include"articolo.h"

class Libro: public Articolo
{
private:
    std::string autore;
    std::string casaEditrice;
    unsigned int pagine;
public:
    Libro(std::string, std::string , unsigned int=0, bool=true, std::string="", std::string ="", unsigned int=0);
    std::string getAutore() const;
    std::string getCasaEditrice() const;
    unsigned int getPagine() const;
    //il metodo virtuale getDynamicType e clone sono ereditati da Articolo
    std::string getDynamicType() const = 0;
    Libro* clone() const = 0;


};

#endif // LIBRO_H
