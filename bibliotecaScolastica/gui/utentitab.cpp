#include "utentitab.h"

UtentiTab::UtentiTab()
{
    //funzione che mi crea l'interfaccia
    createUtentiTab();

    //riempio i campi dati e visualizzo gli utenti su UtentiTab
    fillUtentiRegistrati();
}

//funzione ausiliaria per la costruzione dell interfaccia
void UtentiTab::createUtentiTab()
{
    //elementi grafici
    addUtente = new QPushButton("Aggiungi nuovo utente",this);
    delUtente = new QPushButton("Elimina utente",this);
    modTipoUtente = new QPushButton("Modifica tipo utente",this);
    showUtenti = new QTableWidget(this);

    //setting della QTableWidget
    QStringList titles {"Username", "Password", "Nome", "Cognome", "Tipo utente"};
    showUtenti->setColumnCount(titles.size());
    showUtenti->setHorizontalHeaderLabels(titles);
    showUtenti->setSortingEnabled(false);
    showUtenti->setEditTriggers(QAbstractItemView::NoEditTriggers); //rendo la tabella non editabile

    salvaModificheUt = new QPushButton("Salva modifiche su file", this);

    //textbrowser sotto che mi mostrera i mess d'errore o di avvenuto inserimento
    showMessage = new QTextBrowser(this);
    //ne aggiusto le dimensioni
    QFontMetrics font_metrics(showMessage->font());
    int font_height = font_metrics.height();
    int height = font_height * 2; //altezza settata a circa 2 righe di font
    showMessage->setFixedHeight(height);

    //layout orizzontale per i bottoni sopra
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addUtente);
    buttonLayout->addWidget(delUtente);
    buttonLayout->addWidget(modTipoUtente);

    //inserisco i bottoniTop in una groupbox
    QGroupBox* bottoniTop= new QGroupBox();
    bottoniTop->setFlat(true);
    bottoniTop->setLayout(buttonLayout);

    //layout piu generale che include tutti gli elementi
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(bottoniTop);
    layout->addWidget(showUtenti);
    layout->addWidget(salvaModificheUt);
    layout->addWidget(showMessage);
    setLayout(layout);//applico questo layout alla gUtentiTab

    //collego ogni elemento con il suo slot, tramite segnali e slot
    connect(addUtente, SIGNAL(clicked()), this, SLOT(aggiungiUtente()));
    connect(delUtente, SIGNAL(clicked()), this, SLOT(eliminaUtente()));
    connect(modTipoUtente, SIGNAL(clicked()), this, SLOT(modificaUtente()));
    connect(salvaModificheUt, SIGNAL(clicked()), this, SLOT(salvaTuttoUt()));
}

//fillListaRegistrati inizializza un oggetto Registrazioni, caricando da file i dati
void UtentiTab::fillUtentiRegistrati()
{
    utentiRegistrati = new Registrazioni();

    //provo ad aprire il file
    QFile file(QDir::currentPath().append("/../bibliotecaScolastica/xml/utentidb.xml"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //se il file non si apre
    {
        showMessage->setText("Attenzione! Non è stato possibile caricare i dati; il file potrebbe essere mancante o nella directory sbagliata.");
        showMessage->setTextColor(Qt::red);
    }

    QDomDocument doc;
    doc.setContent(&file);

    file.close(); //chiudo il file perchè i dati son gia in doc (di tipo QDomDocument)

    QDomElement root = doc.firstChild().toElement();  //cioè <utenti> nel doc XML
    QDomElement it= root.firstChild().toElement(); //cioè <utente> singolo; li scorro con un iteratore
    //scorro ogni utente e li inserisco in utentiRegistrati
    while(!it.isNull())
    {
        //inserisco l'utente corrente
        Utente* utente = utentiRegistrati->inserisciUtente(it.attribute("username").toStdString(), it.firstChild().toElement().text().toStdString(),
                                          it.firstChild().nextSibling().toElement().text().toStdString(),
                                          it.firstChild().nextSibling().nextSibling().toElement().text().toStdString(),
                                          it.firstChild().nextSibling().nextSibling().nextSibling().toElement().text().toStdString());

        if(utente) //lo aggiungo nella QTable
            printUtente(utente);

        //ed esamino il prossimo <utente>
        it= it.nextSibling().toElement();
    }
    //indico il numero di utenti registrati
    showMessage->setText("Benvenuto! Ci sono " + QString::number(utentiRegistrati->getNumUtenti()) + " utenti registrati nel sistema bibliotecario.");
}

//stampa l'utente nella QTable showUtenti
void UtentiTab::printUtente(Utente* utente) const
{
    const int row = showUtenti->rowCount();
    showUtenti->insertRow(row);
    showUtenti->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(utente->getUsername())));
    showUtenti->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(utente->getPassword())));
    showUtenti->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(utente->getNome())));
    showUtenti->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(utente->getCognome())));
    showUtenti->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(utente->getTipoUtente())));
}


