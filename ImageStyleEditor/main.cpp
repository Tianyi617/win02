#include "ImageStyleEditor.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ImageStyleEditor editor;
    editor.show();
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    return app.exec();
}
