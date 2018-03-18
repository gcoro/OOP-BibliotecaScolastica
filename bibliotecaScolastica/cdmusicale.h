#ifndef CDMUSICALE_H
#define CDMUSICALE_H

#include<string>
#include<articolo.h>

class CdMusicale: public Articolo
{
private:
    std::string artista;
    std::string genere;
    unsigned int numTracce;
public:
    CdMusicale(std::string, std::string, unsigned int=0, bool = true, std::string="", std::string="", unsigned int = 0);
    std::string getArtista() const;
    std::string getGenere() const;
    unsigned int getNumeroTracce()const;
    std::string getDynamicType() const;
    CdMusicale* clone() const;

};

#endif // CDMUSICALE_H
