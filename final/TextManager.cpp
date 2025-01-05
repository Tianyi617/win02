#include "TextManager.h"
#include "EditableTextItem.h"
#include <QMessageBox>

QGraphicsItem* TextManager::addTextToScene(QGraphicsScene *scene, const QString &text)
{
    if (!scene) return nullptr;

    // 創建可編輯的文字項目
    EditableTextItem *textItem = new EditableTextItem(text);
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(QFont("Arial", 30));

    // 設定可移動、可選取、可聚焦
    textItem->setFlags(
        QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable |
        QGraphicsItem::ItemIsFocusable
        );

    // 設定文字互動模式：支援雙擊進入編輯模式
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    // 設置 zValue 為 100，確保文字在最上層
    textItem->setZValue(100);
    // 加入場景
    scene->addItem(textItem);

    return textItem;
}
