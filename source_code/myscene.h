#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QMouseEvent>
#include <QGraphicsScene>
class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void press(QGraphicsSceneMouseEvent *event);
    void o();
};

#endif // MYSCENE_H
