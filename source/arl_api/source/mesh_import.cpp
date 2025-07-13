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
		constexpr auto chunkSize = 4096;
		if (file) {
			std::vector<char> fileBuffer(chunkSize);
			file.read(reinterpret_cast<char*>(&vBufferSize), sizeof(uint32_t));
			file.read(reinterpret_cast<char*>(&iBufferSize), sizeof(uint32_t));
			file.read(reinterpret_cast<char*>(&mTriangleStripLength), sizeof(uint32_t));
			mVertexBuffer.resize(vBufferSize);
			mIndexBuffer.resize(iBufferSize);
			uint32_t vBufferIndex = 0;
			uint32_t iBufferIndex = 0;
			uint32_t overflowCount = 0;
			constexpr auto vertexSize = sizeof(float) * 8;
			std::vector<char> tempBuffer(vertexSize);
			std::streamsize bytesRead;

			while (true) {
				file.read(fileBuffer.data(), chunkSize);
				bytesRead = file.gcount();
				for (uint32_t i = 0; i < bytesRead;) {
					if (vBufferIndex < vBufferSize) {
						if (i + vertexSize > bytesRead) {
							while (i < bytesRead) {
								tempBuffer[overflowCount] = fileBuffer[i];
								++i;
								++overflowCount;
							}
						}
						else {
							if (overflowCount != 0) {
								while (overflowCount < vertexSize) {
									tempBuffer[overflowCount] = fileBuffer[i];
									++i;
									++overflowCount;
								}
								mVertexBuffer[vBufferIndex] = Vertex(*reinterpret_cast<float*>(tempBuffer.data()), *reinterpret_cast<float*>(tempBuffer.data() + sizeof(float)), *reinterpret_cast<float*>(tempBuffer.data() + sizeof(float) * 2),
																	*reinterpret_cast<float*>(tempBuffer.data() + sizeof(float) * 3), *reinterpret_cast<float*>(tempBuffer.data() + sizeof(float) * 4), *reinterpret_cast<float*>(tempBuffer.data() + sizeof(float) * 5),
																	*reinterpret_cast<float*>(tempBuffer.data() + sizeof(float) * 6), *reinterpret_cast<float*>(tempBuffer.data() + sizeof(float) * 7));
								overflowCount = 0;
							}
							else {
								mVertexBuffer[vBufferIndex] = Vertex(*reinterpret_cast<float*>(fileBuffer.data() + i), *reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float)), *reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float) * 2),
									*reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float) * 3), *reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float) * 4), *reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float) * 5),
									*reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float) * 6), *reinterpret_cast<float*>(fileBuffer.data() + i + sizeof(float) * 7));
								i += vertexSize;
							}
							++vBufferIndex;
						}
					}
					else if (iBufferIndex < iBufferSize) {
						if (i + sizeof(uint32_t) > bytesRead && bytesRead >= chunkSize) {
							while (i < bytesRead) {
								tempBuffer[overflowCount] = fileBuffer[i];
								++i;
								++overflowCount;
							}
						}
						else {
							if (overflowCount != 0) {
								while (overflowCount < sizeof(uint32_t)) {
									tempBuffer[overflowCount] = fileBuffer[i];
									++i;
									++overflowCount;
								}
								mIndexBuffer[iBufferIndex] = *reinterpret_cast<uint32_t*>(tempBuffer.data());
								overflowCount = 0;
							}
							else {
								mIndexBuffer[iBufferIndex] = *reinterpret_cast<uint32_t*>(fileBuffer.data() + i);
								i += sizeof(uint32_t);
							}
							++iBufferIndex;
						}
					}
					else {
						++i;
					}
				}
				if (bytesRead < chunkSize) {
					break;
				}
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
