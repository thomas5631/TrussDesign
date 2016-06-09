// trussDesign.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Node.h"
#include "Element.h"
#include "Solver.h"
#include <algorithm>

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
	auto yLoad = load*cos(angle);

	std::cout << "The x component of the load is: " << xLoad << std::endl;
	std::cout << "The y component of the load is: " << yLoad << std::endl;


	Node node0(xPos, yPos);
	Node nodeP(0.00, 0.00);
	Node nodeR(2.40, 4.80);

	Element elementA(nodeP, node0);
	Element elementB(nodeR, node0);
	Element elementC(nodeP, nodeR);

	//std::vector<std::vector<double> > myVec = {
	//	{ -1, -sin(PI / 3), 0, 0, 0, 0 },
	//	{ 0, cos(PI / 3), 0, 0, 0, 0 },
	//	{1, 0, 0, 1, 0, 0},
	//	{0, 0, 1, 0, -1, 0},
	//	{0, sin(PI/3), 0, 0, 0, 1},
	//	{0, -cos(PI/3), -1, 0, 0, 0}
	//};

	//std::vector<double> forces = {
	//	5.345, -9.258, 0, 0, 0, 0
	//};

	std::vector<std::vector<double> > myVec = {
		{2, 1},
		{1, 4}
	};

	std::vector<double> forces = {
		4, 9
	};

	std::cout << std::endl << "input matrix: " << std::endl << std::endl;
	Solver::output(myVec);

	auto result = Solver::solveGaussian(myVec, forces);

	std::cout << std::endl << "output matrix: " << std::endl << std::endl;
	Solver::output(result);


	//auto fBeam = -yLoad / element1.yLength();
	//auto fBeam2 = -xLoad / element1.xLength();

	//std::cout << "The xBeam calc yields: " << fBeam << std::endl;
	//std::cout << "The yBeam calc yields: " << fBeam2 << std::endl;

	//auto buckingLoad = element1.bucklingload();

	//std::cout << "The bucking load of this beam is: " << buckingLoad << std::endl;


	

	getchar();
	return 0;
}