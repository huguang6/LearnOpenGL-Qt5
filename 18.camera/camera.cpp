#include "camera.h"

QMatrix4x4 Camera::getViewMat()
{
    QMatrix4x4 view;
    view.lookAt( this->cameraPos, this->cameraPos + this->cameraDirection, this->cameraUp );
    return  view;
}

void Camera::DealKeyInputs(CameraMovement direction)
{
    GLfloat velocity = this->movementSpeed;
    if( direction == FORWARD )
        this->cameraPos += this->cameraDirection * velocity;

    if( direction == BACKWARD )
        this->cameraPos -= this->cameraDirection * velocity;

    if( direction == LEFT )
        this->cameraPos -= this->cameraRight * velocity;

    if( direction == RIGHT )
        this->cameraPos += this->cameraRight * velocity;

    if( direction == UP )
        this->cameraPos += QVector3D( 0.0F, 1.0f, 0.0f ) * velocity;

    if( direction == DOWN )
        this->cameraPos -= QVector3D( 0.0F, 1.0f, 0.0f ) * velocity;
}

void Camera::DealMouseMovement(GLfloat Xoffset, GLfloat Yoffset)
{
    Xoffset *= this->sensitivity;
    Yoffset *= this->sensitivity;

    this->yaw += Xoffset;
    this->pitch += Yoffset;

    if( this->pitch > 89.0f )
        this->pitch = 89.0f;
    if( this->pitch < -89.0f )
        this->pitch = -89.0f;

    UpdateCameraLookatMatVectors();
}

void Camera::DealMouseScroll(GLfloat Yoffset)
{
    if( this->zoom >= 1.0f && this->zoom <= 45.0f )
        this->zoom -= Yoffset;

    if( this->zoom > 45.0f )
        this->zoom = 45.0f;

    if( this->zoom < 1.0f )
        this->zoom = 1.0f;
}

void Camera::DealKeyboardInputs()

{
    if( keys[Qt::Key_W] )
        DealKeyInputs( FORWARD );

    if( keys[Qt::Key_S] )
        DealKeyInputs( BACKWARD );

    if( keys[Qt::Key_A] )
        DealKeyInputs( LEFT );

    if( keys[Qt::Key_D] )
        DealKeyInputs( RIGHT );

    if( keys[Qt::Key_Q] )
        DealKeyInputs( UP );

    if( keys[Qt::Key_E] )
        DealKeyInputs( DOWN );
}

void Camera::UpdateCameraLookatMatVectors()
{
    QVector3D deirction( cos( yaw ) * cos( pitch ), sin( pitch ), sin( yaw ) * cos( pitch ) );
    this->cameraDirection = deirction.normalized();
//    this->cameraRight = QVector3D::crossProduct( this->cameraDirection, QVector3D( 0.0f, 1.0f, 0.0f )  ).normalized();
//    this->cameraUp = QVector3D::crossProduct( cameraRight, cameraDirection ).normalized();
}
