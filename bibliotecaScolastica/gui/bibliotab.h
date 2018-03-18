#ifndef BIBLIOTAB_H
#define BIBLIOTAB_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTextBrowser>
#include"biblioteca.h"
#include<QDomDocument>
#include<QDomElement>
#include<QTextStream>
#include<QXmlStreamReader>
#include<QDir>
#include<QFile>
#include<QMessageBox>
#include<QComboBox>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QSpinBox>

class BiblioTab : public QWidget
{
    Q_OBJECT
public:
    BiblioTab();
public slots:
    //slots per l'aggiunta articolo
    void aggiungiArticolo1();
    void aggiungiArticolo2();
    void aggiungiArticoloConfirm();
    void eliminaArticolo();
    void modificaDisponibilitaArticolo();
    void visualizzaInfoArticolo();
    void chiudiInfo();
    void salvaTuttoArticoli();
private:
    Biblioteca* articoliBiblioteca;

    void createBiblioTab(); //funzione per la creazione del QWidget
    QPushButton* addArticolo; //e i suoi elementi
    QPushButton* delArticolo;
    QPushButton* modDisponibilita;
    QPushButton* infoArticolo;
    QTableWidget* showArticoli;
    QPushButton* salvaModificheArt;
    QTextBrowser* showMessage;

    void fillBiblioTab();
    void printArticolo(Articolo*) const;

    //campi dati e funzioni delle finestre di aggiunta articolo
    QDialog* aggiuntaArt;
    QLineEdit* addId;
    QLineEdit* addTitolo;
    QSpinBox* addAnno;
    QComboBox* tipoArt;
    QPushButton* aggiuntaArtNext;
    QDialog* aggiuntaLibroN;
    QLineEdit* lnAddAutore;
    QLineEdit* lnAddLingua;
    QLineEdit* lnAddCasaEd;
    QSpinBox* lnAddPag;
    QComboBox* lnAddGenere;
    QComboBox* lnAddEta;
    QDialog* aggiuntaLibroS;
    QLineEdit* lsAddAutore;
    QLineEdit* lsAddCasaEd;
    QSpinBox* lsAddPag;
    QComboBox* lsAddMateria;
    QSpinBox* lsAddEd;
    QDialog* aggiuntaCd;
    QLineEdit* cdAddArtista;
    QComboBox* cdAddGenere;
    QSpinBox* cdAddTracce;
    QDialog* aggiuntaRivista;
    QSpinBox* rvAddNumero;
    QComboBox* rvAddPeriodicita;
    QLineEdit* rvAddArgomento;
    QSpinBox* rvAddPag;
    QPushButton* aggiuntaArtConfirm;
    void createAddLibroN();
    void createAddLibroS();
    void createAddCd();
    void createAddRivista();
    //campi dati per la modifica
    QString articolodaModificare;
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
};

#endif // BIBLIOTAB_H
