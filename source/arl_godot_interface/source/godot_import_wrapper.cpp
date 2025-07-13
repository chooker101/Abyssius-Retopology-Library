#include <arl_godot_interface/godot_import_wrapper.hpp>

using namespace godot;
using namespace arl_api;
using namespace arl_godot_interface;

void arl_godot_interface::GodotImportWrapper::ImportArlFile(String path)
{
	if (!mMeshImport) {
		mMeshImport = std::make_unique<arl_api::MeshImport>(arl_api::MeshImport());
	}
	std::string cppFilePath = path.utf8().get_data();
	mMeshImport->LoadARLFile(cppFilePath);
	const std::vector<Vertex>& vBuffer = mMeshImport->GetVertexBuffer();
	mIndexBuffer = mMeshImport->GetIndexBuffer();
	mTriangleStripLength = mMeshImport->GetARLStripLength();
	mVertexBuffer.resize(vBuffer.size());
	for (uint32_t i = 0; i < vBuffer.size(); ++i) {
		mVertexBuffer[i] = GodotVertex(vBuffer[i].position.x, vBuffer[i].position.y, vBuffer[i].position.z, vBuffer[i].normal.x, vBuffer[i].normal.y, vBuffer[i].normal.z, vBuffer[i].uvcoord.x, vBuffer[i].uvcoord.y);
	}
	mMeshImport->ClearLoadedMesh();
}

godot::Vector3 arl_godot_interface::GodotImportWrapper::GetVertexPosition(int index)
{
	return mVertexBuffer[index].positon;
}

godot::Vector3 arl_godot_interface::GodotImportWrapper::GetVertexNormal(int index)
{
	return mVertexBuffer[index].normal;
}

godot::Vector2 arl_godot_interface::GodotImportWrapper::GetVertexUVCoordinate(int index)
{
	return mVertexBuffer[index].uvcoord;
}

int arl_godot_interface::GodotImportWrapper::GetVertexIndex(int index)
{
	return mIndexBuffer[index];
}

int arl_godot_interface::GodotImportWrapper::GetVertexBufferSize()
{
	return mVertexBuffer.size();
}

int arl_godot_interface::GodotImportWrapper::GetIndexBufferSize()
{
	return mIndexBuffer.size();
}

int arl_godot_interface::GodotImportWrapper::GetStripLength()
{
	return mTriangleStripLength;
}

void arl_godot_interface::GodotImportWrapper::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("ImportArlFile", "path"), &ImportArlFile);
	ClassDB::bind_method(D_METHOD("GetVertexPosition", "index"), &GetVertexPosition);
	ClassDB::bind_method(D_METHOD("GetVertexNormal", "index"), &GetVertexNormal);
	ClassDB::bind_method(D_METHOD("GetVertexUVCoordinate", "index"), &GetVertexUVCoordinate);
	ClassDB::bind_method(D_METHOD("GetVertexIndex", "path"), &GetVertexIndex);
	ClassDB::bind_method(D_METHOD("GetVertexBufferSize"), &GetVertexBufferSize);
	ClassDB::bind_method(D_METHOD("GetIndexBufferSize"), &GetIndexBufferSize);
	ClassDB::bind_method(D_METHOD("GetStripLength"), &GetStripLength);
}
