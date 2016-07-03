// trussDesign.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Node.h"
#include "Element.h"
#include "Former.h"
#include "Solver.h"


int main()
{
	auto rho = 1000.00;
	auto height = 12.00;
	auto plugA = PI*pow(0.170, 2);

	auto pressure = rho*GRAVITY*height;

	//auto load = plugA*pressure;
	auto load = 10.69E3;;

	std::cout << "The total load is: " << load << std::endl;

	auto angle = PI / 6;        //Angle from x-axis representation

	auto xPos = 0.00;
	auto yPos = 4.80;
	auto xLoad = load*sin(angle);
	auto yLoad = -load*cos(angle);

	std::cout << "The x component of the load is: " << xLoad << std::endl;
	std::cout << "The y component of the load is: " << yLoad << std::endl;

	Node node0(0, xPos, yPos);
	Node nodeP(1, 0.00, 0.00);
	Node nodeR(2, 2.77128, 0.00);

	std::vector<Node> nodeList = { node0, nodeP, nodeR };

	Element elementA(0, nodeP, node0);
	Element elementB(1, nodeR, node0);
	Element elementC(2, nodeP, nodeR);

	std::vector<Element> elementList = { elementA, elementB, elementC };

	auto former = Former(nodeList, elementList);

	std::cout << std::endl << "input matrix: " << std::endl << std::endl;
	auto inputVector = former.inputVec();

	Solver::output(inputVector);

	//std::cout << "Element A: " << elementA.angle() * 180 / PI << std::endl;
	//std::cout << "Element B: " << elementB.angle() * 180 / PI << std::endl;
	//std::cout << "Element C: " << elementC.angle() * 180 / PI << std::endl;


	//std::vector<std::vector<double>> inVec(nodeList.size()*2, std::vector<double>(nodeList.size()*2));    //this initializes the input vector
	//for(auto node: nodeList)
	//{
	//	for(auto element: elementList)
	//	{
	//		if(element.node1().getID() == node.getID())
	//		{
	//			bool xSign = element.node2().x_pos() - element.node1().x_pos();
	//			bool ySign = element.node2().y_pos() - element.node1().y_pos();

	//			std::cout << "The x sign for " << node.getID() << " and element " << element.getID() << " = " << xSign << std::endl;
	//			std::cout << "The y sign for " << node.getID() << " and element " << element.getID() << " = " << ySign << std::endl;
	//		}
	//		else if(element.node2().getID() == node.getID())
	//		{
	//			bool xSign = element.node1().x_pos() - element.node2().x_pos();
	//			bool ySign = element.node1().y_pos() - element.node2().y_pos();

	//			std::cout << "The x sign for " << node.getID() << " and element " << element.getID() << " = " << xSign << std::endl;
	//			std::cout << "The y sign for " << node.getID() << " and element " << element.getID() << " = " << ySign << std::endl;

	//		}
	//	}
	//}


	//std::vector<std::vector<double> > myVec = {
	//	{ -sin(elementA.angle()), -sin(elementB.angle()), 0, 0, 0, 0 },
	//	{ cos(elementA.angle()), cos(elementB.angle()), 0, 0, 0, 0 },
	//	{ sin(elementA.angle()), 0, 0, 1, 0, 0 },
	//	{ 0, 0, cos(elementC.angle()), 0, -1, 0 },
	//	{ 0, sin(elementB.angle()), 0, 0, 0, 1 },
	//	{ 0, -cos(elementB.angle()), -cos(elementC.angle()), 0, 0, 0 }
	//};

	//std::vector<double> forces = {
	//	xLoad, yLoad, 0, 0, 0, 0
	//};

	//std::cout << std::endl << "input matrix: " << std::endl << std::endl;
	//Solver::output(myVec);
	//
	//std::cout << std::endl << "force matrix: " << std::endl << std::endl;
	//Solver::output(forces);

	//auto result = Solver::solveGaussian(myVec, forces);

	//std::cout << std::endl << "output matrix: " << std::endl << std::endl;
	//Solver::output(result);

	//elementA.force(result[0]);
	//elementB.force(result[1]);
	//elementC.force(result[2]);

	getchar();
	return 0;
}