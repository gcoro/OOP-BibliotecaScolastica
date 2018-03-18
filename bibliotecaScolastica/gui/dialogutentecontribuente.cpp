#include "dialogutentecontribuente.h"

DialogUtenteContribuente::DialogUtenteContribuente()
{
    createDialogUtenteContribuente();
    fillDialogUtenteContribuente();
}

void DialogUtenteContribuente::createDialogUtenteContribuente()
{
    //groupbox per libri scolastici + i suoi elementi
    QGroupBox* libroSgroupbox = new QGroupBox("Ricerca libri di testo scolastici");
    QLabel* label1 = new QLabel("Titolo:", this);
    libroSTitolo = new QLineEdit(this);
    QLabel* label2 = new QLabel("Autore:", this);
    libroSAutore = new QLineEdit(this);
    QLabel* label3 = new QLabel("Numero edizione:", this);
    libroSnEdizione = new QLineEdit(this);
    QLabel* label4 = new QLabel("Casa Editrice:", this);
    libroSCasaEd = new QLineEdit(this);
    QLabel* label5 = new QLabel("Materia:", this);
    libroSMateria = new QComboBox(this);
    libroSMateria->addItem("Tutte", "Tutte");
    libroSMateria->addItem("Matematica","Matematica");
    libroSMateria->addItem("Scienze","Scienze");
    libroSMateria->addItem("Filosofia","Filosofia");
    libroSMateria->addItem("Programmazione","Programmazione");
    libroSMateria->addItem("Letteratura italiana","Letteratura italiana");
    libroSMateria->addItem("Letteratura straniera","Letteratura straniera");
    libroSMateria->addItem("Storia","Storia");
    libroSMateria->addItem("Fisica","Fisica");
    libroSMateria->addItem("Arte","Arte");
    libroSMateria->addItem("Psicologia","Psicologia");
    libroSMateria->addItem("Geografia","Geografia");
    libroSMateria->addItem("Politica","Politica");
    libroSMateria->addItem("Grammatica","Grammatica");
    libroSMateria->addItem("Religione","Religione");
    libroSMateria->addItem("Musica","Musica");
    libroSMateria->addItem("Educazione fisica","Educazione fisica");
    libroSMateria->addItem("Elettronica","Elettronica");
    libroSMateria->addItem("Disegno tecnico","Disegno tecnico");
    libroSMateria->addItem("Tecnologia","Tecnologia");
    libroSMateria->setCurrentIndex(0);
    libroSDisponibilita = new QCheckBox("Visualizza solo libri correntemente disponibili", this);
    libroSSearch = new QPushButton("Cerca libro scolastico", this);

    QGridLayout* layout1 = new QGridLayout();
    layout1->addWidget(label1,0,0);
    layout1->addWidget(libroSTitolo,0,1);
    layout1->addWidget(label2,1,0);
    layout1->addWidget(libroSAutore,1,1);
    layout1->addWidget(label3,2,0);
    layout1->addWidget(libroSnEdizione,2,1);
    layout1->addWidget(label4,3,0);
    layout1->addWidget(libroSCasaEd,3,1);
    layout1->addWidget(label5,4,0);
    layout1->addWidget(libroSMateria,4,1);
    layout1->addWidget(libroSDisponibilita,5, 0, 1, 2);
    layout1->addWidget(libroSSearch,6, 0, 1, 2);
    libroSgroupbox->setLayout(layout1);

    //groupbox per libri di narrativa + i suoi elementi
    QGroupBox* libroNgroupbox = new QGroupBox("Ricerca libri di narrativa");
    QLabel* label8 = new QLabel("Titolo:", this);
    libroNTitolo = new QLineEdit(this);
    QLabel* label9 = new QLabel("Autore:", this);
    libroNAutore = new QLineEdit(this);
    QLabel* label10 = new QLabel("Genere narrativo:", this);
    libroNGenere = new QComboBox(this);
    libroNGenere->addItem("Tutti","Tutti");
    libroNGenere->addItem("Biografia","Biografia");
    libroNGenere->addItem("Libro illustrato","Libro illustrato");
    libroNGenere->addItem("Racconti","Racconti");
    libroNGenere->addItem("Romanzo","Romanzo");
    libroNGenere->addItem("Storiografia","Storiografia");
    QLabel* label11 = new QLabel("Fascia d'età consigliata:", this);
    libroNEta = new QComboBox(this);
    libroNEta->addItem("Tutte", "Tutte");
    libroNEta->addItem("Bambini 6-10 anni","Bambini 6-10 anni");
    libroNEta->addItem("Ragazzi 10-13 anni","Ragazzi 10-14 anni");
    libroNEta->addItem("Adolescenti 14-16 anni","Adolescenti 14-16 anni");
    libroNEta->addItem("Giovani adulti 17-22 anni","Giovani adulti 17-22 anni");
    libroNEta->addItem("Adulti","Adulti");
    QLabel* label12 = new QLabel("Lingua originale:", this);
    libroNLingua = new QLineEdit(this);
    libroNDisponibilita = new QCheckBox("Visualizza solo libri correntemente disponibili", this);
    libroNSearch = new QPushButton("Cerca libro narrativa", this);

    QGridLayout* layout2 = new QGridLayout();
    layout2->addWidget(label8,0,0);
    layout2->addWidget(libroNTitolo,0,1);
    layout2->addWidget(label9,1,0);
    layout2->addWidget(libroNAutore,1,1);
    layout2->addWidget(label10,2,0);
    layout2->addWidget(libroNGenere, 2,1);
    layout2->addWidget(label11,3,0);
    layout2->addWidget(libroNEta, 3,1);
    layout2->addWidget(label12,4,0);
    layout2->addWidget(libroNLingua, 4,1);
    layout2->addWidget(libroNDisponibilita, 5, 0, 1, 2);
    layout2->addWidget(libroNSearch, 6, 0, 1, 2);
    libroNgroupbox->setLayout(layout2);

    //groupbox per i CD + i suoi elementi
    QGroupBox* cdgroupbox = new QGroupBox("Ricerca Cd Musicali");
    QLabel* label13 = new QLabel("Titolo:", this);
    cdTitolo = new QLineEdit(this);
    QLabel* label14 = new QLabel("Autore:", this);
    cdArtista = new QLineEdit(this);
    QLabel* label15 = new QLabel("Genere:", this);
    cdGenere = new QComboBox(this);
    cdGenere->addItem("Tutti","Tutti");
    cdGenere->addItem("Audiolibro","Audiolibro");
    cdGenere->addItem("Basi per lezioni di danza","Basi per lezioni di danza");
    cdGenere->addItem("Musica classica","Musica classica");
    cdGenere->addItem("Musica moderna d'intrattenimento","Musica moderna d'intrattenimento");
    cdGenere->addItem("Musica strumentale","Musica strumentale");
    cdGenere->addItem("Suoni rilassanti per lo studio","Suoni rilassanti per lo studio");
    cdDisponibilita = new QCheckBox("Visualizza solo CD correntemente disponibili", this);
    cdSearch = new QPushButton("Cerca CD", this);

    QGridLayout* layout3 = new QGridLayout();
    layout3->addWidget(label13,0,0);
    layout3->addWidget(cdTitolo,0,1);
    layout3->addWidget(label14,1,0);
    layout3->addWidget(cdArtista,1,1);
    layout3->addWidget(label15,2,0);
    layout3->addWidget(cdGenere, 2,1);
    layout3->addWidget(cdDisponibilita, 3, 0, 1, 2);
    layout3->addWidget(cdSearch, 4, 0, 1, 2);
    cdgroupbox->setLayout(layout3);

    //groupbox per riviste + i suoi elementi
    QGroupBox* rivistagroupbox = new QGroupBox("Ricerca riviste");
    QLabel* label18 = new QLabel("Nome rivista:", this);
    rivistaTitolo = new QLineEdit(this);
    QLabel* label19 = new QLabel("Numero:", this);
    rivistaNumero = new QLineEdit(this);
    QLabel* label20 = new QLabel("Argomento:", this);
    rivistaArgomento = new QLineEdit(this);
    rivistaDisponibilita = new QCheckBox("Visualizza solo riviste correntemente disponibili", this);
    rivistaSearch = new QPushButton("Cerca riviste", this);

    QGridLayout* layout4 = new QGridLayout();
    layout4->addWidget(label18, 0, 0);
    layout4->addWidget(rivistaTitolo, 0, 1);
    layout4->addWidget(label19, 1, 0);
    layout4->addWidget(rivistaNumero, 1, 1);
    layout4->addWidget(label20, 2, 0);
    layout4->addWidget(rivistaArgomento, 2, 1);
    layout4->addWidget(rivistaDisponibilita, 3, 0, 1, 2);
    layout4->addWidget(rivistaSearch, 4, 0, 1, 2);
    rivistagroupbox->setLayout(layout4);

    QGridLayout* layoutSx = new QGridLayout();
    layoutSx->addWidget(libroNgroupbox, 0, 0);
    layoutSx->addWidget(libroSgroupbox, 0, 1);
    layoutSx->addWidget(cdgroupbox, 1, 0);
    layoutSx->addWidget(rivistagroupbox, 1, 1);


    QGroupBox* groupSx = new QGroupBox();
    groupSx->setFlat(true);
    groupSx->setLayout(layoutSx);

    //creo la tablewidget
    showSearchResults = new QTableWidget(this);
    QStringList titles {"ID", "Tipologia", "Titolo", "Anno di pubblicazione", "Disponibilita"};
    showSearchResults->setColumnCount(titles.size());
    showSearchResults->setHorizontalHeaderLabels(titles);
    showSearchResults->setEditTriggers(QAbstractItemView::NoEditTriggers); //rendo la tabella non editabile

    vediInfo = new QPushButton("Visualizza piu informazioni", this);

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
    connect(libroNSearch, SIGNAL(clicked()), this, SLOT(contribuenteLNSearch()));
    connect(libroSSearch, SIGNAL(clicked()), this, SLOT(contribuenteLSSearch()));
    connect(cdSearch, SIGNAL(clicked()), this, SLOT(contribuenteCdSearch()));
    connect(rivistaSearch, SIGNAL(clicked()), this, SLOT(contribuenteRivistaSearch()));
    connect(vediInfo, SIGNAL(clicked()), this, SLOT(contribuenteVediInfo()));

    setWindowTitle(tr("Utente contribuente - Ricerca articoli"));
    setFixedWidth(1350);
}

