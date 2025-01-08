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
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    GLint indices[] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    core->glGenVertexArrays( 1, &vao );
    core->glBindVertexArray( vao );

    core->glGenBuffers( 1, &vbo );
    core->glBindBuffer( GL_ARRAY_BUFFER, vbo );

    core->glGenBuffers( 1, &ebo );
    core->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    core->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    core->glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

    core->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0 );
    core->glEnableVertexAttribArray(0);

    core->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

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
    core->glClearColor( 0.8f, 0.8f, 0.8f, 1.0f );
    core->glClear( GL_COLOR_BUFFER_BIT );

    shaderProgram.bind();
    core->glBindVertexArray( vao );
//    core->glDrawArrays( GL_TRIANGLES, 0, 3 );
    core->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    core->glBindVertexArray( 0 );

    update();
}
