#pragma once
#include <cstdint>
#include <string>

namespace arl_cli {
	namespace commands {
		constexpr char help[] = "--help";
		constexpr char mesh_path[] = "--mesh_path";
		constexpr char output_path[] = "--output_path";
		constexpr char rows[] = "--rows";
		constexpr char columns[] = "--columns";
		constexpr char stride[] = "--stride";
	}

	class ARLCommandParser {
	public:
		void Parse(int argc, char** argv);
		const std::string& GetMeshPath() const;
		const std::string& GetARLOutputPath() const;
		uint32_t GetMeshRows() const;
		uint32_t GetMeshColumns() const;
		float GetMeshStride() const;
		bool DidParseSucceed() const;
	private:
		constexpr bool StringEqual(char const* lhs, char const* rhs);
		bool mParseSucceeded = false;
		std::string mMeshPath;
		std::string mARLOutputPath;
		uint32_t mMeshRows = 1;
		uint32_t mMeshColumns = 1;
		float mMeshStride = 1.0f;
	};
}