#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class drawTriangle : public QOpenGLWidget
{
    Q_OBJECT

public:
    drawTriangle(QWidget *parent = NULL);
    ~drawTriangle();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    GLuint vbos[2];
    GLuint vaos[2];
    QOpenGLShaderProgram shaderProgram;
    QOpenGLFunctions_3_3_Core *core;
};

#endif // DRAWTRIANGLE_H
