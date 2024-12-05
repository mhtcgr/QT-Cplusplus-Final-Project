#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <mine.h>
#include "Init.h"

class grid : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    bool hasCentre=0;
    int mineType;//0是没有，1是第一种不可切割的，2是可切割的。
    int hasDevice=0;//等于0说明无设备，1说明有，2说明是剪刀的左边，3说明是剪刀的右边
    explicit grid(int x = 0,int y = 0,int m=0,bool c = 0);
    int px,py;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
signals:
};

#endif // GRID_H
