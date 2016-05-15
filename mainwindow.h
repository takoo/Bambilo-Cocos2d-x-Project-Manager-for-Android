#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setup.h"
#include <QProcess>
#include <QProcessEnvironment>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

class setup;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ifstream ifs;
    ofstream fs;
    string st;
    QString ss;
    QString ant,sdk,cocos,ndk,cocostemplate,cocosconsole;
    QString ANT,NDK,SDK,COCOS_CONSOLE,COCOS_TEMPLATES;
    string word;
    bool sdkFind=false;
    bool antFind=false;
    bool ndkFind=false;
    bool cocosFind=false;
    bool firstwindows=true;
    bool desktopCreate=true;

public slots:
    void loadTools();

private slots:
    void on_pushButton_clicked();
    void yaz();
    void setString();
    void checkPathNDK();
    void checkPathSDK();
    void checkPathANT();
    void checkPathCocos();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();



private:
    Ui::MainWindow *ui;

     setup* s;
     QProcess *pr;

};

#endif // MAINWINDOW_H
