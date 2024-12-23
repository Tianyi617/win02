#include "ImageStyleEditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPainter>
#include <QPen>

ImageStyleEditor::ImageStyleEditor(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)) {
    // 設置主窗口
    this->setWindowTitle("簡易風格樣式製作");
    this->resize(800, 600);

    // 主界面
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 圖片顯示區域
    imageDisplay = new QGraphicsView(this);
    imageDisplay->setScene(scene);
    mainLayout->addWidget(imageDisplay);

    // 功能按鈕
    QHBoxLayout *controlsLayout = new QHBoxLayout();

    uploadButton = new QPushButton("上傳圖片", this);
    connect(uploadButton, &QPushButton::clicked, this, &ImageStyleEditor::uploadImage);
    controlsLayout->addWidget(uploadButton);

    applyBorderButton = new QPushButton("添加邊框", this);
    connect(applyBorderButton, &QPushButton::clicked, this, &ImageStyleEditor::applyBorder);
    controlsLayout->addWidget(applyBorderButton);

    addTextButton = new QPushButton("添加文字", this);
    connect(addTextButton, &QPushButton::clicked, this, &ImageStyleEditor::addText);
    controlsLayout->addWidget(addTextButton);

    aiStyleButton = new QPushButton("AI風格轉換", this);
    connect(aiStyleButton, &QPushButton::clicked, this, &ImageStyleEditor::applyAIStyle);
    controlsLayout->addWidget(aiStyleButton);

    saveButton = new QPushButton("保存圖片", this);
    connect(saveButton, &QPushButton::clicked, this, &ImageStyleEditor::saveImage);
    controlsLayout->addWidget(saveButton);

    // 邊框樣式選擇
    borderStyles = new QComboBox(this);
    borderStyles->addItems({"無邊框", "簡約邊框", "花邊", "圓角", "雙重邊框", "漸變邊框", "陰影邊框"});
    controlsLayout->addWidget(borderStyles);
    QPushButton *removeBorderButton = new QPushButton("刪除邊框", this);
    connect(removeBorderButton, &QPushButton::clicked, this, &ImageStyleEditor::removeBorder);
    controlsLayout->addWidget(removeBorderButton);

    // 自定義文字
    textInput = new QLineEdit(this);
    textInput->setPlaceholderText("輸入文字...");
    controlsLayout->addWidget(textInput);

    mainLayout->addLayout(controlsLayout);
    this->setCentralWidget(centralWidget);
}

ImageStyleEditor::~ImageStyleEditor() {}

void ImageStyleEditor::uploadImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "選擇圖片", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        currentPixmap.load(filePath);
        originalPixmap = currentPixmap;  // 記錄原始圖片
        scene->clear();
        scene->addPixmap(currentPixmap.scaled(imageDisplay->size(), Qt::KeepAspectRatio));
    }
}


void ImageStyleEditor::saveImage() {
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "保存失敗", "沒有圖片可保存，請先上傳圖片！");
        return;
    }

    // 創建一個新的 QPixmap，大小與當前圖片相同
    QPixmap savePixmap(currentPixmap.size());
    savePixmap.fill(Qt::transparent);  // 填充透明背景

    // 創建 QPainter 寫入圖片
    QPainter painter(&savePixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // 將原始圖片繪製到新的 QPixmap 上
    painter.drawPixmap(0, 0, currentPixmap);

    // 將場景中的所有項目（包括文字）繪製到圖片上
    scene->render(&painter);

    painter.end();  // 完成繪製

    // 提示用戶選擇保存路徑
    QString savePath = QFileDialog::getSaveFileName(this, "保存圖片", "", "Images (*.png *.jpg *.bmp)");
    if (!savePath.isEmpty()) {
        if (!savePixmap.save(savePath)) {
            QMessageBox::critical(this, "保存失敗", "圖片保存失敗，請重試！");
        } else {
            QMessageBox::information(this, "保存成功", "圖片已成功保存！");
        }
    }
}


