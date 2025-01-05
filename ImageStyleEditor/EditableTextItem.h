#ifndef EDITABLETEXTITEM_H
#define EDITABLETEXTITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>

class EditableTextItem : public QGraphicsTextItem {
    Q_OBJECT
public:
    explicit EditableTextItem(const QString &text, QGraphicsItem *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // EDITABLETEXTITEM_H
