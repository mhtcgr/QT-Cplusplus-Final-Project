#include "trashcan.h"
TrashCan::TrashCan(int x,int y,int dragAngle)
    :device(x,y,dragAngle),trashCan(":/Trash.png")
{
    setToolTip(QString("垃圾桶"));
    trashCan = trashCan.scaled(40, 40, Qt::KeepAspectRatio);
    setZValue(2);
}
void TrashCan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->translate(x + gridSize / 2, y + gridSize / 2);
    painter->rotate(angle);
    painter->drawPixmap(-gridSize / 2, -gridSize / 2, gridSize, gridSize, trashCan);
    painter->restore();
}
QRectF TrashCan::boundingRect() const
{
    return QRectF(x, y, gridSize, gridSize);
}
void TrashCan::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}
void TrashCan::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    device::mousePressEvent(event);
}
void TrashCan::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    device::mouseMoveEvent(event);
}
std::string TrashCan::GetClassType(void){
    return "trashcan";
}
TrashCan::~TrashCan(){

}




