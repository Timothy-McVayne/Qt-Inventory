#include "APIHandler.h"

QJsonArray addCardGetSets(QString& cardName)
{
    namePrep(cardName);
    QEventLoop eventLoop;

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));;

    QNetworkRequest req(QUrl(QString("https://api.scryfall.com/cards/search?q=" + cardName + "&unique=prints")));
    QNetworkReply* reply = mgr.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        delete reply;
        QJsonArray cardObjects = obj["data"].toArray(); 

        return cardObjects;
    }

    else
    {
        std::cout << "Broke";
        delete reply;
    }
}

void namePrep(QString& response)
{
    //boolean to tell if we have changed any spaces to '+'
    bool altered = false;
    for (int i = 0; i < response.size(); i++)
        if (response[i] == ' ')
        {
            response[i] = '+';
            altered = true;
        }

    //if the name of the card is multiple words, to make sure we get exactly the card we want we need a '+' after the ! so it is recognized
    if (altered)
        response = "!+" + response;
    else
        response = "!" + response;
}