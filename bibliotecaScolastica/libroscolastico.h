#ifndef LIBROSCOLASTICO_H
#define LIBROSCOLASTICO_H

#include<string>
#include"libro.h"


class LibroScolastico: public Libro
{
private:
    std::string materia;
    unsigned int numEdizione;
public:
    LibroScolastico(std::string, std::string, unsigned int=0, bool=true, std::string="",
                    std::string ="", unsigned int=0, std::string = "", unsigned int = 1);
    unsigned int getEdizione() const;
    std::string getMateria() const;
    std::string getDynamicType() const;
    LibroScolastico* clone() const;

};

#endif // LIBROSCOLASTICO_H
