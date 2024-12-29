#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 創建主窗口中心窗口件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 創建按鈕和其他 UI 元素
    QPushButton *loadButton = new QPushButton("加載圖片", this);
    QPushButton *saveButton = new QPushButton("保存圖片", this);
    QPushButton *applyFilterButton = new QPushButton("應用濾鏡", this);

    QComboBox *filterComboBox = new QComboBox(this);
    filterComboBox->addItem("Grayscale");
    filterComboBox->addItem("Invert");
    filterComboBox->addItem("Blur");
    filterComboBox->addItem("Sharpen");
    filterComboBox->addItem("Brightness");
    filterComboBox->addItem("Contrast");
    //新增濾鏡
    filterComboBox->addItem("Sepia");
    filterComboBox->addItem("Edge Detection");
    filterComboBox->addItem("Emboss");
    //新增暖色濾鏡
    filterComboBox->addItem("Warm");
    //新增冷色濾鏡
    filterComboBox->addItem("Cool");
    //新增戲劇濾鏡
    filterComboBox->addItem("Drama");
    //新增油畫濾鏡
    filterComboBox->addItem("Oil Paint");








    // 正確初始化方法
    originalLabel = new QLabel(this); // 初始化為 QLabel
    filteredLabel = new QLabel(this); // 初始化為 QLabel
    originalLabel->setText("原始圖片");
    filteredLabel->setText("濾鏡後圖片");


    // 設置 QLabel 默認大小和屬性
    originalLabel->setFixedSize(300, 300);
    originalLabel->setAlignment(Qt::AlignCenter);
    originalLabel->setStyleSheet("border: 1px solid black");

    filteredLabel->setFixedSize(300, 300);
    filteredLabel->setAlignment(Qt::AlignCenter);
    filteredLabel->setStyleSheet("border: 1px solid black");

    // 創建垂直布局來放置按鈕
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(filterComboBox);
    buttonLayout->addWidget(applyFilterButton);

    // 創建水平方向布局來放置兩個圖片區域
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(originalLabel);
    imageLayout->addWidget(filteredLabel);

    // 創建垂直布局，將按鈕區域和圖片區域加在一起
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(imageLayout);

    // 連接按鈕和槽函數
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadImage);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveImage);
    connect(applyFilterButton, &QPushButton::clicked, [this, filterComboBox]() {
        QString filterType = filterComboBox->currentText();
        onApplyFilter(filterType);
    });


}

MainWindow::~MainWindow() {}

// 加載圖片
void MainWindow::onLoadImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "選擇圖片", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        if (!originalImage.load(filePath)) {
            QMessageBox::warning(this, "錯誤", "無法加載圖片！");
            return;
        }

        // 確保圖片已正確加載並轉換為 QPixmap
        QPixmap pixmap = QPixmap::fromImage(originalImage);
        if (pixmap.isNull()) {
            QMessageBox::warning(this, "錯誤", "圖片轉換為 QPixmap 失敗！");
            return;
        }

        // 顯示圖片
        originalLabel->setPixmap(pixmap.scaled(originalLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        QMessageBox::information(this, "提示", "未選擇圖片！");
    }
}


// 保存圖片
void MainWindow::onSaveImage()
{
    if (filteredImage.isNull()) {
        QMessageBox::warning(this, "警告", "沒有圖片可保存！");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "保存圖片", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        filteredImage.save(filePath);
    }
}

// 應用濾鏡
void MainWindow::onApplyFilter(const QString &filterType)
{
    if (originalImage.isNull()) {
        QMessageBox::warning(this, "警告", "請先加載圖片！");
        return;
    }

    if (filterType == "Grayscale") {
        applyGrayScale();
    } else if (filterType == "Invert") {
        applyInvert();
    } else if (filterType == "Blur") {
        applyBlur();
    } else if (filterType == "Sharpen") {
        applySharpen();
    } else if (filterType == "Brightness") {
        applyBrightness(50); // 提高亮度（可改為用戶輸入值）
    } else if (filterType == "Contrast") {
        applyContrast(1.5); // 增強對比度（可改為用戶輸入值）
    } else if (filterType == "Sepia") {
        applySepia();
    } else if (filterType == "Edge Detection") {
        applyEdgeDetection();
    } else if (filterType == "Emboss") {
        applyEmboss();
    } else if (filterType == "Warm") {
        applyWarm();
    } else if (filterType == "Cool") {
        applyCool();
    } else if (filterType == "Drama") {
        applyDrama();
    } else if (filterType == "Oil Paint") {
        applyOilPaint();
    }



    filteredLabel->setPixmap(QPixmap::fromImage(filteredImage).scaled(filteredLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// 灰階濾鏡
void MainWindow::applyGrayScale()
{
    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int gray = qGray(color.rgb());
            filteredImage.setPixelColor(x, y, QColor(gray, gray, gray));
        }
    }
}

// 反相濾鏡
void MainWindow::applyInvert()
{
    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            filteredImage.setPixelColor(x, y, QColor(255 - color.red(), 255 - color.green(), 255 - color.blue()));
        }
    }
}
void MainWindow::applyBlur()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    QImage tempImage = filteredImage;

    for (int y = 1; y < filteredImage.height() - 1; ++y) {
        for (int x = 1; x < filteredImage.width() - 1; ++x) {
            int r = 0, g = 0, b = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    QColor pixel = tempImage.pixelColor(x + dx, y + dy);
                    r += pixel.red();
                    g += pixel.green();
                    b += pixel.blue();
                }
            }
            r /= 9; g /= 9; b /= 9;
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}
void MainWindow::applySharpen()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    QImage tempImage = filteredImage;

    int kernel[3][3] = {
        { 0, -1,  0 },
        { -1, 5, -1 },
        { 0, -1,  0 }
    };

    for (int y = 1; y < filteredImage.height() - 1; ++y) {
        for (int x = 1; x < filteredImage.width() - 1; ++x) {
            int r = 0, g = 0, b = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    QColor pixel = tempImage.pixelColor(x + dx, y + dy);
                    int factor = kernel[dy + 1][dx + 1];
                    r += pixel.red() * factor;
                    g += pixel.green() * factor;
                    b += pixel.blue() * factor;
                }
            }
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}
void MainWindow::applyBrightness(int value)
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int r = qBound(0, color.red() + value, 255);
            int g = qBound(0, color.green() + value, 255);
            int b = qBound(0, color.blue() + value, 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}
