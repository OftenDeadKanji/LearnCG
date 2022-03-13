#ifndef RENDERERTYPE_H
#define RENDERERTYPE_H

namespace RedWood
{
	enum class RendererType
	{
		eOpenGL,
		eVulkan,
		eDirectX,

		eDefault = eOpenGL
	};
}

#endif