//---------SLOTS di UtentiTab --------

//1)Aggiunta utente
void UtentiTab::aggiungiUtente()
{
    //cancello il testo dalla Qtextbrowser per non creare confusione con utenti aggiunti in precedenza
    showMessage->setText(" ");

    //e poi creo la finestra per l'aggiunta utente
    aggiungiUtDialog = new QDialog();

    //costruisco il nuovo QDialog per l aggiunta utente
    QLabel* username0 = new QLabel("Username:", aggiungiUtDialog);
    addUsername = new QLineEdit(aggiungiUtDialog);
    QLabel* password0 = new QLabel("Password:", aggiungiUtDialog);
    addPassword = new QLineEdit(aggiungiUtDialog);
    QLabel* nome0 = new QLabel("Nome:", aggiungiUtDialog);
    addNome = new QLineEdit(aggiungiUtDialog);
    QLabel* cognome0 = new QLabel("Cognome:", aggiungiUtDialog);
    addCognome = new QLineEdit(aggiungiUtDialog);
    QLabel* tipo0 = new QLabel("Tipo Utente:", aggiungiUtDialog);
    addTipo = new QComboBox(aggiungiUtDialog);
    addTipo->addItem("Studente",  "studente");
    addTipo->addItem("Esterno",  "esterno");
    addTipo->addItem("Contribuente",  "contribuente");
    QPushButton* ok = new QPushButton("Conferma", aggiungiUtDialog);
    //connetto il bottone "ok" al suo slot
    connect(ok, SIGNAL(clicked()), this, SLOT(aggiungiUtenteConfirm()));

    //creo il layout
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(username0,0,0);
    layout->addWidget(addUsername,0,1);
    layout->addWidget(password0,1,0);
    layout->addWidget(addPassword,1,1);
    layout->addWidget(nome0,2,0);
    layout->addWidget(addNome,2,1);
    layout->addWidget(cognome0,3,0);
    layout->addWidget(addCognome,3,1);
    layout->addWidget(tipo0,4,0);
    layout->addWidget(addTipo,4,1);
    layout->addWidget(ok,5,1);

    aggiungiUtDialog->setLayout(layout);
    aggiungiUtDialog->setFixedSize(400,250);
    aggiungiUtDialog->setWindowTitle(tr("Aggiunta nuovo utente"));

    //eseguo
    aggiungiUtDialog->exec();
}

//aggiungiUtenteConfirm() aggiunge alla listaRegistrati di UtentiTab il nuovo utente appena creato,
//e lo visualizza sulla Table (per aggiungerlo definitivamente al file xml "utentidb.xml" occorrera'
//salvare le modifiche tramite l'apposito bottone.
void UtentiTab::aggiungiUtenteConfirm()
{
    //mi salvo le variabili in delle QString
    QString user= addUsername->text().toLower();
    QString pass= addPassword->text().toLower();
    QString nome= addNome->text();
    QString cognome= addCognome->text();
    QString tipo= addTipo->currentText().toLower();

    if(user.isEmpty() || pass.isEmpty() || nome.isEmpty() || cognome.isEmpty() )
    {
        QMessageBox addErr(this);
        addErr.setWindowTitle("Operazione non riuscita");
        addErr.setText("E' necessario compilare tutti i campi della form.");
        addErr.exec();
    }
    else //tutti i campi son stati compilati correttamente
    {
        if(utentiRegistrati->checkAvaiableUsername(user.toStdString()))
        {
            //aggiungo effettivamente l'utente a listaRegistrati
            Utente* utente = utentiRegistrati->inserisciUtente(user.toStdString(),pass.toStdString(),
                                                 nome.toStdString(), cognome.toStdString(),
                                                 tipo.toStdString());
            if(utente)
            {
                //lo visualizzo nella QTable
                printUtente(utente);
                //e do un messaggio di avvenuto inserimento
                showMessage->setTextColor(Qt::green);
                showMessage->setText("Utente aggiunto con successo. Numero utenti registrati: " + QString::number(utentiRegistrati->getNumUtenti()));
            }

            //infine chiudo la finestra per l'aggiunta utente
            aggiungiUtDialog->close();

        }
        else //se l'username è già presente non effettuo l'inserimento, ed avviso di cambiare username
        {
            QMessageBox unavaiable(this);
            unavaiable.setWindowTitle("Inserimento non avvenuto");
            unavaiable.setText("Username già presente. Sceglierne un altro.");
            unavaiable.exec();
        }
    }

}


