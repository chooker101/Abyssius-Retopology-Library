#include <arl_api/triangle_strip_builder.hpp>

using namespace arl_api;

void arl_api::TriangleStripBuilder::GenTriangleStripMesh(std::vector<Vertex>& vertexBuffer, float stride, uint32_t rows, uint32_t cols)
{
	//Assume centered origin
	stride = stride / 2.0f;
	float offsetX = ((rows / 2.0f) * stride);
	float offsetZ = ((cols / 2.0f) * stride);
	float uStride = 1.0f / rows;
	float vStride = 1.0f / cols;
	//Need to add extra row and column for final vertexes
	rows++;
	cols++;

	KdTree tree = KdTree();

	tree.BuildKdTree(vertexBuffer);

	//Good to rebuild, don't necessarily know how vertex buffer is laid out
	
	Vertex vertex;
	mVertexBuffer.clear();
	mVertexBuffer.reserve(rows * cols);
	for (uint32_t x = 0; x < rows; ++x) {
		for (uint32_t z = 0; z < cols; ++z) {
			vertex = Vertex((x * stride) - offsetX, 0.0f, (z * stride) - offsetZ, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			const Vertex& other = tree.NearestNeighbour(vertex);
			vertex.position.y = other.position.y;
			vertex.normal = other.normal; //Should be recalculated
			vertex.uvcoord = Vector2(uStride * x, vStride * z);
			mVertexBuffer.push_back(vertex);
		}
	}

	mIndexBuffer.clear();
	mIndexBuffer.reserve((rows - 1) * cols * 2);
	//Need to start new strips each row, building -x -z to +x +z
	//Any degenerate triangles would be very bad for performance
	for (uint32_t x = 0; x < rows - 1; ++x) {
		for (uint32_t z = 0; z < cols; ++z) {
			uint32_t top = (x + 1) * cols + z;
			uint32_t bottom = x * cols + z;
			mIndexBuffer.push_back(bottom);
			mIndexBuffer.push_back(top);
		}
	}
	mStripLength = cols * 2;
}

const std::vector<Vertex>& TriangleStripBuilder::GetVertexBuffer() const
{
	return mVertexBuffer;
}

const std::vector<uint32_t>& TriangleStripBuilder::GetIndexBuffer() const
{
	return mIndexBuffer;
}

uint32_t TriangleStripBuilder::GetStripLength() const
{
	return mStripLength;
}
