#include "printings.h"

//creates the list of card images
printings::printings(QString card, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.listWidget->setViewMode(QListWidget::IconMode);
	ui.listWidget->setIconSize(QSize(400, 400));
	ui.listWidget->setResizeMode(QListWidget::Adjust);

	QJsonArray printingList = addCardGetSets(card);
	for (int i = 0; i < printingList.size(); i++)
		downloadAndDisplayImage(printingList[i].toObject());

	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onPrintingItemClicked(QListWidgetItem*)));
}

printings::~printings()
{}

//Downloads images from the normal url in the card jsonobject and adds it to the list 
void printings::downloadAndDisplayImage(QJsonObject card) 
{
	QJsonObject temp = card["image_uris"].toObject();
	QUrl imageUrl = temp["normal"].toString();

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	QNetworkRequest request(imageUrl);
	QNetworkReply* reply = manager->get(request);

	connect(reply, &QNetworkReply::finished, this, [=]()
		{
			if (reply->error() == QNetworkReply::NoError)
			{
				QByteArray imageData = reply->readAll();
				QPixmap pixmap;
				pixmap.loadFromData(imageData);

				if (!pixmap.isNull())
				{
					QListWidgetItem* item = new QListWidgetItem(QIcon(pixmap), card["set_name"].toString());
					item->setData(Qt::UserRole, card);
					ui.listWidget->addItem(item);
				}
			}
		reply->deleteLater();
		});
}

//Creates quantity box and emits the signal to update main list CHANGE GET INT SO IT CAN BE STYLED
void printings::onPrintingItemClicked(QListWidgetItem* card)
{ 
	QJsonObject cardJson = card->data(Qt::UserRole).toJsonObject();
	bool ok;
	int quant = QInputDialog::getInt(this, tr("Quantity"), tr("How many would you like to add?: "), 0, 0, 2147483647, 1, &ok, Qt::MSWindowsFixedSizeDialogHint);
	if (ok)
		addToDB(cardJson, quant);

	emit this->cardAdded();

	this->hide(); 
}