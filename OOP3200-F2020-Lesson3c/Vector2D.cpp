#include "Vector2D.h"

#include <iomanip>
#include <string>
#include <sstream>

#include "Mathf.h"

Vector2D<float>::Vector2D(const float x, const float y) : m_x(x), m_y(y)
{}

Vector2D<float>::~Vector2D()
= default;

Vector2D<float>::Vector2D<float>(const Vector2D<float>& rhs)
{
	Set(rhs.GetX(), rhs.GetY());
}

Vector2D<float>Vector2D<float>::operator+(const Vector2D<float>& rhs) const
{
	Vector2D<float> vector;
	vector.Set(GetX() + rhs.GetX(), GetY() + rhs.GetY());
	return vector;
}

Vector2D<float> Vector2D<float>::operator-(const Vector2D& rhs) const
{
	Vector2D vector;
	vector.Set(GetX() - rhs.GetX(), GetY() - rhs.GetY());
	return vector;
}

Vector2D<float> Vector2D<float>::operator*(const Vector2D& rhs) const
{
	Vector2D vector;
	vector.Set(GetX() * rhs.GetX(), GetY() * rhs.GetY());
	return vector;
}

Vector2D<float> Vector2D<float>::operator*(const float scale) const
{
	return Vector2D(GetX() * scale, GetY() * scale);
}

Vector2D<float> Vector2D<float>::operator/(const Vector2D& rhs) const
{
	Vector2D vector;
	vector.Set(GetX() / rhs.GetX(), GetY() / rhs.GetY());
	return vector;
}

Vector2D<float> Vector2D<float>::operator/(const float scale) const
{
	return Vector2D(GetX() / scale, GetY() / scale);
}

Vector2D<float>& Vector2D<float>::operator=(const Vector2D& rhs)
{
	Set(rhs.GetX(), rhs.GetY());
	return *this;
}


Vector2D<float>& Vector2D<float>::operator+=(const Vector2D& rhs)
{
	Set(GetX() + rhs.GetX(), GetY() + rhs.GetY());
	return *this;
}

Vector2D<float>& Vector2D<float>::operator-=(const Vector2D& rhs)
{
	Set(GetX() - rhs.GetX(), GetY() - rhs.GetY());
	return *this;
}

Vector2D<float>& Vector2D<float>::operator*=(const Vector2D& rhs)
{
	Set(GetX() * rhs.GetX(), GetY() * rhs.GetY());
	return *this;
}

Vector2D<float>& Vector2D<float>::operator/=(const Vector2D& rhs)
{
	Set(GetX() / rhs.GetX(), GetY() / rhs.GetY());
	return *this;
}

bool Vector2D<float>::operator==(const Vector2D& rhs) const
{
	return ((GetX() == rhs.GetX()) && (GetY() == rhs.GetY()));
}

bool Vector2D<float>::operator!=(const Vector2D& rhs) const
{
	return ((GetX() != rhs.GetX()) && (GetY() != rhs.GetY()));
}

bool Vector2D<float>::operator>(const Vector2D& rhs) const
{
	return ((GetX() > rhs.GetX()) && (GetY() > rhs.GetY()));
}

bool Vector2D<float>::operator<(const Vector2D& rhs) const
{
	return ((GetX() < rhs.GetX()) && (GetY() > rhs.GetY()));
}

bool Vector2D<float>::operator>=(const Vector2D& rhs) const
{
	return ((GetX() >= rhs.GetX()) && (GetY() >= rhs.GetY()));
}

bool Vector2D<float>::operator<=(const Vector2D& rhs) const
{
	return ((GetX() <= rhs.GetX()) && (GetY() <= rhs.GetY()));
}

float& Vector2D<float>::operator[](const int component)
{
	if ((component == 0) || (component == 1))
	{
		return (component == 0) ? m_x : m_y;
	}
	throw std::out_of_range("index out of range: can only be 0 to return x or 1 to return y");
}


Vector2D<float>& Vector2D<float>::operator++()
{
	Set(GetX() + 1, GetY() + 1);
	return *this;
}

Vector2D<float> Vector2D<float>::operator++(int)
{
	Vector2D vector = *this;
	++*this;
	return vector;
}

Vector2D<float>& Vector2D<float>::operator--()
{
	Set(GetX() - 1, GetY() - 1);
	return *this;
}

Vector2D<float> Vector2D<float>::operator--(int)
{
	Vector2D vector = *this;
	--*this;
	return vector;
}

std::ostream& operator<<(std::ostream& out, const Vector2D<float>& rhs)
{
	out << rhs.ToString();
	return out;
}

std::istream& operator>>(std::istream& in, Vector2D<float>& rhs)
{
	in >> rhs.m_x;
	in.ignore();
	in >> rhs.m_y;

	return in;
}

Vector2D<float>::operator std::string() const
{
	return ToString();
}

float Vector2D<float>::GetX() const
{
	return m_x;
}

float Vector2D<float>::GetY() const
{
	return m_y;
}

void Vector2D<float>::SetX(const float x)
{
	m_x = x;
}

void Vector2D<float>::SetY(const float y)
{
	m_y = y;
}

void Vector2D<float>::Set(const float x, const float y)
{
	m_x = x;
	m_y = y;
}

std::string Vector2D<float>::ToString(const int precision) const
{
	std::stringstream out;

	out << std::fixed << std::setprecision(precision);
	out << "(" << m_x << ", " << m_y << ")";
	return out.str();
}

float Vector2D<float>::GetMagnitude() const
{
	return Mathf::Sqrt(static_cast<float>(static_cast<double>(GetX()) * static_cast<double>(GetX()) + static_cast<double>(GetY()) * static_cast<double>(GetY())));
}

