#ifndef ARTICOLO_H
#define ARTICOLO_H

#include<string>

class Articolo
{
private:
    std::string id; //per distinguere univocamente eventuali articolo diversi ma aventi lo stesso titolo
    std::string titolo;
    unsigned int annoPubblicazione;
    bool disponibilita; //mi dice se l'articolo è disponibile o prestato (1=disponibile, 0=prestato)

public:
    Articolo(std::string, std::string, unsigned int = 0, bool = true); //costruttore
    virtual ~Articolo() = default; //distruttore virtuale
    std::string getId() const;
    std::string getTitolo() const;
    unsigned int getAnnoPubblicazione() const;
    bool getDisponibilita() const;
    void switchDisp();
    virtual std::string getDynamicType() const = 0;
    virtual Articolo* clone() const = 0;
};

#endif // ARTICOLO_H
