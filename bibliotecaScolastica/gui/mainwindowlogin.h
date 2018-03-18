#ifndef MAINWINDOWLOGIN_H
#define MAINWINDOWLOGIN_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include"registrazioni.h"
#include<QFile>
#include<QFileDialog>
#include<QXmlStreamReader>
#include<QMessageBox>
#include<QDomDocument>
#include<QDomElement>
#include<QTextStream>
#include"dialogadmin.h"
#include"dialogutenteesterno.h"
#include"dialogutentestudente.h"
#include"dialogutentecontribuente.h"

class MainWindowLogin: public QDialog
{
    Q_OBJECT

public:

    //costruttore
    MainWindowLogin();

public slots:
    void effettuaLogin();

private:
    //getTipoUtenteFromFile(QString, QString) controlla da file XML se l'utente che sta facendo la login esiste
    //(ossia ha inserito correttamente username e password), in caso positivo ritorna
    //una stringa che identifica il suo tipo di utenza, la stringa "notfound" se non trovato
    QString getTipoUtenteFromFile(QString, QString) const;

    //funzione ausiliaria per la creazione della finestra
    void createMainWindowLogin();

    //componenti grafiche (dichiaro come campi dati solo quelle che mi servono per eseguire delle azioni su di esse)
    QGroupBox* groupBox;
    QLineEdit* userLineEdit;
    QLineEdit* passLineEdit;
    QPushButton* bottone;

};


#endif // MAINWINDOWLOGIN_H
