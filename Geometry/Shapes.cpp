#include "Dependencies.h"

//Move complex constructors to shapes.cpp
//Move complex getters and setters to shapes.cpp

Position::Position()
{
	x = 0.0;
	y = 0.0;
}
Position::Position(float inX, float inY)
{
	X(inX);
	Y(inY);
}

float Position::X(void)
{
	return x;
}
void Position::X(float inX)
{
	/* Input validation */
	x = inX;
}

float Position::Y(void)
{
	return y;
}
void Position::Y(float inY)
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
bool Position::IsEqual(Position inPos)
{
	return (X() == inPos.X()) * (Y() == inPos.Y());
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
bool Shape::IsEqual(Shape inShape)
{
	return Name() == inShape.Name();
}



Vertex::Vertex()
{

}
Vertex::Vertex(std::wstring inName, Position inPos)
{
	Name(inName);
	Pos(inPos);
}
Vertex::Vertex(std::wstring inName, float inX, float inY)
{
	Name(inName);
	Pos(Position(inX, inY));
}

Position Vertex::Pos(void)
{
	return pos;
}
void Vertex::Pos(Position inPos)
{
	pos.Copy(inPos);
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
bool Vertex::IsEqual(Vertex inVert)
{
	return (Name() == inVert.Name()) * Pos().IsEqual(inVert.Pos());
}



Line::Line()
{
	length = 0.0;
}
Line::Line(std::wstring inName, Vertex inVert1, Vertex inVert2)
{
	Name(inName);
	Vert1(inVert1);
	Vert2(inVert2);
	CalculateLength();
}
Line::Line(std::wstring inName, Vertex inVert, float inLength)
{
	Name(inName);
	Vert1(inVert);
	Length(inLength);
	MoveVertexByLength();
	vert2.Name(Vert1().Name() + L"₁");
}

Vertex Line::Vert1(void)
{
	return vert1;
}
void Line::Vert1(Vertex inVert)
{
	vert1.Copy(inVert); CalculateLength();
}

Vertex Line::Vert2(void)
{
	return vert2;
}
void Line::Vert2(Vertex inVert)
{
	vert2.Copy(inVert); CalculateLength();
}

float Line::Length(void)
{
	return length;
}
void Line::Length(float inLength)
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
bool Line::IsEqual(Line inLine)
{
	return Vert1().IsEqual(inLine.Vert1()) *
		   Vert2().IsEqual(inLine.Vert2()) *
		   (Length() == inLine.Length());
}

std::wstring Line::VertexName()
{
	return Vert1().Name() + Vert2().Name();
}
void Line::CalculateLength()
{
	length = (float)sqrt(
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
	turn = 0.0f;
}
Angle::Angle(Line inSide1, Line inSide2)
{
	/* Input validation */
	if (inSide1.Vert2().IsEqual(inSide2.Vert1()) or
		inSide1.Vert1().IsEqual(inSide2.Vert2()) or
		inSide1.Vert1().IsEqual(inSide2.Vert1()) or
		inSide1.Vert2().IsEqual(inSide2.Vert2()))
	{
		Side1(inSide1);
		Side2(inSide2);
		CalculateTurn();
		Name(VertexName());
	}
}
Angle::Angle(Vertex vert1, Vertex vert2, Vertex vert3)
{
	Side1(Line(L"k", vert1, vert2));
	Side2(Line(L"l", vert2, vert3));
	CalculateTurn();
	Name(VertexName());
}
// Angle from Line and turn
//  (figure out how to translate the 3rd vertex)

float Angle::Turn(void)
{
	return turn;
}
void Angle::Turn(float inTurn)
{
	/* Input validation */
	turn = inTurn;
}
float Angle::Degree(void)
{
	return turn * 360;
}
void Angle::Degree(float inDeg)
{
	/* Input validation */
	turn = inDeg / 360;
}
float Angle::Radian(void)
{
	return turn * 2 * Pi;
}
void Angle::Radian(float inRad)
{
	/* Input validation */
	turn = inRad / (2 * Pi);
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
	Turn(inAng.Turn());
	Side1(inAng.Side1());
	Side2(inAng.Side2());
}
void Angle::Print(int mode)
{
	std::wcout << L"Angle " << Name();

	if (mode % 2)
		std::wcout << L" = " << Turn() << L" Turns";
	mode /= 10;
	if (mode % 2)
		std::wcout << L" = " << Degree() << L"°";
	mode /= 10;
	if (mode % 2)
		std::wcout << L" = " << Radian() << L" rad";
}

std::wstring Angle::VertexName()
{
	return Side1().Vert1().Name() +
		   Side2().Vert1().Name() +
		   Side2().Vert2().Name();
}
void Angle::CalculateTurn()
{
	Radian((float)acos((
		(double)pow(Side1().Length(), 2) +
		(double)pow(Side2().Length(), 2) -
		(double)pow(Line(L"a", Side1().Vert1(), Side2().Vert2()).Length(), 2))
		/
		(2 * (double)Side1().Length() * (double)Side2().Length())
	));
}



Triangle::Triangle()
{

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
	std::wcout << L"Triangle " << Name() << L"("  << VertexName() << L"):\n";
	std::wcout << L"-  Perimeter = " << Perimeter() << L" Units\n";
	std::wcout << L"-  Semiperimeter = " << SemiPerimeter() << L" Units\n";
	std::wcout << L"-  Area = " << Area() << L" Units²\n";
	std::wcout << L"-  Sides:\n   =\t";
	side1.Print();
	std::wcout << L"\n   =\t";
	side2.Print();
	std::wcout << L"\n   =\t";
	side3.Print();
}

std::wstring Triangle::VertexName()
{
	return Side1().Vert1().Name() +
		   Side2().Vert1().Name() + 
		   Side3().Vert1().Name();
}
float Triangle::Perimeter()
{
	return side1.Length() + side2.Length() + side3.Length();
}
float Triangle::SemiPerimeter()
{
	return Perimeter() / 2;
}
float Triangle::Area()
{
	return std::sqrt(
		SemiPerimeter() *
		(SemiPerimeter() - side1.Length()) *
		(SemiPerimeter() - side2.Length()) *
		(SemiPerimeter() - side3.Length())
	);
}