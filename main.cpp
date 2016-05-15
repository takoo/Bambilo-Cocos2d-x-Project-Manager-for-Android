#include "mainwindow.h"
#include <QApplication>
#include "setup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    setup *s;
    s=new setup();
    if(w.firstwindows)
    {
    w.show();
    }
    if(!w.firstwindows)
    {
        s->show();
    }

    return a.exec();
}
