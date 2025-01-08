#include "learnOpenGL.h"
#include <QTimer>

LearnOpenGL::LearnOpenGL(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

LearnOpenGL::~LearnOpenGL()
{
    delete shader;
}

void LearnOpenGL::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    shader = new Shader( ":/shader/triangle.vert", ":/shader/triangle.frag" );

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

    shader->use();
    shader->setInt( "texture1", 0 );
    shader->setInt( "texture2", 1 );

    core->glBindVertexArray(0);
    core->glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void LearnOpenGL::resizeGL( int w, int h )
{
    core->glViewport( 0, 0, w, h );
}

void LearnOpenGL::paintGL()
{
    core->glClearColor( 1.0f, 0.5f, 0.5f, 1.0f );
    core->glEnable( GL_DEPTH_TEST );
    core->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    core->glActiveTexture( GL_TEXTURE0 );
    texture1->bind();
    core->glActiveTexture( GL_TEXTURE1 );
    texture2->bind();

    shader->use();
    core->glBindVertexArray( vao );

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 camera;
    model.rotate( QTime::currentTime().msecsSinceStartOfDay() / 50.0f, QVector3D( 0.5f, 1.0f, 0.0f ) );
    view.translate( 0.0f, 0.0f, -3.0f );
    camera.perspective( 45.0f, (float)( 800 / 600 ), 0.1f, 100.0f );

    shader->setMat4( "model", model );
    shader->setMat4( "view", view );
    shader->setMat4( "camera", camera );

    core->glDrawArrays( GL_TRIANGLES, 0, 36 );

    update();
}
