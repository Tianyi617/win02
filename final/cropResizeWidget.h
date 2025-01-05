#ifndef CROPRESIZEWIDGET_H
#define CROPRESIZEWIDGET_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

class cropResizeWidget : public QMainWindow
{
    Q_OBJECT

public:
    cropResizeWidget(QWidget *parent = nullptr);
    ~cropResizeWidget();

private:
    void createAction();         // 建立動作
    void createMenus();          // 建立選單
    void createToolBar();        // 建立工具列
    void loadFile(QString filename); // 載入圖片
    void updateImageDisplay();   // 更新圖片顯示

protected:
    void resizeEvent(QResizeEvent *event) override; // 覆寫視窗調整大小事件

private slots:
    void showOpenFile();         // 打開檔案的插槽
    void cropImage();            // 剪裁圖片的插槽
    void scaleImage();           // 縮放圖片的插槽
signals:
    void backToMainMenu(); // 添加返回主菜單的信號
private:
    QWidget *central;            // 中央窗口
    QMenu *fileMenu;             // 檔案選單
    QToolBar *fileTool;          // 工具列
    QLabel *imgWin;              // 圖片顯示窗口
    QPixmap currentPixmap;       // 當前圖片
    QString filename;            // 當前圖片檔案名

    // 動作
    QAction *openFileAction;     // 開啟檔案動作
    QAction *exitAction;         // 結束動作

    // 按鈕
    QPushButton *cropButton;     // 剪裁按鈕
    QPushButton *scaleButton;    // 縮放按鈕
};

#endif // CROPRESIZEWIDGET_H
