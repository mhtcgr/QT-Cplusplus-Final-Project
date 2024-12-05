#ifndef ROTATER_H
#define ROTATER_H

#include <QObject>
#include "device.h"
class Rotater : public device
{
public:
    QPixmap belt;
    explicit Rotater(int x=0,int y=0,int dragAngle=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    std::string GetClassType(void) override;
    virtual ~Rotater();
signals:
};

#endif // ROTATER_H



