#ifndef SHADER_H
#define SHADER_H

#include <QDebug>
#include <QString>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Shader
{
public:
    explicit Shader( const QString& vertexfileName, const QString& fragfileName );

    // 使用/激活程序
    bool use();

    // uniform工具函数
    void setBool(const QString &name, bool value);
    void setInt(const QString &name, GLint value);
    void setFloat(const QString &name, GLfloat value);
    void setVec2(const QString &name, const QVector2D &vec2d);
    void setVec3(const QString &name, const QVector3D &vec3d);
    void setVec4(const QString &name, const QVector4D &vec4d);
    void setMat4(const QString &name, const QMatrix4x4 &matrix4x4);

//private:
    QOpenGLShaderProgram shaderProgram;
};

#endif // SHADER_H
