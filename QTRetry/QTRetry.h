#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTRetry.h"

class QTRetry : public QMainWindow
{
    Q_OBJECT

public:
    QTRetry(QWidget *parent = nullptr);
    ~QTRetry();

private:
    Ui::QTRetryClass ui;

public slots:
    void on_pushButton1_clicked();
};