//2)Eliminazione Utente
void UtentiTab::eliminaUtente()
{
    //cancello il testo dalla Qtextbrowser per non creare confusione con utenti aggiunti in precedenza
    showMessage->setText(" ");

    //controllo inanzitutto se è stato selezionato l'utente da eliminare
    if(showUtenti->currentIndex().isValid())
    {
        if(showUtenti->item(showUtenti->currentIndex().row(), 4)->text() != "Amministratore") //NON posso eliminare l'amministratore!
        {
            //faccio l'erase dell'utente dalla lista di utenti tramite l'username, che si trova in item(riga corrente, colonna 0)
            QString username = showUtenti->item(showUtenti->currentIndex().row(), 0)->text();
            utentiRegistrati->rimuoviUtente(username.toStdString());
            //rimuovo anche la riga dalla tabella e avviso della rimozione
            showUtenti->removeRow(showUtenti->currentRow());
            showMessage->setTextColor(Qt::green);
            showMessage->setText("Utente eliminato. Numero utenti registrati: " + QString::number(utentiRegistrati->getNumUtenti()));
        }
        else
        {
            QMessageBox err(this);
            err.setWindowTitle("Attenzione");
            err.setText("Impossibile eliminare l'utente amministratore.");
            err.exec();
        }
    }
    else //se nessuna riga è selezionata dico all'amministratore di farlo
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun utente selezionato.\n Selezionare dalla tabella l'utente che si vuole eliminare.");
        err.exec();
    }

}


//3)Modifica del tipo di utente
void UtentiTab::modificaUtente()
{
    //cancello il testo dalla Qtextbrowser per non creare confusione con altre operazioni avvenute
    showMessage->setText(" ");

    //controllo inanzitutto se è stato selezionato l'utente da modificare
    if(showUtenti->currentIndex().isValid())
    {
        //salvo il tipo dell'utente che voglio modificare, e il suo username
        oldTipo = showUtenti->item(showUtenti->currentIndex().row(), 4)->text();
        utentedaModificare = showUtenti->item(showUtenti->currentIndex().row(), 0)->text();

        if(oldTipo!= "Amministratore") //NON posso modificare l'amministratore!
        {
            //creo la finestra per sapere di quale tipo voglio far diventare l'utente
            modificaUtDialog = new QDialog();
            nuovoTipo = "Studente"; //dato che è il valore checked di default

            //radio buttons per la scelta del tipo utente
            QRadioButton *radioStud = new QRadioButton(tr("Studente"));
            connect(radioStud, SIGNAL(clicked()), this, SLOT(setNuovoTipoStud()));
            QRadioButton *radioEst = new QRadioButton(tr("Esterno"));
            connect(radioEst, SIGNAL(clicked()), this, SLOT(setNuovoTipoEst()));
            QRadioButton *radioCont = new QRadioButton(tr("Contribuente"));
            connect(radioCont, SIGNAL(clicked()), this, SLOT(setNuovoTipoCont()));
            radioStud->setChecked(true); //devo averne almeno uno a true

            //groupbox per i radiobutton: in questo caso la scelta è esclusiva di default
            QGroupBox* radiobuttonGroupBox = new QGroupBox(tr("Nuovo tipo dell'utente:"));
            QVBoxLayout* groupboxlayout = new QVBoxLayout();
            groupboxlayout->addWidget(radioStud);
            groupboxlayout->addWidget(radioEst);
            groupboxlayout->addWidget(radioCont);
            radiobuttonGroupBox->setLayout(groupboxlayout);

            //bottone di conferma, che viene connesso ad uno slot
            QPushButton* ok = new QPushButton("Conferma", modificaUtDialog);
            connect(ok, SIGNAL(clicked()), this, SLOT(modificaUtenteConfirm()));

            QVBoxLayout* layout= new QVBoxLayout();
            layout->addWidget(radiobuttonGroupBox);
            layout->addWidget(ok);
            modificaUtDialog->setLayout(layout);
            modificaUtDialog->setWindowTitle(tr("Modifica tipo utente"));

            modificaUtDialog->exec();

        }
        else
        {
            QMessageBox err(this);
            err.setWindowTitle("Attenzione");
            err.setText("Impossibile modificare l'utente amministratore.");
            err.exec();
        }
    }
    else //se nessuna riga è selezionata dico all'amministratore di farlo
    {
        QMessageBox err(this);
        err.setWindowTitle("Attenzione");
        err.setText("Nessun utente selezionato.\n Selezionare dalla tabella l'utente che si vuole modificare.");
        err.exec();
    }
}

