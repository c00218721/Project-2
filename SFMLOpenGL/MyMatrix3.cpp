#include "MyMatrix3.h"

// creates a null matrix
MyMatrix3::MyMatrix3() :
	m11{ 0.0 },
	m12{ 0.0 },
	m13{ 0.0 },
	m21{ 0.0 },
	m22{ 0.0 },
	m23{ 0.0 },
	m31{ 0.0 },
	m32{ 0.0 },
	m33{ 0.0 }
{
}

/// <summary>
/// creates a matrix with given values
/// </summary>
/// <param name="a11">row 1 column 1 value</param>
/// <param name="a12">row 1 column 2 value</param>
/// <param name="a13">row 1 column 3 value</param>
/// <param name="a21">row 2 column 1 value</param>
/// <param name="a22">row 2 column 2 value</param>
/// <param name="a23">row 2 column 3 value</param>
/// <param name="a31">row 3 column 1 value</param>
/// <param name="a32">row 3 column 2 value</param>
/// <param name="a33">row 3 column 3 value</param>
MyMatrix3::MyMatrix3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33) :
	m11{ a11 },
	m12{ a12 },
	m13{ a13 },
	m21{ a21 },
	m22{ a22 },
	m23{ a23 },
	m31{ a31 },
	m32{ a32 },
	m33{ a33 }
{
}

/// <summary>
/// matrix deconstructor
/// </summary>
MyMatrix3::~MyMatrix3()
{
}

/// <summary>
/// function to display matrices in a nice and new layout
/// </summary>
/// <returns>matrix</returns>
std::string MyMatrix3::toString()
{
	char tmpbuf[512];
	sprintf_s(tmpbuf, "{ [ %g, %g, %g ] [ %g, %g, %g ] [ %g, %g, %g ] }", m11, m12, m13, m21, m22, m23, m31, m32, m33);
	return tmpbuf;
}

// make new matrix using 3 3D vectors
MyMatrix3::MyMatrix3(MyVector3D row1, MyVector3D row2, MyVector3D row3)
{
	m11 = row1.X();
	m12 = row1.Y();
	m13 = row1.Z();

	m21 = row2.X();
	m22 = row2.Y();
	m23 = row2.Z();

	m31 = row3.X();
	m32 = row3.Y();
	m33 = row3.Z();
}

/// <summary>
/// addidtion of two matrices
/// </summary>
/// <param name="other">some other matrix</param>
/// <returns>result of the addition</returns>
MyMatrix3 MyMatrix3::operator+(const MyMatrix3 other) const
{
	return MyMatrix3(m11 + other.m11, m12 + other.m12, m13 + other.m13, m21 + other.m21, m22 + other.m22, m23 + other.m23, m31 + other.m31, m32 + other.m32, m33 + other.m33);
}

/// <summary>
/// subtractin of two matrices
/// </summary>
/// <param name="other">some other matrix</param>
/// <returns>difference of two matrices</returns>
MyMatrix3 MyMatrix3::operator-(const MyMatrix3 other) const
{
	return MyMatrix3(m11 - other.m11, m12 - other.m12, m13 - other.m13, m21 - other.m21, m22 - other.m22, m23 - other.m23, m31 - other.m31, m32 - other.m32, m33 - other.m33);
}

/// <summary>
/// multiplication operator for two matrices
/// </summary>
/// <param name="other">some other matrix</param>
/// <returns>result of two matrices mutliplied by each other</returns>
MyMatrix3 MyMatrix3::operator*(const MyMatrix3 other) const
{
	// first row
	double resM11 = m11*other.m11 + m12*other.m21 + m13*other.m31;
	double resM12 = m11*other.m12 + m12*other.m22 + m13*other.m32;
	double resM13 = m11*other.m13 + m12*other.m23 + m13*other.m33;
	// second row
	double resM21 = m21*other.m11 + m22*other.m21 + m23*other.m31;
	double resM22 = m21*other.m12 + m22*other.m22 + m23*other.m32;
	double resM23 = m21*other.m13 + m22*other.m23 + m23*other.m33;
	// third row
	double resM31 = m31*other.m11 + m32*other.m21 + m33*other.m31;
	double resM32 = m31*other.m12 + m32*other.m22 + m33*other.m32;
	double resM33 = m31*other.m13 + m32*other.m23 + m33*other.m33;

	return MyMatrix3(resM11, resM12, resM13, resM21, resM22, resM23, resM31, resM32, resM33);
}

