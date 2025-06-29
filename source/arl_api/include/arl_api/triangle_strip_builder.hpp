#pragma once
#include <arl_api/kd_tree.hpp>

namespace arl_api {
	class TriangleStripBuilder {
	public:
		void GenTriangleStripMesh(std::vector<Vertex>& vertexBuffer, float stride, uint32_t rows, uint32_t cols);
		const std::vector<Vertex>& GetVertexBuffer() const;
		const std::vector<uint32_t>& GetIndexBuffer() const;
		uint32_t GetStripLength() const;
	private:
		std::vector<Vertex> mVertexBuffer;
		std::vector<uint32_t> mIndexBuffer;
		uint32_t mStripLength;
	};
}