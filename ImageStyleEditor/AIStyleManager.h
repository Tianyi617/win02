#ifndef AISTYLEMANAGER_H
#define AISTYLEMANAGER_H

#include <QPixmap>

class AIStyleManager
{
public:
    AIStyleManager() = default;

    // 在這裡定義一個函式來處理 AI 風格轉換
    // 依需求，可以傳入原始 pixmap，或參數指定要轉成什麼風格
    bool applyAIStyle(QPixmap &pixmap);
};

#endif // AISTYLEMANAGER_H
