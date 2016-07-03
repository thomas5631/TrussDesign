#pragma once
class Node
{
	int ID;
	const double xPos;
	const double yPos;

public:
	Node(int ID, const double x_pos, const double y_pos)
		:
		ID(ID),
		xPos{ x_pos },
		yPos{ y_pos }
	{
	}

	virtual ~Node()
	{
	};

	virtual int getID()
	{
		return ID;
	}

	virtual double x_pos() const
	{
		return xPos;
	}

	virtual double y_pos() const
	{
		return yPos;
	}

};

