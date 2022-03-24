#version 430

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_texCoord;
layout(location = 2) in vec3 in_normal;

out vec4 vo_color;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
	gl_Position = projMatrix * viewMatrix * vec4(in_pos, 1.0f);
}