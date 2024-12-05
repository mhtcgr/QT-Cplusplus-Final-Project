#ifndef RETBUTTON_H
#define RETBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
class RetButton : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit RetButton();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
signals:
    void backM();
};

#endif // RETBUTTON_H






