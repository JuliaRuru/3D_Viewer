#include "viewerwidget.h"

ViewerWidget::~ViewerWidget()
{
    makeCurrent();
    free_memory(&picture->vertexes, &picture->data);
    delete picture;
    delete color_line;
    *color_line = nullptr;
    delete color_back;
    *color_back = nullptr;
    delete color_ver;
    *color_ver = nullptr;
    doneCurrent();
}

void ViewerWidget::initializeGL()
{
    initializeOpenGLFunctions();
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    picture = new Engine;
}

void ViewerWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    // Link shader pipeline
    if (!program.link())
        close();
    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void ViewerWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;
    projection.setToIdentity();
    if (this->check_projection) {
        projection.ortho(-aspect, aspect, -1, 1, zNear, zFar);
    } else {
        projection.perspective(fov, aspect, zNear, zFar);
    }
}

void ViewerWidget::paintGL()
{
    initColors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(0.0, 0.0, -2.5);
    program.setUniformValue("mvp_matrix", projection * matrix);

    if (picture->filepath != "") {
        if (line_dot) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
            picture->drawFacets(&program);
            glDisable(GL_LINE_STIPPLE);
        } else {
            picture->drawFacets(&program);
        }
        update();
    }
    if (picture->flag_dot_vert) {
        initColorsVertixes();
        picture->drawVertixes(&program);
        update();
    }
}

void ViewerWidget::initColors()
{
    glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(), 0);
    int colorLocation = program.uniformLocation("color");
    program.setUniformValue(colorLocation, *color_line);
}

void ViewerWidget::initColorsVertixes()
{
    glClearColor(color_ver->redF(), color_ver->greenF(), color_ver->blueF(), 0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color_ver);
    program.disableAttributeArray(vertexLocation);
}
