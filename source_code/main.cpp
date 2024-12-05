#include "mainscene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    QObject::connect(w.shop,&Shop::addMoreMineRequested,w.gameState,&PlayScene::addMoreMine);
    QObject::connect(w.shop,&Shop::doubleValueRequested,w.gameState,&PlayScene::doubleValue);
    QObject::connect(w.shop,&Shop::makeCentreBigger,w.gameState,&PlayScene::centreBigger);
    QObject::connect(w.gameState,&PlayScene::updateMoneyRequested,w.shop,&Shop::updateM);
    w.show();
    return a.exec();
}
