#pragma once
#include <arl_api/vertex.hpp>

#include <memory>
#include <vector>

namespace arl_api {
	class KdNode {
	public:
		Vertex mVertex;
		std::shared_ptr<KdNode> mLeftChild = nullptr;
		std::shared_ptr<KdNode> mRightChild = nullptr;

		KdNode(const Vertex& vertex) : mVertex(vertex) {}
	};

	class KdTree {
	public:
		void BuildKdTree(std::vector<Vertex>& vertices);
		const Vertex& NearestNeighbour(const Vertex& target);
	private:
		float Distance(const Vertex& left, const Vertex& right);
		inline std::shared_ptr<KdNode> _BuildKdTree(std::vector<Vertex>& vertices, uint32_t depth);
		inline std::shared_ptr<KdNode> _NearestNeighbour(std::shared_ptr<KdNode> root, const Vertex& target, std::shared_ptr<KdNode> closest, float closestDist, uint32_t depth);
		std::shared_ptr<KdNode> mTreeRoot = nullptr;
	};
}