#include "MyVector3D.h"
#define PI 3.14159265358979323846

/// <summary>
/// Defautl constructor set all 3 values to zero
/// </summary>
MyVector3D::MyVector3D() :
	m_x{ 0.0 },
	m_y{ 0.0 },
	m_z{ 0.0 }
{
}

/// <summary>
/// constructo from 3 doubles
/// </summary>
/// <param name="x">x componenet</param>
/// <param name="y">y componenet</param>
/// <param name="z">z componenet</param>
MyVector3D::MyVector3D(double x, double y, double z) :
	m_x{ x },
	m_y{ y },
	m_z{ z }
{
}

/// <summary>
/// construct from a SF vector3f
/// </summary>
/// <param name="sfVector">sf vector3f to mathc</param>
MyVector3D::MyVector3D(sf::Vector3f sfVector) :
	m_x{ static_cast<double>(sfVector.x) },
	m_y{ static_cast<double>(sfVector.y) },
	m_z{ static_cast<double>(sfVector.z) }
{
}

/// <summary>
/// construct from a SF vector3i
/// </summary>
/// <param name="sfVector">sf vector3i to match</param>
MyVector3D::MyVector3D(sf::Vector3i sfVector) :
	m_x{ static_cast<double>(sfVector.x) },
	m_y{ static_cast<double>(sfVector.y) },
	m_z{ static_cast<double>(sfVector.z) }
{
}
/// <summary>
/// construct from a 2d sf vector2i
/// set z component to zero
/// </summary>
/// <param name="sfVector">sf vector2i to match</param>
MyVector3D::MyVector3D(sf::Vector2i sfVector) :
	m_x(static_cast<double>(sfVector.x)),
	m_y(static_cast<double>(sfVector.y)),
	m_z(0.0)
{
}
/// <summary>
/// construct from a sf vector2u
/// set z to sero
/// </summary>
/// <param name="sfVector">sf vector2u to match from</param>
MyVector3D::MyVector3D(sf::Vector2u sfVector) :
	m_x{ static_cast<double>(sfVector.x) },
	m_y{ static_cast<double>(sfVector.y) },
	m_z{ 0.0 }
{
}
/// <summary>
/// construct from a sf vector 2f
/// set z to 0
/// </summary>
/// <param name="sfVector">sf vector to match</param>
MyVector3D::MyVector3D(sf::Vector2f sfVector) :
	m_x{ static_cast<double>(sfVector.x) },
	m_y{ static_cast<double>(sfVector.y) },
	m_z{ 0.0 }
{
}
/// <summary>
/// default destructor
/// </summary>
MyVector3D::~MyVector3D()
{
}

/// <summary>
/// to string method using char[] and sprintf
/// %g is a format specifier for sprintf
/// the largest result we can handle is 256 characters to avoid buffer overrun
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and seperated by commas</returns>
std::string MyVector3D::toString()
{
	char tmpbuf[256];
	sprintf_s(tmpbuf, "[ %g, %g, %g ]", m_x, m_y, m_z);
	return tmpbuf;
}
/// <summary>
/// returnt he value of the x component
/// </summary>
/// <returns>value of x</returns>
double MyVector3D::X() const
{
	return m_x;
}

/// <summary>
/// returns the value of Y component
/// </summary>
/// <returns>the value of y</returns>
double MyVector3D::Y() const
{
	return m_y;
}

/// <summary>
/// return the value of Z component
/// </summary>
/// <returns>value of Z</returns>
double MyVector3D::Z() const
{
	return m_z;
}

/// <summary>
/// overload for plus (addition opperator)
/// </summary>
/// <param name="right">the vector to add to current vector</param>
/// <returns>sum of both vectors</returns>
MyVector3D MyVector3D::operator+(const MyVector3D right) const
{
	return MyVector3D(m_x + right.m_x, m_y + right.m_y, m_z + right.m_z);
}

/// <summary>
/// operator overload for minus (subtract operator)
/// </summary>
/// <param name="right">ther vector to subtract from the current</param>
/// <returns>the difference between the vectors</returns>
MyVector3D MyVector3D::operator-(const MyVector3D right) const
{
	return MyVector3D(m_x - right.m_x, m_y - right.m_y, m_z - right.m_z);
}
/// <summary>
/// multiply by a scalar (double) change the vector magnitude by the scaling factor
/// </summary>
/// <param name="scalar">value to multiply by</param>
/// <returns>re-sized vector</returns>
MyVector3D MyVector3D::operator*(const double scalar) const
{
	return MyVector3D(m_x * scalar, m_y * scalar, m_z * scalar);
}
/// <summary>
/// operator overload for divide
/// </summary>
/// <param name="divisor">scalar to affect magnitude by</param>
/// <returns>re-sized vector</returns>
MyVector3D MyVector3D::operator/(const double divisor) const
{
	if (divisor != 0) // never divide by zero 
	{
		return MyVector3D(m_x / divisor, m_y / divisor, m_z / divisor);
	}
	else
	{
		return MyVector3D(); // dividing by zero has no effect according to Pete ??
	}
}

