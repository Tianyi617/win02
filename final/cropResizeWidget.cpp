#include "cropResizeWidget.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QPixmap>
#include <QInputDialog>

cropResizeWidget::cropResizeWidget(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理器"));
    this->setStyleSheet("background-color: #3C3C3C;");

    // Central widget setup
    central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);


    // Image display setup
    imgWin = new QLabel();
    QPixmap initPixmap(300, 200);
    initPixmap.fill(QColor(255, 255, 255));
    imgWin->setPixmap(initPixmap);
    imgWin->setAlignment(Qt::AlignCenter); // 將圖片置中顯示
    mainLayout->addWidget(imgWin);


    mainLayout->addWidget(imgWin);

    // Add buttons for cropping and scaling
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cropButton = new QPushButton(QStringLiteral("剪裁圖片"));
    scaleButton = new QPushButton(QStringLiteral("縮放圖片"));
    QPushButton *backButton = new QPushButton(QStringLiteral("返回主菜單")); // 返回按鈕

    buttonLayout->addWidget(cropButton);
    buttonLayout->addWidget(scaleButton);
    buttonLayout->addWidget(backButton); // 添加返回按鈕

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(central);

    // Connect button actions
    connect(cropButton, &QPushButton::clicked, this, &cropResizeWidget::cropImage);
    connect(scaleButton, &QPushButton::clicked, this, &cropResizeWidget::scaleImage);
    connect(backButton, &QPushButton::clicked, this, &cropResizeWidget::backToMainMenu); // 發射返回信號

    // Create UI components
    createAction();
    createMenus();
    createToolBar();
}

cropResizeWidget::~cropResizeWidget() {}

void cropResizeWidget::createAction()
{
    // Open File action
    openFileAction = new QAction(QStringLiteral("開啟新檔(&O)"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, &QAction::triggered, this, &cropResizeWidget::showOpenFile);

    // Exit action
    exitAction = new QAction(QStringLiteral("結束(&Q)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, &QAction::triggered, this, &cropResizeWidget::close);
}

void cropResizeWidget::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);
}

void cropResizeWidget::createToolBar()
{
    QToolBar *toolBar = addToolBar(QStringLiteral("工具列"));
    toolBar->addAction(openFileAction);
    toolBar->addAction(exitAction);
}
void cropResizeWidget::loadFile(QString filename)
{
    QPixmap pixmap;
    if (!pixmap.load(filename)) {
        qDebug() << "Failed to load image:" << filename;
        return;
    }

    currentPixmap = pixmap;
    updateImageDisplay();
}
void cropResizeWidget::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateImageDisplay(); // 視窗大小改變時同步更新顯示的圖片
}


void cropResizeWidget::showOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("選擇影像檔案"),
        QString(),
        QStringLiteral("Images (*.png *.xpm *.jpg *.bmp *.gif);;All Files (*)"));

    if (!filename.isEmpty()) {
        loadFile(filename);
    }
}
void cropResizeWidget::updateImageDisplay()
{
    if (currentPixmap.isNull()) return;

    // 將圖片縮放到 QLabel 的大小並保持比例
    QSize labelSize = imgWin->size();
    QPixmap scaledPixmap = currentPixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgWin->setPixmap(scaledPixmap);
}


void cropResizeWidget::cropImage()
{
    if (currentPixmap.isNull()) {
        qDebug() << "No image loaded for cropping.";
        return;
    }

    // Get crop dimensions from the user
    bool ok;
    int x = QInputDialog::getInt(this, QStringLiteral("剪裁圖片"), QStringLiteral("輸入 X 起始座標:"), 0, 0, currentPixmap.width(), 1, &ok);
    if (!ok) return;
    int y = QInputDialog::getInt(this, QStringLiteral("剪裁圖片"), QStringLiteral("輸入 Y 起始座標:"), 0, 0, currentPixmap.height(), 1, &ok);
    if (!ok) return;
    int width = QInputDialog::getInt(this, QStringLiteral("剪裁圖片"), QStringLiteral("輸入寬度:"), currentPixmap.width(), 1, currentPixmap.width(), 1, &ok);
    if (!ok) return;
    int height = QInputDialog::getInt(this, QStringLiteral("剪裁圖片"), QStringLiteral("輸入高度:"), currentPixmap.height(), 1, currentPixmap.height(), 1, &ok);
    if (!ok) return;

    // Perform the crop
    QRect cropArea(x, y, width, height);
    currentPixmap = currentPixmap.copy(cropArea);
    imgWin->setPixmap(currentPixmap);
}

void cropResizeWidget::scaleImage()
{
    if (currentPixmap.isNull()) {
        qDebug() << "No image loaded for scaling.";
        return;
    }

    // Get scaling dimensions from the user
    bool ok;
    int newWidth = QInputDialog::getInt(this, QStringLiteral("縮放圖片"), QStringLiteral("輸入新寬度:"), currentPixmap.width(), 1, 10000, 1, &ok);
    if (!ok) return;
    int newHeight = QInputDialog::getInt(this, QStringLiteral("縮放圖片"), QStringLiteral("輸入新高度:"), currentPixmap.height(), 1, 10000, 1, &ok);
    if (!ok) return;

    // Perform the scaling
    currentPixmap = currentPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgWin->setPixmap(currentPixmap);
}

