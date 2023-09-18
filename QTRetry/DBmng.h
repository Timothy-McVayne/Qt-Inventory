#pragma once

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>
#include <qstringlist.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qstring.h>

const auto INVENTORY_SQL = "CREATE TABLE Inventory ("
"Name varchar(255) NOT NULL,"
"SetID varchar(3) NOT NULL,"
"collectID int,"
"rarity varchar(10) NOT NULL,"
"set_name varchar(50) NOT NULL,"
"cmc int NOT NULL,"
"oracle_text varchar(1000) NOT NULL,"
"power int,"
"toughness int,"
"type_line varchar(75) NOT NULL,"
"foil bool,"
"mana_cost varchar(50),"
"released_at varchar(25),"
"image_uris varchar(1000),"
"colors varchar(10),"
"color_identity varchar(10),"
"keywords varchar(1000),"
"legalities varchar(1000),"
"reserved bool,"
"finishes varchar(100),"
"reprint bool,"
"flavor_text varchar(1000),"
"artist varchar(100),"
"full_art bool,"
"loyalty int,"
"PRIMARY KEY(Name, SetID, collectID)); ";

void addCard(QJsonObject card)
{
	QSqlQuery q;

	q.prepare("INSERT INTO Inventory (Name, SetID, collectID, rarity, set_name, cmc, oracle_text, power, toughness,"
		"type_line, foil, mana_cost, released_at, image_uris, colors, color_identity, keywords, legalities,"
		"reserved, finishes, reprint, flavor_text, artist, full_art, loyalty)"
		"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

	q.addBindValue(card["name"].toVariant());
	q.addBindValue(card["set"].toVariant());
	q.addBindValue(card["collector_number"].toVariant());
	q.addBindValue(card["rarity"].toVariant());
	q.addBindValue(card["set_name"].toVariant());
	q.addBindValue(card["cmc"].toVariant());
	q.addBindValue(card["oracle_text"].toVariant());
	q.addBindValue(card["power"].toVariant());
	q.addBindValue(card["toughness"].toVariant());
	q.addBindValue(card["type_line"].toVariant());
	q.addBindValue(card["foil"].toVariant());
	q.addBindValue(card["mana_cost"].toVariant());
	q.addBindValue(card["released_at"].toVariant());
	QJsonArray uris = card["image_uris"].toArray();
	q.addBindValue(uris[2].toVariant());
	q.addBindValue(card["colors"].toVariant());
	q.addBindValue(card["color_identity"].toVariant());
	q.addBindValue(card["keywords"].toVariant());
	q.addBindValue(card["legalities"].toVariant());
	q.addBindValue(card["reserved"].toVariant());
	q.addBindValue(card["finishes"].toVariant());
	q.addBindValue(card["reprint"].toVariant());
	q.addBindValue(card["flavor_text"].toVariant());
	q.addBindValue(card["artist"].toVariant());
	q.addBindValue(card["full_art"].toVariant());
	q.addBindValue(card["loyalty"].toVariant());
	q.exec();
}

QSqlError initDb()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("Inventory.db");

	if (!db.open())
		return db.lastError();

	QStringList tables = db.tables();
	if (tables.contains("Inventory", Qt::CaseInsensitive))
		return QSqlError();

	QSqlQuery q;
	if (!q.exec(INVENTORY_SQL))
		return q.lastError();

	return QSqlError();
}