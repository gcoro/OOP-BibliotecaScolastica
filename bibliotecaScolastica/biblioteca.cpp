#include "biblioteca.h"
//costruttore
Biblioteca::Biblioteca(unsigned int n): totaleArt(n) {}

unsigned int Biblioteca::getNumeroArt() const
{
    return totaleArt;
}

void Biblioteca::piuUno()
{
    totaleArt = totaleArt + 1;
}

bool Biblioteca::checkAvaiableId(std::string id) const
{
    if(totaleArt>0)  //se ancora non c'è nessun articolo, l'ID so già che è avaiable quindi torno true
    {
        bool trovato= false;
        for(auto it = articoli.begin(); it != articoli.end() && !trovato; it++)
        {
            if(id == (*it)->getId())
                trovato=true;
        }
        if(trovato) //se trovo l'ID ritorno false
            return false;
        else //altrimenti non l'ho trovato quindi è avaiable, torno true
            return true;
    }
    else
        return true;
}

//rimuoviArticolo rimuove, se esiste, l'articolo a dalla lista disponibili
void Biblioteca::rimuoviArticolo(std::string idArt)
{
    //cerco tramite l'id (che è univoco) l'elemento da eliminare nella lista disponibili
    bool trovato= false; //trovato mi servirà per smettere di ciclare una volta trovato l'elemento cercato
    for(auto it = articoli.begin() ; it != articoli.end() && trovato== false; it++) //cicla su tutta la lista disponibili
    {
        if((*it)->getId() == idArt) //se l'articolo ha id==all'id cercato
        {
            delete(*it); //distrugge l'oggetto Articolo (ma non il puntatore ad esso)
            it= articoli.erase(it); //elimino il puntatore all'oggetto dalla lista disponibili
            it--;
            trovato = true; //una volta trovato ed eliminato l'elemento posso smettere di ciclare
        }
    }
    if(trovato)
        totaleArt--; //aggiorna il numero degli articoli posseduti dalla biblioteca
}

//cambiaDisponibilita modifica la disponibilita di un articolo
//(in prestito -> disponibile) oppure (disponibile -> in prestito)
//e ritorna la nuova disponibilita (1= disponibile, 0= in prestito)
bool Biblioteca::cambiaDisponibilita(std::string idArt)
{
    bool nuovaDisp;
    for(auto it= articoli.begin(); it != articoli.end(); it++)
    {
        if((*it)->getId() == idArt) //ho trovato l'articolo
        {
            (*it)->switchDisp(); //cambio la disponibilita
            nuovaDisp = (*it)->getDisponibilita(); //mi salvo la nuova disponibilita
        }
    }
    return nuovaDisp; //ritorno la nuova disponibilita
}

//findArticolo trova nella lista articoli l'articolo con id = idArt e lo ritorna
Articolo* Biblioteca::findArticolo(std::string idArt) const
{
    Articolo *  a;
    bool trovato = false;
    for(auto it= articoli.begin(); it != articoli.end() && !trovato; it++)
    {
        if((*it)->getId() == idArt) //ho trovato l'articolo
        {
            a = *it;
            trovato = true;
        }
    }
    return a;
}

