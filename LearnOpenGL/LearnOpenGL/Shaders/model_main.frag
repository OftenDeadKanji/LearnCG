#version 430 

out vec4 FragColor;

in VS_OUT
{
	vec3 fragmentPosition;
	vec2 textureCoordinate;
	mat3 TBN;
} fs_in;

uniform vec3 cameraPos;

struct Material {
	sampler2D Diffuse;
	sampler2D Specular;
	sampler2D Normal;
};

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionalLight
{
	Light light;
	vec3 direction;
};

struct PointLight
{
	Light light;
	vec3 position;
	Attenuation attenuation;
};

uniform Material material;

#define DIRECTIONAL_LIGHT_MAX_COUNT 4
uniform int directionalLightCount;
uniform DirectionalLight directionalLights[DIRECTIONAL_LIGHT_MAX_COUNT];

#define POINT_LIGHT_MAX_COUNT 16
uniform int pointLightCount;
uniform PointLight pointLights[POINT_LIGHT_MAX_COUNT];

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 gammeCorrection(vec3 fragmentColor, float gamma);

void main()
{
	vec3 normal = texture(material.Normal, fs_in.textureCoordinate).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(fs_in.TBN * normal);

	vec3 viewDir = normalize(cameraPos - fs_in.fragmentPosition);

	vec3 result = vec3(0.0f);
	
	int dirLightCount = min(directionalLightCount, DIRECTIONAL_LIGHT_MAX_COUNT);
	for(int i = 0; i < dirLightCount; ++i)
	{
		result += calculateDirectionalLight(directionalLights[i], normal, viewDir);
	}

	int ptLightCount = min(pointLightCount, POINT_LIGHT_MAX_COUNT);
	for(int i = 0; i < ptLightCount; ++i)
	{
		result += calculatePointLight(pointLights[i], normal, fs_in.fragmentPosition, viewDir);
	}

	float gamma = 2.2;
	result = gammeCorrection(result, gamma);

	FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 ambient = light.light.ambient * vec3(texture(material.Diffuse, fs_in.textureCoordinate));

	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.light.diffuse * diff * vec3(texture(material.Diffuse, fs_in.textureCoordinate));

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfway = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfway), 0.0f), 32);
	vec3 specular = light.light.specular * spec * vec3(texture(material.Specular, fs_in.textureCoordinate));

	return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float dist = length(light.position - fs_in.fragmentPosition);
	float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * dist + light.attenuation.quadratic * (dist * dist));

	vec3 ambient = light.light.ambient * vec3(texture(material.Diffuse, fs_in.textureCoordinate));

	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.light.diffuse * diff * vec3(texture(material.Diffuse, fs_in.textureCoordinate));

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	vec3 specular = light.light.specular * spec * vec3(texture(material.Specular, fs_in.textureCoordinate));

	return (ambient + diffuse + specular) * attenuation;
}

vec3 gammeCorrection(vec3 fragmentColor, float gamma)
{
	return pow(fragmentColor, vec3(1.0 / gamma));
}