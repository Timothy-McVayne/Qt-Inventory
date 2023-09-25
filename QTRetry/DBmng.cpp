#include "DBmng.h"

const auto INVENTORY_SQL = "CREATE TABLE Inventory ("
"Name varchar(255) NOT NULL,"
"SetID varchar(5) NOT NULL,"
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
"quantity int,"
"PRIMARY KEY(Name, SetID, collectID)); ";

void addToDB(QJsonObject card, int quant)
{
	QSqlQuery q;
	q.prepare("INSERT INTO Inventory (Name, SetID, collectID, rarity, set_name, cmc, oracle_text, power, toughness, type_line, foil, mana_cost, released_at, image_uris, colors, color_identity, keywords, legalities, reserved, finishes, reprint, flavor_text, artist, full_art, loyalty, quantity)"
		" VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

	q.addBindValue(card["name"].toString());
	q.addBindValue(card["set"].toString());
	q.addBindValue(card["collector_number"].toString().toInt());
	q.addBindValue(card["rarity"].toString());
	q.addBindValue(card["set_name"].toString());
	q.addBindValue(card["cmc"].toInt());
	q.addBindValue(card["oracle_text"].toString());
	q.addBindValue(card["power"].toInt());
	q.addBindValue(card["toughness"].toInt());
	q.addBindValue(card["type_line"].toString());
	q.addBindValue(card["foil"].toBool());
	q.addBindValue(card["mana_cost"].toString());
	q.addBindValue(card["released_at"].toString());

	QJsonObject uris = card["image_uris"].toObject();
	q.addBindValue(uris["normal"].toString());

	QJsonArray colors = card["colors"].toArray();
	QString colorString;
	for (int i = 0; i < colors.size(); i++)
	{
		colorString += colors[i].toString();
		colorString += ", ";
	}
	colorString.truncate(colorString.lastIndexOf(QChar(',')));
	q.addBindValue(colorString);



	QJsonArray colorID = card["color_identity"].toArray();
	QString colorIDS;
	for (int i = 0; i < colorID.size(); i++)
	{
		colorIDS += colorID[i].toString();
		colorIDS += ", ";
	}
	colorIDS.truncate(colorIDS.lastIndexOf(QChar(',')));
	q.addBindValue(colorIDS);



	QJsonArray keywords(card["keywords"].toArray());
	if (keywords.isEmpty())
		q.addBindValue(NULL);
	else
	{
		QString keywordString;
		for (int i = 0; i < keywords.size(); i++)
		{
			keywordString += keywords[i].toString();
			keywordString += ", ";
		}
		keywordString.truncate(keywordString.lastIndexOf(QChar(',')));
		q.addBindValue(keywordString);
	}

	QJsonObject legalities(card["legalities"].toObject());
	QStringList keys = legalities.keys();
	QString legalString;
	for (int i = 0; i < keys.size(); i++)
	{
		legalString += keys[i];
		legalString += '=';
		legalString += legalities[keys[i]].toString();
		legalString += ", "; 
	}
	legalString.truncate(legalString.lastIndexOf(QChar(','))); 
	q.addBindValue(legalString);


	q.addBindValue(card["reserved"].toBool());

	QJsonArray finishes(card["finishes"].toArray());
	QString finishesString;
	for (int i = 0; i < finishes.size(); i++)
	{
		finishesString += finishes[i].toString();
		finishesString += ", ";
	}
	finishesString.truncate(finishesString.lastIndexOf(QChar(',')));
	q.addBindValue(finishesString);

	q.addBindValue(card["reprint"].toBool());
	q.addBindValue(card["flavor_text"].toString());
	q.addBindValue(card["artist"].toString());
	q.addBindValue(card["full_art"].toBool());
	q.addBindValue(card["loyalty"].toInt());
	q.addBindValue(quant);
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