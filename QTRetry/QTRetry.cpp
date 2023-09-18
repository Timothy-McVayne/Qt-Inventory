#include "QTRetry.h"
#include "addCard.h"

QTRetry::QTRetry(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void QTRetry::on_pushButton1_clicked()
{
    addCard* wnd = new addCard(); 
    wnd->show();
}

QTRetry::~QTRetry()
{}
