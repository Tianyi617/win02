#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "ImageStyleEditor.h"
#include "FilterWidget.h"
#include "cropResizeWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showFilterWidget();
    void showCropResizeWidget();
    void showImageStyleEditor(); // 跳轉到 ImageStyleEditor
    void showMainMenu(); // 新增：返回主菜單的槽

private:
    QStackedWidget *stackedWidget;
    QWidget *mainMenuWidget;
    FilterWidget *filterWidget;         // 改為 FilterWidget 指針
    cropResizeWidget *cropResizeWidget;

    ImageStyleEditor *imageStyleEditor;
    QPushButton *createStyledButton(const QString &text, const QString &iconPath);
};

#endif // MAINWINDOW_H
