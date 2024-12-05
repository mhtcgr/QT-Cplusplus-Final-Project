#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include "shop.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    PlayScene* gameState = NULL;
    Shop* shop = NULL;
    Ui::MainScene *ui;

};
#endif // MAINSCENE_H
