#include "centre.h"

Centre::Centre(int p,int u)
    : phase(p),upgraded(u)
{
    setZValue(4);
}
void Centre::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);

    // 绘制一个矩形，位置和大小由项的边界矩形决定
    if(upgraded==false){
        if(phase==0)
            painter->drawPixmap(QRect(x,y,4*gridSize,4*gridSize),QPixmap("://Hub_Level_1.png"));//final 加上图片
        if(phase==1)
            painter->drawPixmap(QRect(x,y,4*gridSize,4*gridSize),QPixmap(":/Hub_Level_2.png"));//final 加上图片
        if(phase==2)
            painter->drawPixmap(QRect(x,y,4*gridSize,4*gridSize),QPixmap("://Hub_Level_3.png"));//final 加上图片
    }
    else{
        if(phase==0)
            painter->drawPixmap(QRect(x,y,5*gridSize,5*gridSize),QPixmap("://Hub_Level_1.png"));//final 加上图片
        if(phase==1)
            painter->drawPixmap(QRect(x,y,5*gridSize,5*gridSize),QPixmap(":/Hub_Level_2.png"));//final 加上图片
        if(phase==2)
            painter->drawPixmap(QRect(x,y,5*gridSize,5*gridSize),QPixmap("://Hub_Level_3.png"));//final 加上图片
    }
}
QRectF Centre::boundingRect() const{
    return QRectF(x, y, 4*gridSize, 4*gridSize);
}


