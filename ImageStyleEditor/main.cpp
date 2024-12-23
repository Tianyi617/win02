#include "ImageStyleEditor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ImageStyleEditor editor;
    editor.show();

    return app.exec();
}
