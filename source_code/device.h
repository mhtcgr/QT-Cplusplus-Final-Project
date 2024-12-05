#ifndef DEVICE_H
#define DEVICE_H

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
enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};
class device : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    int x,y;
    int angle=0;
    int direct = UP;
    int speed=500;
    int timeToDo=0;
    explicit device(int x=0,int y=0,int dragAngle=0);
    void pressLeft(device* dev);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual std::string GetClassType(void);
    virtual ~device();

signals:
    void deleteDevice(int x,int y);
};

#endif // DEVICE_H
