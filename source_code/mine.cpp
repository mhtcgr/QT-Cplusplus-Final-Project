#include "mine.h"
int Mine::value = 1;
Mine::Mine(int x,int y,int t)
    : x{x},y{y},mineType{t}
{setZValue(3);}
void Mine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(mineType==uncuttable)
        painter->drawPixmap(x, y, gridSize, gridSize, QPixmap("://Uncuttable.png"));
    else if(mineType==cuttable)
            painter->drawPixmap(x, y, gridSize, gridSize, QPixmap("://Cuttable.png"));
    else if(mineType==LeftHalf){
            painter->drawPixmap(x, y, gridSize, gridSize, QPixmap("://LeftHalf.png"));
        }
    else
            painter->drawPixmap(x, y, gridSize, gridSize, QPixmap("://RightHalf.png"));



}

QRectF Mine::boundingRect() const{
    return QRectF(x, y, gridSize, gridSize);
}

void Mine::advance(int phase){
    if (!phase)
        return;
    update();
}

