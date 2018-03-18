#include "dialogutenteesterno.h"

DialogUtenteEsterno::DialogUtenteEsterno()
{
    createDialogUtenteEsterno();
    fillDialogUtenteEsterno();
}


void DialogUtenteEsterno::createDialogUtenteEsterno()
{
    //groupbox per libri di narrativa + i suoi elementi
    QGroupBox* libroNgroupbox = new QGroupBox("Ricerca libri di narrativa");
    QLabel* label1 = new QLabel("Titolo:", this);
    libroNTitolo = new QLineEdit(this);
    QLabel* label2 = new QLabel("Autore:", this);
    libroNAutore = new QLineEdit(this);
    QLabel* label3 = new QLabel("Fascia d'età consigliata:", this);
    libroNEta = new QComboBox(this);
    libroNEta->addItem("Tutte", "Tutte");
    libroNEta->addItem("Bambini 6-10 anni","Bambini 6-10 anni");
    libroNEta->addItem("Ragazzi 10-13 anni","Ragazzi 10-14 anni");
    libroNEta->addItem("Adolescenti 14-16 anni","Adolescenti 14-16 anni");
    libroNEta->addItem("Giovani adulti 17-22 anni","Giovani adulti 17-22 anni");
    libroNEta->addItem("Adulti","Adulti");
    libroNDisponibilita = new QCheckBox("Visualizza solo libri correntemente disponibili", this);
    libroNSearch = new QPushButton("Cerca libri narrativa", this);

    QGridLayout* layout1 = new QGridLayout();
    layout1->addWidget(label1,0,0);
    layout1->addWidget(libroNTitolo,0,1);
    layout1->addWidget(label2,1,0);
    layout1->addWidget(libroNAutore,1,1);
    layout1->addWidget(label3,2,0);
    layout1->addWidget(libroNEta,2,1);
    layout1->addWidget(libroNDisponibilita,3, 0, 1, 2);
    layout1->addWidget(libroNSearch,4, 0, 1, 2);
    libroNgroupbox->setLayout(layout1);

    //groupbox per riviste + i suoi elementi
    QGroupBox* rivistagroupbox = new QGroupBox("Ricerca riviste");
    QLabel* label4 = new QLabel("Nome rivista:", this);
    rivistaTitolo = new QLineEdit(this);
    QLabel* label5 = new QLabel("Numero:", this);
    rivistaNumero = new QLineEdit(this);
    QLabel* label6 = new QLabel("Argomento:", this);
    rivistaArgomento = new QLineEdit(this);
    rivistaDisponibilita = new QCheckBox("Visualizza solo riviste correntemente disponibili", this);
    rivistaSearch = new QPushButton("Cerca riviste", this);

    QGridLayout* layout2 = new QGridLayout();
    layout2->addWidget(label4, 0, 0);
    layout2->addWidget(rivistaTitolo, 0, 1);
    layout2->addWidget(label5, 1, 0);
    layout2->addWidget(rivistaNumero, 1, 1);
    layout2->addWidget(label6, 2, 0);
    layout2->addWidget(rivistaArgomento, 2, 1);
    layout2->addWidget(rivistaDisponibilita, 3, 0, 1, 2);
    layout2->addWidget(rivistaSearch, 4, 0, 1, 2);
    rivistagroupbox->setLayout(layout2);

    QVBoxLayout* layoutSx = new QVBoxLayout();
    layoutSx->addWidget(libroNgroupbox);
    layoutSx->addWidget(rivistagroupbox);

    QGroupBox* groupSx = new QGroupBox();
    groupSx->setFlat(true);
    groupSx->setLayout(layoutSx);

    //creo la tablewidget
    showSearchResults = new QTableWidget(this);
    QStringList titles {"ID", "Tipologia", "Titolo", "Anno di pubblicazione", "Disponibilita"};
    showSearchResults->setColumnCount(titles.size());
    showSearchResults->setHorizontalHeaderLabels(titles);
    showSearchResults->setEditTriggers(QAbstractItemView::NoEditTriggers); //rendo la tabella non editabile

    vediInfo = new QPushButton("Visualizza più informazioni", this);

    QVBoxLayout* layoutDx = new QVBoxLayout();
    layoutDx->addWidget(showSearchResults);
    layoutDx->addWidget(vediInfo);

    QGroupBox* groupDx = new QGroupBox();
    groupDx->setFlat(true);
    groupDx->setLayout(layoutDx);

    //riunisco tutto in un unico layout e lo applico
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(groupSx);
    layout->addWidget(groupDx);
    setLayout(layout);

    //connetto i bottoni agli slot
    connect(libroNSearch, SIGNAL(clicked()), this, SLOT(esternoLibroNSearch()));
    connect(rivistaSearch, SIGNAL(clicked()), this, SLOT(esternoRivistaSearch()));
    connect(vediInfo, SIGNAL(clicked()), this, SLOT(esternoVediInfo()));

    setWindowTitle(tr("Utente esterno - Ricerca articoli"));
    setFixedWidth(1100);
}