void ImageStyleEditor::applyBorder() {
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    QString selectedStyle = borderStyles->currentText();
    QPixmap modifiedPixmap = currentPixmap;

    if (selectedStyle == "簡約邊框") {
        applySimpleBorder(modifiedPixmap);
    } else if (selectedStyle == "花邊") {
        applyDecorativeBorder(modifiedPixmap);
    } else if (selectedStyle == "圓角") {
        applyRoundedBorder(modifiedPixmap);
    } else if (selectedStyle == "雙重邊框") {
        applyDoubleBorder(modifiedPixmap);
    } else if (selectedStyle == "漸變邊框") {
        applyGradientBorder(modifiedPixmap);
    } else if (selectedStyle == "陰影邊框") {
        applyShadowBorder(modifiedPixmap);
    } else {
        QMessageBox::information(this, "邊框應用", "無需應用邊框！");
        return;
    }

    currentPixmap = modifiedPixmap;
    scene->clear();
    scene->addPixmap(currentPixmap.scaled(imageDisplay->size(), Qt::KeepAspectRatio));
}


// 添加簡約邊框
void ImageStyleEditor::applySimpleBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen pen(Qt::black);
    pen.setWidth(10); // 邊框寬度
    painter.setPen(pen);
    painter.drawRect(pixmap.rect()); // 繪製邊框
}

// 添加花邊
void ImageStyleEditor::applyDecorativeBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen pen(Qt::blue);
    pen.setWidth(15);
    pen.setStyle(Qt::DotLine); // 使用點線樣式
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());
}

// 添加圓角邊框
void ImageStyleEditor::applyRoundedBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen pen(Qt::green);
    pen.setWidth(12);
    painter.setPen(pen);

    QRectF rect = pixmap.rect();
    painter.drawRoundedRect(rect, 20, 20); // 圓角半徑設為 20
}
void ImageStyleEditor::applyDoubleBorder(QPixmap &pixmap) {
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

void ImageStyleEditor::applyGradientBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QLinearGradient gradient(0, 0, pixmap.width(), pixmap.height());
    gradient.setColorAt(0, Qt::blue);
    gradient.setColorAt(1, Qt::cyan);
    QPen pen(QBrush(gradient), 12);
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());
}

void ImageStyleEditor::applyShadowBorder(QPixmap &pixmap) {
    QPainter painter(&pixmap);
    QPen shadowPen(Qt::darkGray);
    shadowPen.setWidth(20);
    painter.setPen(shadowPen);
    QRectF shadowRect = pixmap.rect().adjusted(-10, -10, 10, 10);  // 陰影邊框稍大
    painter.drawRect(shadowRect);

    QPen borderPen(Qt::black);
    borderPen.setWidth(10);
    painter.setPen(borderPen);
    painter.drawRect(pixmap.rect());
}

void ImageStyleEditor::removeBorder() {
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    currentPixmap = originalPixmap; // 恢復為上傳時的原始圖片
    scene->clear();
    scene->addPixmap(currentPixmap.scaled(imageDisplay->size(), Qt::KeepAspectRatio));
    QMessageBox::information(this, "邊框刪除", "邊框已刪除，圖片已恢復原始狀態！");
}


void ImageStyleEditor::addText() {
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    // 取得用戶輸入的文字
    QString text = textInput->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "操作失敗", "請輸入文字！");
        return;
    }

    // 創建 QGraphicsTextItem 並設置文字
    QGraphicsTextItem *textItem = new QGraphicsTextItem(text);

    // 設置文字顏色和字型
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(QFont("Arial", 30));

    // 設置文字項目可拖動
    textItem->setFlag(QGraphicsItem::ItemIsMovable);
    textItem->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    // 添加文字項目到場景中
    scene->addItem(textItem);

    // 顯示提示
    QMessageBox::information(this, "添加文字", "文字已成功添加，您可以拖動文字到想要的位置！");
}



void ImageStyleEditor::applyAIStyle() {
    // AI風格轉換邏輯，待實現
    QMessageBox::information(this, "AI風格轉換", "AI風格轉換功能尚未實現！");
}
