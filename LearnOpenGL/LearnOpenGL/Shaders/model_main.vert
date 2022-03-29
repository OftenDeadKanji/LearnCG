#version 430

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_texCoord;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;

out vec3 FragPos;
out vec2 TexCoords;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * vec4(in_pos, 1.0f);

	FragPos = vec3(in_pos);
	TexCoords = in_texCoord;

	vec3 T = normalize(vec3(model * vec4(in_tangent, 0.0)));
	vec3 B = normalize(vec3(model * vec4(in_bitangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(in_normal, 0.0)));

	TBN = mat3(T, B, N);
}