void MainWindow::applyContrast(float factor)
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int r = qBound(0, static_cast<int>((color.red() - 128) * factor + 128), 255);
            int g = qBound(0, static_cast<int>((color.green() - 128) * factor + 128), 255);
            int b = qBound(0, static_cast<int>((color.blue() - 128) * factor + 128), 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}
void MainWindow::displaySideBySide()
{
    if (originalImage.isNull() || filteredImage.isNull()) {
        QMessageBox::warning(this, "警告", "請先加載並處理圖片！");
        return;
    }

    // 計算新圖片尺寸
    int newWidth = originalImage.width() + filteredImage.width();
    int newHeight = qMax(originalImage.height(), filteredImage.height());

    QImage combinedImage(newWidth, newHeight, QImage::Format_ARGB32);
    combinedImage.fill(Qt::white); // 背景顏色

    QPainter painter(&combinedImage);

    // 在左邊繪製原始圖片
    painter.drawImage(0, 0, originalImage);

    // 在右邊繪製濾鏡後圖片
    painter.drawImage(originalImage.width(), 0, filteredImage);

    painter.end();

    // 顯示在 filteredLabel 中
    filteredLabel->setPixmap(QPixmap::fromImage(combinedImage)
                                 .scaled(filteredLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

//新增濾鏡
void MainWindow::applySepia()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int r = qBound(0, static_cast<int>(color.red() * 0.393 + color.green() * 0.769 + color.blue() * 0.189), 255);
            int g = qBound(0, static_cast<int>(color.red() * 0.349 + color.green() * 0.686 + color.blue() * 0.168), 255);
            int b = qBound(0, static_cast<int>(color.red() * 0.272 + color.green() * 0.534 + color.blue() * 0.131), 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}

void MainWindow::applyEdgeDetection()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    QImage tempImage = filteredImage;

    int kernel[3][3] = {
        { -1, -1, -1 },
        { -1,  8, -1 },
        { -1, -1, -1 }
    };

    for (int y = 1; y < filteredImage.height() - 1; ++y) {
        for (int x = 1; x < filteredImage.width() - 1; ++x) {
            int r = 0, g = 0, b = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    QColor pixel = tempImage.pixelColor(x + dx, y + dy);
                    int factor = kernel[dy + 1][dx + 1];
                    r += pixel.red() * factor;
                    g += pixel.green() * factor;
                    b += pixel.blue() * factor;
                }
            }
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}

void MainWindow::applyEmboss()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    QImage tempImage = filteredImage;

    int kernel[3][3] = {
        { -2, -1,  0 },
        { -1,  1,  1 },
        {  0,  1,  2 }
    };

    for (int y = 1; y < filteredImage.height() - 1; ++y) {
        for (int x = 1; x < filteredImage.width() - 1; ++x) {
            int r = 0, g = 0, b = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    QColor pixel = tempImage.pixelColor(x + dx, y + dy);
                    int factor = kernel[dy + 1][dx + 1];
                    r += pixel.red() * factor;
                    g += pixel.green() * factor;
                    b += pixel.blue() * factor;
                }
            }
            r = qBound(0, r + 128, 255);
            g = qBound(0, g + 128, 255);
            b = qBound(0, b + 128, 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}

//新增暖色濾鏡
void MainWindow::applyWarm()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int r = qBound(0, static_cast<int>(color.red() * 1.2), 255);
            int g = qBound(0, static_cast<int>(color.green() * 1.1), 255);
            int b = qBound(0, static_cast<int>(color.blue() * 1.0), 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}

//新增冷色濾鏡
void MainWindow::applyCool()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int r = qBound(0, static_cast<int>(color.red() * 0.9), 255);
            int g = qBound(0, static_cast<int>(color.green() * 0.9), 255);
            int b = qBound(0, static_cast<int>(color.blue() * 1.1), 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}

//新增戲劇濾鏡
void MainWindow::applyDrama()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    for (int y = 0; y < filteredImage.height(); ++y) {
        for (int x = 0; x < filteredImage.width(); ++x) {
            QColor color = filteredImage.pixelColor(x, y);
            int r = qBound(0, static_cast<int>(color.red() * 1.2), 255);
            int g = qBound(0, static_cast<int>(color.green() * 0.9), 255);
            int b = qBound(0, static_cast<int>(color.blue() * 0.9), 255);
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}

//新增油畫濾鏡
void MainWindow::applyOilPaint()
{
    if (originalImage.isNull()) return;

    filteredImage = originalImage;
    QImage tempImage = filteredImage;

    for (int y = 1; y < filteredImage.height() - 1; ++y) {
        for (int x = 1; x < filteredImage.width() - 1; ++x) {
            int r = 0, g = 0, b = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    QColor pixel = tempImage.pixelColor(x + dx, y + dy);
                    r += pixel.red();
                    g += pixel.green();
                    b += pixel.blue();
                }
            }
            r /= 9; g /= 9; b /= 9;
            filteredImage.setPixelColor(x, y, QColor(r, g, b));
        }
    }
}
