#include "Dependencies.h"

//Move complex constructors to shapes.cpp
//Move complex getters and setters to shapes.cpp

Position::Position()
{
	x = 0.0; y = 0.0;
}
Position::Position(double inX, double inY)
{
	X(inX); Y(inY);
}

double Position::X(void)
{
	return x;
}
void Position::X(double inX)
{
	/* Input validation */
	x = inX;
}

double Position::Y(void)
{
	return y;
}
void Position::Y(double inY)
{
	/* Input validation */
	y = inY;
}

void Position::Copy(Position inPos)
{
	X(inPos.X());
	Y(inPos.Y());
}
void Position::Print()
{
	std::wcout << (x >= 0 ? (x < 10 ? "( " : "(") : "(") << x 
			  << (y >= 0 ? (y < 10 ? ", " : ",") : ",") << y
			  << ")";
}



Shape::Shape()
{
	name = L"";
}
Shape::Shape(std::wstring inName)
{
	Name(inName);
}

std::wstring Shape::Name(void)
{
	return name;
}
void Shape::Name(std::wstring inName)
{
	/* Input validation */
	name = L"UNDEF";
	if (inName != L"UNDEF" or inName != L"")
		name = inName;
}

void Shape::Copy(Shape inShape)
{
	Name(inShape.Name());
}
void Shape::Print()
{
	std::wcout << name;
}



Vertex::Vertex()
{
	pos = Position();
}
Vertex::Vertex(std::wstring inName, Position inPos)
{
	Name(inName);
	pos.Copy(inPos);
}

Position Vertex::Pos(void)
{
	return pos;
}
void Vertex::Pos(Position inPos)
{
	pos.Copy(inPos);
}
void Vertex::Pos(double inX, double inY)
{
	Pos(Position(inX, inY));
}


void Vertex::Copy(Vertex inVert)
{
	Name(inVert.Name());
	Pos(inVert.Pos());
}
void Vertex::Print()
{
	std::wcout << "pt." << name << " = ";
	pos.Print();
}



Line::Line()
{
	vert1 = Vertex(); vert2 = Vertex(); length = 0.0;
}
Line::Line(std::wstring inName, Vertex inVert1, Vertex inVert2)
{
	Name(inName);
	Vert1(inVert1);
	Vert2(inVert2);
	CalculateLength();
}
Line::Line(std::wstring inName, Vertex inVert, std::wstring vert2, double inLength)
{
	Name(inName);
	Vert1(inVert);
	Length(inLength);
	MoveVertexByLength();
}

Vertex Line::Vert1(void)
{
	return vert1;
}

void Line::Vert1(Vertex inVert)
{
	vert1.Copy(inVert); CalculateLength();
}
void Line::Vert1(Position inPos)
{
	vert1.Pos(inPos); CalculateLength();
}
void Line::Vert1(double inX, double inY)
{
	vert1.Pos(inX, inY); CalculateLength();
}

Vertex Line::Vert2(void)
{
	return vert2;
}
void Line::Vert2(Vertex inVert)
{
	vert2.Copy(inVert); CalculateLength();
}
void Line::Vert2(Position inPos)
{
	vert2.Pos(inPos); CalculateLength();
}
void Line::Vert2(double inX, double inY)
{
	vert2.Pos(inX, inY); CalculateLength();
}

double Line::Length(void)
{
	return length;
}
void Line::Length(double inLength)
{
	/* Input validation */
	length = inLength;
	MoveVertexByLength();
}

void Line::Copy(Line inLine)
{
	Name(inLine.Name());
	Vert1(inLine.Vert1());
	Vert2(inLine.Vert2());
}
void Line::Print()
{
	std::wcout << L"Line " << name << L"(" << VertexName() << L"): ";
	vert1.Print();
	std::wcout << L"; ";
	vert2.Print();
	std::wcout << L" | Length = " << length << L" Units";
}

