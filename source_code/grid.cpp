#include "grid.h"
#include <QPainter>
grid::grid(int x,int y, int m, bool c)
    : hasCentre(c), mineType(m), px{x},py{y}
{

    setZValue(1);
}
void grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //标明该参数没有使用
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(mineType==1){//不可以切
        painter->setBrush(Qt::magenta);
        painter->drawRect(boundingRect());
        painter->drawPixmap(px,py,gridSize,gridSize,QPixmap("://Uncuttable.png"));
    }
    else if(mineType==2){//可以切
        painter->setBrush(Qt::magenta);
        painter->drawRect(boundingRect());
        painter->drawPixmap(px,py,gridSize,gridSize,QPixmap("://Cuttable.png"));
    }
    else{
        painter->drawPixmap(px,py,gridSize,gridSize,QPixmap("://Grid.png"));
    }

    //painter.drawPixmap(i * gridSize - viewportX, j * gridSize - viewportY, QPixmap("F:/Qt/01First/shapez/code/image/grid.png"));
}
QRectF grid::boundingRect() const
{
    // 定义图形项的边界矩形
    return QRectF(px, py, gridSize, gridSize);
}
