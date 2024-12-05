#include "device.h"
#include "playscene.h"
device::device(int x, int y,int dragAngle)
    : x{x}, y{y},angle{dragAngle},direct{dragAngle/90}
{
    setZValue(2);
    setCursor(Qt::OpenHandCursor);
}

void device::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(x, y, gridSize, gridSize);
}

QRectF device::boundingRect() const
{
    return QRectF(x, y, gridSize, gridSize);
}

void device::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    return;
}

void device::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton&&PlayScene::isDragging) {
        // 删除自己
        emit deleteDevice(x/40,y/40);
    }

    if (event->button() == Qt::RightButton) {
        qDebug() << "feel right";
        emit deleteDevice(x/40,y/40);
    }
    return;
}

void device::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScenePos(Qt::LeftButton)).length() < QApplication::startDragDistance())
    {
        return;
    }
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    QPixmap pix(21, 21);
    pix.fill(Qt::white);
    QPainter painter(&pix);
    paint(&painter, nullptr, nullptr);
    drag->setPixmap(pix);
    drag->setHotSpot(QPoint(10, 15));

    // 开始拖动
    drag->exec();
    // 改变光标形状
    setCursor(Qt::OpenHandCursor);
}
std::string device::GetClassType(void){
    return "";
}
device::~device()
{}
