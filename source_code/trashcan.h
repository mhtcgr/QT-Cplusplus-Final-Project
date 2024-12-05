#ifndef TRASHCAN_H
#define TRASHCAN_H

#include <QObject>
#include "device.h"
class TrashCan : public device
{
public:
    QPixmap trashCan;
    explicit TrashCan(int x=0,int y=0,int dragAngle=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    virtual ~TrashCan();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    std::string GetClassType(void) override;
signals:
};

#endif // TRASHCAN_H
