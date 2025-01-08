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
    GLfloat firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
    };
    GLfloat secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    core->glGenVertexArrays( 2, vaos );
    core->glGenBuffers( 2, vbos );

    core->glBindVertexArray( vaos[0] );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbos[0] );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW );
    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

    core->glBindVertexArray( vaos[1] );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbos[1] );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW );
    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    core->glEnableVertexAttribArray(0);

//    core->glBindVertexArray(0);
//    core->glBindBuffer( GL_ARRAY_BUFFER, 0 );

    QOpenGLShader vertexShader( QOpenGLShader::Vertex );
    bool ok = vertexShader.compileSourceFile( ":/shader/triangle.vert" );
    QOpenGLShader fragShader( QOpenGLShader::Fragment );
    ok = fragShader.compileSourceFile( ":/shader/triangle.frag" );

    QOpenGLShader fragShader2( QOpenGLShader::Fragment );
    ok = fragShader2.compileSourceFile( ":/shader/triangle2.frag" );

    shaderProgram.addShader( &vertexShader );
    shaderProgram.addShader( &fragShader );
    shaderProgram.link();

    shaderProgram2.addShader( &vertexShader );
    shaderProgram2.addShader( &fragShader2 );
    shaderProgram2.link();
}

void drawTriangle::resizeGL(int w, int h)
{

}

void drawTriangle::paintGL()
{
    core->glClearColor( 1.0f, 0.5f, 0.5f, 1.0f );
    core->glClear( GL_COLOR_BUFFER_BIT );

    shaderProgram.bind();
    core->glBindVertexArray( vaos[0] );
    core->glDrawArrays( GL_TRIANGLES, 0, 3 );

    shaderProgram2.bind();
    core->glBindVertexArray( vaos[1] );
    core->glDrawArrays( GL_TRIANGLES, 0, 3 );

    update();
}