void DialogUtenteContribuente::fillDialogUtenteContribuente()
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

void DialogUtenteContribuente::printArticoli(std::list<Articolo*> l) const //stampa nella QTableWidget l'articolo a
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

void DialogUtenteContribuente::createVisualizzaInfoArticolo()
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
void DialogUtenteContribuente::printInfoLibroN(LibroNarrativa* libroN) const
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

//stampa le informazioni complete di un libro scolastico
void DialogUtenteContribuente::printInfoLibroS(LibroScolastico* libroS) const
{
    showInfoArticolo->setText("<html><b>ID: </b></html>" + QString::fromStdString(libroS->getId())); //ID
    showInfoArticolo->append("<html><b>Tipo di articolo: </b></html> Libro di testo scolastico"); //Tipo di articolo
    showInfoArticolo->append("<html><b>Materia: </b></html>" + QString::fromStdString(libroS->getMateria())); //Materia
    showInfoArticolo->append("<html><b>Titolo: </b></html>" + QString::fromStdString(libroS->getTitolo())); //Titolo
    showInfoArticolo->append("<html><b>Edizione: </b></html>" + QString::number(libroS->getEdizione()) + "a edizione"); //Numero edizione
    showInfoArticolo->append("<html><b>Autore/i: </b></html>" + QString::fromStdString(libroS->getAutore())); //Autore/i
    showInfoArticolo->append("<html><b>Anno di pubblicazione: </b></html>" + QString::number(libroS->getAnnoPubblicazione())); //Anno pubblicazione
    showInfoArticolo->append("<html><b>Casa editrice: </b></html>" + QString::fromStdString(libroS->getCasaEditrice())); //Casa editrice
    showInfoArticolo->append("<html><b>Numero di pagine: </b></html>" + QString::number(libroS->getPagine())); //Numero di pagine
    if(libroS->getDisponibilita() == true) //Disponibile/In prestito
        showInfoArticolo->append("<html><b>Stato articolo: </b>Disponibile al prestito</html>");
    else
        showInfoArticolo->append("<html><b>Stato articolo: </b>In prestito</html>");
}

