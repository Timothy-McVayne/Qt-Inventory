#pragma once

#include <QWidget>
#include "ui_printings.h"

class printings : public QWidget
{
	Q_OBJECT

public:
	printings(QString card, QWidget *parent = nullptr);
	~printings();

private:
	Ui::printingsClass ui;
	QList<QUrl> getURIS(QJsonArray list);
	void downloadImages(QList<QUrl> list);
};
