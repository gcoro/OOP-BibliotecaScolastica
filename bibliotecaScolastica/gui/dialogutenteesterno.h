#ifndef DIALOGUTENTEESTERNO_H
#define DIALOGUTENTEESTERNO_H

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
#include"biblioteca.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDir>
#include <QMessageBox>

class DialogUtenteEsterno : public QDialog
{
    Q_OBJECT
public:
    DialogUtenteEsterno();

public slots:
    void esternoLibroNSearch();
    void esternoRivistaSearch();
    void esternoVediInfo();
    void chiudiInfo();
private:
    Biblioteca* articoliBiblioteca;
    void createDialogUtenteEsterno();
    void fillDialogUtenteEsterno();
    void printArticoli(std::list<Articolo*>) const;

    //campi dati e funzioni per la visualizzazione delle informazioni articolo
    QDialog* infoArticoloDialog;
    QTextBrowser* showInfoArticolo;
    QPushButton* chiudiInfoArticolo;
    QString articolodaVisualizzare;
    void createVisualizzaInfoArticolo();
    void printInfoLibroN(LibroNarrativa*) const;
    void printInfoRivista(Rivista*) const;

    QTableWidget* showSearchResults;
    //elementi per ricerca libri narrativa
    QLineEdit* libroNTitolo;
    QLineEdit* libroNAutore;
    QComboBox* libroNEta;
    QCheckBox* libroNDisponibilita;
    QPushButton* libroNSearch;
    //elementi per ricerca riviste
    QLineEdit* rivistaTitolo;
    QLineEdit* rivistaNumero;
    QLineEdit* rivistaArgomento;
    QCheckBox* rivistaDisponibilita;
    QPushButton* rivistaSearch;

    QPushButton* vediInfo;


};

#endif // DIALOGUTENTEESTERNO_H
