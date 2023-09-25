#pragma once

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>
#include <qstringlist.h>
#include <qjsonobject.h>
#include "qjsonarray.h"
#include <qjsonarray.h>
#include <qstring.h>
#include "QTRetry.h"
#include <iostream>

void addToDB(QJsonObject card, int quant);
QSqlError initDb();