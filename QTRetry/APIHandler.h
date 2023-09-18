#pragma once

#include "qnetworkaccessmanager.h"
#include "qnetworkreply.h"
#include "qeventloop.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "iostream"

void namePrep(QString& response);
QJsonArray addCardGetSets(QString& cardName);