#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include <QTime>
#include <QTimer>
#include <QLabel>
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
    uint second{0};
    QTimer *timer;
    QLabel *fpsLabel;

    GLuint vbo;
    GLuint vao;

    QTime time{QTime::currentTime()};
    Shader *shader;
    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;
    QOpenGLFunctions_3_3_Core *core;
};

#endif // DRAWTRIANGLE_H
