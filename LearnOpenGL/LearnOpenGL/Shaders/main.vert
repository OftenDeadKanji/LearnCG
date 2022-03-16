#version 430

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec4 in_color;
layout(location = 1) in vec2 in_texCoord;
layout(location = 1) in vec3 in_normal;

out vec4 vo_color;

void main()
{
	gl_Position = vec4(in_pos, 1.0f);
	vo_color = in_color;
}