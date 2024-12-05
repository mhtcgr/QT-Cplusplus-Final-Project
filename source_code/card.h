#ifndef CARD_H
#define CARD_H

#include <QCursor>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QPixmap>
#include "Init.h"

class Card : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    int x,y;
    QString type;
    QPixmap pix;
    bool isDragging=false;

    explicit Card(int x=0,int y=0,QString type = " ",QPixmap pix=QPixmap("path/to/your/image.png"));
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void pressLeft(QString s,QPixmap dragP);
};

#endif // CARD_H
