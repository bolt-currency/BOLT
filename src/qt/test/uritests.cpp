#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("bolt://ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bolt:ZNf9eZmW28AV4rY95k4rAkMCu6ygWowSto?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
