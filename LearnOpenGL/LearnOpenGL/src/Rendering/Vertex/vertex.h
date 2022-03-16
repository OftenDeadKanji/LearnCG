#pragma once

namespace RedWood
{
	struct Vertex
	{
		explicit Vertex(vec3 pos = {}, vec4 color = {}, vec2 texCoord = {}, vec3 norm = {});

		vec3 position;
		vec4 color;
		vec2 textureCoords;
		vec3 normal;
	};
}

