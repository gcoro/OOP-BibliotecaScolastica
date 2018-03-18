#ifndef DIALOGUTENTESTUDENTE_H
#define DIALOGUTENTESTUDENTE_H

#include <QDialog>
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
#include"biblioteca.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDir>
#include <QMessageBox>

class DialogUtenteStudente : public QDialog
{
    Q_OBJECT
public:
    DialogUtenteStudente();
public slots:
    void studenteLibroSSearch();
    void studenteLibroNSearch();
    void studenteCdSearch();
    void studenteVediInfo();
    void chiudiInfo();
private:
    Biblioteca* articoliBiblioteca;
    void createDialogUtenteStudente();
    void fillDialogUtenteStudente();
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
    QLineEdit* libroNLingua;
    QCheckBox* libroNDisponibilita;
    QPushButton* libroNSearch;
    //elementi ricerca Cd
    QLineEdit* cdTitolo;
    QLineEdit* cdArtista;
    QComboBox* cdGenere;
    QCheckBox* cdDisponibilita;
    QPushButton* cdSearch;

    QPushButton* vediInfo;
};

#endif // DIALOGUTENTESTUDENTE_H
