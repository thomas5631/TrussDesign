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
	Node node1(1, 1.759621119, 1.756921119);
	Node nodeP(2, 0.00, 0.00);
	Node nodeR(3, 2.77128, 0.00);

	std::vector<Node> nodeList = { node0, nodeP, nodeR, node1 };

	Element elementA(0, nodeP, node0);
	Element elementB(1, node1, node0);
	Element elementC(2, node1, nodeP);
	Element elementD(3, nodeR, nodeP);
	Element elementE(4, node1, nodeR);
	Element elementF(5, nodeP, nodeP, eType::reactY);
	Element elementG(6, nodeP, nodeP, eType::reactX);
	Element elementH(7, nodeR, nodeR, eType::reactY);

	std::vector<Element> elementList = { elementA, elementB, elementC, elementD, elementE, elementF, elementG, elementH };

	auto former = Former(nodeList, elementList);

	std::cout << std::endl << "input matrix: " << std::endl << std::endl;
	auto inputVector = former.inputVec();

	Solver::output(inputVector);

	std::vector<double> forces = {
		xLoad, yLoad, 0, 0, 0, 0, 0, 0
	};

	std::cout << std::endl << "force matrix: " << std::endl << std::endl;
	Solver::output(forces);

	auto result = Solver::solveGaussian(inputVector, forces);

	std::cout << std::endl << "output matrix: " << std::endl << std::endl;
	Solver::output(result);

	elementA.force(result[0]);
	elementB.force(result[1]);
	elementC.force(result[2]);

	getchar();
	return 0;
}