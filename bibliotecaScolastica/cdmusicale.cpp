#include "cdmusicale.h"

//costruttore di CdMusicale
CdMusicale::CdMusicale(std::string id, std::string t, unsigned int y, bool disp, std::string author, std::string genre, unsigned int tracce)
    : Articolo(id, t, y, disp), artista(author), genere(genre), numTracce(tracce) {}

//getArtista ritorna l'artista di un oggetto CdMusicale
std::string CdMusicale::getArtista() const
{
    return artista;
}

//getGenere ritorna il genere di un oggetto CdMusicale
std::string CdMusicale::getGenere() const
{
    return genere;
}

unsigned int CdMusicale::getNumeroTracce() const
{
    return numTracce;
}
std::string CdMusicale::getDynamicType() const
{
    return "CdMusicale";
}

CdMusicale* CdMusicale::clone() const
{
    return new CdMusicale(*this);
}
