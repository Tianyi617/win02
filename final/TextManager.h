#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QString>
#include <QGraphicsScene>

class TextManager
{
public:
    TextManager() = default;

    // 添加文字到指定場景
    // 傳回可選 QGraphicsItem* 以便後續操作
    QGraphicsItem* addTextToScene(QGraphicsScene *scene, const QString &text);

    // 其他「文字處理」相關函式，可自行延伸
    // void changeTextColor(...);
    // void changeFont(...);
    // etc...
};

#endif // TEXTMANAGER_H
