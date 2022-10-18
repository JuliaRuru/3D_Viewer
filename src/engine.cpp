#include "engine.h"

struct VertexData
{
    QVector3D position;
};

Engine::Engine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();

    initPicture();
}

Engine::~Engine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Engine::initPicture()
{
    QString filename = filepath;
    QFile inputFile(filename);
    if (!inputFile.exists()) {
        return;
    } else {
        QByteArray text_array = filename.toLower().toLatin1();
        char *buff = text_array.data();
        double norm_scale;
        count_elements(buff, &data, &norm_scale);
        allocate_memory(&data, &vertexes);
        filling_matrix(buff, &data, &vertexes, &norm_scale);
        initVertices();

        QVector<GLuint> indices;
        for (int i = 0; i < data.numbers_of_vertexes_in_facet; i++) {
            indices.push_back(data.polygon[i]);
        }
        lines = indices.length();
        indexBuf.bind();
        indexBuf.allocate(indices.data(), sizeof(GLuint)*indices.length());
    }
}

void Engine::initVertices()
{
    QVector<VertexData> vertices;
    for (int i = 1; i < vertexes.rows; i++) {  // цикл по рядам
        VertexData tmp_vert = {QVector3D(vertexes.matrix[i][0], vertexes.matrix[i][1], vertexes.matrix[i][2])};
        vertices.push_back(tmp_vert);
    }
    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), sizeof(VertexData) * vertices.length());
}

void Engine::drawFacets(QOpenGLShaderProgram *program)
{
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
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        offset += sizeof(QVector3D);

        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

        glDrawElements(GL_LINES, arrayBuf.size(), GL_UNSIGNED_INT, nullptr);
    }
}

void Engine::drawVertixes(QOpenGLShaderProgram *program)
{
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
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        offset += sizeof(QVector3D);

        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

        glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);
    }
}

