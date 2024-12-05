#ifndef MINER_H
#define MINER_H


#include <QObject>
#include "device.h"
class Miner : public device
{

public:

    QPixmap miner;
    explicit Miner(int x=0,int y=0,int dragAngle=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    virtual ~Miner();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    std::string GetClassType(void) override;
signals:
};



#endif // MINER_H
