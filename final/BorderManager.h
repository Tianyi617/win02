#ifndef BORDERMANAGER_H
#define BORDERMANAGER_H

#include <QPixmap>

class BorderManager
{
public:
    BorderManager() = default;

    // 在這裡宣告所有「邊框處理」函式
    void applySimpleBorder(QPixmap &pixmap);
    void applyDecorativeBorder(QPixmap &pixmap);
    void applyRoundedBorder(QPixmap &pixmap);
    void applyDoubleBorder(QPixmap &pixmap);
    void applyGradientBorder(QPixmap &pixmap);
    void applyShadowBorder(QPixmap &pixmap);
    // 新增更多邊框
    void applyDashedBorder(QPixmap &pixmap);
    void applyWavyBorder(QPixmap &pixmap);
    void applyNeonBorder(QPixmap &pixmap);
    void applyTornPaperBorder(QPixmap &pixmap);
    void resetBorders(QPixmap &pixmap);
    void setOriginalPixmap(const QPixmap &pixmap); // 設定原始圖片;
private:
    QPixmap originalPixmap; // 儲存原始圖片
};

#endif // BORDERMANAGER_H
