#include "engine.h"

namespace s21 {

struct VertexData {
  QVector3D position;
};

Engine::Engine() : indexBuf(QOpenGLBuffer::IndexBuffer) {
  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
  initPicture(my_controller_);
}

Engine::~Engine() {
  arrayBuf.destroy();
  indexBuf.destroy();
}

void Engine::initPicture(Controller *controller) {
  QString filename = filepath;
  QFile inputFile(filename);
  if (!inputFile.exists()) {
    return;
  } else {
    my_controller_ = controller;
    initVertices();
    QVector<GLuint> indices;
    for (int i = 0; i < my_controller_->getNumbersOfVertexesInFacet(); i++) {
      indices.push_back(my_controller_->getPolygonData(i));
    }
    lines = indices.length();
    indexBuf.bind();
    indexBuf.allocate(indices.data(), sizeof(GLuint) * indices.length());
  }
}

void Engine::initVertices() {
  QVector<VertexData> vertices;
  for (int i = 1; i < my_controller_->getRows(); i++) {
    VertexData tmp_vert = {QVector3D(my_controller_->getMatrixData(i, 0),
                                     my_controller_->getMatrixData(i, 1),
                                     my_controller_->getMatrixData(i, 2))};
    vertices.push_back(tmp_vert);
  }
  arrayBuf.bind();
  arrayBuf.allocate(vertices.data(), sizeof(VertexData) * vertices.length());
}

void Engine::drawFacets(QOpenGLShaderProgram *program) {
  if (filepath == "") {
    return;
  } else {
    glLineWidth(line_width);
    initVertices();
    arrayBuf.bind();
    indexBuf.bind();
    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                                sizeof(VertexData));
    glDrawElements(GL_LINES, arrayBuf.size(), GL_UNSIGNED_INT, nullptr);
  }
}

void Engine::drawVertixes(QOpenGLShaderProgram *program) {
  if (filepath == "") {
    return;
  } else {
    initVertices();
    if (flag_dot_round) {
      glDisable(GL_POINT_SIZE);
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
      glEnable(GL_POINT_SIZE);
    }

    glPointSize(dot_size);
    arrayBuf.bind();
    indexBuf.bind();
    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                                sizeof(VertexData));
    glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);
  }
}

}  //  namespace s21
