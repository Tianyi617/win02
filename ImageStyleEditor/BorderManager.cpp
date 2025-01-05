#include "BorderManager.h"
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
#include <QtMath> // 用於波浪邊框時，需要 sin/cos 函式
#include <QPainterPath>


void BorderManager::applySimpleBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen pen(Qt::black);
    pen.setWidth(10);
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());
}

void BorderManager::applyDecorativeBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen pen(Qt::blue);
    pen.setWidth(15);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());
}

void BorderManager::applyRoundedBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen pen(Qt::green);
    pen.setWidth(12);
    painter.setPen(pen);
    QRectF rect = pixmap.rect();
    painter.drawRoundedRect(rect, 20, 20);
}

void BorderManager::applyDoubleBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen outerPen(Qt::red);
    outerPen.setWidth(15);
    painter.setPen(outerPen);
    painter.drawRect(pixmap.rect());

    QPen innerPen(Qt::yellow);
    innerPen.setWidth(8);
    painter.setPen(innerPen);
    QRectF innerRect = pixmap.rect().adjusted(10, 10, -10, -10);
    painter.drawRect(innerRect);
}

void BorderManager::applyGradientBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QLinearGradient gradient(0, 0, pixmap.width(), pixmap.height());
    gradient.setColorAt(0, Qt::blue);
    gradient.setColorAt(1, Qt::cyan);
    QPen pen(QBrush(gradient), 12);
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());
}

void BorderManager::applyShadowBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen shadowPen(Qt::darkGray);
    shadowPen.setWidth(20);
    painter.setPen(shadowPen);
    QRectF shadowRect = pixmap.rect().adjusted(-10, -10, 10, 10);
    painter.drawRect(shadowRect);

    QPen borderPen(Qt::black);
    borderPen.setWidth(10);
    painter.setPen(borderPen);
    painter.drawRect(pixmap.rect());
}

// ========== 以下為新增 4 種邊框示範 ==========

// 1) 虛線邊框
void BorderManager::applyDashedBorder(QPixmap &pixmap)
{
    QPainter painter(&pixmap);
    QPen pen(Qt::magenta);
    pen.setWidth(12);
    pen.setStyle(Qt::DashLine); // 虛線樣式
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());
}

// 2) 波浪邊框
void BorderManager::applyWavyBorder(QPixmap &pixmap)
{
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::darkGreen);
    pen.setWidth(10);
    painter.setPen(pen);

    QRect rect = pixmap.rect();

    // 參數可自行微調
    int amplitude = 10;   // 波幅
    int waveLength = 20;  // 波長

    // 上邊波浪
    QPainterPath topPath;
    topPath.moveTo(rect.topLeft());
    for (int x = rect.left(); x <= rect.right(); x += waveLength) {
        double midY = rect.top() + amplitude * qSin((double)x / waveLength * M_PI);
        topPath.lineTo(x, midY);
    }
    painter.drawPath(topPath);

    // 右邊波浪
    QPainterPath rightPath;
    rightPath.moveTo(rect.topRight());
    for (int y = rect.top(); y <= rect.bottom(); y += waveLength) {
        double midX = rect.right() + amplitude * qSin((double)y / waveLength * M_PI);
        rightPath.lineTo(midX, y);
    }
    painter.drawPath(rightPath);

    // 下邊波浪
    QPainterPath bottomPath;
    bottomPath.moveTo(rect.bottomRight());
    for (int x = rect.right(); x >= rect.left(); x -= waveLength) {
        double midY = rect.bottom() + amplitude * qSin((double)x / waveLength * M_PI);
        bottomPath.lineTo(x, midY);
    }
    painter.drawPath(bottomPath);

    // 左邊波浪
    QPainterPath leftPath;
    leftPath.moveTo(rect.bottomLeft());
    for (int y = rect.bottom(); y >= rect.top(); y -= waveLength) {
        double midX = rect.left() + amplitude * qSin((double)y / waveLength * M_PI);
        leftPath.lineTo(midX, y);
    }
    painter.drawPath(leftPath);
}

// 3) 霓虹邊框
void BorderManager::applyNeonBorder(QPixmap &pixmap)
{
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = pixmap.rect();

    // 多層發光效果
    for (int i = 0; i < 5; ++i) {
        int alpha = 50 - i * 8; // 漸減透明度
        int sizeAdjust = i * 5; // 往外擴散
        QPen pen(QColor(255, 0, 255, alpha));
        pen.setWidth(10 + i * 4);
        painter.setPen(pen);
        painter.drawRect(rect.adjusted(-sizeAdjust, -sizeAdjust, sizeAdjust, sizeAdjust));
    }

    // 最內層
    QPen pen(Qt::magenta);
    pen.setWidth(8);
    painter.setPen(pen);
    painter.drawRect(rect);
}

// 4) 撕紙邊框
void BorderManager::applyTornPaperBorder(QPixmap &pixmap)
{
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);

    QRect rect = pixmap.rect();
    int toothSize = 10; // 鋸齒大小

    QPainterPath path;
    // 上邊鋸齒
    bool up = true;
    path.moveTo(rect.topLeft());
    for (int x = rect.left(); x <= rect.right(); x += toothSize) {
        if (up)
            path.lineTo(x, rect.top() - toothSize);
        else
            path.lineTo(x, rect.top() + toothSize);
        up = !up;
    }

    // 右邊鋸齒
    bool rightSide = true;
    path.lineTo(rect.topRight());
    for (int y = rect.top(); y <= rect.bottom(); y += toothSize) {
        if (rightSide)
            path.lineTo(rect.right() + toothSize, y);
        else
            path.lineTo(rect.right() - toothSize, y);
        rightSide = !rightSide;
    }

    // 下邊鋸齒
    bool down = true;
    path.lineTo(rect.bottomRight());
    for (int x = rect.right(); x >= rect.left(); x -= toothSize) {
        if (down)
            path.lineTo(x, rect.bottom() + toothSize);
        else
            path.lineTo(x, rect.bottom() - toothSize);
        down = !down;
    }

    // 左邊鋸齒
    bool leftSide = true;
    path.lineTo(rect.bottomLeft());
    for (int y = rect.bottom(); y >= rect.top(); y -= toothSize) {
        if (leftSide)
            path.lineTo(rect.left() - toothSize, y);
        else
            path.lineTo(rect.left() + toothSize, y);
        leftSide = !leftSide;
    }
    path.closeSubpath();
    painter.drawPath(path);
}
void BorderManager::resetBorders(QPixmap &pixmap)
{
    if (!originalPixmap.isNull()) {
        pixmap = originalPixmap; // 還原到原始圖片
    }
}
void BorderManager::setOriginalPixmap(const QPixmap &pixmap)
{
    originalPixmap = pixmap; // 儲存原始圖片
}
