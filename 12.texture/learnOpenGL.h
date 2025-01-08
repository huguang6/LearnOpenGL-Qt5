#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include "shader.h"

class LearnOpenGL : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit LearnOpenGL(QWidget *parent = NULL);
    ~LearnOpenGL();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
//    GLuint texture;
    Shader *shader;
    QOpenGLTexture *texture1;
    QOpenGLFunctions_3_3_Core *core;
};

#endif // DRAWTRIANGLE_H
