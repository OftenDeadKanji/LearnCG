#include "pch.h"
#include "vertex.h"

namespace RedWood
{
	Vertex::Vertex(vec3 pos, vec4 color, vec2 texCoord, vec3 norm)
		: position(pos), color(color), textureCoords(texCoord), normal(norm)
	{}
}
