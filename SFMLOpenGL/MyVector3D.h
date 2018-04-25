#ifndef MYVECTOR3D
#define MYVECTOR3D

#include <iostream>
#include <SFML/Graphics.hpp>

class MyVector3D
{
public:
	MyVector3D();
	MyVector3D(double x, double y, double z);
	MyVector3D(sf::Vector3f sfVector);
	MyVector3D(sf::Vector3i sfVector);
	MyVector3D(sf::Vector2i sfVector);
	MyVector3D(sf::Vector2u sfVector);
	MyVector3D(sf::Vector2f sfVector);
	~MyVector3D();
	std::string toString();
	double X()const; // just return the value of m_x
	double Y()const;
	double Z()const;

	MyVector3D operator +(const MyVector3D right) const;
	MyVector3D operator -(const MyVector3D right) const;
	MyVector3D operator *(const double scalar) const;
	MyVector3D operator /(const double divisor) const;
	MyVector3D operator +=(const MyVector3D right);
	MyVector3D operator -=(const MyVector3D right);

	bool operator == (const MyVector3D right) const;
	bool operator != (const MyVector3D right) const;

	// negative of a vector 
	MyVector3D operator -();
	//new methods for bouncing off sides of table in billiards
	void reverseX();
	void reverseY();

	double length()const;
	double lengthSquared()const;
	double dot(const MyVector3D other) const;
	MyVector3D crossProduct(const MyVector3D other)const;
	double angleBetween(const MyVector3D other)const;
	MyVector3D unit() const;
	void normalise();
	MyVector3D projection(const MyVector3D other)const;
	// projection of other onto the current vector so answer will parralell to current vector.
	MyVector3D rejection(const MyVector3D other)const;


	operator sf::Vector2i() { return sf::Vector2i(static_cast<int>(m_x), static_cast<int>(m_y)); };
	operator sf::Vector2f() { return sf::Vector2f(static_cast<float>(m_x), static_cast<float>(m_y)); };
	operator sf::Vector2u() { return sf::Vector2u(static_cast<unsigned int>(m_x), static_cast<unsigned int>(m_y)); };
	operator sf::Vector3i() { return sf::Vector3i(static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_z)); };
	operator sf::Vector3f() { return sf::Vector3f(static_cast<float>(m_x), static_cast<float>(m_y), static_cast<float>(m_z)); };

private:
	double m_x;
	double m_y;
	double m_z;
};

#endif // !MYVECTOR3D
