#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <arl_api/mesh_import.hpp>

namespace arl_godot_interface {
	//For convert on load, should make memory more stable
	struct GodotVertex {
		godot::Vector3 positon;
		godot::Vector3 normal;
		godot::Vector2 uvcoord;

		GodotVertex() : positon(), normal(), uvcoord() {}
		GodotVertex(float px, float py, float pz, float nx, float ny, float nz, float u, float v) : positon(px, py, pz), normal(nx, ny, nz), uvcoord(u, v) {}
	};

	class GodotImportWrapper : public godot::Node {
		GDCLASS(GodotImportWrapper, godot::Node)
	public:
		void ImportArlFile(godot::String path);
		godot::Vector3 GetVertexPosition(int index);
		godot::Vector3 GetVertexNormal(int index);
		godot::Vector2 GetVertexUVCoordinate(int index);
		int GetVertexIndex(int index);
		int GetVertexBufferSize();
		int GetIndexBufferSize();
		int GetStripLength();
	protected:
		static void _bind_methods();
	private:
		std::unique_ptr<arl_api::MeshImport> mMeshImport;
		
		//Store copies and close orginal, should speed up access a bit
		std::vector<GodotVertex> mVertexBuffer;
		std::vector<uint32_t> mIndexBuffer;
		uint32_t mTriangleStripLength = 0;
	};
}