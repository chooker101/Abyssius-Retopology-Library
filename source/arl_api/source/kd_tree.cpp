#include <arl_api/kd_tree.hpp>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace arl_api;

enum class Axis {
	Z,
	X
};

void arl_api::KdTree::BuildKdTree(std::vector<Vertex>& vertices)
{
	mTreeRoot = _BuildKdTree(vertices, 0);
}

const Vertex& arl_api::KdTree::NearestNeighbour(const Vertex& target)
{
	assert(mTreeRoot); //Tree not built
	return _NearestNeighbour(mTreeRoot, target, nullptr, std::numeric_limits<float>::max(), 0)->mVertex;
}

float arl_api::KdTree::Distance(const Vertex& left, const Vertex& right)
{
	float sum = 0.0f;
	for (uint32_t i = 0; i < 2; ++i) {
		if (static_cast<Axis>(i) == Axis::Z) {
			sum += (left.position.z - right.position.z) * (left.position.z - right.position.z);
		}
		else {
			sum += (left.position.x - right.position.x) * (left.position.x - right.position.x);
		}
	}
	return std::sqrt(sum);
}

inline std::shared_ptr<KdNode> arl_api::KdTree::_BuildKdTree(std::vector<Vertex>& vertices, uint32_t depth)
{
	if (vertices.empty()) return nullptr;
	Axis axis = static_cast<Axis>(depth % 2);
	std::sort(vertices.begin(), vertices.end(), [&](const Vertex& left, const Vertex& right) {
		if (axis == Axis::Z) {
			return left.position.z < right.position.z;
		}
		else {
			return left.position.x < right.position.x;
		}
	});

	uint32_t medianIndex = vertices.size() / 2;
	std::shared_ptr<KdNode> node = std::make_shared<KdNode>(vertices[medianIndex]);

	std::vector<Vertex> leftVertices(vertices.begin(), vertices.begin() + medianIndex);
	std::vector<Vertex> rightVertices(vertices.begin() + medianIndex + 1, vertices.end());

	node->mLeftChild = _BuildKdTree(leftVertices, depth + 1);
	node->mRightChild = _BuildKdTree(rightVertices, depth + 1);

	return node;
}

inline std::shared_ptr<KdNode> arl_api::KdTree::_NearestNeighbour(std::shared_ptr<KdNode> root, const Vertex& target, std::shared_ptr<KdNode> closest, float closestDist, uint32_t depth)
{
	if (!root) return closest;

	Axis axis = static_cast<Axis>(depth % 2);

	float dist = Distance(root->mVertex, target);
	if (dist < closestDist) {
		closestDist = dist;
		closest = root;
	}

	std::shared_ptr<KdNode> nextBranch;
	std::shared_ptr<KdNode> otherBranch;
	
	float target_pos = axis == Axis::Z ? target.position.z : target.position.x;
	float root_pos = axis == Axis::Z ? root->mVertex.position.z : root->mVertex.position.x;

	if (target_pos < root_pos) {
		nextBranch = root->mLeftChild;
		otherBranch = root->mRightChild;
	}
	else {
		nextBranch = root->mRightChild;
		otherBranch = root->mLeftChild;
	}

	closest = _NearestNeighbour(nextBranch, target, closest, closestDist, depth + 1);

	if (otherBranch) {
		float radius = Distance(closest->mVertex, target);
		if (std::abs(target_pos - root_pos) < radius) {
			closest = _NearestNeighbour(otherBranch, target, closest, closestDist, depth + 1);
		}
	}
	return closest;
}
