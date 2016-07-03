#pragma once

#include "Node.h"
#include "Element.h"
#include <vector>
#include <iostream>

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
				if (element.node1().getID() == node.getID())
				{
					int xSign = sgn(element.node2().x_pos() - element.node1().x_pos());
					int ySign = sgn(element.node2().y_pos() - element.node1().y_pos());

					int yLocA = 2 * node.getID();
					int xLocA = 2 * node.getID() + 1;
					int yLocB = element.getID();
					int xLocB = element.getID();

					inVec[xLocA][xLocB] = xSign*cos(element.angle());
					inVec[yLocA][yLocB] = ySign*sin(element.angle());

					//std::cout << "The x sign for " << node.getID() << " and element " << element.getID() << " = " << xSign << std::endl;
					//std::cout << "The y sign for " << node.getID() << " and element " << element.getID() << " = " << ySign << std::endl;
				}
				else if (element.node2().getID() == node.getID())
				{
					int xSign = sgn(element.node1().x_pos() - element.node2().x_pos());
					int ySign = sgn(element.node1().y_pos() - element.node2().y_pos());

					int yLocA = 2 * node.getID();
					int xLocA = 2 * node.getID() + 1;
					int yLocB = element.getID();
					int xLocB = element.getID();

					inVec[xLocA][xLocB] = xSign*cos(element.angle());
					inVec[yLocA][yLocB] = ySign*sin(element.angle());

					//std::cout << "The x sign for " << node.getID() << " and element " << element.getID() << " = " << xSign << std::endl;
					//std::cout << "The y sign for " << node.getID() << " and element " << element.getID() << " = " << ySign << std::endl;

				}
			}
		}
		return inVec;
	}

};

