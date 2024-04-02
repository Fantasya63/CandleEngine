#include "cdpch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Ref: https://learnopengl.com/Model-Loading/Model

namespace Candle {

	static Assimp::Importer importer;

	Mesh::Mesh(const std::string& path) {
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::string err = "ASSIMP::";
			err.append(importer.GetErrorString());
			CD_CORE_ERROR(err);
			return;
		}
	}

	Mesh::~Mesh() {

	}
}
