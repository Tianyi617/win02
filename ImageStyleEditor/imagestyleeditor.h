#ifndef IMAGESTYLEEDITOR_H
#define IMAGESTYLEEDITOR_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

class ImageStyleEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit ImageStyleEditor(QWidget *parent = nullptr);
    ~ImageStyleEditor();

private slots:
    void uploadImage();
    void saveImage();
    void applyBorder();
    void addText();
    void applyAIStyle();
    void applySimpleBorder(QPixmap &pixmap); // 添加簡約邊框
    void applyDecorativeBorder(QPixmap &pixmap); // 添加花邊
    void applyRoundedBorder(QPixmap &pixmap); // 添加圓角邊框
    void applyDoubleBorder(QPixmap &pixmap);  // 雙重邊框
    void applyGradientBorder(QPixmap &pixmap);  // 漸變邊框
    void applyShadowBorder(QPixmap &pixmap);  // 陰影邊框
    void removeBorder();  // 刪除邊框

private:
    QGraphicsView *imageDisplay;
    QGraphicsScene *scene;
    QPushButton *uploadButton;
    QPushButton *saveButton;
    QPushButton *applyBorderButton;
    QPushButton *addTextButton;
    QPushButton *aiStyleButton;
    QLineEdit *textInput;
    QComboBox *borderStyles;
    QPixmap currentPixmap;
    QPixmap originalPixmap;  // 新增這一行

};

#endif // IMAGESTYLEEDITOR_H
