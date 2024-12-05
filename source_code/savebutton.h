#ifndef SAVEBUTTON_H
#define SAVEBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class SaveButton : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SaveButton();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
signals:
    void saveFile();
};

#endif // SAVEBUTTON_H
