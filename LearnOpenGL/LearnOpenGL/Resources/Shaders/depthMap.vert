#version 430

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_texCoord;
layout(location = 3) in vec3 in_normal;
layout(location = 4) in vec3 in_tangent;
layout(location = 5) in vec3 in_bitangent;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
	gl_Position = lightSpaceMatrix * model * vec4(in_pos, 1.0);
}