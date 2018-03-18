#include "bibliotab.h"

BiblioTab::BiblioTab()
{
    createBiblioTab(); //creo l'interfaccia grafica
    fillBiblioTab(); //riempio i campi dati (da file xml)
}

void BiblioTab::createBiblioTab()
{
    //elementi grafici
    addArticolo = new QPushButton("Aggiungi nuovo articolo",this);
    delArticolo = new QPushButton("Cancella articolo dalla biblioteca",this);
    modDisponibilita = new QPushButton("Modifica disponibilita articolo", this);
    infoArticolo = new QPushButton("Visualizza informazioni articolo", this);

    showArticoli = new QTableWidget(this);
    QStringList titles {"ID", "Tipologia", "Titolo", "Anno di pubblicazione", "Disponibilita"}; //table
    showArticoli->setColumnCount(titles.size());
    showArticoli->setHorizontalHeaderLabels(titles);
    showArticoli->setSortingEnabled(false);
    showArticoli->setEditTriggers(QAbstractItemView::NoEditTriggers); //rendo la tabella non editabile

    salvaModificheArt = new QPushButton("Salva modifiche su file", this);

    //textbrowser sotto che mi mostrera i mess d'errore o di avvenuto inserimento
    showMessage = new QTextBrowser(this);
    //ne aggiusto le dimensioni
    QFontMetrics font_metrics(showMessage->font());
    int font_height = font_metrics.height();
    int height = font_height * 2; //altezza settata a circa 2 righe di font
    showMessage->setFixedHeight(height);

    //layout orizzontale per i bottoni sopra
    QGridLayout* buttonLayout = new QGridLayout();
    buttonLayout->addWidget(addArticolo, 0, 0);
    buttonLayout->addWidget(delArticolo, 0, 1);
    buttonLayout->addWidget(modDisponibilita, 1, 0);
    buttonLayout->addWidget(infoArticolo, 1, 1);

    //inserisco i bottoniTop in una groupbox
    QGroupBox* bottoniTop= new QGroupBox();
    bottoniTop->setLayout(buttonLayout);
    bottoniTop->setFlat(true);

    //layout piu generale che include tutti gli elementi
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(bottoniTop);
    layout->addWidget(showArticoli);
    layout->addWidget(salvaModificheArt);
    layout->addWidget(showMessage);
    setLayout(layout);//applico questo layout alla gUtentiTab

    //collego ogni elemento con il suo slot, tramite segnali e slot
    connect(addArticolo, SIGNAL(clicked()), this, SLOT(aggiungiArticolo1()));
    connect(delArticolo, SIGNAL(clicked()), this, SLOT(eliminaArticolo()));
    connect(modDisponibilita, SIGNAL(clicked()), this, SLOT(modificaDisponibilitaArticolo()));
    connect(infoArticolo, SIGNAL(clicked()), this, SLOT(visualizzaInfoArticolo()));
    connect(salvaModificheArt, SIGNAL(clicked()), this, SLOT(salvaTuttoArticoli()));
}

void BiblioTab::fillBiblioTab()
{
    articoliBiblioteca = new Biblioteca();

    //provo ad aprire il file con gli articoli
    QFile file(QDir::currentPath().append("/../bibliotecaScolastica/xml/articolidb.xml"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //se il file non si apre
    {
        showMessage->setText("Attenzione! Non è stato possibile caricare i dati; il file potrebbe essere mancante o nella directory sbagliata.");
        showMessage->setTextColor(Qt::red);
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

        //lo aggiungo nella QTable
        printArticolo(a);
        }
        //ed esamino il prossimo <articolo>
        it= it.nextSibling().toElement();
     }

    //una volta inseriti tutti, indico il numero di articoli posseduti
    showMessage->setText("Benvenuto! La biblioteca possiede " + QString::number(articoliBiblioteca->getNumeroArt()) + " articoli.");
}

void BiblioTab::printArticolo(Articolo* a) const //stampa nella QTableWidget l'articolo a
{
    const int row = showArticoli->rowCount();
    showArticoli->insertRow(row);
    showArticoli->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a->getId())));
    showArticoli->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a->getDynamicType())));
    showArticoli->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a->getTitolo())));
    showArticoli->setItem(row, 3, new QTableWidgetItem(QString::number(a->getAnnoPubblicazione())));
    if(a->getDisponibilita())
        showArticoli->setItem(row, 4, new QTableWidgetItem("Disponibile"));
    else
        showArticoli->setItem(row, 4, new QTableWidgetItem("In prestito"));
}


