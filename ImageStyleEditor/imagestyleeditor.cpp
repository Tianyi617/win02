#include "ImageStyleEditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <QPainter>
#include <QPen>
#include <QGraphicsTextItem>
#include "MyGraphicsView.h"
#include "ImageEditCommand.h"
#include "EditableTextItem.h"
#include <QShortcut>



// ====== 建構子 ======
ImageStyleEditor::ImageStyleEditor(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), m_undoStack(new QUndoStack(this))
{
    this->setWindowTitle("簡易風格樣式製作");
    this->resize(1200, 600);

    // 中央 widget 與主要 layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 圖片顯示區域 (MyGraphicsView)
    imageDisplay = new MyGraphicsView(this);
    imageDisplay->setScene(scene);
    mainLayout->addWidget(imageDisplay);

    // 初始化背景項目
    backgroundItem = new QGraphicsPixmapItem();
    scene->addItem(backgroundItem);

    // 旋轉滑動條
    QSlider *rotationSlider = new QSlider(Qt::Horizontal, this);
    rotationSlider->setRange(0, 360);
    connect(rotationSlider, &QSlider::valueChanged, this, &ImageStyleEditor::onRotationSliderChanged);

    // 功能按鈕與控件布局
    QHBoxLayout *controlsLayout = new QHBoxLayout();

    // 撤銷與重做按鈕
    undoButton = new QPushButton("上一步", this);
    redoButton = new QPushButton("下一步", this);
    connect(undoButton, &QPushButton::clicked, this, &ImageStyleEditor::undo);
    connect(redoButton, &QPushButton::clicked, this, &ImageStyleEditor::redo);
    connect(m_undoStack, &QUndoStack::canUndoChanged, undoButton, &QPushButton::setEnabled);
    connect(m_undoStack, &QUndoStack::canRedoChanged, redoButton, &QPushButton::setEnabled);
    undoButton->setEnabled(false);
    redoButton->setEnabled(false);
    controlsLayout->addWidget(undoButton);
    controlsLayout->addWidget(redoButton);

    // 刪除文字按鈕
    QPushButton *removeTextButton = new QPushButton("刪除文字", this);
    connect(removeTextButton, &QPushButton::clicked, this, &ImageStyleEditor::removeText);
    controlsLayout->addWidget(removeTextButton);

    // 上傳圖片按鈕
    uploadButton = new QPushButton("上傳圖片", this);
    connect(uploadButton, &QPushButton::clicked, this, &ImageStyleEditor::uploadImage);
    controlsLayout->addWidget(uploadButton);

    // 添加邊框按鈕
    applyBorderButton = new QPushButton("添加邊框", this);
    connect(applyBorderButton, &QPushButton::clicked, this, &ImageStyleEditor::applyBorder);
    controlsLayout->addWidget(applyBorderButton);

    // 添加文字按鈕
    addTextButton = new QPushButton("添加文字", this);
    connect(addTextButton, &QPushButton::clicked, this, &ImageStyleEditor::addText);
    controlsLayout->addWidget(addTextButton);

    // AI 風格轉換按鈕
    aiStyleButton = new QPushButton("AI風格轉換", this);
    connect(aiStyleButton, &QPushButton::clicked, this, &ImageStyleEditor::applyAIStyle);
    controlsLayout->addWidget(aiStyleButton);

    // 保存圖片按鈕與快捷鍵
    saveButton = new QPushButton("保存圖片", this);
    connect(saveButton, &QPushButton::clicked, this, &ImageStyleEditor::saveImage);
    controlsLayout->addWidget(saveButton);
    QShortcut *saveShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(saveShortcut, &QShortcut::activated, saveButton, &QPushButton::click);

    // 上傳邊框素材按鈕
    uploadBorderButton = new QPushButton("上傳邊框素材", this);
    connect(uploadBorderButton, &QPushButton::clicked, this, &ImageStyleEditor::uploadBorder);
    controlsLayout->addWidget(uploadBorderButton);

    // 邊框樣式選擇
    borderStyles = new QComboBox(this);
    borderStyles->addItems({
        "無邊框", "簡約邊框", "花邊", "圓角",
        "雙重邊框", "漸變邊框", "陰影邊框",
        "虛線邊框", "波浪邊框", "霓虹邊框", "撕紙邊框"
    });
    controlsLayout->addWidget(borderStyles);

    // 刪除邊框按鈕
    QPushButton *removeBorderButton = new QPushButton("刪除邊框", this);
    connect(removeBorderButton, &QPushButton::clicked, this, &ImageStyleEditor::removeBorder);
    controlsLayout->addWidget(removeBorderButton);

    // 自定義文字輸入框
    textInput = new QLineEdit(this);
    textInput->setPlaceholderText("輸入文字...");
    controlsLayout->addWidget(textInput);

    // 添加旋轉滑動條到控件布局
    controlsLayout->addWidget(rotationSlider);

    // 將控件布局加入主布局
    mainLayout->addLayout(controlsLayout);
    this->setCentralWidget(centralWidget);

    // 調試輸出場景中的項目
    QList<QGraphicsItem*> itemsInScene = scene->items();
    for (QGraphicsItem *item : itemsInScene) {
        qDebug() << "Item:" << item << "Type:" << item->type() << "Z-Value:" << item->zValue();
    }
}

