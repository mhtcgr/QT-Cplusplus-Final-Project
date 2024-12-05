#include "card.h"
#include "Init.h"
#include "cutter.h"
Card::Card(int x,int y,QString type,QPixmap pix)
    :x{x},y{y},type{type},pix{pix}
{

    setZValue(5);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //标明该参数没有使用
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->fillRect(boundingRect(), Qt::white);
    painter->drawPixmap(x,y,pix);
}

QRectF Card::boundingRect() const
{
    // 定义图形项的边界矩形

    return QRectF(x, y, gridSize, gridSize);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::mouseReleaseEvent(event);

}
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        if (isDragging)
        {
            isDragging = false;
        }
        else
        {// 创建自定义鼠标图标
            if(type=="cutter"){
                QCursor customCursor(QPixmap(":/bc/bigCutter.png"), 0, 0);// 设置整个应用程序的鼠标图标
                qApp->setOverrideCursor(customCursor);
                emit pressLeft(type,QPixmap(":/bc/bigCutter.png"));
            }

            else{
                QCursor customCursor(pix, 0, 0);// 设置整个应用程序的鼠标图标
                qApp->setOverrideCursor(customCursor);
                emit pressLeft(type,pix);
            }
            isDragging = true;
        }
    }
    else
        setCursor(Qt::ClosedHandCursor);
}
void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::mouseMoveEvent(event);

}

