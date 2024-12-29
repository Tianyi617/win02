#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("圖片處理工具");
    window.resize(400, 700);
    window.show();

    return app.exec();
}
