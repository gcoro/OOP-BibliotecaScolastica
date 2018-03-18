#ifndef DIALOGADMIN_H
#define DIALOGADMIN_H

#include <QDialog>
#include <QTabWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QTextBrowser>
#include <QGridLayout>
#include <QFileInfo>
#include"utentitab.h"
#include"bibliotab.h"

#include<QDomDocument>
#include<QDomElement>
#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<QMessageBox>


class DialogAdmin: public QDialog
{
    Q_OBJECT

public:
    DialogAdmin();

private:

    void createDialogAdmin(); //funz di ausilio al costruttore

    //elementi grafici
    QTabWidget* schede;
    UtentiTab* utentiTab;
    BiblioTab* biblioTab;

};

#endif // DIALOGADMIN_H