/// <summary>
/// multiplication operator for matrix and a 3D vector
/// </summary>
/// <param name="vector">vector with x,y,z values</param>
/// <returns>result of the multiplication</returns>
MyVector3D MyMatrix3::operator*(const MyVector3D vector) const
{
	// row 1
	double resM11 = m11*vector.X() + m12*vector.Y() + m13*vector.Z();
	// row 2
	double resM21 = m21*vector.X() + m22*vector.Y() + m23*vector.Z();
	// row 3
	double resM31 = m31*vector.X() + m32*vector.Y() + m33*vector.Z();

	// return result
	return MyVector3D(resM11, resM21, resM31);
}

/// <summary>
/// multiplication operator for a matrix and a scalar
/// </summary>
/// <param name="scale">number that is used for the scaling</param>
/// <returns>scaled matrix</returns>
MyMatrix3 MyMatrix3::operator*(const double scale) const
{
	// first row
	double resM11 = m11*scale;
	double resM12 = m12*scale;
	double resM13 = m13*scale;
	// second row
	double resM21 = m21*scale;
	double resM22 = m22*scale;
	double resM23 = m23*scale;
	// third row
	double resM31 = m31*scale;
	double resM32 = m32*scale;
	double resM33 = m33*scale;

	return MyMatrix3(resM11, resM12, resM13, resM21, resM22, resM23, resM31, resM32, resM33);
}

/// <summary>
/// creates transpose of a given matrix
/// </summary>
/// <returns>transpose of a given matrix</returns>
MyMatrix3 MyMatrix3::transpose() const
{
	double new11 = m11;
	double new12 = m21;
	double new13 = m31;

	double new21 = m12;
	double new22 = m22;
	double new23 = m32;

	double new31 = m13;
	double new32 = m23;
	double new33 = m33;

	return MyMatrix3(new11, new12, new13, new21, new22, new23, new31, new32, new33);
}

/// <summary>
/// gets the determinant of a matrix
/// </summary>
/// <returns>returns the determinant</returns>
double MyMatrix3::determinant() const
{
	double detA = m11*(m22 * m33 - m32 * m23) - m21*(m33 * m12 - m32 * m13) + m31*(m23 * m12 - m22 * m13);
	return detA;
}

/// <summary>
/// gets the determinant, checks if it is not 0 and returns the inverse
/// if determinant is 0 then returns emtpy matrix
/// </summary>
/// <returns>an inverse of a matrix or empty matrix depending on the determinant</returns>
MyMatrix3 MyMatrix3::inverse() const
{
	MyVector3D row1 = { m33 * m22 - m32 * m23, m32 * m13 - m33 * m12, m23 * m12 - m22 * m13 };
	MyVector3D row2 = { m31 * m23 - m33 * m21, m33 * m11 - m31 * m13, m21 * m13 - m23 * m11 };
	MyVector3D row3 = { m32 * m21 - m31 * m22, m31 * m12 - m32 * m11, m22 * m11 - m21 * m12 };
	if (determinant() == 0)
	{
		std::cout << "Inverse does not exist. ie determinant = 0 therefore trying to divide by 0" << std::endl;
		return MyMatrix3();
	}
	else
		return MyMatrix3((MyMatrix3(row1, row2, row3) * (1 / determinant())));
}

