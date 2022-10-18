#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QQuaternion>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include "engine.h"

class Engine;

class ViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~ViewerWidget();
    Engine *picture = nullptr;

    QColor *color_line = new QColor(214, 214, 214, 255);
    QColor *color_back = new QColor(0, 0, 0, 255);
    QColor *color_ver = new QColor(0, 0, 255, 255);

    void resizeGL(int w, int h) override;
    void initializeGL() override;

    void initColors();
    void initColorsVertixes();
    bool check_projection = false;
    bool line_dot = false;


protected:
    void paintGL() override;
    void initShaders();

private:
    QMatrix4x4 projection;
    QOpenGLShaderProgram program;

};

#endif // VIEWERWIDGET_H
