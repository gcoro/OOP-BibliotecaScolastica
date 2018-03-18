#ifndef LIBRONARRATIVA_H
#define LIBRONARRATIVA_H

#include"libro.h"

class LibroNarrativa: public Libro
{
private:
    std::string linguaOriginale;
    std::string genereNarrativo;
    std::string etaTarget;
public:
    LibroNarrativa(std::string, std::string, unsigned int=0, bool=true, std::string="",
                   std::string ="", unsigned int=0, std::string="", std::string= "", std::string= "" );
    std::string getLinguaOriginale() const;
    std::string getGenereNarrativo() const;
    std::string getEtaTarget() const;
    std::string getDynamicType() const;
    LibroNarrativa* clone() const;

};

#endif // LIBRONARRATIVA_H
