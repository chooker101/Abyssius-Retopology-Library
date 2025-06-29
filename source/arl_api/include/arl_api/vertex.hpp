#pragma once
#include <cstdint>
#include <utility>
#include <fstream>

namespace arl_api {
	//old math lib
	class Vector3
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float vector[3];
		};
		Vector3() = default;
		Vector3(float inX, float inY, float inZ);

		float operator[](uint32_t i);
		Vector3 operator*(const float b) const;
		Vector3 operator+(const Vector3& b) const;
		Vector3 operator-(const Vector3& b) const;

		float Magnitude() const;
		Vector3 Cross(const Vector3& b) const;
		float Dot(const Vector3& b) const;
		const Vector3 GetNormal();
		const Vector3 GetNormal() const;
	};

	class Vector2
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};
			float vector[2];
		};
		Vector2() = default;
		Vector2(float inX, float inY);
		float& operator[](uint32_t i);
	};

	class Vertex
	{
	public:
		Vertex() = default;
		Vertex(float x, float y, float z, float normx, float normy, float normz, float u, float v) : position(x, y, z), normal(normx, normy, normz), uvcoord(u, v) {}

		friend std::ostream& operator<<(std::ostream& os, const Vertex& obj);
		friend std::istream& operator>>(std::istream& is, Vertex& obj);

		Vector3 position;
		Vector3 normal;
		Vector2 uvcoord;
	};
}