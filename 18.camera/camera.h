#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QOpenGLShader>
#include <QDebug>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Camera( QVector3D position = QVector3D( 0.0f, 0.0f, 0.0f ), int width = 800, int height = 600 )
    {
        this->cameraPos = position;
        this->lastX = width / 2;
        this->lastY = height / 2;
        this->UpdateCameraLookatMatVectors();
    }

public:
    QMatrix4x4 getViewMat(); // view矩阵
    void DealMouseMovement( GLfloat Xoffset, GLfloat Yoffset ); //鼠标产生的偏移量
    void DealMouseScroll( GLfloat Yoffset ); //滚轮
    void DealKeyboardInputs(); //键盘输入
    void DealKeyInputs( CameraMovement direction ); //单词处理键盘事件
    void UpdateCameraLookatMatVectors(); //更新lookAt相关三个变量

public:
    QVector3D cameraPos = QVector3D( 0.0f, 0.0f, 3.0f ); //相机位置
    QVector3D cameraTarget = QVector3D( 0.0f, 0.0f, -1.0f ); //相机对立方向上一个向量
    QVector3D cameraDirection = QVector3D( cameraPos - cameraTarget ); //相机朝向，一般z轴负向
    QVector3D cameraUp = QVector3D( 0.0f, 1.0f, 0.0f ); // 指向y正半轴
    QVector3D cameraRight = QVector3D( QVector3D::crossProduct( cameraDirection, cameraUp ) );

    GLfloat sensitivity  = 0.001f; //鼠标灵敏度
    GLfloat movementSpeed = 0.1f;
    GLfloat zoom = 45.0f; //投影矩阵的角度
    GLfloat yaw = -90.0f; //偏航角
    GLfloat pitch = 0.0f; //俯视角
    GLboolean isFirstMouse = GL_TRUE;
    GLboolean isLeftMousePress = GL_FALSE;

    GLfloat lastX = 400.0f; // 上一次x
    GLfloat lastY = 300.0f; // 上一次y

    // 记录案件是否按下
    GLboolean keys[1024] = {0};
};

#endif // CAMERA_H
