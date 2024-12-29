#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QLabel>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadImage();    // 加載圖片
    void onSaveImage();    // 保存圖片
    void onApplyFilter(const QString &filterType); // 應用濾鏡
    void displaySideBySide(); // 並排顯示

private:
    QImage originalImage;  // 保存原始圖片
    QImage filteredImage;  // 保存濾鏡後的圖片
    QLabel *originalLabel; // 用於顯示原始圖片
    QLabel *filteredLabel; // 用於顯示濾鏡後的圖片


    void applyGrayScale(); // 灰階濾鏡
    void applyInvert();    // 反相濾鏡
    void applyBlur();      // 模糊濾鏡
    void applySharpen();   // 銳化濾鏡
    void applyBrightness(int factor); // 調整亮度
    void applyContrast(float factor); // 調整對比度
    //新增濾鏡
    void applySepia();     // 復古濾鏡
    void applyEdgeDetection(); //邊緣偵測
    void applyEmboss();    //浮雕
    //新增暖色濾鏡
    void applyWarm();      //暖色濾鏡
    //新增冷色濾鏡
    void applyCool();      //冷色濾鏡
    //新增戲劇濾鏡
    void applyDrama();     //戲劇濾鏡
    //新增油畫濾鏡
    void applyOilPaint();  //油畫濾鏡


};

#endif // MAINWINDOW_H
