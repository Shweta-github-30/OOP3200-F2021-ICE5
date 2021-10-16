#include "Vector3D.h"

<float>Vector3D::Vector3D(const float x, const float y, const float z) : m_x(x), m_y(y), m_z(z)
{

}
Vector3D<float>::~Vector3D()
= default;

float Vector3D; <float>::GetX() const
{
	return m_x;
}
float Vector3D<float>::GetY() const
{
	return m_y;
}
float Vector3D<float>::Getz() const
{
	return m_z;
}
void Vector3D<float>::setX(const float x)
{
	m_x = x;
}
void Vector3D<float>::setY(const float Y)
{
	m_y = y;
}
void Vector3D<float>::setX(const float )
{
	m_z = z;
}
void Vector3D<float>::set(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

std::string Vector3D:Tostring() const
{
	std::string outputstring;
	outputstring += "(" +std::to_string (m_x) + ", " + std::to_string (m_y) + ", " + std::to_string (m_z) + ")";

	return outputstring;
}