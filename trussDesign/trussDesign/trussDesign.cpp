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

	/*double a[6][6] = {
		{ -1, -sin(PI / 3), 0, 0, 0, 0 },
		{ 0, cos(PI / 3), 0, 0, 0, 0 },
		{1, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, -1, 0},
		{0, sin(PI/3), 0, 0, 0, 1},
		{0, -cos(PI/3), -1, 0, 0, 0}
	};*/

	std::vector<std::vector<double> > myVec = {
		{11, 9, 24, 2},
		{1, 5, 2, 6},
		{3, 17, 18, 1},
		{2, 5, 7, 1}
	};

	//std::vector<std::vector<double> > myVec = {
	//	{ 1, 3, 5 },
	//	{ 2, 4, 7 },
	//	{ 1, 1, 0 }

	//};



	std::cout << std::endl << "The a matrix: " << std::endl << std::endl;
	Solver::output(myVec);

	auto pivot = Solver::pivotise(myVec);
	
	std::cout << std::endl << "The pivot matrix: " << std::endl << std::endl;
	Solver::output(pivot);

	std::cout << std::endl << "The a matrix: " << std::endl << std::endl;
	Solver::output(myVec);

	//std::vector<std::vector<double> > u, l;


	//Solver::lu(myVec, l, u);
	//std::cout << std::endl << "The l matrix: " << std::endl << std::endl;
	//Solver::output(l);
	//std::cout << std::endl << "The u matrix: " << std::endl << std::endl;
	//Solver::output(u);

	//auto fBeam = -yLoad / element1.yLength();
	//auto fBeam2 = -xLoad / element1.xLength();

	//std::cout << "The xBeam calc yields: " << fBeam << std::endl;
	//std::cout << "The yBeam calc yields: " << fBeam2 << std::endl;

	//auto buckingLoad = element1.bucklingload();

	//std::cout << "The bucking load of this beam is: " << buckingLoad << std::endl;


	

	getchar();
	return 0;
}

//using namespace std;
//int main()
//{
//	int n, i, j, k;
//	cout.precision(4);        //set precision
//	cout.setf(ios::fixed);
//	cout << "\nEnter the no. of equations\n";
//	cin >> n;                //input the no. of equations
//	float a[n][n + 1], x[n];        //declare an array to store the elements of augmented-matrix    
//	cout << "\nEnter the elements of the augmented-matrix row-wise:\n";
//	for (i = 0; i<n; i++)
//		for (j = 0; j <= n; j++)
//			cin >> a[i][j];    //input the elements of array
//	for (i = 0; i<n; i++)                    //Pivotisation
//		for (k = i + 1; k<n; k++)
//			if (a[i][i]<a[k][i])
//				for (j = 0; j <= n; j++)
//				{
//					double temp = a[i][j];
//					a[i][j] = a[k][j];
//					a[k][j] = temp;
//				}
//	cout << "\nThe matrix after Pivotisation is:\n";
//	for (i = 0; i<n; i++)            //print the new matrix
//	{
//		for (j = 0; j <= n; j++)
//			cout << a[i][j] << setw(16);
//		cout << "\n";
//	}
//	for (i = 0; i<n - 1; i++)            //loop to perform the gauss elimination
//		for (k = i + 1; k<n; k++)
//		{
//			double t = a[k][i] / a[i][i];
//			for (j = 0; j <= n; j++)
//				a[k][j] = a[k][j] - t*a[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
//		}
//
//	cout << "\n\nThe matrix after gauss-elimination is as follows:\n";
//	for (i = 0; i<n; i++)            //print the new matrix
//	{
//		for (j = 0; j <= n; j++)
//			cout << a[i][j] << setw(16);
//		cout << "\n";
//	}
//	for (i = n - 1; i >= 0; i--)                //back-substitution
//	{                        //x is an array whose values correspond to the values of x,y,z..
//		x[i] = a[i][n];                //make the variable to be calculated equal to the rhs of the last equation
//		for (j = 0; j<n; j++)
//			if (j != i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
//				x[i] = x[i] - a[i][j] * x[j];
//		x[i] = x[i] / a[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
//	}
//	cout << "\nThe values of the variables are as follows:\n";
//	for (i = 0; i<n; i++)
//		cout << x[i] << endl;            // Print the values of x, y,z,....    
//	return 0;
//}