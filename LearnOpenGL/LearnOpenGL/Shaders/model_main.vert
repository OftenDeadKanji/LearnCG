#version 430

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_texCoord;
layout(location = 2) in vec3 in_normal;

out vec2 TexCoords;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	TexCoords = in_texCoord;
	gl_Position = proj * view * vec4(in_pos, 1.0f);
}