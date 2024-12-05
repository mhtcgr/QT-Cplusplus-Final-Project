#include "myscene.h"
#include "card.h"

MyScene::MyScene()
{

}
void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit press(event);
}
