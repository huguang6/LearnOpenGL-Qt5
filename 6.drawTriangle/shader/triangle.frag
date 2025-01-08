#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;

void main()
{
    FragColor = ourColor; //vec4( 0.0f, 0.5f, 0.5f, 1.0f );
}
