#include "cutter.h"
cutter::cutter(int x,int y,int dragAngle)
    :device(x,y,dragAngle),cut(":/bc/bigCutter.png")
{
    setToolTip(QString("剪刀"));
    setZValue(2);
}
void cutter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->translate(x + gridSize / 2, y + gridSize / 2);
    painter->rotate(angle);
    if(angle==270){
        painter->drawPixmap(- 3*gridSize / 2, -gridSize / 2, 2*gridSize, gridSize, cut);
    }
    else if(angle==180){
        painter->drawPixmap(-3*gridSize / 2, -gridSize / 2, 2*gridSize, gridSize, cut);
    }
    else if(angle==90){
        painter->drawPixmap(-gridSize / 2, -gridSize / 2, 2*gridSize, gridSize, cut);
    }
    else
        painter->drawPixmap(-gridSize / 2, -gridSize / 2, 2*gridSize, gridSize, cut);
    painter->restore();
}
QRectF cutter::boundingRect() const
{
    if(angle==270){
        return QRectF(x, y, gridSize, 2*gridSize);
    }
    if(angle==180){
        return QRectF(x, y, 2*gridSize, gridSize);
    }
    if(angle==90){
        return QRectF(x, y, gridSize, 2*gridSize);
    }
    return QRectF(x, y, 2*gridSize, gridSize);
}
void cutter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}
void cutter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    device::mousePressEvent(event);
}
void cutter::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    device::mouseMoveEvent(event);
}
std::string cutter::GetClassType(void){
    return "cutter";
}
cutter::~cutter(){

}
