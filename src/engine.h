#ifndef ENGINE_H
#define ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QVector>
#include <QColor>
#include <QTimer>
#include <QQuaternion>

extern "C" {
#include "rendering_calculations.h"
}

class Engine : protected QOpenGLFunctions
{

public:
    Engine();
    virtual ~Engine();

    void drawFacets(QOpenGLShaderProgram *program);
    void drawVertixes(QOpenGLShaderProgram *program);
    void initColorsVertixes();

    QString filepath = NULL;
    void initPicture();
    void initVertices();

    int vertex_label, facets_label;
    data_t data = { 0, 0, 0, {0, 0, 0}, 0 };
    vertexes_t vertexes = { 0, 0, 0 };
    double line_width = 1.0;
    double dot_size = 1.0;
    bool flag_dot_vert = false;
    bool flag_dot_round = false;

private:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    GLsizei lines;
};

#endif // ENGINE_H