void UtentiTab::setNuovoTipoStud()
{
    nuovoTipo = "Studente";
}

void UtentiTab::setNuovoTipoEst()
{
    nuovoTipo = "Esterno";
}

void UtentiTab::setNuovoTipoCont()
{
    nuovoTipo = "Contribuente";
}

void UtentiTab::modificaUtenteConfirm()
{
    if(oldTipo == nuovoTipo) //se il tipo corrisponde a quello che era già, non faccio nulla e avverto di ciò
    {
        showMessage->setTextColor(Qt::yellow);
        showMessage->setText("Utente non modificato, in quanto già del tipo selezionato.");
    }
    else //altrimenti cerco l'utente e lo "modifico"
        //(copio i dati, lo cancello, e lo ricreo come oggetto del nuovo tipo) tramite il metodo di Registrzioni
    {
        utentiRegistrati->cambiaTipoUtente(utentedaModificare.toStdString(), nuovoTipo.toStdString());

        //infine lo cambio anche nella tabella e do un messaggio dell'avvenuto cambiamento
        showUtenti->item(showUtenti->currentIndex().row(), 4)->setText(nuovoTipo);
        showMessage->setTextColor(Qt::green);
        showMessage->setText("Tipo utente modificato con successo.");
    }
    modificaUtDialog->close(); //infine chiudo la finestra di modifica
}

//4) Salvare modifiche su file xml
void UtentiTab::salvaTuttoUt()
{
    //cancello il testo dalla Qtextbrowser per non creare confusione con altre operazioni avvenute
    showMessage->setText(" ");

    QDomDocument doc;
    QDomElement root = doc.createElement("utenti"); //<utenti> elemento radice
    doc.appendChild(root); //inserisco la radice
    //ciclo sugli utenti presenti nella lista registrati
    for(auto it= utentiRegistrati->registrati.begin();  it!= utentiRegistrati->registrati.end(); it++)
    {
        //salvo in delle variabili QString le informazioni dell'utente che sto esaminando
        QString username = QString::fromStdString((*it)->getUsername());
        QString password = QString::fromStdString((*it)->getPassword());
        QString nome =  QString::fromStdString((*it)->getNome());
        QString cognome =  QString::fromStdString((*it)->getCognome());
        QString tipo = QString::fromStdString((*it)->getTipoUtente());

        //creo gli elementi del file xml, con i rispettivi valori
        QDomElement utente= doc.createElement("utente"); //crea il tag <utente>
        utente.setAttribute("username", username); //aggiunge al tag utente l'attributo username con il rispettivo username dell'utente
        QDomElement uPass = doc.createElement("password");
        uPass.appendChild(doc.createTextNode(password));
        QDomElement uNome = doc.createElement("nome");
        uNome.appendChild(doc.createTextNode(nome));
        QDomElement uCognome = doc.createElement("cognome");
        uCognome.appendChild(doc.createTextNode(cognome));
        QDomElement uTipo = doc.createElement("tipoUtente");
        uTipo.appendChild(doc.createTextNode(tipo));

        //aggiungo i vari elementi
        utente.appendChild(uPass);
        utente.appendChild(uNome);
        utente.appendChild(uCognome);
        utente.appendChild(uTipo);
        root.appendChild(utente);
    }
    //apro il file in scrittura
    QFile file(QDir::currentPath().append("/../bibliotecaScolastica/xml/utentidb.xml"));
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
    showMessage->setText("Modifiche salvate. Utenti registrati: " + QString::number(utentiRegistrati->getNumUtenti()));

}

