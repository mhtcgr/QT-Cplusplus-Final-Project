#ifndef MINE_H
#define MINE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "Init.h"
enum typeOfMine{cuttable,uncuttable,LeftHalf,RightHalf};
class Mine : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    int mineType;
    static int value;
    int x,y;
    explicit Mine(int x=0,int y=0,int t=cuttable);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void advance(int phase) override;
signals:
};

#endif // MINE_H
