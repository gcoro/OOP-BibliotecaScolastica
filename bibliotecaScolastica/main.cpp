
#include <QApplication>
#include"gui/mainwindowlogin.h"
#include"gui/dialogadmin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //creo la finestra principale
    MainWindowLogin w;
    //e la eseguo
    return w.exec();

}
