#version 430

in vec4 vo_color;

out vec4 FragColor;

void main()
{
	FragColor = vo_color;
}