#pragma once
#include <vector>
#include <algorithm>

class Solver
{
public:

	Solver()
	{
	}

	virtual ~Solver()
	{
	}


	static bool abs_compare(int a, int b)
	{
		return (abs(a) < abs(b));
	}


	template<typename T>
	static void pivotise(std::vector<std::vector<T> > &A)
	{
		//initializing row and column max pos. vectors
		std::vector<std::vector<T>> A_T(A[0].size(), std::vector<T>(A.size()));
		
		for (unsigned k = 0; k < A.size(); k++)
		{
			for (unsigned i = 0; i < A.size(); ++i)
				for (unsigned j = 0; j < A[0].size(); ++j)
					A_T[j][i] = A[i][j];

			unsigned pos;
			if (k == A.size() - 1)
				pos = A.size() - 1;
			else
				pos = std::distance(A_T[k].begin(), std::max_element(A_T[k].begin(), A_T[k].end(), abs_compare));
			//std::cout << "position: " << pos << std::endl;
			auto r = A[pos][k];

			for (unsigned i = 0; i < A.size(); i++)
				A[pos][i] = A[pos][i] / r;

			//output(A); //issue with 3x3

			for (unsigned j = 0; j < A.size(); j++)
			{
				
				if(j != pos)
				{
					auto mfact = A[j][k];
					for (auto i = 0; i < A[k].size(); ++i)
					{
						A[j][i] -= A[pos][i] * mfact;
					}
				}
			}
		}

		

		//auto r = std::max_element(A_T[0].begin(), A_T[0].end());
		//std::cout<< "Max for this loop: " << r[0] << std::endl;

		//for (auto i = 0; i < A[0].size(); ++i)
		//	A[0][i] = A[0][i] / r[0];

		//std::cout << std::endl;
		//output(A);

		//for (unsigned j = 1; j < A.size(); j++)
		//{
		//	auto mfact = A[j][0];
		//	for (auto i = 0; i < A[0].size(); ++i)
		//	{
		//		A[j][i] -= A[0][i] * mfact;
		//	}
		//}
		//	std::cout << std::endl;
		//	output(A);

	}

	template<typename T>
	static void lu(std::vector<std::vector<T> > &a, std::vector<std::vector<double> > &l, std::vector<std::vector<double> > &u)
	{
		l = {
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		};

		u = {
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		};

		for (unsigned i = 0; i < a.size(); i++)
		{

			for (unsigned j = 0; j < a[0].size(); j++)
			{
				u[i][j] = (a[i][j]);
				for (unsigned k = 0; k < i; k++)
				{
					u[i][j] -= u[k][j] * l[i][k];
				}
				l[i][j] = (1 / u[j][j]) * a[i][j];
				for (unsigned k = 0; k < j; k++)
				{
					l[i][j] -= (1 / u[j][j]) * u[k][j] * l[i][k];
				}
			}
		}
	}

	template<typename T>
	static void output(std::vector<std::vector<T> > &myVec)
	{
		for (auto row : myVec)
		{
			for (auto val : row)
			{
				std::cout << val << ",\t";
			}
			std::cout << "\n";
		}
	}
};
