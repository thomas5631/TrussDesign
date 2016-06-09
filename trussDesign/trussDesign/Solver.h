#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

class Solver
{
	// The multiplication function accepts any pair of vectors and returns the product
	// An example input and output is as follows:
	//			INPUT						           OUTPUT
	//     [ 1    2    3 ]       [ 7    8 ]         [ 58    64 ]
	//                       x   [ 9    10]    =
	//     [ 4    5    6 ]       [ 11   12]         [ 139  154 ]
	template<typename T>
	static std::vector<std::vector<T>> vectorMultiply(const std::vector<std::vector<T> > &A, const std::vector<std::vector<T> > &B)
	{
		if (A[0].size() != B.size())
			throw std::runtime_error("Matrix multiplication not possible given that dimensions of matrix A = " + std::to_string(A.size()) +
				" x " + std::to_string(A[0].size()) + " and the dimensions of matrix B = " + std::to_string(B.size()) + " x " +
				std::to_string(B[0].size()));

		std::vector<std::vector<T>> C(A.size(), std::vector<T>(B[0].size()));
		for (unsigned i = 0; i < A.size(); ++i)
			for (unsigned j = 0; j < B[0].size(); ++j)
				for (unsigned k = 0; k < B.size(); ++k)
					C[i][j] += A[i][k] * B[k][j];

		return C;
	}

	template<typename T>
	static std::vector<T> vectorMultiply(const std::vector<std::vector<T> > &A, const std::vector<T> &B)
	{
		if (A[0].size() != B.size())
			throw std::runtime_error("Matrix multiplication not possible given that dimensions of matrix A = " + std::to_string(A.size()) +
				" x " + std::to_string(A[0].size()) + " and the dimensions of matrix B = " + std::to_string(B.size()) + " x " + "1");

		std::vector<T> C(B.size());
		for (unsigned i = 0; i < B.size(); ++i)
			for (unsigned j = 0; j < B.size(); ++j)
				C[i] += A[i][j] * B[j];
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
					for (unsigned i = 0; i < A[k].size(); ++i)
					{
						A[j][i] -= A[pos][i] * mfact;
					}
				}
			}
		}
		return A;
	}

	// The luDecomposer function accepts any (non sparse) square matrix, and returns a lower and upper decomposed matrix by reference.
	// Example input and output as follows:
	//         INPUT                                              OUTPUT
	//    [ 1    3    5 ]           [ 1.00000  0.00000  0.00000 ]       [ 2.00000  4.00000  7.00000 ]
	//    [ 2    4    7 ]           [ 0.50000  1.00000  0.00000 ]   +   [ 0.00000  1.00000  1.50000 ]
	//    [ 1    1    0 ]           [ 0.50000 -1.00000  1.00000 ]       [ 0.00000  0.00000 -2.00000 ]
	template<typename T>
	static void luDecomposer(const std::vector<std::vector<T> > &lhs, const std::vector<T> &rhs, std::vector<std::vector<double> > &lower,
		std::vector<std::vector<double> > &upper, std::vector<T> &B)
	{
		if (lhs[0].size() != lhs.size())                   //checks that the lhs matrix is square, if not, throws an error.
			throw std::runtime_error("Solution not possible for non square matrix. Dimensions of this matrix are: "
				+ std::to_string(lhs.size()) + " x " + std::to_string(lhs[0].size()));
		if (lhs.size() != rhs.size())                      //checks that the solution matrix dimensions are appropriate for input
			throw std::runtime_error("Solution not possible for non corresponding A and B matrix. Dimensions of this matrix A are: "
				+ std::to_string(lhs.size()) + " x " + std::to_string(lhs[0].size()) + " Dimension of matrix B is: " + std::to_string(rhs.size()));

		auto P = pivotise(lhs);
		B = vectorMultiply(P, rhs);

		auto A = vectorMultiply(P, lhs);

		std::vector<std::vector<T>> l(A.size(), std::vector<T>(A.size()));    //this temporary matrix holds the lower triangle before return
		std::vector<std::vector<T>> u(A.size(), std::vector<T>(A.size()));    //this temporary matrix holds the upper triangle before return

		for (unsigned i = 0; i < A.size(); i++) {
			l[i][i] = 1;                                       //initializes the descending vertical of l to 1
			for (unsigned j = 0; j < i + 1; j++) {             //this loop completes the calculation for the upper triangle
				T s1 = 0;
				for (unsigned k = 0; k < j; k++)
					s1 += u[k][i] * l[j][k];
				u[j][i] = A[j][i] - s1;
			}
			for (auto j = i; j < A.size(); j++) {              //this loop completes the calculation for the lower triangle
				T s2 = 0;
				for (unsigned k = 0; k < i; k++)
					s2 += u[k][i] * l[j][k];
				l[j][i] = (A[j][i] - s2) / u[i][i];
			}
		}
		upper = u;
		lower = l;
	}
public:
	// The solveGaussian function accepts any square coefficient matrix and corresponding resultant matrix to calculate the member matrix values
	// For example:
	//         INPUT            OUTPUT
	// [ 2    1 ]     [ 4 ]     [ 1 ]
	//             +         =
	// [ 1    4 ]     [ 9 ]     [ 2 ]
	static std::vector<double> solveGaussian(const std::vector<std::vector<double>> &A, const std::vector<double> &B)
	{
		std::vector<std::vector<double> > l, u;
		std::vector<double> b;
		luDecomposer(A, B, l, u, b);

		std::vector<double> z(A.size());       //this temporary matrix holds the result of l*z = b
		std::vector<double> x(A.size());       //this temporary matrix holds the result of u*x = z

		for (unsigned i = 0; i < l.size(); i++)
		{
			auto temp = 0.0;
			for (unsigned j = 0; j < i; j++)
				temp += l[i][j] * z[j];
			z[i] = (b[i] - temp) / l[i][i];
		}

		for (auto i = int(u.size())-1; i >= 0; --i)
		{
			auto temp = 0.0;
			for (auto j =int(u.size()-1); j > i; j--)
				temp += u[i][j] * x[j];
			x[i] = (z[i] - temp) / u[i][i]; //output x is not correct
		}

		return x;
	}


	// Outputs a matrix in readable form.
	static void output(std::vector<std::vector<double> > &myVec)
	{
		for (auto row : myVec)
		{
			for (auto val : row)
			{
				std::cout << std::setw(12) << val;
			}
			std::cout << "\n";
		}
	}

	static void output(std::vector<double> &myVec)
	{
		for (auto value : myVec)
		{
			std::cout << std::setw(12) << value << std::endl;
		}
	}
};
