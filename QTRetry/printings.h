#pragma once

#include <QWidget>
#include "qmessagebox.h"
#include "qinputdialog.h"
#include "qdir.h"
#include "ui_printings.h"
#include "APIHandler.h"
#include "DBmng.h"

class printings : public QWidget
{
	Q_OBJECT

public:
	printings(QString card, QWidget *parent = nullptr);
	~printings();

private:
	Ui::printingsClass ui;
	void downloadAndDisplayImage(QJsonObject);

private slots:
	void onPrintingItemClicked(QListWidgetItem*);
};
