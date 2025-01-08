#include "shader.h"

Shader::Shader( const QString& vertexfileName, const QString& fragfileName )
{
    QOpenGLShader vertexShader( QOpenGLShader::Vertex );
    bool ok = vertexShader.compileSourceFile( vertexfileName );
    QOpenGLShader fragShader( QOpenGLShader::Fragment );
    ok = fragShader.compileSourceFile( fragfileName );

    shaderProgram.addShader( &vertexShader );
    shaderProgram.addShader( &fragShader );
    shaderProgram.link();
}

bool Shader::use()
{
    return shaderProgram.bind();
}

void Shader::setBool(const QString &name, bool value)
{
    GLint location = shaderProgram.uniformLocation( name );
    shaderProgram.setUniformValue( location, value );
}

void Shader::setInt(const QString &name, GLint value)
{
    GLint location = shaderProgram.uniformLocation( name );
    shaderProgram.setUniformValue( location, value );
}

void Shader::setFloat(const QString &name, GLfloat value)
{
    GLint location = shaderProgram.uniformLocation( name );
    shaderProgram.setUniformValue( location, value );
}

void Shader::setVec3(const QString &name, const QVector3D &vec3d)
{
    GLint location = shaderProgram.uniformLocation( name );
    shaderProgram.setUniformValue( location, vec3d );
}

void Shader::setVec4(const QString &name, const QVector4D &vec4d)
{
    GLint location = shaderProgram.uniformLocation( name );
    shaderProgram.setUniformValue( location, vec4d );
}
