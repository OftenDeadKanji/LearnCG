#version 430

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_texCoord;
layout(location = 3) in vec3 in_normal;
layout(location = 4) in vec3 in_tangent;
layout(location = 5) in vec3 in_bitangent;

out VS_OUT
{
	vec3 color;
	vec3 normal;
	vec3 fragmentPosition;
	vec2 textureCoordinate;
	mat3 TBN;
	vec4 fragmentPositionInLightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 lightSpaceMatrix;

void main()
{
	gl_Position = proj * view * model * vec4(in_pos, 1.0);

	vs_out.color = in_color;
	vs_out.normal = in_normal;
	vs_out.fragmentPosition = vec3(in_pos);
	vs_out.textureCoordinate = in_texCoord;

	vec3 T = normalize(vec3(model * vec4(in_tangent, 0.0)));
	vec3 B = normalize(vec3(model * vec4(in_bitangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(in_normal, 0.0)));

	vs_out.TBN = mat3(T, B, N);

	vs_out.fragmentPositionInLightSpace = lightSpaceMatrix * vec4(vs_out.fragmentPosition, 1.0);
}