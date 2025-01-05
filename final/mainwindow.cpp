#include "MainWindow.h"
#include "ImageStyleEditor.h"
#include "FilterWidget.h"
#include "CropResizeWidget.h"
#include <QLabel>
#include <QPalette>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    stackedWidget(new QStackedWidget(this)),
    filterWidget(new FilterWidget(this)),
    cropResizeWidget(new ::cropResizeWidget(this)),
    imageStyleEditor(new ImageStyleEditor(this))
{
    this->setWindowTitle("多功能圖像處理工具");
    this->resize(900, 600);

    // 主菜單界面
    mainMenuWidget = new QWidget(this);
    QVBoxLayout *menuLayout = new QVBoxLayout(mainMenuWidget);

    QLabel *titleLabel = new QLabel("多功能圖像處理工具", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    QPushButton *filterButton = createStyledButton("圖片濾鏡應用", ":/images/filter.png");
    QPushButton *cropResizeButton = createStyledButton("圖片裁剪與縮放", ":/images/crop.png");
    QPushButton *imageStyleButton = createStyledButton("風格樣式製作", ":/images/style.png");

    menuLayout->addWidget(titleLabel);
    menuLayout->addWidget(filterButton);
    menuLayout->addWidget(cropResizeButton);
    menuLayout->addWidget(imageStyleButton);
    menuLayout->setSpacing(20);
    menuLayout->setContentsMargins(50, 50, 50, 50);
    mainMenuWidget->setLayout(menuLayout);

    // 配置濾鏡界面
    QVBoxLayout *filterLayout = new QVBoxLayout(filterWidget);
    QPushButton *filterBackButton = new QPushButton("返回主菜單", filterWidget);
    connect(filterBackButton, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    QLabel *filterLabel = new QLabel(filterWidget);
    filterLabel->setAlignment(Qt::AlignCenter);
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterBackButton);

    // 配置裁剪與縮放界面
    QVBoxLayout *cropResizeLayout = new QVBoxLayout(cropResizeWidget);
    QPushButton *cropResizeBackButton = new QPushButton("返回主菜單", cropResizeWidget);
    connect(cropResizeBackButton, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    QLabel *cropResizeLabel = new QLabel(cropResizeWidget);
    cropResizeLabel->setAlignment(Qt::AlignCenter);
    cropResizeLayout->addWidget(cropResizeLabel);
    cropResizeLayout->addWidget(cropResizeBackButton);

    // 配置風格樣式製作界面
    QVBoxLayout *styleLayout = new QVBoxLayout(imageStyleEditor);
    QPushButton *styleBackButton = new QPushButton("返回主菜單", imageStyleEditor);
    connect(styleBackButton, &QPushButton::clicked, this, &MainWindow::showMainMenu);
    QLabel *styleLabel = new QLabel(imageStyleEditor);
    styleLabel->setAlignment(Qt::AlignCenter);
    styleLayout->addWidget(styleLabel);
    styleLayout->addWidget(styleBackButton);

    // 添加界面到 QStackedWidget
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(filterWidget);
    stackedWidget->addWidget(cropResizeWidget);
    stackedWidget->addWidget(imageStyleEditor);

    setCentralWidget(stackedWidget);

    // 按鈕槽連接
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::showFilterWidget);
    connect(cropResizeButton, &QPushButton::clicked, this, &MainWindow::showCropResizeWidget);
    connect(imageStyleButton, &QPushButton::clicked, this, &MainWindow::showImageStyleEditor);
    connect(imageStyleEditor, &ImageStyleEditor::backToMainMenu, this, &MainWindow::showMainMenu);
    connect(filterWidget, &FilterWidget::backToMainMenu, this, &MainWindow::showMainMenu);
    connect(cropResizeWidget, &cropResizeWidget::backToMainMenu, this, &MainWindow::showMainMenu);

}

MainWindow::~MainWindow() {}

void MainWindow::showFilterWidget()
{
    stackedWidget->setCurrentWidget(filterWidget);
}

void MainWindow::showCropResizeWidget()
{
    stackedWidget->setCurrentWidget(cropResizeWidget);
}

void MainWindow::showImageStyleEditor()
{
    stackedWidget->setCurrentWidget(imageStyleEditor);
}

void MainWindow::showMainMenu()
{
    stackedWidget->setCurrentWidget(mainMenuWidget);
}

QPushButton *MainWindow::createStyledButton(const QString &text, const QString &iconPath)
{
    QPushButton *button = new QPushButton(text, this);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(32, 32));
    button->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    padding: 10px 20px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #367b3d;"
        "}"
        );
    return button;
}
