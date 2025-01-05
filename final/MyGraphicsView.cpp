#include "MyGraphicsView.h"
#include <QGraphicsItem>
#include <QDebug>

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        double scaleFactor = 1.1;
        if (event->angleDelta().y() < 0) {
            scaleFactor = 1.0 / scaleFactor;
        }
        scale(scaleFactor, scaleFactor);
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* clickedItem = itemAt(event->pos());
        if (clickedItem) {
            qDebug() << "Clicked on item:" << clickedItem
                     << "Type:" << clickedItem->type();

            // 檢查是否是 QGraphicsTextItem
            if (dynamic_cast<QGraphicsTextItem*>(clickedItem)) {
                qDebug() << "Clicked on a QGraphicsTextItem";
                setDragMode(QGraphicsView::NoDrag); // 禁用拖拽模式
                QGraphicsView::mousePressEvent(event); // 傳遞事件到文字項目
                return;
            } else if (clickedItem->type() == QGraphicsPixmapItem::Type) {
                qDebug() << "Clicked on a background item";
            } else {
                qDebug() << "Clicked on a non-text item";
            }
        } else {
            qDebug() << "Clicked on empty space";
        }

        // 點擊非文字項目或空白處，啟用拖拽模式
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

    QGraphicsView::mousePressEvent(event);
}


void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 放開左鍵後，恢復為無拖拽模式
        setDragMode(QGraphicsView::NoDrag);
    }

    // 傳遞事件到基底類別
    QGraphicsView::mouseReleaseEvent(event);
}
