#pragma once
class Node
{
	const double xPos;
	const double yPos;
public:
	Node(const double x_pos, const double y_pos)
		: xPos{ x_pos },
		yPos{ y_pos }
	{
	}

	virtual ~Node()
	{
	};

	virtual double x_pos() const
	{
		return xPos;
	}

	virtual double y_pos() const
	{
		return yPos;
	}
};