//crea interfaccia per l'aggiunta di un libro di narrativa
void BiblioTab::createAddLibroN()
{
    aggiuntaLibroN = new QDialog();

    //elementi grafici per libro narrativa
    QGroupBox* g = new QGroupBox("Completa informazioni Libro di Narrativa");
    QGridLayout* gLayout = new QGridLayout();

    QLabel* label0 = new QLabel("Autore:", aggiuntaLibroN);
    lnAddAutore = new QLineEdit(aggiuntaLibroN);
    QLabel* label1 = new QLabel("Casa Editrice:", aggiuntaLibroN);
    lnAddCasaEd = new QLineEdit(aggiuntaLibroN);
    QLabel* label2= new QLabel("Numero pagine:", aggiuntaLibroN);
    lnAddPag = new QSpinBox(aggiuntaLibroN);
    lnAddPag->setRange(0, 2000);
    lnAddPag->setSingleStep(1);
    lnAddPag->setValue(100);
    QLabel* label2bis= new QLabel("Lingua originale:",aggiuntaLibroN);
    lnAddLingua = new QLineEdit(aggiuntaLibroN);
    QLabel* label3= new QLabel("Genere letterario:", aggiuntaLibroN);
    lnAddGenere = new QComboBox(aggiuntaLibroN);
    lnAddGenere->addItem("Romanzo","Romanzo");
    lnAddGenere->addItem("Biografia","Biografia");
    lnAddGenere->addItem("Racconti","Racconti");
    lnAddGenere->addItem("Storiografia","Storiografia");
    lnAddGenere->addItem("Libro illustrato","Libro illustrato");
    lnAddGenere->model()->sort(0); // ordino alfabeticamente
    QLabel* label4= new QLabel("Fascia di età target:", aggiuntaLibroN);
    lnAddEta = new QComboBox(aggiuntaLibroN);
    lnAddEta->addItem("Bambini 6-10 anni","Bambini 6-10 anni");
    lnAddEta->addItem("Ragazzi 10-13 anni","Ragazzi 10-14 anni");
    lnAddEta->addItem("Adolescenti 14-16 anni","Adolescenti 14-16 anni");
    lnAddEta->addItem("Giovani adulti 17-22 anni","Giovani adulti 17-22 anni");
    lnAddEta->addItem("Adulti","Adulti");

    gLayout-> addWidget(label0, 0 , 0);
    gLayout-> addWidget(lnAddAutore, 0 , 1);
    gLayout-> addWidget(label1, 1 , 0);
    gLayout-> addWidget(lnAddCasaEd, 1 , 1);
    gLayout-> addWidget(label2, 2 , 0);
    gLayout-> addWidget(lnAddPag, 2 , 1);
    gLayout-> addWidget(label2bis, 3, 0);
    gLayout-> addWidget(lnAddLingua, 3, 1);
    gLayout-> addWidget(lnAddGenere, 4 , 1);
    gLayout-> addWidget(label3, 4 , 0);
    gLayout-> addWidget(label4, 5 , 0);
    gLayout-> addWidget(lnAddEta, 5 , 1);
    g->setLayout(gLayout);

    //push button e il suo slot
    aggiuntaArtConfirm = new QPushButton("Conferma", aggiuntaLibroN);
    connect(aggiuntaArtConfirm, SIGNAL(clicked()), this, SLOT(aggiungiArticoloConfirm()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(g);
    layout->addWidget(aggiuntaArtConfirm);
    aggiuntaLibroN->setLayout(layout);

    aggiuntaLibroN->setWindowTitle(tr("Inserimento nuovo articolo (2)"));
    aggiuntaLibroN->setFixedWidth(350);
    aggiuntaLibroN->exec();
}

//crea interfaccia per l'aggiunta di un libro scolastico
void BiblioTab::createAddLibroS()
{
    aggiuntaLibroS = new QDialog();

    //elementi grafici per libro Scolastico
    QGroupBox* g = new QGroupBox("Completa informazioni Libro Scolastico");
    QGridLayout* gLayout = new QGridLayout();

    QLabel* label0 = new QLabel("Autore/i:", aggiuntaLibroS);
    lsAddAutore = new QLineEdit(aggiuntaLibroS);
    QLabel* label1 = new QLabel("Casa Editrice:", aggiuntaLibroS);
    lsAddCasaEd = new QLineEdit(aggiuntaLibroS);
    QLabel* label2= new QLabel("Numero pagine:", aggiuntaLibroS);
    lsAddPag = new QSpinBox(aggiuntaLibroS);
    lsAddPag->setRange(0, 2000);
    lsAddPag->setSingleStep(1);
    lsAddPag->setValue(100);
    QLabel* label3= new QLabel("Materia trattata:", aggiuntaLibroS);
    lsAddMateria = new QComboBox(aggiuntaLibroS);
    lsAddMateria->addItem("Matematica","Matematica");
    lsAddMateria->addItem("Scienze","Scienze");
    lsAddMateria->addItem("Filosofia","Filosofia");
    lsAddMateria->addItem("Programmazione","Programmazione");
    lsAddMateria->addItem("Letteratura italiana","Letteratura italiana");
    lsAddMateria->addItem("Letteratura straniera","Letteratura straniera");
    lsAddMateria->addItem("Storia","Storia");
    lsAddMateria->addItem("Fisica","Fisica");
    lsAddMateria->addItem("Arte","Arte");
    lsAddMateria->addItem("Psicologia","Psicologia");
    lsAddMateria->addItem("Geografia","Geografia");
    lsAddMateria->addItem("Politica","Politica");
    lsAddMateria->addItem("Grammatica","Grammatica");
    lsAddMateria->addItem("Religione","Religione");
    lsAddMateria->addItem("Musica","Musica");
    lsAddMateria->addItem("Educazione fisica","Educazione fisica");
    lsAddMateria->addItem("Elettronica","Elettronica");
    lsAddMateria->addItem("Disegno tecnico","Disegno tecnico");
    lsAddMateria->addItem("Tecnologia","Tecnologia");
    lsAddMateria->model()->sort(0); //siccome sono tanti elementi li ordino alfabeticamente
    QLabel* label4= new QLabel("Numero Edizione:", aggiuntaLibroS);
    lsAddEd = new QSpinBox(aggiuntaLibroS);
    lsAddEd->setRange(1, 50);
    lsAddEd->setSingleStep(1);
    lsAddEd->setValue(1);

    gLayout-> addWidget(label0, 0 , 0);
    gLayout-> addWidget(lsAddAutore, 0 , 1);
    gLayout-> addWidget(label1, 1 , 0);
    gLayout-> addWidget(lsAddCasaEd, 1 , 1);
    gLayout-> addWidget(label2, 2 , 0);
    gLayout-> addWidget(lsAddPag, 2 , 1);
    gLayout-> addWidget(label3, 3 , 0);
    gLayout-> addWidget(lsAddMateria, 3 , 1);
    gLayout-> addWidget(label4, 4 , 0);
    gLayout-> addWidget(lsAddEd, 4 , 1);
    g->setLayout(gLayout);

    //push button e il suo slot
    aggiuntaArtConfirm = new QPushButton("Conferma", aggiuntaLibroS);
    connect(aggiuntaArtConfirm, SIGNAL(clicked()), this, SLOT(aggiungiArticoloConfirm()));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(g);
    layout->addWidget(aggiuntaArtConfirm);
    aggiuntaLibroS->setLayout(layout);

    aggiuntaLibroS->setWindowTitle(tr("Inserimento nuovo articolo (2)"));
    aggiuntaLibroS->setFixedWidth(350);
    aggiuntaLibroS->exec();
}

//crea interfaccia per l'aggiunta di un CD
void BiblioTab::createAddCd()
{
   aggiuntaCd = new QDialog();

   //elementi grafici per aggiuntaCd
   QGroupBox* g = new QGroupBox("Completa informazioni CD");
   QGridLayout* gLayout = new QGridLayout();
   QLabel* label0 = new QLabel("Artista/i:", aggiuntaCd);
   cdAddArtista= new QLineEdit(aggiuntaCd);
   QLabel* label1= new QLabel("Genere:", aggiuntaCd);
   cdAddGenere = new QComboBox(aggiuntaCd);
   cdAddGenere->addItem("Musica classica","Musica classica");
   cdAddGenere->addItem("Musica moderna d'intrattenimento","Musica moderna d'intrattenimento");
   cdAddGenere->addItem("Audiolibro","Audiolibro");
   cdAddGenere->addItem("Musica strumentale","Musica strumentale");
   cdAddGenere->addItem("Suoni rilassanti per lo studio","Suoni rilassanti per lo studio");
   cdAddGenere->addItem("Basi per lezioni di danza","Basi per lezioni di danza");
   cdAddGenere->model()->sort(0);
   QLabel* label2 = new QLabel("Numero tracce:", aggiuntaCd);
   cdAddTracce = new QSpinBox(aggiuntaCd);
   cdAddTracce->setRange(1, 100);
   cdAddTracce->setSingleStep(1);
   cdAddTracce->setValue(1);

   gLayout-> addWidget(label0, 0 , 0);
   gLayout-> addWidget(cdAddArtista, 0 , 1);
   gLayout-> addWidget(label1, 1 , 0);
   gLayout-> addWidget(cdAddGenere, 1 , 1);
   gLayout-> addWidget(label2, 2 , 0);
   gLayout-> addWidget(cdAddTracce, 2 , 1);
   g->setLayout(gLayout);

   //push button e il suo slot
   aggiuntaArtConfirm = new QPushButton("Conferma", aggiuntaCd);
   connect(aggiuntaArtConfirm, SIGNAL(clicked()), this, SLOT(aggiungiArticoloConfirm()));

   QGridLayout* layout = new QGridLayout;
   layout->addWidget(g);
   layout->addWidget(aggiuntaArtConfirm);
   aggiuntaCd->setLayout(layout);

   aggiuntaCd->setWindowTitle(tr("Inserimento nuovo articolo (2)"));
   aggiuntaCd->setFixedWidth(350);
   aggiuntaCd->exec();
}

//crea interfaccia per l'aggiunta di una rivista
void BiblioTab::createAddRivista()
{
    aggiuntaRivista = new QDialog();

    //elementi grafici per libro Scolastico
    QGroupBox* g = new QGroupBox("Completa informazioni Libro Scolastico");
    QGridLayout* gLayout = new QGridLayout();

    QLabel* label0 = new QLabel("Numero volume:", aggiuntaRivista);
    rvAddNumero = new QSpinBox(aggiuntaRivista);
    rvAddNumero->setRange(1, 5000);
    rvAddNumero->setSingleStep(1);
    rvAddNumero->setValue(1);
    QLabel* label1 = new QLabel("Periodicità:", aggiuntaRivista);
    rvAddPeriodicita = new QComboBox(aggiuntaRivista);
    rvAddPeriodicita->addItem("Settimanale","Settimanale");
    rvAddPeriodicita->addItem("Bisettimanale","Bisettimanale");
    rvAddPeriodicita->addItem("Mensile","Mensile");
    rvAddPeriodicita->addItem("Bimensile","Bimensile");
    rvAddPeriodicita->addItem("Trimestrale","Trimestrale");
    rvAddPeriodicita->addItem("Periodicità variabile","Periodicità variabile");
    QLabel* label2= new QLabel("Argomento trattato:", aggiuntaRivista);
    rvAddArgomento = new QLineEdit(aggiuntaRivista);
    QLabel* label3= new QLabel("Numero pagine:", aggiuntaRivista);
    rvAddPag = new QSpinBox(aggiuntaRivista);
    rvAddPag->setRange(1, 500);
    rvAddPag->setSingleStep(1);
    rvAddPag->setValue(50);

    gLayout-> addWidget(label0, 0 , 0);
    gLayout-> addWidget(rvAddNumero, 0 , 1);
    gLayout-> addWidget(label1, 1 , 0);
    gLayout-> addWidget(rvAddPeriodicita, 1 , 1);
    gLayout-> addWidget(label2, 2 , 0);
    gLayout-> addWidget(rvAddArgomento, 2 , 1);
    gLayout-> addWidget(label3, 3 , 0);
    gLayout-> addWidget(rvAddPag, 3 , 1);
    g->setLayout(gLayout);

    //push button e il suo slot
    aggiuntaArtConfirm = new QPushButton("Conferma", aggiuntaRivista);
    connect(aggiuntaArtConfirm, SIGNAL(clicked()), this, SLOT(aggiungiArticoloConfirm()));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(g);
    layout->addWidget(aggiuntaArtConfirm);
    aggiuntaRivista->setLayout(layout);

    aggiuntaRivista->setWindowTitle(tr("Inserimento nuovo articolo (2)"));
    aggiuntaRivista->setFixedWidth(350);
    aggiuntaRivista->exec();
}

//crea la finestra per la visualizzazione delle informazioni complete di un articolo
void BiblioTab::createVisualizzaInfoArticolo()
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

//stampa nel QTextBrowser showInfoArticolo le informazioni complete di un libro di narrativa
void BiblioTab::printInfoLibroN(LibroNarrativa* libroN) const
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

//stampa nel QTextBrowser showInfoArticolo le informazioni complete di un libro scolastico
void BiblioTab::printInfoLibroS(LibroScolastico* libroS) const
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

//stampa nel QTextBrowser showInfoArticolo le informazioni complete di un CD
void BiblioTab::printInfoCd(CdMusicale* cd) const
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

//stampa nel QTextBrowser showInfoArticolo le informazioni complete di una rivista
void BiblioTab::printInfoRivista(Rivista* rivista) const
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

//-------SLOTS di BiblioTab ------

//1) Aggiunta articolo
void BiblioTab::aggiungiArticolo1()
{
    //cancello il testo dalla Qtextbrowser per non creare confusione con azioni precedenti
    showMessage->setText(" ");

    aggiuntaArt = new QDialog();

    //combo box per la scelta del tipo utente
    QLabel* labelTipoArt= new QLabel("Tipo di articolo da aggiungere:", aggiuntaArt);
    tipoArt = new QComboBox(aggiuntaArt);
    tipoArt->addItem("Libro di narrativa","libronarrativa");
    tipoArt->addItem("Libro di testo scolastico","libroscolastico");
    tipoArt->addItem("Cd musicale","cdmusicale");
    tipoArt->addItem("Rivista","rivista");

    //groupbox con le lineEdit all'interno
    QGroupBox* g = new QGroupBox("Inserisci dati articolo");
    QGridLayout* gLayout = new QGridLayout();
    QLabel* labelId = new QLabel("ID:", aggiuntaArt);
    addId = new QLineEdit(aggiuntaArt);
    QLabel* labelTitolo= new QLabel("Titolo/Nome:", aggiuntaArt);
    addTitolo = new QLineEdit(aggiuntaArt);
    QLabel* labelAnno = new QLabel("Anno di pubblicazione:", aggiuntaArt);
    addAnno = new QSpinBox(aggiuntaArt);
    addAnno->setRange(1200, 2017);
    addAnno->setSingleStep(1);
    addAnno->setValue(2017);

    gLayout-> addWidget(labelId, 0 , 0);
    gLayout-> addWidget(addId, 0 , 1);
    gLayout-> addWidget(labelTitolo, 1 , 0);
    gLayout-> addWidget(addTitolo, 1 , 1);
    gLayout-> addWidget(labelAnno, 2 , 0);
    gLayout-> addWidget(addAnno, 2 , 1);
    g->setLayout(gLayout);

    //push button e il suo slot
    aggiuntaArtNext = new QPushButton("Avanti", aggiuntaArt);
    connect(aggiuntaArtNext, SIGNAL(clicked()), this, SLOT(aggiungiArticolo2()));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(labelTipoArt);
    layout->addWidget(tipoArt);
    layout->addWidget(g);
    layout->addWidget(aggiuntaArtNext);

    aggiuntaArt->setLayout(layout);
    aggiuntaArt->setWindowTitle(tr("Inserimento nuovo articolo (1)"));
    aggiuntaArt->setFixedWidth(350);
    aggiuntaArt->exec();
}

void BiblioTab::aggiungiArticolo2()
{
    //controllo inanzitutto che i campi siano compilati
    if(addId->text().isEmpty() || addTitolo->text().isEmpty())
    {
        QMessageBox addErr(this);
        addErr.setWindowTitle("Operazione non riuscita");
        addErr.setText("E' necessario inserire ID e Titolo.");
        addErr.exec();
    }
    else if(!articoliBiblioteca->checkAvaiableId(addId->text().toUpper().toStdString())) //controllo se l'ID inserito è valido
    {
        QMessageBox addErr(this);
        addErr.setWindowTitle("ID già usato");
        addErr.setText("E' già presente un articolo con l'ID specificato. \n Scegliere un altro ID.");
        addErr.exec();
    }
    else
    {
        aggiuntaArt->close(); //chiudo la finestra precedente
        QString tipo = tipoArt->currentText(); //a seconda del tipo che voglio andare a creare apro un diverso dialog
        if(tipo == "Libro di narrativa")
        {
            createAddLibroN();
        }
        else if(tipo == "Libro di testo scolastico")
        {
            createAddLibroS();
        }
        else if(tipo == "Cd musicale")
        {
            createAddCd();
        }
        else if(tipo == "Rivista")
        {
            createAddRivista();
        }
    }
}

void BiblioTab::aggiungiArticoloConfirm()
{
    //non controllo che i campi siano compilati, in quanto è possibile anche lasciarli vuoti

    //mi salvo inanzitutto le variabil in comune dei vari tipi di articolo
    QString tipo = tipoArt->currentText();
    QString id= addId->text().toUpper();
    QString titolo= addTitolo->text();
    unsigned int anno= addAnno->value();

    Articolo * a; //puntatore polimorfo a articolo
    //e poi le altre a seconda di quale tipo di articolo sto creando
    if(tipo == "Libro di narrativa")
    {
        QString autore = lnAddAutore->text();
        QString casaEd = lnAddCasaEd->text();
        unsigned int pagine = lnAddPag->value();
        QString lingua = lnAddLingua->text();
        QString genere = lnAddGenere->currentText();
        QString eta = lnAddEta->currentText();
        //creo l'oggetto libro narrativa
        a = new LibroNarrativa(id.toStdString(), titolo.toStdString(), anno, true, autore.toStdString(),
                               casaEd.toStdString(), pagine, lingua.toStdString(), genere.toStdString(), eta.toStdString());
        //chiudo finestra
        aggiuntaLibroN->close();
    }
    else if(tipo == "Libro di testo scolastico")
    {
        QString autore = lsAddAutore->text();
        QString casaEd = lsAddCasaEd->text();
        unsigned int pagine = lsAddPag->value();
        QString materia = lsAddMateria->currentText();
        unsigned int numEd = lsAddEd->value();
        //creo l'oggetto libro scolastico
        a = new LibroScolastico(id.toStdString(), titolo.toStdString(), anno, true, autore.toStdString(),
                               casaEd.toStdString(), pagine, materia.toStdString(), numEd);
        //chiudo finestra
        aggiuntaLibroS->close();
    }
    else if(tipo == "Cd musicale")
    {
        QString artista = cdAddArtista->text();
        QString genere = cdAddGenere->currentText();
        unsigned int tracce =  cdAddTracce->value();
        //creo l'oggetto Cd
        a = new CdMusicale(id.toStdString(), titolo.toStdString(), anno, true, artista.toStdString(), genere.toStdString(), tracce);

        //chiudo la finestra di aggiunta (faccio ora perchè poi non mi è piu possibile distinguere tra le varie finesrre)
        aggiuntaCd->close();
    }
    else if(tipo == "Rivista")
    {
        unsigned int numero = rvAddNumero->value();
        QString periodicita = rvAddPeriodicita->currentText();
        QString argomento = rvAddArgomento->text();
        unsigned int pagine =  rvAddPag->value();
        //creo l'oggetto Rivista
        a = new Rivista(id.toStdString(), titolo.toStdString(), anno, true, numero,
                        periodicita.toStdString(), argomento.toStdString(), pagine);
        //chiudo la finestra di aggiunta
        aggiuntaRivista->close();
    }

    if(a) //se ho creato correttamente a
    {
        articoliBiblioteca->articoli.push_back(a);
        articoliBiblioteca->piuUno(); //incremento contatore
        printArticolo(a); //lo visualizzo nella QTable
        //e do un messaggio di avvenuto inserimento
        showMessage->setTextColor(Qt::green);
        showMessage->setText("Articolo aggiunto con successo. Numero articoli nella biblioteca: " + QString::number(articoliBiblioteca->getNumeroArt()));
    }
}

//2)Eliminazione articolo
void BiblioTab::eliminaArticolo()
{
    showMessage->setText(" ");

    if(showArticoli->currentIndex().isValid()) //controllo se è stata selezionata una riga della table (cioe un articolo)
    {
        //faccio l'erase dell'articolo da articoliBiblioteca tramite l'ID, che si trova in item(riga corrente, colonna 0)
        QString id = showArticoli->item(showArticoli->currentIndex().row(), 0)->text();
        articoliBiblioteca->rimuoviArticolo(id.toStdString());
        //rimuovo anche la riga dalla tabella e avviso della rimozione
        showArticoli->removeRow(showArticoli->currentRow());
        showMessage->setTextColor(Qt::green);
        showMessage->setText("Articolo eliminato. La biblioteca possiede " + QString::number(articoliBiblioteca->getNumeroArt()) + " articoli.");

    }
    else //se nessuna riga è selezionata dico di farlo
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo selezionato.\n Selezionare dalla tabella l'articolo che si vuole eliminare.");
        err.exec();
    }
}

//3) Modifica disponibilita
void BiblioTab::modificaDisponibilitaArticolo()
{
    showMessage->setText(" "); //ripulisco la textbrowser per non creare confusione

    //controllo inanzitutto se è stato selezionato l'articolo da modificare
    if(showArticoli->currentIndex().isValid())
    {
        //mi salvo l'ID dell'articolo da modificare
        articolodaModificare = showArticoli->item(showArticoli->currentIndex().row(), 0)->text();

        //modifico la disponibilita, e mi salvo la nuova
        bool nuovaDisp = articoliBiblioteca->cambiaDisponibilita(articolodaModificare.toStdString());
        //la "traduco" in parole
        QString nuovaDispStringa;
        if(nuovaDisp == true)
            nuovaDispStringa = "Disponibile";
        else
            nuovaDispStringa = "In prestito";

        //infine lo cambio anche nella tabella e do un messaggio dell'avvenuto cambiamento
        showArticoli->item(showArticoli->currentIndex().row(), 4)->setText(nuovaDispStringa);
        showMessage->setTextColor(Qt::green);
        showMessage->setText("Disponibilita modificata con successo. Ora l'articolo è " + nuovaDispStringa.toUpper() + ".");
    }
    else //se nessuna riga è selezionata dico di farlo
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun articolo selezionato.\n Selezionare dalla tabella l'articolo da prestare/ritornare.");
        err.exec();
    }
}

