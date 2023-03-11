#ifndef SRC_VIEW_ENGINE_H
#define SRC_VIEW_ENGINE_H

#include <QColor>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuaternion>
#include <QTimer>
#include <QVector2D>
#include <QVector3D>
#include <QVector>

#include "../Controller/controller.h"

namespace s21 {

class Engine : protected QOpenGLFunctions {

public:
  explicit Engine();
  virtual ~Engine();

  void drawFacets(QOpenGLShaderProgram *program);
  void drawVertixes(QOpenGLShaderProgram *program);
  void initColorsVertixes();

  QString filepath = NULL;
  void initPicture(Controller *controller);
  void initVertices();
  int vertex_label, facets_label;

  double line_width = 1.0;
  double dot_size = 1.0;
  bool flag_dot_vert = false;
  bool flag_dot_round = false;

private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
  GLsizei lines;
  Controller *my_controller_ = nullptr;
};

} //  namespace s21

#endif // SRC_VIEW_ENGINE_H