float Vector2D<float>::GetSqrMagnitude() const
{
	return static_cast<float>(static_cast<double>(GetX()) * static_cast<double>(GetX()) + static_cast<double>(GetY()) * static_cast<double>(GetY()));
}

void Vector2D<float>::SetScale(const Vector2D& scale)
{
	*this *= scale;
}

Vector2D<float> Vector2D<float>::GetNormalized() const
{
	Vector2D vector = Vector2D(GetX(), GetY());
	vector.Normalize();
	return vector;
}

void Vector2D<float>::Normalize()
{
	const auto magnitude = GetMagnitude();
	if (static_cast<double>(magnitude) > 9.99999974737875E-06)
	{
		Set(GetX() / magnitude, GetY() / magnitude);
	}
	else
	{
		*this = Vector2D::Zero();
	}
}

Vector2D<float> Vector2D<float>::MoveTowards(const Vector2D& current, const Vector2D& target, const float max_distance_delta)
{
	const auto vector = target - current;
	const auto magnitude = vector.GetMagnitude();
	if (static_cast<double>(magnitude) <= static_cast<double>(max_distance_delta) || static_cast<double>(magnitude) == 0.0)
	{
		return target;
	}	
	return current + vector / magnitude * max_distance_delta;
}

Vector2D<float> Vector2D<float>::Scale(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.GetX() * b.GetX(), a.GetY() * b.GetY());
}

Vector2D<float> Vector2D<float>::Reflect(const Vector2D& in_direction, const Vector2D& in_normal)
{
	return in_normal * (-2.0f * Vector2D::Dot(in_normal, in_direction)) + in_direction;
}

Vector2D<float> Vector2D<float>::Perpendicular(const Vector2D& in_direction)
{
	return Vector2D(-in_direction.GetY(), in_direction.GetX());
}

float Vector2D<float>::Dot(const Vector2D& lhs, const Vector2D& rhs)
{
	return static_cast<float>(static_cast<double>(lhs.GetX()) * static_cast<double>(rhs.GetX()) + static_cast<double>(lhs.
		GetY()) * static_cast<double>(rhs.GetY()));
}

float Vector2D<float>::Angle(const Vector2D& from, const Vector2D& to)
{
	const auto denominator = static_cast<float>(Mathf::Sqrt(from.GetSqrMagnitude() * to.GetSqrMagnitude()));
	if (denominator < Mathf::EpsilonNormalSqrt)
	{
		return 0.0F;
	}

	const auto dot = Mathf::Clamp(Vector2D::Dot(from, to) / denominator, -1.0F, 1.0F);
	return static_cast<float>(Mathf::Acos(dot)) * Mathf::Rad2Deg;
}

float Vector2D<float>::SignedAngle(const Vector2D& from, const Vector2D& to)
{
	const auto unsigned_angle = Vector2D::Angle(from, to);
	const auto sign = Mathf::Sign(from.GetX() * to.GetY() - from.GetY() * to.GetX());
	return unsigned_angle * sign;
}

float Vector2D<float>::Distance(const Vector2D& a, const Vector2D& b)
{
	const auto delta_x = static_cast<double>(b.GetX()) - static_cast<double>(a.GetX());
	const auto delta_y = static_cast<double>(b.GetY()) - static_cast<double>(a.GetY());
	
	return Mathf::Sqrt(static_cast<float>(delta_x * delta_x + delta_y * delta_y));
}

Vector2D<float> Vector2D<float>::ClampMagnitude(const Vector2D& vector, const float max_length)
{
	if (static_cast<double>(vector.GetSqrMagnitude()) > static_cast<double>(max_length) * static_cast<double>(max_length))
	{
		return vector.GetNormalized() * max_length;
	}	
	return vector;
}

float Vector2D<float>::SqrMagnitude(const Vector2D& a)
{
	return static_cast<float>(static_cast<double>(a.GetX()) * static_cast<double>(a.GetX()) + static_cast<double>(a.GetY()) *
		static_cast<double>(a.GetY()));
}

Vector2D<float> Vector2D<float>::Min(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(Mathf::Min(lhs.GetX(), rhs.GetX()), Mathf::Min(lhs.GetY(), rhs.GetY()));
}

Vector2D<float> Vector2D<float>::Max(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(Mathf::Max(lhs.GetX(), rhs.GetX()), Mathf::Max(lhs.GetY(), rhs.GetY()));
}

Vector2D<float> Vector2D<float>::Zero()
{
	return Vector2D(0.0f, 0.0f);
}

Vector2D<float> Vector2D<float>::One()
{
	return Vector2D(1.0f, 1.0f);
}

Vector2D<float> Vector2D<float>::Up()
{
	return Vector2D(0.0f, 1.0f);
}

Vector2D<float> Vector2D<float>::Down()
{
	return Vector2D(0.0f, -1.0f);
}

Vector2D<float> Vector2D<float>::Right()
{
	return Vector2D(1.0f, 0.0f);
}

Vector2D<float> Vector2D<float>::Left()
{
	return Vector2D(-1.0f, 0.0f);
}

Vector2D<float> Vector2D<float>::Lerp(const Vector2D& a, const Vector2D& b, float t)
{
	t = Mathf::Clamp01(t);
	return Vector2D(a.GetX() + (b.GetX() - a.GetX()) * t, a.GetY() + (b.GetY() - a.GetY()) * t);
}

Vector2D<float> Vector2D<float>::LerpUnclamped(const Vector2D& a, const Vector2D& b, const float t)
{
	return Vector2D(a.GetX() + (b.GetX() - a.GetX()) * t, a.GetY() + (b.GetY() - a.GetY()) * t);
}
