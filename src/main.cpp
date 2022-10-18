#include "mainwindow.h"
#include "viewerwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("3D Viewer by drodolfo, ssister & mrorscha");
    w.show();
    return a.exec();
}
