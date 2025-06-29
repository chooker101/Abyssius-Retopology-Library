#include <arl_api/mesh_export.hpp>
#include <fstream>

using namespace arl_api;

void arl_api::MeshExport::ExportARLFile(std::string path, uint32_t tStripLength, const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer)
{
	std::ofstream file(path, std::ios::binary);

	if (file.is_open()) {
		file << static_cast<uint32_t>(vertexBuffer.size());
		file << static_cast<uint32_t>(indexBuffer.size());
		file << tStripLength;
		//Need to implement a stream operation overload
		std::ostream_iterator<Vertex> vertex_iterator(file);
		std::copy(vertexBuffer.begin(), vertexBuffer.end(), vertex_iterator);
		std::ostream_iterator<uint32_t> index_iterator(file);
		std::copy(indexBuffer.begin(), indexBuffer.end(), index_iterator);
		file << std::endl;
		file.flush();
		file.close();
	}
}
