#include <arl_api/mesh_import.hpp>

#include <cassert>
#include <fstream>
#include <future>

namespace arl_api {
	void MeshImport::LoadMesh(const std::string& meshPath) {
		if (mIsMeshLoaded) {
			ClearLoadedMesh();
		}

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_RemoveComponent | aiProcess_GenSmoothNormals);
		//std::unique_ptr<aiScene> scene = std::make_unique<aiScene>(file);

		assert(scene); //Need proper error handling

		//Shouldn't need multimesh, but might add later
		assert(scene->mNumMeshes == 1);
		const aiMesh* assimpMesh = scene->mMeshes[0];

		mVertexBuffer.clear();
		mVertexBuffer.resize(assimpMesh->mNumVertices);
		for (uint32_t i = 0; i < assimpMesh->mNumVertices; ++i) {
			mVertexBuffer[i] = Vertex(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z,
				assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z,
				assimpMesh->mTextureCoords[0][i].x, assimpMesh->mTextureCoords[0][i].y);
		}

		mIndexBuffer.clear();
		mIndexBuffer.resize(assimpMesh->mNumFaces * 3);
		for (uint32_t i = 0, j = 0; i < assimpMesh->mNumFaces; ++i, j += 3) {
			assert(assimpMesh->mFaces[i].mNumIndices == 3);
			mIndexBuffer[j] = assimpMesh->mFaces[i].mIndices[0];
			mIndexBuffer[j + 1] = assimpMesh->mFaces[i].mIndices[1];
			mIndexBuffer[j + 2] = assimpMesh->mFaces[i].mIndices[2];
		}
		mIsMeshLoaded = true;
	}

	void MeshImport::LoadARLFile(const std::string& arlPath)
	{
		if (mIsMeshLoaded) {
			ClearLoadedMesh();
		}
		std::ifstream file(arlPath, std::ios::binary);
		uint32_t vBufferSize = 0;
		uint32_t iBufferSize = 0;

		//Needs a lot of optimization
		if (file) {
			file >> vBufferSize;
			file >> iBufferSize;
			file >> mTriangleStripLength;
			mVertexBuffer.resize(vBufferSize);
			for (uint32_t i = 0; i < vBufferSize; ++i) {
				file >> mVertexBuffer[i];
			}
			mIndexBuffer.resize(iBufferSize);
			for (uint32_t i = 0; i < iBufferSize; ++i) {
				file >> mIndexBuffer[i];
			}
			mIsMeshLoaded = true;
		}
	}

	void MeshImport::ClearLoadedMesh()
	{
		mVertexBuffer.clear();
		mIndexBuffer.clear();
		mTriangleStripLength = 0;
		mIsMeshLoaded = false;
	}

	const std::vector<Vertex>& MeshImport::GetVertexBuffer() const
	{
		return mVertexBuffer;
	}

	const std::vector<uint32_t>& MeshImport::GetIndexBuffer() const
	{
		return mIndexBuffer;
	}

	uint32_t MeshImport::GetARLStripLength() const
	{
		return mTriangleStripLength;
	}
}
