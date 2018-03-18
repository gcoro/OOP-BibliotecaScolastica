#include "libronarrativa.h"

//costruttore di LibroNarrativa
LibroNarrativa::LibroNarrativa(std::string id, std::string titolo, unsigned int anno, bool disp, std::string autore,
                               std::string casaed, unsigned int pagine, std::string lingua, std::string genere, std::string eta)
    : Libro(id, titolo, anno, disp, autore, casaed, pagine), linguaOriginale(lingua), genereNarrativo(genere), etaTarget(eta) {}

std::string LibroNarrativa::getLinguaOriginale() const
{
    return linguaOriginale;
}


std::string LibroNarrativa::getGenereNarrativo() const
{
    return genereNarrativo;
}

std::string LibroNarrativa::getEtaTarget() const
{
    return etaTarget;
}

std::string LibroNarrativa::getDynamicType() const
{
    return "LibroNarrativa";
}

LibroNarrativa* LibroNarrativa::clone() const
{
    return new LibroNarrativa(*this);
}

