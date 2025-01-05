#include "EditableTextItem.h"

EditableTextItem::EditableTextItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent) {
    setFlag(QGraphicsItem::ItemIsMovable);    // 支援拖動
    setFlag(QGraphicsItem::ItemIsSelectable); // 支援選擇
}

void EditableTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    // 修改文字內容
    bool ok;
    QString newText = QInputDialog::getText(nullptr, "編輯文字",
                                            "輸入新文字:", QLineEdit::Normal, toPlainText(), &ok);
    if (ok && !newText.isEmpty()) {
        setPlainText(newText); // 更新文字
    }

    // 修改字型
    QFont font = QFontDialog::getFont(&ok, this->font(), nullptr, "選擇字型");
    if (ok) {
        setFont(font);
    }

    // 修改顏色
    QColor color = QColorDialog::getColor(defaultTextColor(), nullptr, "選擇文字顏色");
    if (color.isValid()) {
        setDefaultTextColor(color);
    }

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
