#pragma once
#include "Node.h"

enum class eType {basic, reactX, reactY};

class Element
{
	int ID;
	Node nodeA;
	Node nodeB;
	double load;
	const eType elementType;

	virtual double xLength()
	{
		return nodeA.x_pos() - nodeB.x_pos();;
	}

	virtual double yLength()
	{
		return nodeA.y_pos() - nodeB.y_pos();
	}

	virtual double length()
	{
		auto x = xLength();
		auto y = yLength();

		return sqrt(pow(x, 2) + pow(y, 2));
	}

public:

	Element(int ID, Node &node1, Node &node2, const eType elementType = eType::basic):
		ID(ID),
		nodeA(node1),
		nodeB(node2),
		load(0),
		elementType(elementType)
	{
	}

	virtual ~Element()
	{
	}

	Node node1() const
	{
		return nodeA;
	}

	Node node2() const
	{
		return nodeB;
	}

	int getID() const
	{
		return ID;
	}

	eType getType() const
	{
		return elementType;
	}

	virtual double bucklingload()
		//returns the buckling load of the element. This cannot be exceeded.
	{
		return (IMPERFECTION*pow(PI, 2)*MODULUS*SECONDMOMENT) / (pow(1000* length(), 2));
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
			std::cout << "Buckling load exceeded in element " << this->ID << std::endl;
	}
};

