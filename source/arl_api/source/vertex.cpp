#include <arl_api/vertex.hpp>
#include <cassert>
#include <cmath>
#include <fstream>

using namespace arl_api;

arl_api::Vector3::Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ)
{
}

float arl_api::Vector3::operator[](uint32_t i)
{
	assert(i < 3); //Todo: add debug log
	return vector[i];
}

Vector3 arl_api::Vector3::operator*(const float b) const
{
	return Vector3(x * b, y * b, z * b);
}

Vector3 arl_api::Vector3::operator+(const Vector3& b) const
{
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 arl_api::Vector3::operator-(const Vector3& b) const
{
	return Vector3(x - b.x, y - b.y, z - b.z);
}

float arl_api::Vector3::Magnitude() const
{
	if (x + y + z == 0.0f) {
		return 0.0f;
	}
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3 arl_api::Vector3::Cross(const Vector3& b) const
{
	return Vector3
	(
		(y * b.z) - (z * b.y),
		(z * b.x) - (x * b.z),
		(x * b.y) - (y * b.x)
	);
}

float arl_api::Vector3::Dot(const Vector3& b) const
{
	return (x * b.x) + (y * b.y) + (z * b.z);
}

const Vector3 arl_api::Vector3::GetNormal()
{
	const float dec = 1.0f / Magnitude();
	return this->operator*(dec);
}

const Vector3 arl_api::Vector3::GetNormal() const
{
	const float dec = 1.0f / Magnitude();
	return this->operator*(dec);
}

arl_api::Vector2::Vector2(float inX, float inY) : x(inX), y(inY)
{
}

float& arl_api::Vector2::operator[](uint32_t i)
{
	return vector[i];
}

std::ostream& arl_api::operator<<(std::ostream& os, const Vertex& obj)
{
	os << obj.position.x;
	os << obj.position.y;
	os << obj.position.z;
	os << obj.normal.x;
	os << obj.normal.y;
	os << obj.normal.z;
	os << obj.uvcoord.x;
	os << obj.uvcoord.y;
	return os;
}

std::istream& arl_api::operator>>(std::istream& is, Vertex& obj)
{
	is >> obj.position.x;
	is >> obj.position.y;
	is >> obj.position.z;
	is >> obj.normal.x;
	is >> obj.normal.y;
	is >> obj.normal.z;
	is >> obj.uvcoord.x;
	is >> obj.uvcoord.y;
	return is;
}
