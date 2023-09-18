#include "QTRetry.h"
#include "DBmng.h"
#include "APIHandler.h"
#include <QtWidgets/QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    //std::cout << initDb().text().toStdString();
    QApplication a(argc, argv);
    QTRetry w;

    //std::string card = "austere command";
    
   //QJsonObject cardList = addCardGetSets(card);

    w.show(); 

    return a.exec();
}
