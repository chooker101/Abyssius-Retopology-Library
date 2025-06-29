#pragma once
#include <arl_api/vertex.hpp>

#include <memory>

//Likely move to cpp as should not be needed in other objects
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace arl_api {
	class MeshImport {
	public:
		void LoadMesh(const std::string& meshPath);
		void LoadARLFile(const std::string& arlPath);
		void ClearLoadedMesh();
		const std::vector<Vertex>& GetVertexBuffer() const;
		const std::vector<uint32_t>& GetIndexBuffer() const;
		uint32_t GetARLStripLength() const;
	private:
		bool mIsMeshLoaded = false; //Used to reset if another mesh is loaded
		
		std::vector<Vertex> mVertexBuffer;
		std::vector<uint32_t> mIndexBuffer;
		uint32_t mTriangleStripLength = 0;
	};
}