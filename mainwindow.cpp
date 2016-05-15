#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <cstring>
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QDir>


bool checkndk=false;
bool checksdk=false;
bool checkant=false;
bool checkcocos=false;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     setWindowIcon(QIcon(":/icons/Bambilo.ico"));
      pr=new QProcess(this);


    connect(pr,SIGNAL(readyReadStandardOutput()),this,SLOT(yaz()));

    pr->start("whoami");


   loadTools();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::yaz()
{
  ss=pr->readAllStandardOutput();
  ss.remove(ss.length()-1,ss.length());
  ss="/home/"+ss+"/.bashrc";


}

void MainWindow::on_pushButton_2_clicked()
{
 checkcocos=true;
 cocos=QFileDialog::getExistingDirectory();
 checkPathCocos();
 setString();
 COCOS_CONSOLE="COCOS_CONSOLE_ROOT="+cocosconsole;
 COCOS_TEMPLATES="COCOS_TEMPLATES_ROOT="+cocostemplate;
}

void MainWindow::on_pushButton_3_clicked()
{
 checksdk=true;
 sdk=QFileDialog::getExistingDirectory();
 SDK="ANDROID_SDK_ROOT="+sdk;
 checkPathSDK();
}

void MainWindow::on_pushButton_4_clicked()
{
 checkndk=true;
 ndk=QFileDialog::getExistingDirectory();
 NDK="NDK_ROOT="+ndk;
 checkPathNDK();


}

void MainWindow::on_pushButton_5_clicked()
{ checkant=true;
  ant=QFileDialog::getExistingDirectory();
  ANT="ANT_ROOT="+ant;
  checkPathANT();
}

void MainWindow::setString()
{
    cocostemplate=cocos+"/templates";
    cocosconsole=cocos+"/tools/cocos2d-console/bin";

}

void MainWindow::checkPathNDK()
{


    if(checkndk)
    {

    if(ndk.toStdString().find("/android-ndk")==string::npos)
    {      QMessageBox::critical(this,"Wrong Directory"," ANDROID-NDK not found!");


    }
    if(ndk.toStdString().find("/android-ndk")!=string::npos)
    {

      ui->lineEdit_3->setText(ndk);

    }
    }
}

 void MainWindow::checkPathSDK()
 {
    if(checksdk)
    {
        if(sdk.toStdString().find("sdk")==string::npos)
        {
             QMessageBox::critical(this,"Wrong Directory","ANDROID-SDK not found!");
        }
        if(sdk.toStdString().find("sdk")!=string::npos)
        {
             ui->lineEdit_2->setText(sdk);
        }



    }
 }
   void MainWindow::checkPathANT()
   {
    if(checkant)
    {
        if(ant.toStdString().find("bin")==string::npos)
        {
            QMessageBox::critical(this,"Wrong Directory","ANT not found!");
        }

        if(ant.toStdString().find("bin")!=string::npos)
        {
            ui->lineEdit_4->setText(ant);
        }

    }
  }
   void MainWindow::checkPathCocos()
   {
    if(checkcocos)
    {
        if(cocos.toStdString().find("2d-x")==string::npos)
        {
            QMessageBox::critical(this,"Wrong Directory","COCOS not found!");
        }

        if(cocos.toStdString().find("2d-x")!=string::npos)
        {
            ui->lineEdit->setText(cocos);
        }

    }


}



void MainWindow::on_pushButton_clicked()
{
   QSettings checktool("Tools","tool");
    if(ui->lineEdit_4->text()!="")
    {
    checktool.setValue("setANT",ANT);
    }
    if(ui->lineEdit_3->text()!="")
    {
     checktool.setValue("setNDK",NDK);
    }
    if(ui->lineEdit_2->text()!="")
    {
    checktool.setValue("setSDK",SDK);
    }
    if(ui->lineEdit->text()!="")
    {
    checktool.setValue("setCOCOS_TEMPLATES",COCOS_TEMPLATES);
    checktool.setValue("setCOCOS_CONSOLE",COCOS_CONSOLE);
    checktool.setValue("setCOCOS",cocos);
    }


    ifs.open(ss.toStdString().c_str(),ios::in);
    fs.open(ss.toStdString().c_str(),ios::app);


    while(ifs>>word)
    {   if(!sdkFind)
        {
        if(word==SDK.toStdString())
        {
            QMessageBox::information(this,"File already exist","File already exist the System Variables(ANDROID-SDK)");
            ui->lineEdit_2->clear();
            sdkFind=true;
        }
        }
        if(!ndkFind)
        {
        if(word==NDK.toStdString())
        {
           QMessageBox::information(this,"File already exist","File already exist the System Variables(ANDROID-NDK)");
           ui->lineEdit_3->clear();
           ndkFind=true;
        }
        }

        if(!antFind)
        {
        if(word==ANT.toStdString())
        {

           QMessageBox::information(this,"File already exist","File already exist the System Variables(ANT)");

           ui->lineEdit_4->clear();
           antFind=true;

        }
        }

        if(!cocosFind)
        {
            if(word=="cocos2d-x")
            {
                QMessageBox::information(this,"File already exist","File already exist the System Variables(COCOS2D-X)");
                ui->lineEdit->clear();
                cocosFind=true;
            }
        }


    }

   if(ui->lineEdit->text()!="")
   {
       if(!cocosFind)
       {   fs<<"\n# Add environment variable for cocos2d-x";
           fs<<"\nexport "<<COCOS_CONSOLE.toStdString();
           fs<<"\nexport PATH=$COCOS_CONSOLE_ROOT:$PATH";
           fs<<"\n\nexport "<<COCOS_TEMPLATES.toStdString();
           fs<<"\nexport PATH=$COCOS_TEMPLATES_ROOT:$PATH";
       }
   }


   if(ui->lineEdit_2->text()!="")
   {
   if(!sdkFind)
    {
        fs<<"\n\nexport "<<SDK.toStdString();
        fs<<"\nexport PATH=$ANDROID_SDK_ROOT:$PATH";
        fs<<"\nexport PATH=$ANDROID_SDK_ROOT/tools:$ANDROID_SDK_ROOT/platform-tools:$PATH";

    }
   }

  if(ui->lineEdit_3->text()!="")
  {
      if(!ndkFind)
      {
          fs<<"\n\nexport "<<NDK.toStdString();
          fs<<"\nexport PATH=$NDK_ROOT:$PATH";
      }
  }

  if(ui->lineEdit_4->text()!="")
  {
   if(!antFind )
   {
    fs<<"\n\nexport "<<ANT.toStdString();
    fs<<"\nexport PATH=$ANT_ROOT:$PATH";

   }
}


    ifs.close();
    fs.close();

}

void MainWindow::loadTools()
{
  QSettings checktool("Tools","tool");
  if(checktool.contains("setANT")
     &&checktool.contains("setSDK")
     &&checktool.contains("setNDK")&&checktool.contains("setCOCOS_TEMPLATES")
     &&checktool.contains("setCOCOS_CONSOLE"))
  {

  firstwindows=false;
  }



  }






