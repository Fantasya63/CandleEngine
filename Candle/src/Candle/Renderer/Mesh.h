#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Candle/Renderer/Material.h"


namespace Candle {
	
	class Mesh
	{
	public:

	protected:
		struct SubMesh
		{

		};

	private:

	};

	class StaticMesh : public Mesh
	{
	public:
		static Ref<StaticMesh> Create(const std::string& path);

	private:
		std::vector<SubMesh> m_Submeshes;
		std::vector<Material> m_Materials;

		// Remove vertex arrays when we go to vulcan
	};
}
