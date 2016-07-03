#pragma once
#include "Node.h"

class Element
{
	const char name;
	const Node node1;
	const Node node2;
	double load;

	virtual double length()
	{
		auto x = xLength();
		auto y = yLength();

		return sqrt(pow(x, 2) + pow(y, 2));
	}

public:

	Element(char name, Node &node1, Node &node2):
		name(name),
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

	virtual double angle()
	{
		double angle;
		auto xDiff = fabs(xLength());
		auto yDiff = fabs(yLength());

		angle = atan(yDiff / xDiff);

		return angle;
	}

	void force(double load)
	{
		this->load = load;

		if (load < -bucklingload())
			std::cout << "Buckling load exceeded in element " << this->name << std::endl;
	}
};

