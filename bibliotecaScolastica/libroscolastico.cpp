#include "libroscolastico.h"


//costruttore di LibroScolastico
LibroScolastico::LibroScolastico(std::string id, std::string titolo, unsigned int anno, bool disp, std::string author,
                                 std::string casaed, unsigned int pag, std::string mat, unsigned int ed )
    : Libro(id, titolo, anno, disp, author, casaed, pag), materia(mat), numEdizione(ed) {}

unsigned int LibroScolastico::getEdizione() const
{
    return numEdizione;
}
std::string LibroScolastico::getMateria() const
{
    return materia;
}

std::string LibroScolastico::getDynamicType() const
{
    return "LibroScolastico";
}

LibroScolastico* LibroScolastico::clone() const
{
    return new LibroScolastico(*this);
}
