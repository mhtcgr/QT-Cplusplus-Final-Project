#ifndef CUTTER_H
#define CUTTER_H

#include <QObject>
#include "device.h"
class cutter : public device
{

public:
    QPixmap cut;
    explicit cutter(int x=0,int y=0,int dragAngle=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    virtual ~cutter();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    std::string GetClassType(void) override;
signals:
};

#endif // CUTTER_H
