#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include <QTime>
#include <QTimer>
#include <QLabel>
#include "shader.h"
#include "camera.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = NULL);
    ~GLWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    uint second{0};
    QTimer *timer;
    QLabel *fpsLabel;

    GLuint vbo;
    GLuint vao;

    QTime time{QTime::currentTime()};
    Shader *shader;
    Camera *camera;
    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;
    QOpenGLFunctions_3_3_Core *core;
};

#endif // DRAWTRIANGLE_H
