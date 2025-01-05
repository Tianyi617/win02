#ifndef IMAGESTYLEEDITOR_H
#define IMAGESTYLEEDITOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QUndoStack>
#include "BorderManager.h"
#include "TextManager.h"
#include "AIStyleManager.h"

class ImageStyleEditor : public QMainWindow
{
    Q_OBJECT
    // <-- 在類別開頭或結尾都可以
    friend class ImageEditCommand;

public:
    explicit ImageStyleEditor(QWidget *parent = nullptr);
    ~ImageStyleEditor();
    // 在 public 區塊宣告
    QImage renderSceneToImage() const;

private slots:
    void uploadImage();
    void saveImage();
    void applyBorder();
    void removeBorder();
    void addText();
    void applyAIStyle();
    void rotateSelectedText(int angle);
    void onRotationSliderChanged(int value);
    // 新增
    void undo();
    void redo();
    void uploadBorder();
    void removeText();
private:
    QGraphicsScene *scene;
    QGraphicsView *imageDisplay;

    QPushButton *uploadButton;
    QPushButton *applyBorderButton;
    QPushButton *addTextButton;
    QPushButton *aiStyleButton;
    QPushButton *saveButton;
    QPushButton *uploadBorderButton;

    QLineEdit *textInput;
    QComboBox *borderStyles;

    QPixmap currentPixmap;
    QPixmap originalPixmap;

    // 我們的 Manager
    BorderManager borderMgr;
    TextManager textMgr;
    AIStyleManager aiMgr;
    // 這裡加一個「背景圖片」的指標，用來替換圖片
    QGraphicsPixmapItem *backgroundItem = nullptr;
    // 新增 Undo/Redo
    QUndoStack *m_undoStack;
    QPushButton *undoButton;
    QPushButton *redoButton;
    // 因為已經將 ImageEditCommand 宣告為 friend class
    // 即便 loadImageToScene() 是 private, ImageEditCommand 也可以呼叫
    void loadImageToScene(const QImage &img);

    // 在每次執行編輯操作前後，將狀態做為命令推到 QUndoStack
    void pushNewState(const QImage &oldState, const QImage &newState, const QString &cmdName);
    QList<QGraphicsPixmapItem*> borderItems; // 儲存所有上傳的邊框素材

};

#endif // IMAGESTYLEEDITOR_H
