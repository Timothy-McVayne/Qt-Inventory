#include "addCard.h"

addCard::addCard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void addCard::on_pushButton_clicked()
{
	QString card = ui.lineEdit->text();
	hide();
	printings* wnd = new printings(card);
	wnd->show();
}

void addCard::on_lineEdit_returnPressed()
{
	on_pushButton_clicked(); 
}

addCard::~addCard()
{}