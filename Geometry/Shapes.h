#pragma once

#include "Dependencies.h"

class Position
{	
protected:
	float x;
	float y;

public:
	Position();
	Position(float inX, float inY);

	float X(void);
	void  X(float inX);
	
	float Y(void);
	void  Y(float inY);
	
	void Copy(Position inPos);
	void Print();
	bool IsEqual(Position inPos);
};


class Shape
{
protected:
	std::wstring name;

public:
	Shape();
	Shape(std::wstring inName);

	virtual std::wstring Name(void);
	virtual void Name(std::wstring inName);

	virtual void Copy(Shape inShape);
	virtual void Print();
	virtual bool IsEqual(Shape inShape);
};


class Vertex :public Shape
{
protected:
	Position pos;

public:
	Vertex();
	Vertex(std::wstring inName, Position inPos);
	Vertex(std::wstring inName, float inX, float inY);

	Position Pos(void);
	void     Pos(Position inPos);

	void Copy(Vertex inVert);
	void Print();
	bool IsEqual(Vertex inVert);
};


class Line :public Shape
{
protected:
	Vertex vert1, vert2;
	float  length;

public:
	Line();
	Line(std::wstring inName, Vertex inVert1, Vertex inVert2);
	Line(std::wstring inName, Vertex inVert, float inLength);

	Vertex Vert1(void);
	void   Vert1(Vertex inVert);

	Vertex Vert2(void);
	void   Vert2(Vertex inVert);

	float Length(void);
	void  Length(float inLength);

	void Copy(Line inLine);
	void Print();
	bool IsEqual(Line inLine);

	std::wstring VertexName();
	void CalculateLength();
	void MoveVertexByLength();
};


class Angle: public Shape
{
protected:
	float turn;
	Line  side1;
	Line  side2;

public:
	Angle(void);
	Angle(Line inSide1, Line inSide2);
	Angle(Vertex vert1, Vertex vert2, Vertex vert3);
	// Angle from Line and turn
	//  (figure out how to translate the 3rd vertex)

	float Turn(void);
	void  Turn(float inTurn);
	float Degree(void);
	void  Degree(float inDeg);
	float Radian(void);
	void  Radian(float inRad);

	Line Side1(void);
	void Side1(Line inLine);

	Line Side2(void);
	void Side2(Line inLine);

	void Copy(Angle inAng);
	//##1 - turns
	//#1# - degrees
	//1## - radians
	void Print(int mode = 1);
	bool IsEqual(Angle inAng);

	std::wstring VertexName();
	void CalculateTurn();
};


class Triangle :public Shape
{
protected:
	Line side1;
	Line side2;
	Line side3;

public:
	Triangle();
	Triangle(std::wstring inName,Line inSide1, Line inSide2, Line inSide3);
	Triangle(std::wstring inName,Vertex inPoint1, Vertex inPoint2, Vertex inPoint3);

	Line Side1(void);
	void Side1(Line inLine);

	Line Side2(void);
	void Side2(Line inLine);

	Line Side3(void);
	void Side3(Line inLine);

	void Copy(Triangle inTrg);
	void Print();
	bool IsEqual(Triangle inTrg);

	std::wstring VertexName();
	float Perimeter();
	float SemiPerimeter();
	float Area();

	/*
	//Semiperimeter (s) - value | >= 0
	*
	* s = (side1 + side2 + side3)/2
	*
	//Angles (alpha, beta, gamma) - value | 0 -> 359
	*
	* alpha = acos((pow(side2.len,2)+pow(side3.len,2)-pow(side1.len,2))/(2*side2.len*side3.len)
	*	
	//Heights (h1,h2,h3) - line
	*
	* h1 = (2*area)/side1
	*
	//Angular Bisectors (l1,l2,l3) - line
	*
	* l1 = (2/(side2+side3))*sqrt(side2*side3*s*(s-side1))
	*
	//Medians (m1,m2,m3) - line
	*
	* m1 = (sqrt(2*(pow(side2,2)+pow(side3,2))-pow(side1,2))/2
	*
	//In radius (r) - value
	*
	* r = sqrt(((s-side1)*(s-side2)*(s-side3))/s)
	*
	//CircumCircle"s radius "Out radius"? (R) - value
	*
	* R = (side1*side2*side3)/(4*sqrt(s*(s-side1)*(s-side2)*(s-side3)))
	*
	//Perpendicular bisector (M1,M2,M3) - line
	//CircumCenter - where the Perpendicular bisectors meet (O) - vertex
	//InCenter - where the Angular bisectors meet (I) - vertex
	//BaryCenter / Centroid - where the Medians meet (G) - vertex
	//etc...
	*/
};