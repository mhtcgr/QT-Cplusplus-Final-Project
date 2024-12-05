#include "retbutton.h"
#include "QPainter"
RetButton::RetButton()
{}
void RetButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(Qt::LeftButton == event->button()){
        emit backM();
    }
}
void RetButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //标明该参数没有使用
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(QBrush(Qt::darkGray));
    painter->drawRect(QRect(740,600,50,40));
}

QRectF RetButton::boundingRect() const
{
    // 定义图形项的边界矩形

    return QRectF(740,600,50,40);
}
