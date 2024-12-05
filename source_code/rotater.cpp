#include "rotater.h"

Rotater::Rotater(int x,int y,int dragAngle)
    :device(x,y,dragAngle),belt(":/gk/rotater.png")
{
    setToolTip(QString("旋转器"));
    belt = belt.scaled(40, 40, Qt::KeepAspectRatio);
    setZValue(2);
}
void Rotater::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->translate(x + gridSize / 2, y + gridSize / 2);
    painter->rotate(angle);
    painter->drawPixmap(-gridSize / 2, -gridSize / 2, gridSize, gridSize, belt);
    painter->restore();
}
QRectF Rotater::boundingRect() const
{
    return QRectF(x, y, gridSize, gridSize);
}
void Rotater::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}
void Rotater::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    device::mousePressEvent(event);
}
void Rotater::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    device::mouseMoveEvent(event);
}
std::string Rotater::GetClassType(void){
    return "rotator";
}
Rotater::~Rotater(){

}
