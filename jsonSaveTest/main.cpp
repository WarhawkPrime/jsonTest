#include "mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <QMessageBox>
#include <QDebug>

#include<QTranslator>

#include "Char.h"

#include <iostream>

using namespace std;

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Char newChar("Roderic", 32, 8);
    newChar.saveJ();


    Char newChar2;
    newChar2.loadJ();
    //newChar2.setName("Akatosh");
    //newChar2.setHp(40);
    //newChar2.saveJ();

    return a.exec();
}
