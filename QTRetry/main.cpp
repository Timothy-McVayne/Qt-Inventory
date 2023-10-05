#include "QTRetry.h"
#include <QtWidgets/QApplication>
#include <qfile.h>
#include <iostream>
#include "qfontdatabase.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleSheetFile("MyStyle.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    QTRetry w;
    w.show(); 

    return a.exec();
}
              


/*QFile styleSheetFile("py_dracula_dark.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet); */