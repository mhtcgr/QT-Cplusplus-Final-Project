#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QToolButton>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMimeData>
#include <QMimeData>
#include <QMatrix4x4>
#include "device.h"
#include "grid.h"
#include "centre.h"
#include "card.h"
#include "Init.h"
#include "miner.h"
#include "mine.h"
#include "myscene.h"
#include "cardscene.h"
#include "trashcan.h"
#include "retbutton.h"
#include "savebutton.h"
namespace Ui {
class PlayScene;
}
class PlayScene : public QMainWindow
{
    Q_OBJECT

public:
    static int upgrade1;
    static int upgrade2;
    static int upgrade3;
    static int money;
    static int timeOfCutter;
    static int timeOfBelt;
    static int timeOfMiner;
    static int typeNeeded;
    static int score;
    static int phase;
    Centre *centre;
    static int dragAngle;//拖拽的那个东西旋转的角度
    static QString dragText;
    static bool isDragging;
    QPixmap dragPic;
    QGraphicsView view1;
    QGraphicsView view2;
    MyScene *scen;
    CardScene *cs;
    QGraphicsPixmapItem dev;
    QGraphicsPixmapItem background;
    QGraphicsTextItem *textItem;
    QGraphicsTextItem *moneyItem;
    RetButton *hideButton;
    QGraphicsTextItem *buttonText;
    SaveButton* saveButton;
    QGraphicsTextItem *saveText;
    explicit PlayScene(QWidget *parent = nullptr);
    device* deviceVector[32+1][40+1];//虽然屏幕上只有20x15但是总共地图有40x30
    grid* gridVector[32+1][40+1];
    Mine* mineVector[32+1][40+1];
    void handleLeftDevice(device* dev);
    ~PlayScene();
    //绘图事件
    //void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void addD(QGraphicsSceneMouseEvent *event);
    void addDevice(device* dev=nullptr,int posx=0,int posy=0);
    void deleteDev(int posx=0,int posy=0);
signals:
    void backMainScene();
    void updateMoneyRequested();
public slots:
    void handleLeftButtonClicked(QString s,QPixmap dragP);
    void addMoreMine();
    void doubleValue();
    void centreBigger();
private:
    Ui::PlayScene *ui;
};

#endif // PLAYSCENE_H
