#ifndef NONINTERACTIVEPIXMAPITEM_H
#define NONINTERACTIVEPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class NonInteractivePixmapItem : public QGraphicsPixmapItem
{
public:
    using QGraphicsPixmapItem::QGraphicsPixmapItem;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override { Q_UNUSED(event); }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override { Q_UNUSED(event); }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override { Q_UNUSED(event); }
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override { Q_UNUSED(event); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override { Q_UNUSED(event); }
};
#endif // NONINTERACTIVEPIXMAPITEM_H