/// <summary>
/// returns a given row
/// </summary>
/// <param name="row">a value that will return a given row</param>
/// <returns>wanted row</returns>
MyVector3D MyMatrix3::row(int row) const
{
	if (row == 1)
	{
		return MyVector3D(m11, m12, m13);
	}
	else if (row == 2)
	{
		return MyVector3D(m21, m22, m23);
	}
	else if (row == 3)
	{
		return MyVector3D(m31, m32, m33);
	}
	else
	{
		std::cout << "There is no such row" << std::endl;
		return MyVector3D();
	}
}

/// <summary>
/// returns a given column
/// </summary>
/// <param name="row">a value that will return a given column</param>
/// <returns>wanted column</returns>
MyVector3D MyMatrix3::column(int column) const
{
	if (column == 1)
	{
		return MyVector3D(m11, m21, m31);
	}
	else if (column == 2)
	{
		return MyVector3D(m12, m22, m32);
	}
	else if (column == 3)
	{
		return MyVector3D(m13, m23, m33);
	}
	else
	{
		std::cout << "There is no such column" << std::endl;
		return MyVector3D();
	}
}

/// <summary>
/// checks if two matrices are the same
/// </summary>
/// <param name="other">some other matrix</param>
/// <returns>true or false depending on the result of the equality check</returns>
bool MyMatrix3::operator==(const MyMatrix3 other) const
{
	if (row(1) == other.row(1) && row(2) == other.row(2) && row(3) == other.row(3))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// checks if two matrices are the NOT same
/// </summary>
/// <param name="other">some other matrix</param>
/// <returns>true or false depending on the result of the inequality check</returns>
bool MyMatrix3::operator!=(const MyMatrix3 other) const
{
	if (row(1) != other.row(1) && row(2) != other.row(2) && row(3) != other.row(3))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// creates and rotates a matrix by a given value on the X axis
/// </summary>
/// <param name="angleRadians">angle to rotate by in radians</param>
/// <returns>rotated matrix that can be used to rotate an actual matrix</returns>
MyMatrix3 MyMatrix3::rotationX(double angleRadians)
{
	MyVector3D row1 = { 1,0,0 };
	MyVector3D row2 = { 0,cos(angleRadians),-sin(angleRadians) };
	MyVector3D row3 = { 0,sin(angleRadians),cos(angleRadians) };

	return MyMatrix3(MyMatrix3(row1, row2, row3));
}

/// <summary>
/// creates and rotates a matrix by a given value on the Y axis
/// </summary>
/// <param name="angleRadians">angle to rotate by in radians</param>
/// <returns>rotated matrix that can be used to rotate an actual matrix</returns>
MyMatrix3 MyMatrix3::rotationY(double angleRadians)
{
	MyVector3D row1 = { cos(angleRadians),0,sin(angleRadians) };
	MyVector3D row2 = { 0,1,0 };
	MyVector3D row3 = { -sin(angleRadians),0,cos(angleRadians) };

	return MyMatrix3(MyMatrix3(row1, row2, row3));
}

/// <summary>
/// creates and rotates a matrix by a given value on the Z axis
/// </summary>
/// <param name="angleRadians">angle to rotate by in radians</param>
/// <returns>rotated matrix that can be used to rotate an actual matrix</returns>
MyMatrix3 MyMatrix3::rotationZ(double angleRadians)
{
	MyVector3D row1 = { cos(angleRadians),-sin(angleRadians),0 };
	MyVector3D row2 = { sin(angleRadians),cos(angleRadians),0 };
	MyVector3D row3 = { 0,0,1 };

	return MyMatrix3(row1, row2, row3);
}

MyMatrix3 MyMatrix3::translation(MyVector3D displacement)
{
	return MyMatrix3{
		1,0,displacement.X(),
		0,1,displacement.Y(),
		0,0,1 };
}

MyMatrix3 MyMatrix3::scale(double scalingfactor)
{
	return MyMatrix3{
		scalingfactor,0,0,
		0,scalingfactor,0,
		0,0,scalingfactor };
}