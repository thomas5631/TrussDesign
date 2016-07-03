#pragma once

#include "Node.h"
#include "Element.h"
#include <vector>

class Former
{
	const std::vector<Node> nodeList;
	const std::vector<Element> elementList;

	template <typename T> 
	int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

public:

	Former(std::vector<Node> &nodeList, std::vector<Element> &elementList)
		:
		nodeList(nodeList),
		elementList(elementList)
	{
	}

	virtual ~Former()
	{
	}

	std::vector<std::vector<double>> inputVec()
	{
		std::vector<std::vector<double>> inVec(nodeList.size() * 2, std::vector<double>(nodeList.size() * 2));    //this initializes the input vector

		for (auto node : nodeList)
		{
			for (auto element : elementList)
			{
				if(element.getType() == eType::basic)
				{
					auto xSign = 0;
					auto ySign = 0;

					if (element.node1().getID() == node.getID())
					{
						xSign = sgn(element.node2().x_pos() - element.node1().x_pos());
						ySign = sgn(element.node2().y_pos() - element.node1().y_pos());
					}
					else if (element.node2().getID() == node.getID())
					{
						xSign = sgn(element.node1().x_pos() - element.node2().x_pos());
						ySign = sgn(element.node1().y_pos() - element.node2().y_pos());
					}

					inVec[2 * node.getID()][element.getID()] = ySign*sin(element.angle());
					inVec[2 * node.getID() + 1][element.getID()] = xSign*cos(element.angle());
				}

				else if (element.getType() == eType::reactY)
				{
					if (element.node1().getID() == node.getID())
					{
						inVec[2 * node.getID()][element.getID()] = 1;
					}
				}

				else if (element.getType() == eType::reactX)
				{
					if (element.node1().getID() == node.getID())
					{
						inVec[2 * node.getID() + 1][element.getID()] = -1; //axis convention -x, +y for pin forces 
					}
				}
				
			}


		}
		return inVec;
	}

};

