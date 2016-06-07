#pragma once
#include <vector>
#include <algorithm>
#include <functional>

class Solver
{
public:

	Solver()
	{
	}

	virtual ~Solver()
	{
	}

	template<typename T>
	static std::vector<std::vector<T>> vectorMultiply(const std::vector<std::vector<T> > &A, const std::vector<std::vector<T> > &B)
	{
		std::vector<std::vector<T>> C(A.size(), std::vector<T>(B[0].size()));
		for (unsigned i = 0; i < A.size(); ++i)
			for (unsigned j = 0; j < B[0].size(); ++j)
				for (unsigned k = 0; k < B.size(); ++k)
					C[i][j] += A[i][k] * B[k][j];

		return C;
	}


	// The transpose function accepts any square vector of vectors and returns the transpose matrix A_T
	// An example input and output is as follows:
	//			INPUT						OUTPUT
	//     [ 1    3    5 ]             [ 1    2    1 ]
	//     [ 2    4    7 ]             [ 3    4    1 ]
	//     [ 1    1    0 ]             [ 5    7    0 ]
	// This function is used to ensure stability in LU decomposition operations.
	template<typename T>
	static std::vector<std::vector<T>> transpose(const std::vector<std::vector<T> > &A)
	{
			std::vector<std::vector<T>> A_T(A[0].size(), std::vector<T>(A.size()));
			for (unsigned i = 0; i < A.size(); ++i)            //this loop iterates over the entire input matrix and
				for (unsigned j = 0; j < A[0].size(); ++j)     //populates the transpose matrix with a version of the 
					A_T[j][i] = A[i][j];                       //input matrix which has the rows and columns switched

			return A_T;
	}


	// The pivotise function accepts any square vector of vectors (non sparse) and returns the pivot matrix P
	// An example input and output is as follows:
	//			INPUT						OUTPUT
	//     [ 1    3    5 ]             [ 0    1    0 ]
	//     [ 2    4    7 ]             [ 1    0    0 ]
	//     [ 1    1    0 ]             [ 0    0    1 ]
	// This function is used to ensure stability in LU decomposition operations.
	template<typename T>
	static std::vector<std::vector<T>> pivotise(std::vector<std::vector<T> > A)
	{
		std::vector<unsigned> posHist;                         //this vector will hold the row position history of maxima in A_T

		for (unsigned k = 0; k < A.size(); k++)
		{
			std::vector<std::vector<T>> A_T = transpose(A);    //transpose the input vector for easier manipulation (pivoting is column dominant)

			for (unsigned q = 0; q < posHist.size(); q++)      //this loop iterates over the position history of maxima, setting all Transpose 
			{												   //row entries to zero if the row has been previously picked
				for (unsigned i = 0; i < A_T.size(); i++)
					A_T[i][posHist[q]] = 0.0;
			}

			unsigned pos = std::distance(A_T[k].begin(), std::max_element(A_T[k].begin(), A_T[k].end(),    //searches each column of the Transpose
					[](T a, T b) {return (abs(a) < abs(b)); }));                                           //to find the position of the maximum
			posHist.push_back(pos);                            //appends the result to the position history vector

			for (unsigned i = 0; i < A.size(); i++)            //normalizes the maximal row entries by dividing every entry by the maximum
				A[pos][i] = A[pos][i] / A_T[k][pos];


			for (unsigned j = 0; j < A.size(); j++)            //this loop subtracts the maximal row * the corresponding entry from each given row 
			{												   //(now unity in the max position) from each row in sequence.
				if (j != pos)
				{
					auto mfact = A[j][k];
					for (auto i = 0; i < A[k].size(); ++i)
					{
						A[j][i] -= A[pos][i] * mfact;
					}
				}
			}
		}
		return A;
	}

	template<typename T>
	static void luDecomposer(std::vector<std::vector<T> > &A, std::vector<std::vector<double> > &lower, std::vector<std::vector<double> > &upper)
	{
		lower(A[0].size(), std::vector<T>(A.size()));
		upper(A[0].size(), std::vector<T>(A.size()));

		for (unsigned i = 0; i < A.size(); i++)
		{
			for (unsigned j = 0; j < A[i].size(); j++)
			{
				upper[i][j] = (A[i][j]);
				for (unsigned k = 0; k < i; k++)
				{
					upper[i][j] -= upper[k][j] * lower[i][k];
				}
				lower[i][j] = (1 / upper[j][j]) * A[i][j];
				for (unsigned k = 0; k < j; k++)
				{
					lower[i][j] -= (1 / upper[j][j]) * upper[k][j] * lower[i][k];
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
				std::cout << std::setw(10) <<val;
			}
			std::cout << "\n";
		}
	}
};
