#include "pch.h"
#include "vertex.h"

namespace RedWood
{
	Vertex::Vertex(vec3 pos, vec2 texCoord, vec3 norm)
		: position(pos), textureCoords(texCoord), normal(norm)
	{}
}