std::wstring Line::VertexName()
{
	return Vert1().Name() + Vert2().Name();
}
void Line::CalculateLength()
{
	length = sqrt(
		pow((Vert1().Pos().X()- Vert2().Pos().X()),2) +
		pow((Vert1().Pos().Y() - Vert2().Pos().Y()), 2)
	);
}
void Line::MoveVertexByLength()
{
	Vert2(Vertex(Vert2().Name(), Position(
		Vert1().Pos().X() + Length(),
		Vert1().Pos().Y()
	)));
}



Angle::Angle(void)
{

}
Angle::Angle(Line inSide1, Line inSide2)
{

}
Angle::Angle(Vertex vert1, Vertex vert2, Vertex vert3)
{

}
// Angle from Line and turn
//  (figure out how to translate the 3rd vertex)

double Angle::Turn(void)
{
	return turn;
}
void Angle::Turn(double inTurn)
{

}
double Angle::Degree(void)
{
	return turn * 360;
}
void Angle::Degree(double inDeg)
{

}
double Angle::Radian(void)
{
	return turn * Pi;
}
void Angle::Radian(double inRad)
{

}

Line Angle::Side1(void)
{
	return side1;
}
void Angle::Side1(Line inLine)
{
	/* Input validation */
	side1 = inLine;
}

Line Angle::Side2(void)
{
	return side2;
}
void Angle::Side2(Line inLine)
{
	/* Input validation */
	side2 = inLine;
}

void Angle::Copy(Angle inAng)
{

}
void Angle::Print(void)
{

}



Triangle::Triangle()
{
	side1 = Line(); side2 = Line(); side3 = Line();
}
Triangle::Triangle(std::wstring inName, Line inSide1, Line inSide2, Line inSide3)
{
	Name(inName);
	Side1(inSide1);
	Side2(inSide2);
	Side3(inSide3);
}
Triangle::Triangle(std::wstring inName, Vertex inPoint1, Vertex inPoint2, Vertex inPoint3)
{
	Name(inName);
	Side1(Line(L"a", inPoint1, inPoint2));
	Side2(Line(L"b", inPoint2, inPoint3));
	Side3(Line(L"c", inPoint3, inPoint1));
}

Line Triangle::Side1(void)
{
	return side1;
}
void Triangle::Side1(Line inLine)
{
	/* Input validation */
	side1 = inLine;
}

Line Triangle::Side2(void)
{
	return side2;
}
void Triangle::Side2(Line inLine)
{
	/* Input validation */
	side2 = inLine;
}

Line Triangle::Side3(void)
{
	return side3;
}
void Triangle::Side3(Line inLine)
{
	/* Input validation */
	side3 = inLine;
}

void Triangle::Copy(Triangle inTrg)
{
	side1.Copy(inTrg.Side1());
	side2.Copy(inTrg.Side2());
	side3.Copy(inTrg.Side3());
}
void Triangle::Print()
{
	std::wcout << "Triangle " << Name() << "("  << VertexName() << "):\n";
	std::wcout << "-  Perimeter = " << Perimeter() << " Units\n";
	std::wcout << "-  Semiperimeter = " << SemiPerimeter() << " Units\n";
	std::wcout << "-  Area = " << Area() << " Units^2\n";
	std::wcout << "-  Sides:\n   =\t";
	side1.Print();
	std::wcout << "\n   =\t";
	side2.Print();
	std::wcout << "\n   =\t";
	side3.Print();
}

std::wstring Triangle::VertexName()
{
	return Side1().Vert1().Name() +
		   Side2().Vert1().Name() + 
		   Side3().Vert1().Name();
}
double Triangle::Perimeter()
{
	return side1.Length() + side2.Length() + side3.Length();
}
double Triangle::SemiPerimeter()
{
	return Perimeter() / 2;
}
double Triangle::Area()
{
	return std::sqrt(SemiPerimeter() *
		(SemiPerimeter() - side1.Length()) *
		(SemiPerimeter() - side2.Length()) *
		(SemiPerimeter() - side3.Length())
	);
}