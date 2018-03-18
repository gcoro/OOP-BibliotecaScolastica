#include "mainwindowlogin.h"

MainWindowLogin::MainWindowLogin()
{
    //creo le componenti della finestra con una funzione privata
    createMainWindowLogin();

    //aggiungo tutto ciò che ho appena creato al layout della finestra
    QVBoxLayout* layout = new QVBoxLayout; //layout verticale
    layout->addWidget(groupBox);
    setLayout(layout);//applico questo layout alla MainWindowLogin

    //do una dimensione fissa alla finestra
    setFixedSize(350,150);

    //imposto un titolo per la finestra
    setWindowTitle(tr("Login alla biblioteca"));
}

//funzione che verrà invocata dal costruttore e mi crea i vari widget
void MainWindowLogin::createMainWindowLogin()
{
    //creo i vari oggetti per la finestra di login
    groupBox = new QGroupBox("Effettua l'accesso");

    QLabel* userLabel = new QLabel("Username", this);
    userLineEdit = new QLineEdit(this);
    QLabel* passLabel = new QLabel("Password", this);
    passLineEdit = new QLineEdit(this);
    passLineEdit->setEchoMode(QLineEdit::Password); //serve ad oscurare la pass

    bottone = new QPushButton("Login", this);

    //creo un layout per il posizionamento delle componenti
    QGridLayout* layout = new QGridLayout();

    //aggiungo gli elementi creati al layout
    layout-> addWidget(userLabel, 0 , 0);
    layout-> addWidget(userLineEdit, 0, 1);
    layout-> addWidget(passLabel, 1, 0);
    layout-> addWidget(passLineEdit, 1, 1);
    layout-> addWidget(bottone, 2, 1);

    //applico il layout creato alla QGroupBox
    groupBox ->setLayout(layout);

    //collego ogni elemento con il suo slot, tramite i segnali
    connect(bottone, SIGNAL(clicked()), this, SLOT(effettuaLogin()));
}

//funzione che restituisce il tipo di utente che prova a loggarsi, altrimenti una stringa "notfound" (o "err" per errori con il file)
QString MainWindowLogin::getTipoUtenteFromFile(QString user, QString pass) const
{
    //provo ad aprire il file
    QFile file(QDir::currentPath().append("/../bibliotecaScolastica/xml/utentidb.xml"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //se il file non si apre
        return "err";

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return "err";
    }

    file.close(); //chiudo il file perchè i dati son gia in doc (di tipo QDomDocument)

    QDomElement root = doc.firstChild().toElement();  //cioè <utenti> nel doc XML
    QDomElement it= root.firstChild().toElement(); //cioè <utente> singolo; li scorro con un iteratore
    bool trovato = false;
    QString tipo = "notfound";
    while(!it.isNull() && !trovato)
    {
        QString u= it.attribute("username");
        if( u == user) //l'username inserito corrisponde ad una entry nel file
        {
            QString p = it.firstChild().toElement().text();
            if( p == pass) //se la password inserita è corretta, procedo a trovare il tipo utente
            {
                //salta al tag <tipoUtente> che è quello che mi interessa
                tipo = it.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();
                trovato = true;
            }
        }
        //se non ho ancora trovato l'user che sto cercando continuo a esaminare il prossimo <utente>
        it= it.nextSibling().toElement();
    }
    return tipo;
}

//slot che mi effettua la login
void MainWindowLogin::effettuaLogin()
{
    //controllo gli input delle lineEdit, se sono stati riempiti li metto tutti in lowercase
    QString user= userLineEdit->text().toLower();
    QString pass = passLineEdit->text().toLower();
    if(!user.isEmpty() && !pass.isEmpty()) //se non sono vuoti
    {
        //chiamo getTipoUtente che,se l'utente esiste, controlla che tipo è
        QString x = getTipoUtenteFromFile(user, pass);
        //apro una diversa interfaccia a seconda del tipo di utente che sta accedendo
        if(x == "Amministratore")
        {
            DialogAdmin adm;
            adm.exec(); //apro la finestra amministratore
            userLineEdit->clear();
            passLineEdit->clear();
        }
        else if(x == "Esterno")
        {
            DialogUtenteEsterno ue;
            ue.exec();
            userLineEdit->clear();
            passLineEdit->clear();
        }
        else if(x == "Studente")
        {
            DialogUtenteStudente us;
            us.exec();
            userLineEdit->clear();
            passLineEdit->clear();
        }
        else if(x == "Contribuente")
        {
            DialogUtenteContribuente uc;
            uc.exec();
            userLineEdit->clear();
            passLineEdit->clear();
        }
        else if(x == "notfound") //utente non trovato, lo segnalo all utente in una QMessageBox
        {
            QMessageBox loginErr(this);
            loginErr.setText("Login fallita. Controllare di aver inserito username e password correttamente.");
            loginErr.exec();
        }
        else //se x è qualcos'altro (ovvero è "err" per errori con i file)
        {
            QMessageBox fileErr(this);
            fileErr.setText("Errore durante il recupero dei dati da file. Riprovare.");
            fileErr.exec();
        }      
    }
    else //campi vuoti
    {
        QMessageBox empty(this);
        empty.setText("Inserire username e password.");
        empty.exec();
    }

    //la finestra corrente (questa della login) ho scelto di tenerla aperta al di sotto delle nuove finestre,
    //per comodità dell'utente di non dover ri-eseguire il progetto ogni volta per fare login con diverse credenziali
}


