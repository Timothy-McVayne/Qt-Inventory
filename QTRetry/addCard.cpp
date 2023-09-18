#include "addCard.h"
#include "printings.h"

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
	QString card = ui.lineEdit->text();
	hide();
	printings* wnd = new printings(card);
	wnd->show();
}

addCard::~addCard()
{}