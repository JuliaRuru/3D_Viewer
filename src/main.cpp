#include <QApplication>

#include "View/mainwindow.h"
#include "View/viewerwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model = s21::Model();
  s21::Controller controller(&model);
  s21::MainWindow view(&controller);
  view.setWindowTitle("3D Viewer by drodolfo, ssister & mrorscha");
  view.show();
  return a.exec();
}
