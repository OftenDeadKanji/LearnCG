#version 430 

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in mat3 TBN;

uniform vec3 cameraPos;

struct Material {
	sampler2D Diffuse;
	sampler2D Specular;
	sampler2D Normal;
};
uniform Material material;

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};
#define DIRECTIONAL_LIGHT_MAX_COUNT 8
uniform int directionalLightCount;
uniform DirectionalLight directionalLights[DIRECTIONAL_LIGHT_MAX_COUNT];

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragColor);

void main()
{
	vec3 normal = texture(material.Normal, TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	vec3 color = vec3(texture(material.Diffuse, TexCoords));

	int dirLightCount = min(directionalLightCount, DIRECTIONAL_LIGHT_MAX_COUNT);
	for(int i = 0; i < dirLightCount; ++i)
	{
		color = calculateDirectionalLight(directionalLights[i], normal, color);
	}

	FragColor = vec4(color, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 FragColor)
{
	vec3 lightDir = normalize(-light.direction);

	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * light.color;

	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * light.color;

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * light.color;

	vec3 result = (ambient + diffuse + specular) * FragColor;
	return result;
}