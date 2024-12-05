#include "savebutton.h"
#include "QPainter"
SaveButton::SaveButton()
{}

void SaveButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(Qt::LeftButton == event->button()){
        emit saveFile();
    }
}
void SaveButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //标明该参数没有使用
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(QBrush(Qt::darkMagenta));
    painter->drawRect(QRect(690,600,50,40));
}

QRectF SaveButton::boundingRect() const
{
    // 定义图形项的边界矩形

    return QRectF(690,600,50,40);
}