//stampa le informazioni complete di un CD
void DialogUtenteContribuente::printInfoCd(CdMusicale* cd) const
{
    showInfoArticolo->setText("<html><b>ID: </b></html>" + QString::fromStdString(cd->getId())); //ID
    showInfoArticolo->append("<html><b>Tipo di articolo: </b></html> CD musicale"); //Tipo di articolo
    showInfoArticolo->append("<html><b>Titolo: </b></html>" + QString::fromStdString(cd->getTitolo())); //Titolo
    showInfoArticolo->append("<html><b>Artista/i: </b></html>" + QString::fromStdString(cd->getArtista())); //Artista
    showInfoArticolo->append("<html><b>Anno di pubblicazione: </b></html>" + QString::number(cd->getAnnoPubblicazione())); //Anno pubblicazione
    showInfoArticolo->append("<html><b>Genere: </b></html>" + QString::fromStdString(cd->getGenere())); //Genere
    showInfoArticolo->append("<html><b>Numero tracce: </b></html>" + QString::number(cd->getNumeroTracce())); //numero tracce
    if(cd->getDisponibilita() == true) //Disponibile/In prestito
        showInfoArticolo->append("<html><b>Stato articolo: </b>Disponibile al prestito</html>");
    else
        showInfoArticolo->append("<html><b>Stato articolo: </b>In prestito</html>");
}