//restituisce una lista che contiene i libri di narrativa che corrispondono alle caratteristiche cercate
std::list<Articolo*> Biblioteca::cercaLibroNarrativa(std::string titolo, std::string autore,
                                                     std::string genere, std::string eta, std::string lingua,
                                                     bool onlyDisponibili)
{
    std::list <Articolo*> l;

    for (auto it = articoli.begin(); it != articoli.end(); it ++)
    {
        if((*it)->getDynamicType() == "LibroNarrativa") //controllo intanto che sia un libro di narrativa
        {
            //converto a libro di narrativa
            LibroNarrativa* libro = dynamic_cast<LibroNarrativa*>(*it);
            //mi salvo quei campi, che l'utente ha digitato, dell'oggetto, così posso trasformarli in lowercase e
            //fare un confronto "case insensitive"
            std::string lowercaseTitolo = libro->getTitolo();
            std::string lowercaseAutore = libro->getAutore();
            std::string lowercaseLingua = libro->getLinguaOriginale();
            std::transform(lowercaseTitolo.begin(), lowercaseTitolo.end(), lowercaseTitolo.begin(), std::ptr_fun<int, int>(std::tolower));
            std::transform(lowercaseAutore.begin(), lowercaseAutore.end(), lowercaseAutore.begin(), std::ptr_fun<int, int>(std::tolower));
            std::transform(lowercaseLingua.begin(), lowercaseLingua.end(), lowercaseLingua.begin(), std::ptr_fun<int, int>(std::tolower));
            //e poi gli altri campi normali (quelli che vengono presi dalle qcombobox in input)
            std::string notformattedGenere = libro->getGenereNarrativo();
            std::string notformattedEta = libro->getEtaTarget();

            if(lowercaseTitolo.find(titolo) != std::string::npos && lowercaseAutore.find(autore) != std::string::npos
                    && lowercaseLingua.find(lingua) != std::string::npos) // controllo i match sui campi digitazione (faccio anche il match PARZIALE)
            {
                if((eta == "Tutte" || eta == notformattedEta) && (genere == "Tutti" || genere == notformattedGenere)) //controllo le combobox
                {
                    if(onlyDisponibili == false || libro->getDisponibilita() == true) //e infine la disponibilita (prendo l'articolo se nnon ha specificato che disp voglio, oppure se l'articolo è cmq disponibile)
                    {
                        //l'articolo corrisponde alla ricerca: faccio una copia dell articolo e la inserisco in l
                        Articolo* a = libro->clone();
                        l.push_back(a);
                    }
                }
            }
        }
    }
    return l;
}

std::list<Articolo*> Biblioteca::cercaLibroScolastico(std::string titolo, std::string autore,
                                                      std::string numEd, std::string casaEd,
                                                      std::string materia, bool onlyDisponibili)
{
    std::list <Articolo*> l;
    for (auto it = articoli.begin(); it != articoli.end(); it ++)
    {
        if((*it)->getDynamicType() == "LibroScolastico") //controllo intanto che sia un libro scolastico
        {
            //converto a libro scolastico
            LibroScolastico* libroS = dynamic_cast<LibroScolastico*>(*it);
            //mi salvo quei campi dell'oggetto da confrontare coi campi digitazione utente, così posso trasformarli in lowercase e
            //fare un confronto "case insensitive"
            std::string lowercaseTitolo = libroS->getTitolo();
            std::string lowercaseAutore = libroS->getAutore();
            std::string lowercaseCasaEd = libroS->getCasaEditrice();
            std::transform(lowercaseTitolo.begin(), lowercaseTitolo.end(), lowercaseTitolo.begin(), std::ptr_fun<int, int>(std::tolower));
            std::transform(lowercaseAutore.begin(), lowercaseAutore.end(), lowercaseAutore.begin(), std::ptr_fun<int, int>(std::tolower));
            std::transform(lowercaseCasaEd.begin(), lowercaseCasaEd.end(), lowercaseCasaEd.begin(), std::ptr_fun<int, int>(std::tolower));
            //e poi gli altri campi normali (uno perche viene dalle qcombobox in input + un campo digitazione numerico)
            std::string notformattedMateria = libroS->getMateria();
            std::string numberNumEd = std::to_string(libroS->getEdizione());

            if(lowercaseTitolo.find(titolo) != std::string::npos && lowercaseAutore.find(autore) != std::string::npos
                    && lowercaseCasaEd.find(casaEd) != std::string::npos) // controllo i match sui campi digitazione (faccio anche il match PARZIALE)
            {
                if(numEd == numberNumEd || numEd == "") //controllo il numero edizione (non uso find perche sennò ad es. trova 110 se scrivo 1
                {
                    if(materia == "Tutte" || materia == notformattedMateria) //controllo la combobox
                    {
                        if(onlyDisponibili == false || libroS->getDisponibilita() == true) //e infine la disponibilita (prendo l'articolo se non ha specificato che disp voglio, oppure se l'articolo è disponibile)
                        {
                            //l'articolo corrisponde alla ricerca: faccio una copia dell articolo e la inserisco in l
                            Articolo* a = libroS->clone();
                            l.push_back(a);
                        }
                    }
                }
            }
        }
    }
    return l; //ritorno la lista con i libriS corrispondenti
}

