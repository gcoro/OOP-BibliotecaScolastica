#ifndef DIALOGUTENTECONTRIBUENTE_H
#define DIALOGUTENTECONTRIBUENTE_H
#include<QDialog>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include"libronarrativa.h"
#include"libroscolastico.h"
#include"cdmusicale.h"
#include"rivista.h"
#include "biblioteca.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDir>
#include <QMessageBox>


class DialogUtenteContribuente: public QDialog
{
    Q_OBJECT
public:
    DialogUtenteContribuente();
public slots:
    void contribuenteLNSearch();
    void contribuenteLSSearch();
    void contribuenteCdSearch();
    void contribuenteRivistaSearch();
    void contribuenteVediInfo();
    void chiudiInfo();
private:
    Biblioteca* articoliBiblioteca;
    void createDialogUtenteContribuente();
    void fillDialogUtenteContribuente();
    void printArticoli(std::list<Articolo*>) const;

    //campi dati e funzioni per la visualizzazione delle informazioni articolo
    QDialog* infoArticoloDialog;
    QTextBrowser* showInfoArticolo;
    QPushButton* chiudiInfoArticolo;
    QString articolodaVisualizzare;
    void createVisualizzaInfoArticolo();
    void printInfoLibroN(LibroNarrativa*) const;
    void printInfoLibroS(LibroScolastico*) const;
    void printInfoCd(CdMusicale*) const;
    void printInfoRivista(Rivista*) const;

    QTableWidget* showSearchResults;
    //elementi per ricerca libri scolastici
    QLineEdit* libroSTitolo;
    QLineEdit* libroSnEdizione;
    QLineEdit* libroSAutore;
    QLineEdit* libroSCasaEd;
    QComboBox* libroSMateria;
    QCheckBox* libroSDisponibilita;
    QPushButton* libroSSearch;
    //elementi per ricerca libri narrativa
    QLineEdit* libroNTitolo;
    QLineEdit* libroNAutore;
    QComboBox* libroNGenere;
    QComboBox* libroNEta;
    QLineEdit* libroNLingua;
    QCheckBox* libroNDisponibilita;
    QPushButton* libroNSearch;
    //elementi ricerca Cd
    QLineEdit* cdTitolo;
    QLineEdit* cdArtista;
    QComboBox* cdGenere;
    QCheckBox* cdDisponibilita;
    QPushButton* cdSearch;
    //elementi per ricerca riviste
    QLineEdit* rivistaTitolo;
    QLineEdit* rivistaNumero;
    QLineEdit* rivistaArgomento;
    QCheckBox* rivistaDisponibilita;
    QPushButton* rivistaSearch;

    QPushButton* vediInfo;
};

#endif // DIALOGUTENTECONTRIBUENTE_H
