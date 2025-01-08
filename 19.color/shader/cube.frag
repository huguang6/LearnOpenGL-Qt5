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
    FragColor = vec4( lightColor, 1.0f ) * mix(texture2D(texture1, TexCoord), texture2D(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}