void DialogUtenteEsterno::fillDialogUtenteEsterno()
{
    articoliBiblioteca = new Biblioteca();

    //provo ad aprire il file con gli articoli
    QFile file(QDir::currentPath().append("/../bibliotecaScolastica/xml/articolidb.xml"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //se il file non si apre
    {
        QMessageBox error(this);
        error.setText("Errore di recupero informazioni dal file.");
        error.exec();
    }

    QDomDocument doc;
    doc.setContent(&file);

    file.close(); //chiudo il file perchè i dati son gia in doc (di tipo QDomDocument)

    QDomElement root = doc.firstChild().toElement();  //cioè <articoli> nel doc XML
    QDomElement it= root.firstChild().toElement(); //cioè <articolo> singolo; li scorro con un iteratore
    //scorro intanto ogni articolo disponibile e li inserisco in articoliBiblioteca
    while(!it.isNull())
    {
        Articolo* a; //puntatore polimorfo ad Articolo
        //controllo inanzitutto che tipo di articolo è (poiche ogni articolo ha un diverso numero di campi dati)
        QString tipo = it.attribute("tipologia").toLower();
        if(tipo == "libronarrativa")
        {
            //lista parametri: ID, titolo, anno, disponibilita, autore, casa editrice, pagine, genere, eta target
            a = new LibroNarrativa(it.attribute("id").toStdString(),
                                   it.firstChild().toElement().text().toStdString(),
                                   it.firstChild().nextSibling().toElement().text().toInt(),
                                   it.firstChild().nextSibling().nextSibling().toElement().text().toLower() == "disponibile",
                                   it.firstChild().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                   it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                   it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toInt(),
                                   it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                   it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                   it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString()
                                   );

        }
        else if(tipo == "libroscolastico")
        {
            //lista parametri: ID, titolo, anno, disponibilita, autore, casa editrice, pagine, materia, numero edizione
            a = new LibroScolastico(it.attribute("id").toStdString(),
                                    it.firstChild().toElement().text().toStdString(),
                                    it.firstChild().nextSibling().toElement().text().toInt(),
                                    it.firstChild().nextSibling().nextSibling().toElement().text().toLower() == "disponibile",
                                    it.firstChild().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                    it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                    it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toInt(),
                                    it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                                    it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toInt()
                                    );
        }
        else if(tipo == "cdmusicale")
        {
            //lista parametri: ID, titolo, anno, disponibilita, artista/i, genere, numero tracce
            a = new CdMusicale(it.attribute("id").toStdString(),
                               it.firstChild().toElement().text().toStdString(),
                               it.firstChild().nextSibling().toElement().text().toInt(),
                               it.firstChild().nextSibling().nextSibling().toElement().text().toLower() == "disponibile",
                               it.firstChild().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                               it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                               it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toInt()
                               );
        }
        else if(tipo== "rivista")
        {
            //lista parametri: ID, titolo, anno, disponibilita, numero volume, periodicita, argomento, pagine
            a = new Rivista(it.attribute("id").toStdString(),
                            it.firstChild().toElement().text().toStdString(),
                            it.firstChild().nextSibling().toElement().text().toInt(),
                            it.firstChild().nextSibling().nextSibling().toElement().text().toLower() == "disponibile",
                            it.firstChild().nextSibling().nextSibling().nextSibling().toElement().text().toInt(),
                            it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                            it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toStdString(),
                            it.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toInt()
                            );
        }

        if(a)
        {
        //faccio la push_back nella lista del nuovo articolo, e devo incrementare il contatore
        articoliBiblioteca->articoli.push_back(a);
        articoliBiblioteca->piuUno();
        }
        //ed esamino il prossimo <articolo>
        it= it.nextSibling().toElement();
     }
}

void DialogUtenteEsterno::printArticoli(std::list<Articolo*> l) const //stampa nella QTableWidget l'articolo a
{
    for(auto it = l.begin(); it != l.end(); it++)
    {
        const int row = showSearchResults->rowCount();
        showSearchResults->insertRow(row);
        showSearchResults->setItem(row, 0, new QTableWidgetItem(QString::fromStdString((*it)->getId())));
        showSearchResults->setItem(row, 1, new QTableWidgetItem(QString::fromStdString((*it)->getDynamicType())));
        showSearchResults->setItem(row, 2, new QTableWidgetItem(QString::fromStdString((*it)->getTitolo())));
        showSearchResults->setItem(row, 3, new QTableWidgetItem(QString::number((*it)->getAnnoPubblicazione())));
        if((*it)->getDisponibilita())
            showSearchResults->setItem(row, 4, new QTableWidgetItem("Disponibile"));
        else
            showSearchResults->setItem(row, 4, new QTableWidgetItem("In prestito"));
    }
}

void DialogUtenteEsterno::createVisualizzaInfoArticolo()
{
    infoArticoloDialog = new QDialog();

    showInfoArticolo = new QTextBrowser(infoArticoloDialog);
    chiudiInfoArticolo = new QPushButton("Chiudi informazioni",infoArticoloDialog);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(showInfoArticolo);
    layout->addWidget(chiudiInfoArticolo);
    infoArticoloDialog->setLayout(layout);

    connect(chiudiInfoArticolo, SIGNAL(clicked()), this, SLOT(chiudiInfo()));
}

//stampa le informazioni complete di un libro narrativa
void DialogUtenteEsterno::printInfoLibroN(LibroNarrativa* libroN) const
{
    showInfoArticolo->setText("<html><b>ID: </b></html>" + QString::fromStdString(libroN->getId())); //ID
    showInfoArticolo->append("<html><b>Tipo di articolo: </b></html> Libro di narrativa"); //Tipo di articolo
    showInfoArticolo->append("<html><b>Titolo: </b></html>" + QString::fromStdString(libroN->getTitolo())); //Titolo
    showInfoArticolo->append("<html><b>Autore: </b></html>" + QString::fromStdString(libroN->getAutore())); //Autore
    showInfoArticolo->append("<html><b>Anno di pubblicazione: </b></html>" + QString::number(libroN->getAnnoPubblicazione())); //Anno pubblicazione
    showInfoArticolo->append("<html><b>Lingua originale: </b></html>" + QString::fromStdString(libroN->getLinguaOriginale())); //Lingua originale
    showInfoArticolo->append("<html><b>Casa editrice: </b></html>" + QString::fromStdString(libroN->getCasaEditrice())); //Casa editrice
    showInfoArticolo->append("<html><b>Numero di pagine: </b></html>" + QString::number(libroN->getPagine())); //Numero di pagine
    showInfoArticolo->append("<html><b>Genere narrativo: </b></html>" + QString::fromStdString(libroN->getGenereNarrativo())); //Genere
    showInfoArticolo->append("<html><b>Età target: </b></html>" + QString::fromStdString(libroN->getEtaTarget())); //Fascia d'eta
    if(libroN->getDisponibilita() == true) //Disponibile/In prestito
        showInfoArticolo->append("<html><b>Stato articolo: </b>Disponibile al prestito</html>");
    else
        showInfoArticolo->append("<html><b>Stato articolo: </b>In prestito</html>");
}

//stampa le informazioni complete di una rivista
void DialogUtenteEsterno::printInfoRivista(Rivista* rivista) const
{
    showInfoArticolo->setText("<html><b>ID: </b></html>" + QString::fromStdString(rivista->getId())); //ID
    showInfoArticolo->append("<html><b>Tipo di articolo: </b></html> Rivista"); //Tipo di articolo
    showInfoArticolo->append("<html><b>Nome: </b></html>" + QString::fromStdString(rivista->getTitolo())); //Nome/titolo
    showInfoArticolo->append("<html><b>Numero: </b></html>" + QString::number(rivista->getNumero())); //numero volume
    showInfoArticolo->append("<html><b>Argomento: </b></html>" + QString::fromStdString(rivista->getArgomento())); //argomento
    showInfoArticolo->append("<html><b>Periodicità: </b></html>" + QString::fromStdString(rivista->getPeriodicita())); //periodicita
    showInfoArticolo->append("<html><b>Anno di pubblicazione: </b></html>" + QString::number(rivista->getAnnoPubblicazione())); //Anno pubblicazione
    showInfoArticolo->append("<html><b>Numero pagine: </b></html>" + QString::number(rivista->getNumeroPagine())); //numero Pagine
    if(rivista->getDisponibilita() == true) //Disponibile/In prestito
        showInfoArticolo->append("<html><b>Stato articolo: </b>Disponibile al prestito</html>");
    else
        showInfoArticolo->append("<html><b>Stato articolo: </b>In prestito</html>");
}

//SLOTS
void DialogUtenteEsterno::esternoLibroNSearch()
{
    //svuoto la QtableWidget
    showSearchResults->clearSelection();
    showSearchResults->clearContents();
    showSearchResults->setRowCount(0);

    //mi salvo gli input dell utente
    QString titolo = libroNTitolo->text().toLower();
    QString autore = libroNAutore->text().toLower();
    QString genere = "Tutti"; //Utente Esterno non ha la ricerca per genere
    QString eta = libroNEta->currentText(); //non faccio toLower perche non sono campi digitazione e quindi minuscole e maiuscole saranno sempre uguali
    QString lingua = ""; //Utente Esterno non ha la ricerca per lingua
    bool onlyDisponibili = false;
    if(libroNDisponibilita->isChecked())
       onlyDisponibili = true;
    else
        onlyDisponibili = false;
    std::list<Articolo*> libriRitornati = articoliBiblioteca->cercaLibroNarrativa
            (titolo.toStdString(), autore.toStdString(), genere.toStdString(), eta.toStdString(), lingua.toStdString(), onlyDisponibili);

    printArticoli(libriRitornati);  //stampo nella QTableWidget gli elementi

    //Se non ho trovato nessun elemento lo comunico con una messagebox
    if(libriRitornati.begin() == libriRitornati.end())
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo corrispondente trovato :(");
        err.exec();
    }

    //infine distruggo gli elementi di libriRitornati, per non creare garbage
    for(auto it = libriRitornati.begin(); it != libriRitornati.end(); it++)
    {
        delete *it; //deallocazione della memoria puntata dall'oggetto Articolo* (quindi l'oggetto stesso)
        it = libriRitornati.erase(it);
        it--;
    }

}

void DialogUtenteEsterno::esternoRivistaSearch()
{
    //svuoto la QtableWidget
    showSearchResults->clearSelection();
    showSearchResults->clearContents();
    showSearchResults->setRowCount(0);

    //mi salvo gli input dell utente
    QString titolo = rivistaTitolo->text().toLower();
    QString numero = rivistaNumero->text(); //salvo come stringa anche se ci si aspetta un numero, se l'utente inserisce altro, il tutto funzionerà ma non troverà corrispondenze
    QString argomento = rivistaArgomento->text().toLower();
    bool onlyDisponibili = false;
    if(rivistaDisponibilita->isChecked())
       onlyDisponibili = true;
    else
        onlyDisponibili = false;

    std::list<Articolo*> rvRitornate = articoliBiblioteca->cercaRivista
            (titolo.toStdString(), numero.toStdString(), argomento.toStdString(), onlyDisponibili);

    printArticoli(rvRitornate);  //stampo nella QTableWidget gli elementi

    //Se non ho trovato nessun elemento lo comunico con una messagebox
    if(rvRitornate.begin() == rvRitornate.end())
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo corrispondente trovato :(");
        err.exec();
    }

    //infine distruggo gli elementi di rvRitornate, per non creare garbage
    for(auto it = rvRitornate.begin(); it != rvRitornate.end(); it++)
    {
        delete *it; //deallocazione della memoria puntata dall'oggetto Articolo* (quindi l'oggetto stesso)
        it = rvRitornate.erase(it);
        it--;
    }
}

void DialogUtenteEsterno::esternoVediInfo()
{
    if(showSearchResults->currentIndex().isValid())
    {
        //creo la finestra
        createVisualizzaInfoArticolo();

        //mi salvo l'ID dell'articolo da visualizzare
        articolodaVisualizzare = showSearchResults->item(showSearchResults->currentIndex().row(), 0)->text();

        //trovo l'articolo desiderato e me lo salvo con un puntatore a
        Articolo* a = articoliBiblioteca->findArticolo(articolodaVisualizzare.toStdString());

        //vedo che tipo è e stampo le informazioni
        QString tipo = QString::fromStdString(a->getDynamicType()).toLower();
        if(tipo == "libronarrativa")
            printInfoLibroN(static_cast<LibroNarrativa*>(a));
        else if(tipo == "rivista")
            printInfoRivista(static_cast<Rivista*>(a));

        infoArticoloDialog->setFixedSize(400,300);
        infoArticoloDialog->setWindowTitle("Informazioni articolo");
        infoArticoloDialog->exec();
    }
    else //se nessuna riga è selezionata dico di farlo
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo selezionato.\n Selezionare dalla tabella l'articolo del quale si vuole visualizzare le informazioni.");
        err.exec();
    }
}

void DialogUtenteEsterno::chiudiInfo()
{
    infoArticoloDialog->close();
}
