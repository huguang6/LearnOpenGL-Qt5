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
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, //left
        0.5f, -0.5f, 0.0f,  //right
        0.0f, 0.5f, 0.0f   //top
    };

    core->glGenVertexArrays( 1, &vao );
    core->glBindVertexArray( vao );

    core->glGenBuffers( 1, &vbo );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbo );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

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

    GLint location = shaderProgram.uniformLocation( "ourColor" );
    shaderProgram.setUniformValue( location, QVector4D( 0.4, abs( sin(float(time.elapsed() / 1000.0f))), 0.0f, 1.0f ) );

    core->glBindVertexArray( vao );
    core->glDrawArrays( GL_TRIANGLES, 0, 3 );

    update();
}