/// <summary>
/// operator overload for plus equals
/// thios will change the value of the current vector
/// </summary>
/// <param name="right">the vector to add</param>
/// <returns>sum of both vectors</returns>
MyVector3D MyVector3D::operator+=(const MyVector3D right)
{
	m_x += right.m_x;
	m_y += right.m_y;
	m_z += right.m_z;
	return MyVector3D(m_x, m_y, m_z);
}

/// <summary>
/// operator overload for minus equals
/// this will change the current vector
/// </summary>
/// <param name="right">vector to subtract</param>
/// <returns>the difference between the vectors</returns>
MyVector3D MyVector3D::operator-=(const MyVector3D right)
{
	m_x -= right.m_x;
	m_y -= right.m_y;
	m_z -= right.m_z;
	return MyVector3D(m_x, m_y, m_z);
}

/// <summary>
/// operator overload for equality check
/// </summary>
/// <param name="right">vector to compare with</param>
/// <returns>true if the same</returns>
bool MyVector3D::operator==(const MyVector3D right) const
{
	if (m_x == right.m_x && m_y == right.m_y && m_z == right.m_z)
	{
		return true;
	}
	return false;
}
/// <summary>
/// operator overload for inequality
/// </summary>
/// <param name="right">vector to compare with</param>
/// <returns>true is not equal</returns>
bool MyVector3D::operator!=(const MyVector3D right) const
{
	return !(this->operator==(right)); //equal and not equal are complimentry sets whose union is the domain
}
/// <summary>
/// operator overload for uniary negative
/// </summary>
/// <returns>the negative of the vector</returns>
MyVector3D MyVector3D::operator-()
{
	return MyVector3D(-m_x, -m_y, -m_z);
}
/// <summary>
/// negate the x component for use when hitting the left & right cushions
/// </summary>
void MyVector3D::reverseX()
{
	m_x = -m_x;
}
/// <summary>
/// negate the y component for use when hitting the top and bottom cushions
/// </summary>
void MyVector3D::reverseY()
{
	m_y = -m_y;
}
/// <summary>
/// calculate the lenght of the vector 
/// </summary>
/// <returns>lenght</returns>
double MyVector3D::length() const
{
	const double result = std::sqrt(m_x*m_x + m_y*m_y + m_z* m_z);
	return result;
}
/// <summary>
/// the lenght of the vector squared (not square rooted)
/// </summary>
/// <returns>lenght squared</returns>
double MyVector3D::lengthSquared() const
{
	const double result = std::pow(m_x, 2) + std::pow(m_y, 2) + std::pow(m_z, 2);
	return result;
}
/// <summary>
/// dot product of vectors
/// </summary>
/// <param name="other">seconf vector</param>
/// <returns>scalar dot product</returns>
double MyVector3D::dot(const MyVector3D other) const
{
	const double result = m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
	return result;
}
/// <summary>
/// cross product of two vectors
/// </summary>
/// <param name="other">other vector</param>
/// <returns>cross product vector</returns>
MyVector3D MyVector3D::crossProduct(const MyVector3D other) const
{
	const double x = m_y * other.m_z - m_z * other.m_y;
	const double y = m_z * other.m_x - m_x * other.m_z;
	const double z = m_x * other.m_y - m_y * other.m_x;
	return MyVector3D(x, y, z);
}

/// <summary>
/// get the angle between two vectors
/// </summary>
/// <param name="other">other vector</param>
/// <returns>angle in degrees</returns>
double MyVector3D::angleBetween(const MyVector3D other) const
{
	// formula
	// angle = arccos (a dot b / |a|*|b|)

	double top = dot(other);
	double under = length() * other.length();
	double angle;
	if (under != 0) // never divide by zero
	{
		double answer = top / under;
		if (answer > 1) answer = 1;
		if (answer < -1) answer = -1;
		angle = std::acos(answer);
		return (angle * 180 / PI);
	}
	return 0.0; // angle with null vector is zero according to Pete ?
}

/// <summary>
/// return a unit vector along the current vector
/// </summary>
/// <returns>unit vector</returns>
MyVector3D MyVector3D::unit() const
{
	const double x = m_x / length();
	const double y = m_y / length();
	const double z = m_z / length();
	return MyVector3D(x, y, z);
}

/// <summary>
/// re-size current vector to magnitude one
/// </summary>
void MyVector3D::normalise()
{
	const double orignalLenght = length();
	m_x /= orignalLenght;
	m_y /= orignalLenght;
	m_z /= orignalLenght;
}

/// <summary>
///  projection of one vector onto the current vector
/// </summary>
/// <param name="other">vector to project</param>
/// <returns>projection parralell to current</returns>
MyVector3D MyVector3D::projection(const MyVector3D other) const
{
	double lenghtSq = lengthSquared();
	double dotProduct = dot(other);
	double scale = 1.0; // default for null vector involvement
	if (lenghtSq != 0)
	{
		scale = dotProduct / lenghtSq;
	}

	return this->operator*(scale);
}

/// <summary>
/// perpendicular component of vector relative to current vector
/// defined as orignal - projection
/// </summary>
/// <param name="other">vector to project/reject</param>
/// <returns>rejection perpendiucular to current</returns>
MyVector3D MyVector3D::rejection(const MyVector3D other) const
{
	return other - projection(other);
}
