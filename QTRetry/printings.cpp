#include "printings.h"
#include "APIHandler.h"

printings::printings(QString card, QWidget *parent)
	: QWidget(parent)
{
	QJsonArray printingList = addCardGetSets(card);
	
	QList<QUrl> uris = getURIS(printingList);
	downloadImages(uris);
	for (int i = 0; i < uris.size(); i++)
		qDebug() << uris[i];
	

	ui.setupUi(this);
	ui.listWidget->setViewMode(QListWidget::IconMode); 
	ui.listWidget->setIconSize(QSize(200, 200));
	ui.listWidget->setResizeMode(QListWidget::Adjust);
}

printings::~printings()
{}

QList<QUrl> printings::getURIS(QJsonArray list)
{
	QList<QUrl> uris;
	for (int i = 0; i < list.count(); i++)
	{
		QJsonObject temp = list[i].toObject();
		QJsonObject temp2 = temp["image_uris"].toObject();
		uris.push_back(QUrl(temp2["normal"].toString()));
	}

	return uris;
}

void printings::downloadImages(QList<QUrl> list)
{

}