#ifndef BELT_H
#define BELT_H

#include <QObject>
#include "device.h"
class Belt : public device
{

public:
    QPixmap belt;
    explicit Belt(int x=0,int y=0,int dragAngle=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    virtual ~Belt();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    std::string GetClassType(void) override;
signals:
};



#endif // BELT_H
