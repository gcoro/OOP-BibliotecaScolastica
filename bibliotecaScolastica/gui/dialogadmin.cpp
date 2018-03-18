#include "dialogadmin.h"

DialogAdmin::DialogAdmin()
{
    createDialogAdmin();


    setFixedSize(600,460);
    setWindowTitle(tr("Pannello Amministratore"));

}


void DialogAdmin::createDialogAdmin()
{
    //creo gli elementi grafici

    //creo il tabWidget e le sue schede

    schede = new QTabWidget(this);
    schede->addTab(new UtentiTab(), tr("Gestione Utenti"));
    schede->addTab(new BiblioTab(), tr("Gestione Biblioteca"));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(schede);
    setLayout(layout); //applico layout a finestra this

}