void ImageStyleEditor::removeText()
{
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    QList<QGraphicsTextItem *> textItemsToRemove;

    // 調試輸出選中項目
    qDebug() << "Selected items count:" << selectedItems.size();

    for (QGraphicsItem *item : selectedItems) {
        qDebug() << "Selected item type:" << item->type();
        if (auto textItem = dynamic_cast<QGraphicsTextItem *>(item)) {
            textItemsToRemove.append(textItem);
        }
    }

    if (textItemsToRemove.isEmpty()) {
        QMessageBox::information(this, "刪除文字", "未選中任何文字項目！");
        return;
    }

    for (QGraphicsTextItem *textItem : textItemsToRemove) {
        scene->removeItem(textItem);
        delete textItem;
    }

    QMessageBox::information(this, "刪除文字", "選中的文字項目已刪除！");
}


ImageStyleEditor::~ImageStyleEditor()
{
    // scene 是用 new，但指定了 parent，所以由 Qt 自動管理，無需手動刪
}
// 把 scene (背景圖片 + 邊框 + 文字物件) 轉成一張 QImage
QImage ImageStyleEditor::renderSceneToImage() const
{
    if (currentPixmap.isNull()) {
        return QImage();
    }

    // 以 currentPixmap 的尺寸為基準
    QImage snapshot(currentPixmap.size(), QImage::Format_ARGB32);
    snapshot.fill(Qt::transparent);

    QPainter painter(&snapshot);
    painter.setRenderHint(QPainter::Antialiasing);

    // scene->sceneRect() 預設和圖片大小相同
    QRectF targetRect(0, 0, snapshot.width(), snapshot.height());
    QRectF sourceRect = scene->sceneRect();

    scene->render(&painter, targetRect, sourceRect);
    painter.end();

    return snapshot;
}

// 清空 scene，使用 QImage 畫回去 (flatten 的做法)
void ImageStyleEditor::loadImageToScene(const QImage &img)
{
    scene->clear();  // 清除所有 item (包括文字)

    // 如果您想保留文字作為獨立項目，而不是「蓋掉」，請不要直接 clear
    // 而應該只更新 backgroundItem->setPixmap(...)
    // 不過這裡要配合「簡易快照」的思路，就整張圖 flatten 了

    if (!img.isNull()) {
        QPixmap pm = QPixmap::fromImage(img);
        currentPixmap = pm;
        originalPixmap = pm;  // 可能也更新 original？
        backgroundItem = new QGraphicsPixmapItem(pm);
        scene->addItem(backgroundItem);
        scene->setSceneRect(0, 0, pm.width(), pm.height());
    }
}

// ============= 圖片上傳 ============
void ImageStyleEditor::uploadImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "選擇圖片", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        currentPixmap.load(filePath);
        originalPixmap = currentPixmap;
        // 設定邊框管理器的原始圖片
        borderMgr.setOriginalPixmap(originalPixmap);
        // 設置背景圖片
        backgroundItem->setPixmap(currentPixmap);
        backgroundItem->setZValue(-1); // 背景設置到最底層

        // 禁止背景項目接收事件
        backgroundItem->setAcceptHoverEvents(false);
        backgroundItem->setAcceptedMouseButtons(Qt::NoButton);
        backgroundItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
        backgroundItem->setFlag(QGraphicsItem::ItemIsFocusable, false);

        // 調整場景尺寸
        scene->setSceneRect(0, 0, currentPixmap.width(), currentPixmap.height());

        // 調試輸出
        qDebug() << "BackgroundItem Mouse Buttons:"
                 << backgroundItem->acceptedMouseButtons()
                 << "Z-Value:" << backgroundItem->zValue();
    }
}




