#pragma once

#include <QWidget>
#include "ui_addCard.h"

class addCard : public QWidget
{
	Q_OBJECT

public:
	addCard(QWidget* parent = nullptr);
	~addCard();

private:
	Ui::addCardClass ui;

public slots:
	void on_pushButton_clicked();
	void on_lineEdit_returnPressed();
};
