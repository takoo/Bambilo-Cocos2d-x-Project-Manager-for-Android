#ifndef SETUP_H
#define SETUP_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QProcess>

class MainWindow;
namespace Ui {
class setup;
}

class setup : public QMainWindow
{
    Q_OBJECT

public:
    explicit setup(QWidget *parent = 0);
    QString procCOCOS_CONSOLE,procCOCOS_TEMPLATES,procSDK,procNDK,procANT,procCOCOS;
    QProcess *prc;

    QString proje;
    QString path,dir;
    bool projeStatus=true;


    ~setup();


private slots:
    void on_pushButton_clicked();
    void yazdir();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_4_clicked();
    void readProcess();



 public   slots:



private:
    Ui::setup *ui;
    MainWindow *v;

};

#endif // SETUP_H
