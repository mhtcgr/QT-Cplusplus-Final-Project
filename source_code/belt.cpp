#include "belt.h"

Belt::Belt(int x,int y,int dragAngle)
    :device(x,y,dragAngle),belt(":/image/belt.png")
{
    setToolTip(QString("传送带"));
    belt = belt.scaled(40, 40, Qt::KeepAspectRatio);
    setZValue(2);
}
void Belt::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->translate(x + gridSize / 2, y + gridSize / 2);
    painter->rotate(angle);
    painter->drawPixmap(-gridSize / 2, -gridSize / 2, gridSize, gridSize, belt);
    painter->restore();
}
QRectF Belt::boundingRect() const
{
    return QRectF(x, y, gridSize, gridSize);
}
void Belt::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}
void Belt::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    device::mousePressEvent(event);
}
void Belt::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    device::mouseMoveEvent(event);
}
std::string Belt::GetClassType(void){
    return "Belt";
}
Belt::~Belt(){

}
