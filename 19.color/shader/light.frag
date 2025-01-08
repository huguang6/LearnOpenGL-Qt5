#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4( lightColor, 1.0f );
}
