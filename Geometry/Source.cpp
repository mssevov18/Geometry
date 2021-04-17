#include "Dependencies.h"

int main()
{
	int empty = _setmode(_fileno(stdout), _O_U16TEXT);
	empty = _setmode(_fileno(stdin), _O_U16TEXT);

	Position pos(0.0, 0.0);
	Line line(L"a", Vertex(L"A", pos), L"B", 10.0);
	line.Print();
	std::wcout << std::endl;
	line.Length(line.Length() + 5.0);
	line.Print();
	std::wcout << std::endl;
	pos.X(-5.0);
	line.Vert1(pos);
	line.Print();
	std::wcout << std::endl;

	Vertex a = Vertex(L"A", Position(-0.5, 0.0));
	Vertex b = Vertex(L"B", Position( 0.5, 0.0));
	Vertex c = Vertex(L"C", Position( 0.0, 1.0));

	Triangle ABC1 = Triangle(L"n", a, b, c);
	ABC1.Print();
	std::wcout << std::endl;

	Line ab = Line(L"a", a, b);
	Line bc = Line(L"b", b, c);
	Line ca = Line(L"c", c, a);

	Triangle ABC2 = Triangle(L"m", ab, bc, ca);
	ABC2.Print();
	std::wcout << std::endl;


}