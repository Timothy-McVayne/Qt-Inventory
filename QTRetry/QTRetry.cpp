#include "QTRetry.h"

QTRetry::QTRetry(QWidget *parent)
    : QMainWindow(parent)
{
    initDb();
    ui.setupUi(this);
    updateList();
}

void QTRetry::on_pushButton1_clicked()
{
    addCard* wnd = new addCard();
    wnd->show();
}

void QTRetry::updateList()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT * FROM Inventory");
    query->exec();
    model->setQuery(*query);
    ui.tableView->setModel(model);
}

QTRetry::~QTRetry()
{}
