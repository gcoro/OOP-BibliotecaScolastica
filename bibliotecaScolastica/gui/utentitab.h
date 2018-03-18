#ifndef UTENTITAB_H
#define UTENTITAB_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include "registrazioni.h"
#include<QFile>
#include<QDomDocument>
#include<QDomElement>
#include<QXmlStreamReader>
#include<QTextStream>
#include<QDir>
#include<QTextBrowser>
#include<QRadioButton>


//questa classe è un QWidget creato apposta per essere inserito nella QTableWidget del dialogAdmin
class UtentiTab : public QWidget
{
    Q_OBJECT

public:
    UtentiTab(); //costruttore

public slots:
    //slot della DialogAdmin
    void aggiungiUtente();
    void eliminaUtente();
    void modificaUtente();
    void salvaTuttoUt();

    //slot della finestra aggiungiUtDialog
    void aggiungiUtenteConfirm();
    //slot della finestra modificaUtDialog
    void modificaUtenteConfirm();
    void setNuovoTipoStud();
    void setNuovoTipoEst();
    void setNuovoTipoCont();

private:
    Registrazioni* utentiRegistrati;

    //Qwidgets
    QPushButton* addUtente;
    QPushButton* delUtente;
    QPushButton* modTipoUtente;
    QTableWidget* showUtenti;
    QPushButton* salvaModificheUt;
    QTextBrowser* showMessage;
    //campi dati per l'aggiunta utente:
    QDialog* aggiungiUtDialog;
    QLineEdit* addUsername;
    QLineEdit* addPassword;
    QLineEdit* addNome;
    QLineEdit* addCognome;
    QComboBox* addTipo;
    //campi per la modifica utente:
    QDialog* modificaUtDialog;
    QString utentedaModificare;
    QString oldTipo;
    QString nuovoTipo;

    //createUtentiTab per creare l interfaccia grafica
    void createUtentiTab();
    //inizializza listaRegistrati con i dati presi da file
    void fillUtentiRegistrati();
    //stampa un utente nella QTable
    void printUtente(Utente*) const;
};

#endif // GUTENTITAB_H
