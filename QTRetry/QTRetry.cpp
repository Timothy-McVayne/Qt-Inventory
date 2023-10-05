#include "QTRetry.h"

QTRetry::QTRetry(QWidget* parent)
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
    connect(wnd, &addCard::cardAddedfromPrints, this, &QTRetry::updateList);
}

void QTRetry::updateList()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT Name, set_name,  rarity, collectID, setID, quantity, NULL as dlt_row FROM Inventory");
    query->exec();
    model->setQuery(*query);

    QSortFilterProxyModel* m = new QSortFilterProxyModel(this); 
    m->setDynamicSortFilter(true);
    m->setSourceModel(model);

    m->setHeaderData(0, Qt::Horizontal, "Name");
    m->setHeaderData(1, Qt::Horizontal, "Set");
    m->setHeaderData(2, Qt::Horizontal, "Rarity");
    m->setHeaderData(5, Qt::Horizontal, "Quantity");

    ui.tableView->setModel(m);
    ui.tableView->setColumnHidden(3, true); 
    ui.tableView->setColumnHidden(4, true);
    ui.tableView->setSortingEnabled(true);

    for (int i = 0; i < ui.tableView->model()->rowCount(); i++)
    {
        QPushButton* deleteButton = new QPushButton("Delete");
        ui.tableView->setIndexWidget(ui.tableView->model()->index(i, 6), deleteButton);
        connect(deleteButton, &QPushButton::clicked, this, &QTRetry::deleteButtonClicked);
    }
    ui.tableView->resizeColumnsToContents();
}

void QTRetry::deleteButtonClicked()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    QModelIndex buttonIndex = ui.tableView->indexAt(senderButton->pos());

    if (buttonIndex.isValid()) 
    {
        int row = buttonIndex.row();

        QModelIndex keyIndex1 = ui.tableView->model()->index(row, 0);
        QModelIndex keyIndex2 = ui.tableView->model()->index(row, 4);
        QModelIndex keyIndex3 = ui.tableView->model()->index(row, 3); 

        QString key1 = ui.tableView->model()->data(keyIndex1).toString();
        QString key2 = ui.tableView->model()->data(keyIndex2).toString();
        int key3 = ui.tableView->model()->data(keyIndex3).toInt();

        QSqlQuery query;
        query.prepare("DELETE FROM Inventory WHERE Name = :key1 AND SetID = :key2 AND collectID = :key3");
        query.bindValue(":key1", key1);
        query.bindValue(":key2", key2);
        query.bindValue(":key3", key3);

        if (query.exec()) 
        {
            ui.tableView->model()->removeRow(row);
            updateList();
        }
        else {
            qDebug() << "Error deleting row from the database:" << query.lastError().text();
        }
    }
    else {
        qDebug() << "Invalid button index.";
    }
}

QTRetry::~QTRetry()
{}