// ============= 保存圖片 ============
void ImageStyleEditor::saveImage() {
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "保存失敗", "沒有圖片可保存，請先上傳圖片！");
        return;
    }

    // 1. 建立一個 QImage，其大小和 currentPixmap 相同
    QImage finalImage(currentPixmap.size(), QImage::Format_ARGB32);
    finalImage.fill(Qt::transparent);

    // 2. 使用 QPainter 針對 finalImage
    QPainter painter(&finalImage);
    painter.setRenderHint(QPainter::Antialiasing);

    // 3. 讓 scene->render() 1:1 繪製
    //    targetRect 與 sourceRect 都等於圖片大小
    QRectF targetRect(0, 0, finalImage.width(), finalImage.height());
    QRectF sourceRect = scene->sceneRect();
    scene->render(&painter, targetRect, sourceRect);

    painter.end();

    // 4. 選擇儲存路徑
    QString savePath = QFileDialog::getSaveFileName(
        this, "保存圖片", "", "Images (*.png *.jpg *.bmp)");
    if (!savePath.isEmpty()) {
        // 5. 將合成好的 finalImage 儲存
        if (!finalImage.save(savePath)) {
            QMessageBox::critical(this, "保存失敗", "圖片保存失敗，請重試！");
        } else {
            QMessageBox::information(this, "保存成功", "圖片已成功保存！");
        }
    }
}


void ImageStyleEditor::uploadBorder()
{
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳背景圖片！");
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(this, "選擇邊框素材", "", "Images (*.png *.jpg *.bmp)");
    if (filePath.isEmpty()) {
        return; // 用戶取消操作
    }

    QPixmap borderPixmap(filePath);
    if (borderPixmap.isNull()) {
        QMessageBox::warning(this, "上傳失敗", "無法載入邊框素材，請確認檔案格式是否正確！");
        return;
    }

    // 計算稍微大於背景的邊框大小
    QSize increasedSize(
        currentPixmap.width() * 1.1, // 增加 10%
        currentPixmap.height() * 1.1 // 增加 10%
        );

    // 調整邊框大小
    QPixmap resizedBorder = borderPixmap.scaled(
        increasedSize,
        Qt::IgnoreAspectRatio, // 忽略原比例
        Qt::SmoothTransformation // 平滑縮放
        );

    // 創建邊框項目並加入場景
    QGraphicsPixmapItem* borderItem = new QGraphicsPixmapItem(resizedBorder);
    borderItem->setZValue(10); // 確保邊框位於背景上層

    // 設置邊框的中心對齊到背景
    QPointF offset(
        (resizedBorder.width() - currentPixmap.width()) / 2.0,
        (resizedBorder.height() - currentPixmap.height()) / 2.0
        );
    borderItem->setPos(-offset); // 偏移使邊框中心對齊背景

    scene->addItem(borderItem);
    borderItems.append(borderItem); // 儲存邊框項目

    QMessageBox::information(this, "邊框添加成功", "邊框已成功添加到背景圖片上層！");
}


