#pragma once
#include "Node.h"

class Element
{
	const Node node1;
	const Node node2;
	const double load;

	virtual double length()
	{
		auto x = xLength();
		auto y = yLength();

		return sqrt(pow(x, 2) + pow(y, 2));
	}
public:

	Element(Node &node1, Node &node2):
		node1(node1),
		node2(node2),
		load(0)
	{

	}

	virtual ~Element()
	{
	}

	virtual double bucklingload()
		//returns the buckling load of the element. This cannot be exceeded.
	{
		return (IMPERFECTION*pow(PI, 2)*MODULUS*SECONDMOMENT) / (pow(1000* length(), 2));
	}

	virtual double xLength()
	{
		return node1.x_pos() - node2.x_pos();;
	}

	virtual double yLength()
	{
		return node1.y_pos() - node2.y_pos();
	}
};

