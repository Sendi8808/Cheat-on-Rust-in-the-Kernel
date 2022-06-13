//#pragma once
//
//#include <corecrt_math_defines.h>
//#include <sstream>
//#include <algorithm>
//
//class Vector3
//{
//public:
//	Vector3()
//	{
//		x = y = z = 0.f;
//	}
//
//	Vector3(float fx, float fy, float fz)
//	{
//		x = fx;
//		y = fy;
//		z = fz;
//	}
//
//	float x, y, z;
//
//	Vector3 operator+(const Vector3& input) const
//	{
//		return Vector3{ x + input.x, y + input.y, z + input.z };
//	}
//	inline float operator[](int i) const {
//		return ((float*)this)[i];
//	}
//
//	Vector3 operator-(const Vector3& input) const
//	{
//		return Vector3{ x - input.x, y - input.y, z - input.z };
//	}
//
//	Vector3 operator/(float input) const
//	{
//		return Vector3{ x / input, y / input, z / input };
//	}
//
//	Vector3 operator*(float input) const
//	{
//		return Vector3{ x * input, y * input, z * input };
//	}
//	float lengthx() const
//	{
//		return std::sqrt((x * x) + (y * y));
//	}
//	Vector3& operator+=(const Vector3& v)
//	{
//		x += v.x;
//		y += v.y;
//		z += v.z;
//
//		return *this;
//	}
//	float dot(const Vector3 v) { return (x * v.x + y * v.y + z * v.z); }
//	Vector3& operator-=(const Vector3& v)
//	{
//		x -= v.x;
//		y -= v.y;
//		z -= v.z;
//
//		return *this;
//	}
//
//	Vector3& operator/=(float input)
//	{
//		x /= input;
//		y /= input;
//		z /= input;
//		return *this;
//	}
//
//	Vector3& operator*=(float input)
//	{
//		x *= input;
//		y *= input;
//		z *= input;
//		return *this;
//	}
//
//	bool operator==(const Vector3& input) const
//	{
//		return x == input.x && y == input.y && z == input.z;
//	}
//
//	void make_absolute()
//	{
//		x = std::abs(x);
//		y = std::abs(y);
//		z = std::abs(z);
//	}
//
//	float Clamp01(float value)
//	{
//		float result;
//		if (value < 0)
//		{
//			result = 0;
//		}
//		else if (value > 1.f)
//		{
//			result = 1.f;
//		}
//		else
//		{
//			result = value;
//		}
//		return result;
//	}
//
//	static float my_sqrt(float number) {
//		long        i;
//		float       x2, y;
//		const float threehalfs = 1.5F;
//
//		x2 = number * 0.5F;
//		y = number;
//		i = *(long*)&y; // floating point bit level hacking [sic]
//		i = 0x5f3759df - (i >> 1); // Newton's approximation
//		y = *(float*)&i;
//		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
//		y = y * (threehalfs - (x2 * y * y)); // 2nd iteration
//
//		return 1 / y;
//	}
//
//	float Lerp()
//	{
//		return x + (y - x) * Clamp01(z);
//	}
//
//	float length_sqr() const
//	{
//		return (x * x) + (y * y) + (z * z);
//	}
//	float length() const
//	{
//		return std::sqrt(length_sqr());
//	}
//	float Length() {
//		return std::sqrt(x * x + y * y + z * z);
//	}
//
//	Vector3 Normalized228() {
//		float len = Length();
//		return Vector3(x / len, y / len, z / len);
//	}
//
//	float length_2d() const
//	{
//		return std::sqrt((x * x) + (y * y));
//	}
//
//	Vector3 normalize()
//	{
//		Vector3 out = *this;
//		auto l = length();
//		if (l == 0)
//			return *this;
//		;
//		out.x /= l;
//		out.y /= l;
//		out.z /= l;
//		return out;
//	}
//
//	float unity_magnitude()
//	{
//		return (float)sqrt((double)(x * x + y * y + z * z));
//	}
//
//	Vector3 Cross(Vector3 rhs)
//	{
//		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
//	}
//
//	Vector3 unity_Normalize()
//	{
//		float num = unity_magnitude();
//		if (num > 1E-05f)
//		{
//			x /= num;
//			y /= num;
//			z /= num;
//		}
//		else
//		{
//			x = 0;
//			y = 0;
//			z = 0;
//		}
//
//		return { x,y,z };
//	}
//
//	float Magnitude() { return sqrt(this->x * this->x + this->y * this->y + this->z * this->z); }
//	Vector3 Normalized()
//	{
//		float num = this->Magnitude();
//		if (num > 9.99999974737875E-06)
//		{
//			return { this->x / num, this->y / num, this->z / num };
//		}
//		return Vector3{};
//	}
//
//
//	Vector3 normalized() const
//	{
//		return { x == 0 ? 0 : x / length(), y == 0 ? 0 : y / length(), z == 0 ? 0 : z / length() };
//	}
//
//	float dot_product(Vector3 input) const
//	{
//		return (x * input.x) + (y * input.y) + (z * input.z);
//	}
//
//	float distance(Vector3 input) const
//	{
//		return (*this - input).length();
//	}
//	float distancesqr(Vector3 input) const
//	{
//		Vector3 dif = { x - input.x, y - input.y, z - input.z };
//		return dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;
//	}
//
//	float distance_2d(Vector3 input) const
//	{
//		return (*this - input).length_2d();
//	}
//
//
//	bool empty() const
//	{
//		return (x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
//	}
//
//	std::string stringify()
//	{
//		std::stringstream penis;
//		penis << std::to_string(x);
//		penis << " ";
//		penis << std::to_string(y);
//		penis << " ";
//		penis << std::to_string(z);
//		return penis.str();
//	}
//};
//
//class Vector4
//{
//public:
//	Vector4()
//	{
//		x = y = z = w = 0.f;
//	}
//
//	Vector4(float fx, float fy, float fz, float fw)
//	{
//		x = fx;
//		y = fy;
//		z = fz;
//		w = fw;
//	}
//
//	float x, y, z, w;
//
//	Vector4 operator+(const Vector4& input) const
//	{
//		return Vector4{ x + input.x, y + input.y, z + input.z, w + input.w };
//	}
//
//	Vector4 operator-(const Vector4& input) const
//	{
//		return Vector4{ x - input.x, y - input.y, z - input.z, w - input.w };
//	}
//
//	Vector4 operator/(float input) const
//	{
//		return Vector4{ x / input, y / input, z / input, w / input };
//	}
//
//	Vector4 operator*(float input) const
//	{
//		return Vector4{ x * input, y * input, z * input, w * input };
//	}
//
//	Vector4& operator-=(const Vector4& v)
//	{
//		x -= v.x;
//		y -= v.y;
//		z -= v.z;
//		w -= v.w;
//
//		return *this;
//	}
//
//	Vector4& operator/=(float input)
//	{
//		x /= input;
//		y /= input;
//		z /= input;
//		w /= input;
//		return *this;
//	}
//
//	Vector4& operator*=(float input)
//	{
//		x *= input;
//		y *= input;
//		z *= input;
//		w *= input;
//		return *this;
//	}
//
//	bool operator==(const Vector4& input) const
//	{
//		return x == input.x && y == input.y && z == input.z && w == input.w;
//	}
//
//	void make_absolute()
//	{
//		x = std::abs(x);
//		y = std::abs(y);
//		z = std::abs(z);
//		w = std::abs(w);
//	}
//
//	float length_sqr() const
//	{
//		return (x * x) + (y * y) + (z * z) + (w * w);
//	}
//
//	float length() const
//	{
//		return std::sqrt(length_sqr());
//	}
//
//	float length_2d() const
//	{
//		return std::sqrt((x * x) + (y * y));
//	}
//
//	Vector4 normalized() const
//	{
//		return { x / length(), y / length(), z / length(), w / length() };
//	}
//
//	float dot_product(Vector4 input) const
//	{
//		return (x * input.x) + (y * input.y) + (z * input.z) + (w * input.w);
//	}
//
//	float distance(Vector4 input) const
//	{
//		return (*this - input).length();
//	}
//
//	float distance_2d(Vector4 input) const
//	{
//		return (*this - input).length_2d();
//	}
//
//	bool empty() const
//	{
//		return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
//	}
//
//	static Vector4 QuaternionLookRotation(Vector3 forward, Vector3 up)
//	{
//		Vector3 vector = forward.unity_Normalize();
//		Vector3 vector2 = (up).Cross(vector).unity_Normalize();
//		Vector3 vector3 = (vector).Cross(vector2);
//		auto m00 = vector2.x;
//		auto m01 = vector2.y;
//		auto m02 = vector2.z;
//		auto m10 = vector3.x;
//		auto m11 = vector3.y;
//		auto m12 = vector3.z;
//		auto m20 = vector.x;
//		auto m21 = vector.y;
//		auto m22 = vector.z;
//
//
//		float num8 = (m00 + m11) + m22;
//		auto quaternion = Vector4();
//		if (num8 > 0.f)
//		{
//			auto num = (float)sqrt(num8 + 1.f);
//			quaternion.w = num * 0.5f;
//			num = 0.5f / num;
//			quaternion.x = (m12 - m21) * num;
//			quaternion.y = (m20 - m02) * num;
//			quaternion.z = (m01 - m10) * num;
//			return quaternion;
//		}
//		if ((m00 >= m11) && (m00 >= m22))
//		{
//			auto num7 = (float)sqrt(((1.f + m00) - m11) - m22);
//			auto num4 = 0.5f / num7;
//			quaternion.x = 0.5f * num7;
//			quaternion.y = (m01 + m10) * num4;
//			quaternion.z = (m02 + m20) * num4;
//			quaternion.w = (m12 - m21) * num4;
//			return quaternion;
//		}
//		if (m11 > m22)
//		{
//			auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
//			auto num3 = 0.5f / num6;
//			quaternion.x = (m10 + m01) * num3;
//			quaternion.y = 0.5f * num6;
//			quaternion.z = (m21 + m12) * num3;
//			quaternion.w = (m20 - m02) * num3;
//			return quaternion;
//		}
//		auto num5 = (float)sqrt(((1.f + m22) - m00) - m11);
//		auto num2 = 0.5f / num5;
//		quaternion.x = (m20 + m02) * num2;
//		quaternion.y = (m21 + m12) * num2;
//		quaternion.z = 0.5f * num5;
//		quaternion.w = (m01 - m10) * num2;
//		return quaternion;
//	}
//
//
//
//};
//
//class Vector2
//{
//public:
//	Vector2()
//	{
//		x = y = 0.f;
//	}
//
//	Vector2(float fx, float fy)
//	{
//		x = fx;
//		y = fy;
//	}
//
//	float x, y;
//
//	Vector2 operator+(const Vector2& input) const
//	{
//		return Vector2{ x + input.x, y + input.y };
//	}
//
//	Vector2 operator-(const Vector2& input) const
//	{
//		return Vector2{ x - input.x, y - input.y };
//	}
//
//	Vector2 operator+(const Vector3& input) const
//	{
//		return Vector2{ x + input.x, y + input.y };
//	}
//
//	Vector2 operator-(const Vector3& input) const
//	{
//		return Vector2{ x - input.x, y - input.y };
//	}
//
//	Vector2 operator/(float input) const
//	{
//		return Vector2{ x / input, y / input };
//	}
//
//	Vector2 operator*(float input) const
//	{
//		return Vector2{ x * input, y * input };
//	}
//
//	Vector2& operator-=(const Vector2& v)
//	{
//		x -= v.x;
//		y -= v.y;
//		return *this;
//	}
//
//	Vector2& operator/=(float input)
//	{
//		x /= input;
//		y /= input;
//		return *this;
//	}
//
//	Vector2& operator*=(float input)
//	{
//		x *= input;
//		y *= input;
//		return *this;
//	}
//
//	float length() const
//	{
//		return std::sqrt((x * x) + (y * y));
//	}
//
//	Vector2 normalized() const
//	{
//		return { x / length(), y / length() };
//	}
//
//	float dot_product(Vector2 input) const
//	{
//		return (x * input.x) + (y * input.y);
//	}
//
//
//	float distance(Vector2 input) const
//	{
//		return (*this - input).length();
//	}
//
//	bool empty() const
//	{
//		return x == 0.f && y == 0.f;
//	}
//
//	std::string stringify()
//	{
//		std::stringstream penis;
//		penis << std::to_string(x);
//		penis << " ";
//		penis << std::to_string(y);
//		penis << " ";
//		return penis.str();
//	}
//};
//
