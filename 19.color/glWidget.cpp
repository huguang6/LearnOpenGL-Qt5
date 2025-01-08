#include "glWidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

//    fpsLabel = new QLabel;
//    fpsLabel->setStyleSheet( "QLabel{ font-size: 32px; color: blue; }" );
//    fpsLabel->setFixedSize( 300, 64 );
//    fpsLabel->show();
//    fpsLabel->raise();

//    timer = new QTimer( this );
//    QObject::connect( timer, &QTimer::timeout, this, [&]() {
//        fpsLabel->setText( QString( "fps: %1" ).arg( second ) );
//    });

//    timer->start( 1000 );
}

GLWidget::~GLWidget()
{
    delete cubeShader;
    delete lightShader;
    delete camera;
}

void GLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    cubeShader = new Shader( ":/shader/cube.vert", ":/shader/cube.frag" );
    lightShader = new Shader( ":/shader/light.vert", ":/shader/light.frag" );
    camera = new Camera( QVector3D( 0.0f, 0.0f, 0.0f ), this->width(), this->height() );

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //立方体物体
    core->glGenVertexArrays( 1, &vao );
    core->glBindVertexArray( vao );

    core->glGenBuffers( 1, &vbo );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbo );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    //位置属性
    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

    //纹理
    core->glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat) ) );
    core->glEnableVertexAttribArray(1);

    texture1 = new QOpenGLTexture( QImage( ":/image/container.jpg" ).mirrored(), QOpenGLTexture::GenerateMipMaps );
    if( !texture1->isCreated() )
        qWarning() << "texture1 image load failed!" << endl;

    texture1->setWrapMode( QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat );
    texture1->setWrapMode( QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat );

    texture1->setMinificationFilter( QOpenGLTexture::Linear );
    texture1->setMagnificationFilter( QOpenGLTexture::Linear );

    texture2 = new QOpenGLTexture( QImage( ":/image/awesomeface.png" ).mirrored(), QOpenGLTexture::GenerateMipMaps );
    if( !texture2->isCreated() )
        qWarning() << "texture2 image load failed!" << endl;

    texture2->setWrapMode( QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat );
    texture2->setWrapMode( QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat );

    texture2->setMinificationFilter( QOpenGLTexture::Linear );
    texture2->setMagnificationFilter( QOpenGLTexture::Linear );

    cubeShader->use();
    cubeShader->setInt( "texture1", 0 );
    cubeShader->setInt( "texture2", 1 );

    core->glBindVertexArray(0);
    core->glBindBuffer( GL_ARRAY_BUFFER, 0 );

    //光立方体
    core->glGenVertexArrays( 1, &lightVao );
    core->glBindVertexArray( lightVao );

    core->glGenBuffers( 1, &vbo );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbo );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    //位置属性
    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

    core->glBindVertexArray(0);
    core->glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void GLWidget::resizeGL( int w, int h )
{
    core->glViewport( 0, 0, w, h );
}

void GLWidget::paintGL()
{
    // fps
    if( second >= 60 )
        second = 0;

    second++;

    QVector3D cubePositions[] = {
        QVector3D( 0.0f,  0.0f,  0.0f),
        QVector3D( 2.0f,  5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D( 2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f,  3.0f, -7.5f),
        QVector3D( 1.3f, -2.0f, -2.5f),
        QVector3D( 1.5f,  2.0f, -2.5f),
        QVector3D( 1.5f,  0.2f, -1.5f),
        QVector3D(-1.3f,  1.0f, -1.5f)
    };

    //光颜色
    QVector3D lightColor( 1.0f, 1.0f, 0.0f );

    core->glClearColor( 1.0f, 0.5f, 0.5f, 1.0f );
    core->glEnable( GL_DEPTH_TEST );
    core->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    core->glActiveTexture( GL_TEXTURE0 );
    texture1->bind();
    core->glActiveTexture( GL_TEXTURE1 );
    texture2->bind();

    //绘制物体
    cubeShader->use();
    core->glBindVertexArray( vao );

    camera->DealKeyboardInputs();
    cubeShader->setMat4( "view", camera->getViewMat() );

    QMatrix4x4 projection;
    projection.perspective( camera->zoom, (GLfloat)( width() / height() ), 0.1f, 100.0f );
    cubeShader->setMat4( "camera", projection );
    cubeShader->setVec3( "lightColor", lightColor ); //光颜色

    for( uint i = 0; i < 10; i++ )
    {
        QMatrix4x4 model;
        model.translate( cubePositions[i] );
        model.rotate( 10.0f * ( i + 1 ), QVector3D( 1.0f, 0.3f, 0.5f ) );

        cubeShader->setMat4( "model", model );
        core->glDrawArrays( GL_TRIANGLES, 0, 36 );
    }

    //绘制光源
    lightShader->use();
    core->glBindVertexArray( lightVao );
    camera->DealKeyboardInputs();
    lightShader->setMat4( "view", camera->getViewMat() );

    QMatrix4x4 lightprojection;
    lightprojection.perspective( camera->zoom, (GLfloat)( width() / height() ), 0.1f, 100.0f );
    lightShader->setMat4( "camera", lightprojection );
    lightShader->setVec3( "lightColor", lightColor ); //光颜色

    QMatrix4x4 lightModel;
    lightModel.translate( QVector3D( 1.0f, 1.0f, 1.0f ) );
    lightShader->setMat4( "model", lightModel );
    core->glDrawArrays( GL_TRIANGLES, 0, 36 );


    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
        camera->isLeftMousePress = GL_TRUE;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        camera->isLeftMousePress = GL_FALSE;
        camera->isFirstMouse = GL_TRUE;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLint xpos = event->pos().x();
    GLint ypos = event->pos().y();

    if( camera->isLeftMousePress )
    {
        if( camera->isFirstMouse )
        {
            camera->lastX = xpos;
            camera->lastY = ypos;
            camera->isFirstMouse = GL_FALSE;
        }
    }

    GLfloat Xoffset = xpos - camera->lastX;
    GLfloat Yoffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;
    camera->DealMouseMovement( Xoffset, Yoffset );
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint offset = event->angleDelta();
    camera->DealMouseScroll( offset.y() / 20.0f );
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if( key >= 0 && key < 1024 )
        camera->keys[key] = GL_TRUE;
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if( key >= 0 && key < 1024 )
        camera->keys[key] = GL_FALSE;
}
