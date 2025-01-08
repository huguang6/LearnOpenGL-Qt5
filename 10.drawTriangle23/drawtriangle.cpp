#include "drawtriangle.h"

drawTriangle::drawTriangle(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

drawTriangle::~drawTriangle()
{

}

void drawTriangle::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    float vertices[] = {
        // 位置              // 颜色
         0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.0f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    core->glGenVertexArrays( 1, &vao );
    core->glBindVertexArray( vao );

    core->glGenBuffers( 1, &vbo );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbo );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    //位置属性
    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

    //颜色属性
    core->glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat) ) );
    core->glEnableVertexAttribArray(1);

    core->glBindVertexArray(0);
    core->glBindBuffer( GL_ARRAY_BUFFER, 0 );

    QOpenGLShader vertexShader( QOpenGLShader::Vertex );
    bool ok = vertexShader.compileSourceFile( ":/shader/triangle.vert" );
    QOpenGLShader fragShader( QOpenGLShader::Fragment );
    ok = fragShader.compileSourceFile( ":/shader/triangle.frag" );

    shaderProgram.addShader( &vertexShader );
    shaderProgram.addShader( &fragShader );
    shaderProgram.link();
}

void drawTriangle::resizeGL(int w, int h)
{

}

void drawTriangle::paintGL()
{
    core->glClearColor( 1.0f, 0.5f, 0.5f, 1.0f );
    core->glClear( GL_COLOR_BUFFER_BIT );

    shaderProgram.bind();
    core->glBindVertexArray( vao );
    core->glDrawArrays( GL_TRIANGLES, 0, 3 );

    update();
}
