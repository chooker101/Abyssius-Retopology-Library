#include <arl_api/mesh_export.hpp>
#include <fstream>

using namespace arl_api;

void arl_api::MeshExport::ExportARLFile(std::string path, uint32_t tStripLength, const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer)
{
	std::ofstream file(path, std::ios::binary);

	if (file.is_open()) {
		uint32_t vertexBufferSize = vertexBuffer.size();
		uint32_t indexBufferSize = indexBuffer.size();
		file.write(reinterpret_cast<const char*>(&vertexBufferSize), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&indexBufferSize), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&tStripLength), sizeof(uint32_t));
		//Need to implement a stream operation overload
		std::ostream_iterator<Vertex> vertex_iterator(file);
		std::copy(vertexBuffer.begin(), vertexBuffer.end(), vertex_iterator);
		//std::ostream_iterator<uint32_t> index_iterator(file);
		//std::copy(indexBuffer.begin(), indexBuffer.end(), index_iterator);
		for (int i = 0; i < indexBufferSize; ++i) {
			file.write(reinterpret_cast<const char*>(&indexBuffer[i]), sizeof(uint32_t));
		}
		file << std::endl;
		file.flush();
		file.close();
	}
}