//stampa le informazioni complete di una rivista
void DialogUtenteContribuente::printInfoRivista(Rivista* rivista) const
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

//------ SLOTS -------

void DialogUtenteContribuente::contribuenteLNSearch()
{
    //svuoto la QtableWidget
    showSearchResults->clearSelection();
    showSearchResults->clearContents();
    showSearchResults->setRowCount(0);
    //mi salvo gli input dell utente
    QString titolo = libroNTitolo->text().toLower();
    QString autore = libroNAutore->text().toLower();
    QString genere = libroNGenere->currentText(); //non faccio toLower perche non sono campi digitazione e quindi minuscole e maiuscole saranno sempre uguali
    QString eta = libroNEta->currentText(); //non faccio toLower perche non sono campi digitazione e quindi minuscole e maiuscole saranno sempre uguali
    QString lingua = libroNLingua->text().toLower();
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

void DialogUtenteContribuente::contribuenteLSSearch()
{
    //svuoto la QtableWidget
    showSearchResults->clearSelection();
    showSearchResults->clearContents();
    showSearchResults->setRowCount(0);

    //mi salvo gli input dell utente
    QString titolo = libroSTitolo->text().toLower();
    QString autore = libroSAutore->text().toLower();
    QString numedizione = libroSnEdizione->text(); //salvo come stringa anche se ci si aspetta un numero, se l'utente inserisce altro, il tutto funzionerà ma non troverà corrispondenze
    QString casaed = libroSCasaEd->text().toLower();
    QString materia = libroSMateria->currentText(); //non faccio toLower perche non sono campi digitazione e quindi minuscole e maiuscole saranno sempre uguali
    bool onlyDisponibili = false;
    if(libroSDisponibilita->isChecked())
       onlyDisponibili = true;
    else
        onlyDisponibili = false;

    std::list<Articolo*> libriSRitornati = articoliBiblioteca->cercaLibroScolastico
            (titolo.toStdString(), autore.toStdString(), numedizione.toStdString(),
             casaed.toStdString(), materia.toStdString(), onlyDisponibili);

    printArticoli(libriSRitornati);  //stampo nella QTableWidget gli elementi

    //Se non ho trovato nessun elemento lo comunico con una messagebox
    if(libriSRitornati.begin() == libriSRitornati.end())
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo corrispondente trovato :(");
        err.exec();
    }

    //infine distruggo gli elementi di libriRitornati, per non creare garbage
    for(auto it = libriSRitornati.begin(); it != libriSRitornati.end(); it++)
    {
        delete *it; //deallocazione della memoria puntata dall'oggetto Articolo* (quindi l'oggetto stesso)
        it = libriSRitornati.erase(it);
        it--;
    }
}
void DialogUtenteContribuente::contribuenteCdSearch()
{
    //svuoto la QtableWidget
    showSearchResults->clearSelection();
    showSearchResults->clearContents();
    showSearchResults->setRowCount(0);

    //mi salvo gli input dell utente
    QString titolo = cdTitolo->text().toLower();
    QString artista = cdArtista->text().toLower();
    QString genere = cdGenere->currentText(); //non faccio toLower perche non sono campi digitazione e quindi minuscole e maiuscole saranno sempre uguali
    bool onlyDisponibili = false;
    if(cdDisponibilita->isChecked())
       onlyDisponibili = true;
    else
        onlyDisponibili = false;

    std::list<Articolo*> cdRitornati = articoliBiblioteca->cercaCdMusicale
            (titolo.toStdString(), artista.toStdString(), genere.toStdString(), onlyDisponibili);

    printArticoli(cdRitornati);  //stampo nella QTableWidget gli elementi

    //Se non ho trovato nessun elemento lo comunico con una messagebox
    if(cdRitornati.begin() == cdRitornati.end())
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo corrispondente trovato :(");
        err.exec();
    }

    //infine distruggo gli elementi di CdRitornati, per non creare garbage
    for(auto it = cdRitornati.begin(); it != cdRitornati.end(); it++)
    {
        delete *it; //deallocazione della memoria puntata dall'oggetto Articolo* (quindi l'oggetto stesso)
        it = cdRitornati.erase(it);
        it--;
    }
}

void DialogUtenteContribuente::contribuenteRivistaSearch()
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

void DialogUtenteContribuente::contribuenteVediInfo()
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
        else if(tipo == "libroscolastico")
            printInfoLibroS(static_cast<LibroScolastico*>(a));
        else if(tipo == "cdmusicale")
            printInfoCd(static_cast<CdMusicale*>(a));
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

void DialogUtenteContribuente::chiudiInfo()
{
    infoArticoloDialog->close();
}
