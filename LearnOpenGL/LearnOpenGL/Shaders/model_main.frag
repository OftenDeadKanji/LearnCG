#version 430 

out vec4 FragColor;
uniform sampler2D shadowMap;

in VS_OUT
{
	vec3 color;
	vec3 normal;
	vec3 fragmentPosition;
	vec2 textureCoordinate;
	mat3 TBN;
	vec4 fragmentPositionInLightSpace;
} fs_in;

uniform vec3 cameraPos;
uniform vec3 lightPos;

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

uniform bool withDiffuseTexture;
uniform bool withSpecularTexture;
uniform bool withNormalTexture;


vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuseSampled, vec3 specularSampled);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseSampled, vec3 specularSampled);

float shadowCalculation(vec4 fragmentPositionInLightSpace, vec3 normal, vec3 lightDir);

vec3 gammaCorrection(vec3 fragmentColor, float gamma);

void main()
{
	vec3 diffuseColor, specularColor, normal;
	if(withDiffuseTexture)
	{
		diffuseColor = vec3(texture(material.Diffuse, fs_in.textureCoordinate));
	}
	else
	{
		diffuseColor = fs_in.color;
	}

	if(withSpecularTexture)
	{
		specularColor = vec3(texture(material.Specular, fs_in.textureCoordinate));
	}
	else
	{
		specularColor = fs_in.color;
	}

	if (withNormalTexture)
	{
		normal = texture(material.Normal, fs_in.textureCoordinate).rgb;
		normal = normalize(normal * 2.0 - 1.0);
		normal = normalize(fs_in.TBN * normal);
	}
	else
	{
		normal = fs_in.normal;
	}

	vec3 viewDir = normalize(cameraPos - fs_in.fragmentPosition);

	vec3 result = vec3(0.0f);
	
	int dirLightCount = min(directionalLightCount, DIRECTIONAL_LIGHT_MAX_COUNT);
	for(int i = 0; i < dirLightCount; ++i)
	{
		result += calculateDirectionalLight(directionalLights[i], normal, viewDir, diffuseColor, specularColor);
	}

	int ptLightCount = min(pointLightCount, POINT_LIGHT_MAX_COUNT);
	for(int i = 0; i < ptLightCount; ++i)
	{
		result += calculatePointLight(pointLights[i], normal, fs_in.fragmentPosition, viewDir, diffuseColor, specularColor);
	}

	if (withDiffuseTexture)
	{
		float gamma = 2.2;
		result = gammaCorrection(result, gamma);
	}

	FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuseSampled, vec3 specularSampled)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 ambient = light.light.ambient * diffuseSampled;

	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.light.diffuse * diff * diffuseSampled;

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfway = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfway), 0.0f), 32);
	vec3 specular = light.light.specular * spec * specularSampled;

	float shadow = shadowCalculation(fs_in.fragmentPositionInLightSpace, normal, lightDir);

	return ambient + (1.0 - shadow) * (diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseSampled, vec3 specularSampled)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float dist = length(light.position - fs_in.fragmentPosition);
	float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * dist + light.attenuation.quadratic * (dist * dist));

	vec3 ambient = light.light.ambient * diffuseSampled;

	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.light.diffuse * diff * diffuseSampled;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	vec3 specular = light.light.specular * spec * specularSampled;

	return (ambient + diffuse + specular) * attenuation;
}

float shadowCalculation(vec4 fragmentPositionInLightSpace, vec3 normal, vec3 lightDir)
{
	vec3 projectionCoords = fragmentPositionInLightSpace.xyz / fragmentPositionInLightSpace.w;
	projectionCoords = projectionCoords * 0.5 + 0.5;
	
	float closestDepth = texture(shadowMap, projectionCoords.xy).r;
	float currentDepth = projectionCoords.z;

	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projectionCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0;

	if(projectionCoords.z > 1.0)
	{
		shadow = 0.0;
	}

	return shadow;
}

vec3 gammaCorrection(vec3 fragmentColor, float gamma)
{
	return pow(fragmentColor, vec3(1.0 / gamma));
}