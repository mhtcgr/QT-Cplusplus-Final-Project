#include "miner.h"

Miner::Miner(int x,int y,int dragAngle)
    :device(x,y,dragAngle),miner(":/image/miner.png")
{
    setToolTip(QString("开采器"));
    miner = miner.scaled(40, 40, Qt::KeepAspectRatio);
    setZValue(3);
}
void Miner::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->translate(x + gridSize / 2, y + gridSize / 2);
    painter->rotate(angle);
    painter->drawPixmap(-gridSize / 2, -gridSize / 2, gridSize, gridSize, miner);
    painter->restore();
}

QRectF Miner::boundingRect() const
{
    return QRectF(x, y, gridSize, gridSize);
}
void Miner::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}
void Miner::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    device::mousePressEvent(event);
}
void Miner::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    device::mouseMoveEvent(event);
}

std::string Miner::GetClassType(void){
    return "Miner";
}

Miner::~Miner(){

}
