#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0
layout (location = 1) in vec2 aTexCoord; // 纹理变量的属性位置值为 1

out vec2 TexCoord;

uniform mat4 model  = mat4( 1.0f );
uniform mat4 view  = mat4( 1.0f );
uniform mat4 camera  = mat4( 1.0f );

void main()
{
    gl_Position = camera * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
