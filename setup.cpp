#include "setup.h"
#include "ui_setup.h"
#include <QSettings>
#include <QDebug>
#include <QProcessEnvironment>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>



 bool status=false;
 QString st;

setup::setup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setup)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/Bambilo"));
    v=new MainWindow();
    prc=new QProcess();
    //---------
   /* ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);*/
    //--------
    QSettings checktool("Tools","tool");
    procCOCOS_CONSOLE=checktool.value("setCOCOS_CONSOLE").toString();
    procCOCOS_TEMPLATES=checktool.value("setCOCOS_TEMPLATES").toString();
    procSDK=checktool.value("setSDK").toString();
    procNDK=checktool.value("setNDK").toString();
    procANT=checktool.value("setANT").toString();
    procCOCOS=checktool.value("setCOCOS").toString();

    string ant=procANT.toStdString().erase(0,9);
    string ndk=procNDK.toStdString().erase(0,9);
    string sdk=procSDK.toStdString().erase(0,17);
    string cocostemplates=procCOCOS_TEMPLATES.toStdString().erase(0,21);
    string cocosconsole=procCOCOS_CONSOLE.toStdString().erase(0,19);


  // ------------------------------------------------------ process settings

    QProcessEnvironment env=QProcessEnvironment::systemEnvironment();
    env.insert("JAVA_HOME","/usr");
    env.insert("PATH",env.value("PATH")+":$JAVA_HOME:$PATH");

    env.insert("COCOS_CONSOLE_ROOT",QString::fromStdString(cocosconsole));
    env.insert("PATH",env.value("PATH")+":$COCOS_CONSOLE_ROOT:$PATH");

    env.insert("COCOS_TEMPLATES_ROOT",QString::fromStdString(cocostemplates));
    env.insert("PATH",env.value("PATH")+":$COCOS_TEMPLATES_ROOT:$PATH");

    env.insert("ANDROID_SDK_ROOT",QString::fromStdString(sdk));
    env.insert("PATH",env.value("PATH")+":$ANDROID_SDK_ROOT:$PATH");
    env.insert("PATH",env.value("PATH")+":$ANDROID_SDK_ROOT/tools:$ANDROID_SDK_ROOT/platform-tools:$PATH");

    env.insert("NDK_ROOT",QString::fromStdString(ndk));
    env.insert("PATH",env.value("PATH")+":$NDK_ROOT:$PATH");

    env.insert("ANT_ROOT",QString::fromStdString(ant));
    env.insert("PATH",env.value("PATH")+":$ANT_ROOT:$PATH");
    prc->setWorkingDirectory(procCOCOS);
    prc->setProcessEnvironment(env);
    connect(prc,SIGNAL(readyReadStandardOutput()),this,SLOT(yazdir()));
    connect(prc,SIGNAL(readChannelFinished()),this,SLOT(readProcess()));




}

setup::~setup()
{
    delete ui;
}

void setup::yazdir()
{
    ui->textBrowser->append(prc->readAllStandardOutput());



}


void setup::on_pushButton_clicked()
{

 proje=QFileDialog::getExistingDirectory();
 projeStatus=true;

 if(proje.toStdString().find("2d-x")==string::npos)
 {
     QMessageBox::critical(this,"ERROR","Please open Cocos2d game project");
     projeStatus=false;

 }
 if(projeStatus)
 {
 if(proje.toStdString().find("2d-x")!=string::npos)
 {
     QFile f(proje);
     path = f.fileName();

     dir = path.section("/",-1,-1);
     ui->statusBar->showMessage("                                                                                                  Current Game Project= "+dir);

 }
 }







}

void setup::on_pushButton_2_clicked()
{


    if(prc->atEnd())
    {
        prc->waitForFinished();
    }
         prc->setReadChannel(QProcess::StandardOutput);

        prc->setWorkingDirectory(procCOCOS);
        prc->start(procCOCOS+"/tools/cocos2d-console/bin/cocos",QStringList()<<"new"<<ui->lineEdit->text()
         <<"-p"<<ui->lineEdit_2->text()<<"-l"<<"cpp");
        proje=ui->lineEdit->text();
        ui->statusBar->showMessage("                                                                                                  Current Game Project= "+proje);


}

void setup::on_pushButton_3_clicked()
{
    if(prc->atEnd())
{

   prc->waitForFinished();

}

    prc->setReadChannel(QProcess::StandardOutput);


    prc->setWorkingDirectory(proje);


   prc->start(procCOCOS+"/tools/cocos2d-console/bin/cocos",QStringList()<<"compile"<<"-p"<<"android");



}

void setup::on_commandLinkButton_clicked()
{   v->firstwindows=true;
    v->show();


}

void setup::on_pushButton_4_clicked()
{
    if(prc->atEnd())
    {

   prc->waitForFinished();
    }

    prc->setReadChannel(QProcess::StandardOutput);

    prc->setWorkingDirectory(proje);

   prc->start(procCOCOS+"/tools/cocos2d-console/bin/cocos",QStringList()<<"run"<<proje<<"-p"<<"android");


}

void setup::readProcess()
{

  st= ui->textBrowser->toPlainText();
  if(st.toStdString().find("Build succeed")!=string::npos)
  {
      QMessageBox::information(this,dir,dir+" APK ready");

  }
}




