#include "QTRetry.h"
#include <QtWidgets/QApplication>
#include <qfile.h>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTRetry w;
    w.show(); 

    return a.exec();
}
              


/*QFile styleSheetFile("py_dracula_dark.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet); */