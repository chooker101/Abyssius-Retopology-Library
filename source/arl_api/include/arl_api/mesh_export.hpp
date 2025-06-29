#pragma once
#include <arl_api/vertex.hpp>
#include <vector>
#include <string>

namespace arl_api {
	class MeshExport {
	public:
		// VertexBufferSize, IndexBufferSize, TriangleStripLength, VertexBuffer, IndexBuffer
		void ExportARLFile(std::string path, uint32_t tStripLength, const std::vector<Vertex>& vertexBuffer, const std::vector<uint32_t>& indexBuffer);
	};
}