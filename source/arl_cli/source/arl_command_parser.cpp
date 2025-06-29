#include <arl_cli/arl_command_parser.hpp>
#include <iostream>
#include <cassert>

using namespace arl_cli;

void arl_cli::ARLCommandParser::Parse(int argc, char** argv)
{
	for (uint32_t i = 1; i < argc; ++i) {
		if (StringEqual(commands::help, argv[i])) {
			std::cout << "Usage: ./arl_cli --mesh_path <file_path> --output_path <file_path> --rows <int> --columns <int> --stride <float>" << std::endl;
			std::cout << "    mesh_path: Path to the mesh to be transformed (full path)" << std::endl;
			std::cout << "    output_path: Path to the binary .arl file (full path)" << std::endl;
			std::cout << "    rows: Number of rows of quads (+x axis)" << std::endl;
			std::cout << "    columns: Number of columns of quads (+z axis)" << std::endl;
			std::cout << "    stride: Size of each quad (assumed sqaure)" << std::endl;
			std::cout << "    help: Display this message and return" << std::endl;
			mParseSucceeded = false;
			return;
		}
		else if (StringEqual(commands::mesh_path, argv[i])) {
			mMeshPath.assign(argv[++i]);
		}
		else if (StringEqual(commands::output_path, argv[i])) {
			mARLOutputPath.assign(argv[++i]);
		}
		else if (StringEqual(commands::rows, argv[i])) {
			mMeshRows = atoi(argv[++i]);
		}
		else if (StringEqual(commands::columns, argv[i])) {
			mMeshColumns = atoi(argv[++i]);
		}
		else if (StringEqual(commands::stride, argv[i])) {
			mMeshStride = std::atof(argv[++i]);
		}
		else {
			std::cout << "For usage: ./arl_cli --help" << std::endl;
			mParseSucceeded = false;
			return;
		}
	}
	assert(!mMeshPath.empty());
	assert(!mARLOutputPath.empty());
	mParseSucceeded = true;
}

const std::string& arl_cli::ARLCommandParser::GetMeshPath() const
{
	return mMeshPath;
}

const std::string& arl_cli::ARLCommandParser::GetARLOutputPath() const
{
	return mARLOutputPath;
}

uint32_t arl_cli::ARLCommandParser::GetMeshRows() const
{
	return mMeshRows;
}

uint32_t arl_cli::ARLCommandParser::GetMeshColumns() const
{
	return mMeshColumns;
}

float arl_cli::ARLCommandParser::GetMeshStride() const
{
	return mMeshStride;
}

bool arl_cli::ARLCommandParser::DidParseSucceed() const
{
	return mParseSucceeded;
}

constexpr bool arl_cli::ARLCommandParser::StringEqual(char const* lhs, char const* rhs)
{
	while (*lhs || *rhs) {
		if (*lhs++ != *rhs++) {
			return false;
		}
	}
	return true;
}
