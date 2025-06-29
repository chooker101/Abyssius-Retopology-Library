#include <iostream>
#include <arl_api/mesh_import.hpp>
#include <arl_api/triangle_strip_builder.hpp>
#include <arl_api/mesh_export.hpp>
#include <arl_cli/arl_command_parser.hpp>

using namespace arl_cli;

int main(int argc, char** argv) {
    ARLCommandParser parser = ARLCommandParser();

    parser.Parse(argc, argv);
    if (parser.DidParseSucceed()) {
        arl_api::MeshImport meshImport = arl_api::MeshImport();
        arl_api::MeshExport meshExport = arl_api::MeshExport();
        arl_api::TriangleStripBuilder stripBuilder = arl_api::TriangleStripBuilder();
        meshImport.LoadMesh(parser.GetMeshPath());
        std::vector<arl_api::Vertex> vBuffer(meshImport.GetVertexBuffer());
        stripBuilder.GenTriangleStripMesh(vBuffer, parser.GetMeshStride(), parser.GetMeshRows(), parser.GetMeshColumns());
        meshExport.ExportARLFile(parser.GetARLOutputPath(), stripBuilder.GetStripLength(), stripBuilder.GetVertexBuffer(), stripBuilder.GetIndexBuffer());
    }
    return 0;
}