std::list<Articolo*> Biblioteca::cercaCdMusicale(std::string titolo, std::string artista,
                                                 std::string genere, bool onlyDisponibili)
{
    std::list <Articolo*> l;
    for (auto it = articoli.begin(); it != articoli.end(); it ++)
    {
        if((*it)->getDynamicType() == "CdMusicale") //controllo intanto che sia un CD
        {
            //converto (per poter invocare i metodi di CdMusicale)
            CdMusicale* cd = dynamic_cast<CdMusicale*>(*it);
            //mi salvo quei campi dell'oggetto da confrontare coi campi digitazione utente, così posso trasformarli in lowercase e
            //fare un confronto "case insensitive"
            std::string lowercaseTitolo = cd->getTitolo();
            std::string lowercaseArtista = cd->getArtista();
            std::transform(lowercaseTitolo.begin(), lowercaseTitolo.end(), lowercaseTitolo.begin(), std::ptr_fun<int, int>(std::tolower));
            std::transform(lowercaseArtista.begin(), lowercaseArtista.end(), lowercaseArtista.begin(), std::ptr_fun<int, int>(std::tolower));
            //e poi gli altri campi normali (genere che viene dalle qcombobox in input quindi non ha problemi di uppercase o lowercase)
            std::string notformattedGenere = cd->getGenere();

            if(lowercaseTitolo.find(titolo) != std::string::npos && lowercaseArtista.find(artista) != std::string::npos) // controllo i match sui campi digitazione (faccio anche il match PARZIALE)
            {
                if(genere == "Tutti" || genere == notformattedGenere) //controllo la combobox
                {
                    if(onlyDisponibili == false || cd->getDisponibilita() == true) //e infine la disponibilita (prendo l'articolo se non ha specificato che disp voglio, oppure se l'articolo è disponibile)
                    {
                        //l'articolo corrisponde alla ricerca: faccio una copia dell articolo e la inserisco in l
                        Articolo* a = cd->clone();
                        l.push_back(a);
                    }
                }
            }
        }
    }
    return l; //ritorno la lista con i CD corrispondenti
}

std::list<Articolo*> Biblioteca::cercaRivista(std::string titolo, std::string numero, std::string argomento, bool onlyDisponibili)
{
    std::list <Articolo*> l;
    for (auto it = articoli.begin(); it != articoli.end(); it ++)
    {
        if((*it)->getDynamicType() == "Rivista") //controllo intanto che sia una rivista
        {
            // dynamic_cast a rivista che mi interpreta l'articolo come una rivista
            Rivista* rv = dynamic_cast<Rivista*>(*it);
            //mi salvo quei campi dell'oggetto da confrontare coi campi digitazione utente, così posso trasformarli in lowercase e
            //fare un confronto "case insensitive"
            std::string lowercaseTitolo = rv->getTitolo();
            std::string lowercaseArgomento = rv->getArgomento();
            std::transform(lowercaseTitolo.begin(), lowercaseTitolo.end(), lowercaseTitolo.begin(), std::ptr_fun<int, int>(std::tolower));
            std::transform(lowercaseArgomento.begin(), lowercaseArgomento.end(), lowercaseArgomento.begin(), std::ptr_fun<int, int>(std::tolower));
            //e poi il campo digitazione numerico
            std::string numberNumeroRv = std::to_string(rv->getNumero());

            if(lowercaseTitolo.find(titolo) != std::string::npos && lowercaseArgomento.find(argomento) != std::string::npos) // controllo i match sui campi digitazione (faccio anche il match PARZIALE)
            {
                if(numero == numberNumeroRv || numero == "") //controllo il numero rv, se inserito. (non uso find perche sennò ad es. trova 110 se scrivo 1
                {
                    if(onlyDisponibili == false || rv->getDisponibilita() == true) //e infine la disponibilita (prendo l'articolo se non ha specificato che disp voglio, oppure se l'articolo è disponibile)
                    {
                        //l'articolo corrisponde alla ricerca: faccio una copia dell articolo e la inserisco in l
                        Articolo* a = rv->clone();
                        l.push_back(a);
                    }

                }
            }
        }
    }
    return l; //ritorno la lista con le riviste corrispondenti
}