//4) Visualizza articolo
void BiblioTab::visualizzaInfoArticolo()
{
    showMessage->setText(" "); //ripulisco la textbrowser della finestra principale ad ogni operazione per non creare confusione

    if(showArticoli->currentIndex().isValid())
    {
        //creo la finestra
        createVisualizzaInfoArticolo();

        //mi salvo l'ID dell'articolo da visualizzare
        articolodaVisualizzare = showArticoli->item(showArticoli->currentIndex().row(), 0)->text();

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

void BiblioTab::chiudiInfo()
{
    infoArticoloDialog->close();
}

//5)Salvataggio
void BiblioTab::salvaTuttoArticoli()
{
    showMessage->setText(" "); //ripulisco la textbrowser della finestra principale ad ogni operazione per non creare confusione

    QDomDocument doc;
    QDomElement root = doc.createElement("articoli"); //<articoli> elemento radice
    doc.appendChild(root); //inserisco la radice

    //ciclo sugli elementi presenti nella lista articoli
    for(auto it= articoliBiblioteca->articoli.begin();  it!= articoliBiblioteca->articoli.end(); it++)
    {
        //salvo inanzitutto le informazioni condivise di tutti i sottotipi di articolo, dell articolo corrente
        QString tipo = QString::fromStdString((*it)->getDynamicType()).toLower();
        QString id = QString::fromStdString((*it)->getId());
        QString titolo = QString::fromStdString((*it)->getTitolo());
        QString anno =  QString::number((*it)->getAnnoPubblicazione());
        QString disp;
        if((*it)->getDisponibilita() == true)
            disp = "disponibile";
        else
            disp = "in prestito";

        //e, dopo aver creato l'elemento articolo, inserisco queste prime informazioni nel file xml
        QDomElement articolo = doc.createElement("articolo"); // crea <articolo>
        articolo.setAttribute("tipologia", tipo); //attributi di <articolo>
        articolo.setAttribute("id", id);
        QDomElement aTitolo  = doc.createElement("titolo"); // <titolo>
        aTitolo.appendChild(doc.createTextNode(titolo));
        articolo.appendChild(aTitolo);
        QDomElement aAnno  = doc.createElement("anno"); // <anno>
        aAnno.appendChild(doc.createTextNode(anno));
        articolo.appendChild(aAnno);
        QDomElement aDisponibilita  = doc.createElement("disponibilita"); // <disponibilita>
        aDisponibilita.appendChild(doc.createTextNode(disp));
        articolo.appendChild(aDisponibilita);

        //diramo a seconda del sottotipo e continuo l'append delle imformazioni
        if(tipo == "libronarrativa" || tipo == "libroscolastico")
        {
            Libro* libro = static_cast<Libro*>(*it);

            QString autore = QString::fromStdString(libro->getAutore());
            QString casaEd = QString::fromStdString(libro->getCasaEditrice());
            QString pagine = QString::number(libro->getPagine());

            QDomElement aAutore  = doc.createElement("autore"); // <autore>
            aAutore.appendChild(doc.createTextNode(autore));
            articolo.appendChild(aAutore);
            QDomElement aCasaEd  = doc.createElement("casaEditrice"); // <casaEditrice>
            aCasaEd.appendChild(doc.createTextNode(casaEd));
            articolo.appendChild(aCasaEd);
            QDomElement aPagine  = doc.createElement("pagine"); // <pagine>
            aPagine.appendChild(doc.createTextNode(pagine));
            articolo.appendChild(aPagine);

            if(tipo == "libronarrativa")
            {
                LibroNarrativa* libroN = static_cast<LibroNarrativa*>(libro);

                 QString lingua = QString::fromStdString(libroN->getLinguaOriginale());
                 QString genere = QString::fromStdString(libroN->getGenereNarrativo());
                 QString eta = QString::fromStdString(libroN->getEtaTarget());

                 QDomElement aLingua  = doc.createElement("linguaOriginale"); // <linguaOriginale>
                 aLingua.appendChild(doc.createTextNode(lingua));
                 articolo.appendChild(aLingua);
                 QDomElement aGenere  = doc.createElement("genere"); // <genere>
                 aGenere.appendChild(doc.createTextNode(genere));
                 articolo.appendChild(aGenere);
                 QDomElement aEta  = doc.createElement("etaTarget"); // <etaTarget>
                 aEta.appendChild(doc.createTextNode(eta));
                 articolo.appendChild(aEta);
            }
            else if(tipo == "libroscolastico")
            {
                LibroScolastico* libroS = static_cast<LibroScolastico*>(libro);

                QString materia = QString::fromStdString(libroS->getMateria());
                QString edizione = QString::number(libroS->getEdizione());

                QDomElement aMateria  = doc.createElement("materia"); // <materia>
                aMateria.appendChild(doc.createTextNode(materia));
                articolo.appendChild(aMateria);
                QDomElement aEdizione  = doc.createElement("edizione"); // <edizione>
                aEdizione.appendChild(doc.createTextNode(edizione));
                articolo.appendChild(aEdizione);
            }

        }
        else if(tipo == "cdmusicale")
        {
            CdMusicale* cd = static_cast<CdMusicale*>(*it);

            QString artista = QString::fromStdString(cd->getArtista());
            QString genereCd = QString::fromStdString(cd->getGenere());
            QString tracce = QString::number(cd->getNumeroTracce());

            QDomElement aArtista  = doc.createElement("artista"); // <artista>
            aArtista.appendChild(doc.createTextNode(artista));
            articolo.appendChild(aArtista);
            QDomElement aGenereCd  = doc.createElement("genere"); // <genere>
            aGenereCd.appendChild(doc.createTextNode(genereCd));
            articolo.appendChild(aGenereCd);
            QDomElement aTracce  = doc.createElement("tracce"); // <tracce>
            aTracce.appendChild(doc.createTextNode(tracce));
            articolo.appendChild(aTracce);

        }
        else if(tipo == "rivista")
        {
            Rivista* rivista = static_cast<Rivista*>(*it);

            QString volume = QString::number(rivista->getNumero());
            QString periodicita = QString::fromStdString(rivista->getPeriodicita());
            QString argomento = QString::fromStdString(rivista->getArgomento());
            QString pagineRivista = QString::number(rivista->getNumeroPagine());

            QDomElement aVolume  = doc.createElement("numeroVolume"); // <numeroVolume>
            aVolume.appendChild(doc.createTextNode(volume));
            articolo.appendChild(aVolume);
            QDomElement aPeriodicita  = doc.createElement("periodicita"); // <periodicita>
            aPeriodicita.appendChild(doc.createTextNode(periodicita));
            articolo.appendChild(aPeriodicita);
            QDomElement aArgomento  = doc.createElement("argomento"); // <argomento>
            aArgomento.appendChild(doc.createTextNode(argomento));
            articolo.appendChild(aArgomento);
            QDomElement aPagineRivista  = doc.createElement("pagine"); // <pagine>
            aPagineRivista.appendChild(doc.createTextNode(pagineRivista));
            articolo.appendChild(aPagineRivista);
        }

        root.appendChild(articolo); //appendo alla root l'articolo appena creato

    } //fine ciclo for

    //apro il file in scrittura
    QFile file(QDir::currentPath().append("/../bibliotecaScolastica/xml/articolidb.xml"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //se il file non si apre
    {
        showMessage->setTextColor(Qt::red);
        showMessage->setText("Salvataggio non riuscito. Errore nell'apertura del file");
    }
    QTextStream xout(&file);
    xout<< doc.toString();
    file.flush();
    file.close();

    //operazione avvenuta con successo
    showMessage->setTextColor(Qt::green);
    showMessage->setText("Modifiche salvate. Articoli totali: " + QString::number(articoliBiblioteca->getNumeroArt()));
}