// ============= 套用邊框 ============
void ImageStyleEditor::applyBorder() {
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }
    // 1. 先做舊快照
    QImage oldState = renderSceneToImage();

    // 2. 執行原本的套用邊框邏輯
    QString selectedStyle = borderStyles->currentText();
    QPixmap modifiedPixmap = currentPixmap;

    if (selectedStyle == "簡約邊框") {
        borderMgr.applySimpleBorder(modifiedPixmap);
    } else if (selectedStyle == "花邊") {
        borderMgr.applyDecorativeBorder(modifiedPixmap);
    } else if (selectedStyle == "圓角") {
        borderMgr.applyRoundedBorder(modifiedPixmap);
    } else if (selectedStyle == "雙重邊框") {
        borderMgr.applyDoubleBorder(modifiedPixmap);
    } else if (selectedStyle == "漸變邊框") {
        borderMgr.applyGradientBorder(modifiedPixmap);
    } else if (selectedStyle == "陰影邊框") {
        borderMgr.applyShadowBorder(modifiedPixmap);

        // 新增 4 種
    } else if (selectedStyle == "虛線邊框") {
        borderMgr.applyDashedBorder(modifiedPixmap);
    } else if (selectedStyle == "波浪邊框") {
        borderMgr.applyWavyBorder(modifiedPixmap);
    } else if (selectedStyle == "霓虹邊框") {
        borderMgr.applyNeonBorder(modifiedPixmap);
    } else if (selectedStyle == "撕紙邊框") {
        borderMgr.applyTornPaperBorder(modifiedPixmap);

    } else {
        QMessageBox::information(this, "邊框應用", "無需應用邊框！");
        return;
    }

    // 更新 currentPixmap
    currentPixmap = modifiedPixmap;
    backgroundItem->setPixmap(currentPixmap);
    scene->setSceneRect(0, 0, currentPixmap.width(), currentPixmap.height());
    // 3. 取新的快照
    QImage newState = renderSceneToImage();

    // 4. 推到 UndoStack
    pushNewState(oldState, newState, "套用邊框: " + selectedStyle);
}




void ImageStyleEditor::removeBorder()
{
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    // 刪除所有上傳的邊框項目
    for (QGraphicsPixmapItem* item : borderItems) {
        scene->removeItem(item);
        delete item; // 釋放記憶體
    }
    borderItems.clear(); // 清空列表

    // 重置內建邊框
    borderMgr.resetBorders(currentPixmap); // 假設 borderManager 提供 resetBorders 方法

    // 恢復 original 圖片
    currentPixmap = originalPixmap;

    // 更新背景圖片
    backgroundItem->setPixmap(currentPixmap);
    scene->setSceneRect(0, 0, currentPixmap.width(), currentPixmap.height());

    QMessageBox::information(this, "邊框刪除", "所有邊框已刪除，圖片已恢復原始狀態！");
}




// ============= 添加文字 ============
void ImageStyleEditor::addText()
{
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    QString text = textInput->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "操作失敗", "請輸入文字！");
        return;
    }

    // 添加文字到場景
    auto textItem = new EditableTextItem(text);
    textItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction); // 啟用文字編輯模式
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(QFont("Arial", 20));
    textItem->setZValue(100); // 確保文字顯示在最上層
    scene->addItem(textItem);
    qDebug() << "Text item flags:" << textItem->flags();

    // 調試輸出
    qDebug() << "Added EditableTextItem with Z-Value:" << textItem->zValue();
}

void ImageStyleEditor::undo()
{
    m_undoStack->undo();
}

void ImageStyleEditor::redo()
{
    m_undoStack->redo();
}



// ============= AI風格轉換 ============
void ImageStyleEditor::applyAIStyle()
{
    if (currentPixmap.isNull()) {
        QMessageBox::warning(this, "操作失敗", "請先上傳圖片！");
        return;
    }

    QImage oldState = renderSceneToImage();

    bool ok = aiMgr.applyAIStyle(currentPixmap);
    if (!ok) {
        QMessageBox::warning(this, "AI處理失敗", "AI風格處理過程失敗，請檢查程式或模型。");
        return;
    }

    // 不要清空 scene，而是只更新 backgroundItem
    backgroundItem->setPixmap(currentPixmap);
    scene->setSceneRect(0, 0, currentPixmap.width(), currentPixmap.height());

    QImage newState = renderSceneToImage();

    pushNewState(oldState, newState, "AI 風格轉換");
}


// ============= 旋轉文字 (原有功能) ============
void ImageStyleEditor::rotateSelectedText(int angle) {
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "操作失敗", "請選擇要旋轉的文字！");
        return;
    }
    for (QGraphicsItem *item : selectedItems) {
        auto textItem = dynamic_cast<QGraphicsTextItem *>(item);
        if (textItem) {
            textItem->setRotation(angle);
        }
    }
}
void ImageStyleEditor::onRotationSliderChanged(int value) {
    rotateSelectedText(value);
}

void ImageStyleEditor::pushNewState(const QImage &oldState,
                                    const QImage &newState,
                                    const QString &cmdName)
{
    ImageEditCommand *cmd = new ImageEditCommand(this, oldState, newState, cmdName);
    m_undoStack->push(cmd);
}
