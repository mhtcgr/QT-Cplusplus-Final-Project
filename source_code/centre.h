#ifndef CENTRE_H
#define CENTRE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QKeyEvent>
#include "Init.h"

class Centre : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    int phase;
    int upgraded=false;
    int x=720,y=560;
    explicit Centre(int p=0,int u=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

signals:
};

#endif // CENTRE_H
