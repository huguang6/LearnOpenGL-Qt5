#include "learnOpenGL.h"

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

    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // 左上
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    core->glGenVertexArrays( 1, &vao );
    core->glBindVertexArray( vao );

    core->glGenBuffers( 1, &vbo );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbo );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    core->glGenBuffers(1, &ebo);
    core->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    core->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//    core->glGenTextures( 1, &texture );
//    core->glBindTexture( GL_TEXTURE_2D, texture );

//    // 为当前绑定的纹理对象设置环绕、过滤方式
//    core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    QImage boxImage( ":/image/container.jpg", "jpg" );
//    boxImage = boxImage.mirrored();
//    if( !boxImage.isNull() )
//    {
//        core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, boxImage.width(), boxImage.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, boxImage.bits() );
//        core->glGenerateMipmap(GL_TEXTURE_2D);
//    }


    //位置属性
    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

    //颜色属性
    core->glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat) ) );
    core->glEnableVertexAttribArray(1);

    //纹理
    core->glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat) ) );
    core->glEnableVertexAttribArray(2);

    texture1 = new QOpenGLTexture( QImage( ":/image/container.jpg" ).mirrored(), QOpenGLTexture::GenerateMipMaps );
    if( !texture1->isCreated() )
        qWarning() << "texture1 image load failed!" << endl;

    texture1->setWrapMode( QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge );
    texture1->setWrapMode( QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge );

    texture1->setMinificationFilter( QOpenGLTexture::Nearest );
    texture1->setMagnificationFilter( QOpenGLTexture::Nearest );



    texture2 = new QOpenGLTexture( QImage( ":/image/awesomeface.png" ).mirrored(), QOpenGLTexture::GenerateMipMaps );
    if( !texture2->isCreated() )
        qWarning() << "texture2 image load failed!" << endl;

    texture2->setWrapMode( QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat );
    texture2->setWrapMode( QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat );

    texture2->setMinificationFilter( QOpenGLTexture::Nearest );
    texture2->setMagnificationFilter( QOpenGLTexture::Nearest );

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
    core->glClear( GL_COLOR_BUFFER_BIT );

    core->glActiveTexture( GL_TEXTURE0 );
    texture1->bind();
    core->glActiveTexture( GL_TEXTURE1 );
    texture2->bind();

    shader->use();
    core->glBindVertexArray( vao );

    QMatrix4x4 mat4;
    mat4.scale( 1.2 );
    mat4.translate( 0.2f, 0.1f, 0.0f );
    mat4.rotate( sin( time.elapsed() / 100 ), QVector3D( 0.0f, 0.0f, 1.0f ) );
    shader->setMat4( "tansform", mat4 );

//    core->glDrawArrays( GL_TRIANGLES, 0, 3 );
    core->glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

    update();
}
