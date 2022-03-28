#version 430 

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_Diffuse1;

void main()
{
	FragColor = texture(texture_Diffuse1, TexCoords);
}