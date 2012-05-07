// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__83AF816C_AA6B_4139_BE04_A2A0FFB0D15B__INCLUDED_)
#define AFX_MATRIX_H__83AF816C_AA6B_4139_BE04_A2A0FFB0D15B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <iostream>
using namespace std;
#include <assert.h>
#include <math.h>
#include <stdexcept>


template <class T>
class Matrix
{
	//constructors
public:
	Matrix(void);
public:
	Matrix(T** M, int row, int col);
public:
	Matrix(Matrix &m);
	//destructor
public:
	~Matrix(void);

	//members 
public:
	Matrix transpose(void);   //get a transpose matrix
public:
	Matrix identity(void);		//get the identity matrix of a square matrix
public:
	Matrix gaussjordan(Matrix &a, Matrix &b);  //get the linear solution by gauss-jordan elimination
public:
	Matrix inverse(void);    //get the inverse matrix of a square Matrix;
public:
	T** matrix;
public:
	int rows;
public:
	int cols;

	//overload operators
public:
	Matrix operator* (Matrix &);
public:
	Matrix operator+ (Matrix &);
public:
	Matrix operator- (Matrix &);
public:
	Matrix operator* (T alpha);

	//output 
public:
	void printmatrix(void);
};

template<class T>
Matrix<T>::Matrix(void)
{
	rows = cols = 0;
	matrix = NULL;
}

template<class T>
Matrix<T>::Matrix(T ** M, int y, int x)
{
	rows = y;
	cols = x;

	int i, j, k;
	matrix = new T*[rows];
	for (k=0; k<rows; k++)
	{
		matrix[k] = new T[cols];
	}

	for (j=0; j<rows; j++)
	{
		for (i=0; i<cols; i++)
		{
			matrix[j][i] = M[j][i];
		}
	}
}

template<class T>
Matrix<T>::Matrix(Matrix &m)
{
	rows = m.rows;
	cols = m.cols;

	int i, j, k;
	matrix = new T*[rows];
	for (k=0; k<rows; k++)
	{
		matrix[k] = new T[cols];
	}

	for (j=0; j<rows; j++)
	{
		for (i=0; i<cols; i++)
		{
			matrix[j][i] = m.matrix[j][i];
		}
	}
}

template<class T>
Matrix<T>::~Matrix()
{
	if (matrix)
	{
		for (int k=0; k<rows; k++)
		{
			delete[] matrix[k];
			matrix[k] = NULL;
		}
		delete[] matrix;
		matrix = NULL;
	}
}

//get the tanspose matrix
template<class T>
Matrix<T> Matrix<T>::transpose()
{
	int i,j,k;
	int trows = cols;
	int tcols = rows;

	T **temp = new T*[trows];
	for (k=0; k<trows; k++)
	{
		temp[k] = new T[tcols];
	}

	for (j=0; j<trows; j++)
	{
		for (i=0; i<tcols; i++)
		{
			temp[j][i] = matrix[i][j];
		}
	}

	Matrix<T> retmatrix(temp, trows, tcols);

	for (k=0; k<trows; k++)
	{
		delete[] temp[k];
		temp[k] = NULL;
	}
	delete[] temp;
	temp = NULL;

	return retmatrix;
}

//get identity matrix
template<class T>
Matrix<T> Matrix<T>::identity()
{
	//assert it is a square matrix
	assert(rows == cols);

	int i, j, k;

	T **temp = new T*[rows];
	for (k=0; k<rows; k++)
	{
		temp[k] = new T[cols];
	}

	for (j=0; j<rows; j++)
	{
		for (i=0; i<cols; i++)
		{
			if (j==i)
				temp[j][i] = (T)1.0;
			else
				temp[j][i] = (T)0.0;
		}
	}

	Matrix<T> retmatrix(temp, rows, cols);

	for (k=0; k<rows; k++)
	{
		delete[] temp[k];
		temp[k] = NULL;
	}
	delete[] temp;
	temp = NULL;

	return retmatrix;
}

//get gauss-jordan solution
template<class T>
Matrix<T> Matrix<T>::gaussjordan(Matrix<T> &a, Matrix<T> &b)
{
	T tmp;
	int i,j,k,l,ll;
	int icol, irow;
	int n = a.rows;
	int m = b.cols;
	double big, dum, pivinv;
	int *indxc = new int[n];
	int *indxr = new int[n];
	int *ipiv	 = new int[n];

	for (k=0; k<n; k++)
	{
		indxc[k] = 0;
		indxr[k] = 0;
		ipiv[k] = 0;		
	}

	for (i=0; i<n; i++)
	{
		big = 0.0;
		//get pivot element
		for (j=0; j<n; j++)
		{
			if (ipiv[j] != 1)
			{
				for (k=0; k<n; k++)
				{
					if (ipiv[k]==0)
						if (fabs(a.matrix[j][k]) >= big)
						{
							big = fabs(a.matrix[j][k]);
							irow= j;
							icol= k;
						}
				}
			}//if(ipiv[j]!=1)
		}//for(j=0; j<n; j++)
		++(ipiv[icol]);

		//interchange rows
		if (irow != icol)
		{
			for (l=0; l<n; l++)
			{
				//swap a[irow][l] and a[icol][l];
				tmp = a.matrix[irow][l];
				a.matrix[irow][l] = a.matrix[icol][l];
				a.matrix[icol][l] = tmp;
			}
			for (l=0; l<m; l++)
			{
				//swap b[irow][l] and b[icol][l];
				tmp = b.matrix[irow][l];
				b.matrix[irow][l] = b.matrix[icol][l];
				b.matrix[icol][l] = tmp;
			}
		}//if (irow != icol)
		indxr[i] = irow;
		indxc[i] = icol;

		//in case is a singular matrix
		if (a.matrix[icol][icol] == 0.0) 
			throw runtime_error("gaussjordan: singular matrix");

		pivinv = 1.0/a.matrix[icol][icol];
		a.matrix[icol][icol] = 1.0;
		for (l=0; l<n; l++)
			a.matrix[icol][l] *= pivinv;
		for (l=0; l<m; l++)
			b.matrix[icol][l] *= pivinv;
		//a.matrix[icol][icol] = 1.0;

		//reduce the rows, except for the pivot element
		for (ll=0; ll<n; ll++)
		{
			if (ll!=icol)
			{
				dum = a.matrix[ll][icol];
				a.matrix[ll][icol] = 0.0;
				for (l=0; l<n; l++)
					a.matrix[ll][l] -= a.matrix[icol][l]*dum;
				for (l=0; l<m; l++)
					b.matrix[ll][l] -= b.matrix[icol][l]*dum;
			}
		}//for (ll=0; ll<n; ll++)
	}

	//this is the end of the main loop over columns of the reduction. it only remains to unscramble the solution
	//in view of the column interchanges. we do this by interchanging pairs of columns in the reverse order that 
	//the permutation was built up.
	for (l=n-1; l>=0; l--)
	{
		if (indxr[l]!=indxc[l])
			for (k=0; k<n; k++)
			{
				tmp = a.matrix[k][indxr[l]];
				a.matrix[k][indxr[l]] = a.matrix[k][indxc[l]];
				a.matrix[k][indxc[l]] = tmp;
			}
	}// and we are done

	delete[] indxc;
	delete[] indxr;
	delete[] ipiv;
	return a;
}

//get inverse matrix of a square matrix
template<class T>
Matrix<T> Matrix<T>::inverse()
{
	assert(rows==cols);

	Matrix<T> temp(matrix, rows, cols);
	gaussjordan(temp, identity());

	return temp;
}

//overload * operator
template<class T>
Matrix<T> Matrix<T>::operator* (Matrix<T> &rmatrix)
{
	//assert
	assert(this->cols == rmatrix.rows);

	int i,j,k,t;
	int nrows = this->rows;
	int ncols = rmatrix.cols;

	T **temp = new T*[nrows];
	for (k=0; k<nrows; k++)
	{
		temp[k] = new T[ncols];
	}

	for (j=0; j<nrows; j++)
	{
		for (i=0; i<ncols; i++)
		{
			temp[j][i] = (T)0.0;
		}
	}

	for (j=0; j<nrows; j++)
	{
		for (i=0; i<ncols; i++)
		{
			for (t=0; t<rmatrix.rows; t++)
			{
				temp[j][i] += matrix[j][t]*rmatrix.matrix[t][i];
			}
		}
	}

	Matrix<T> retmatrix(temp, nrows, ncols);

	for (k=0; k<nrows; k++)
	{
		delete[] temp[k];
		temp[k] = NULL;
	}
	delete[] temp;
	temp = NULL;

	return retmatrix;
}

//overload operator -
template<class T>
Matrix<T> Matrix<T>::operator- (Matrix<T> &rmatrix)
{
	assert(rows==rmatrix.rows);
	assert(cols == rmatrix.cols);
	int i, j, k;

	T **temp = new T*[rows];
	for (k=0; k<rows; k++)
	{
		temp[k] = new T[cols];
	}

	for (j=0; j<rows; j++)
	{
		for (i=0; i<cols; i++)
		{
			temp[j][i] = matrix[j][i] - rmatrix.matrix[j][i];
		}
	}

	Matrix<T> retmatrix(temp, rows, cols);
	for (k=0; k<rows; k++)
	{
		delete[] temp[k];
		temp[k] = NULL;
	}
	delete[] temp;
	temp = NULL;

	return retmatrix;
}

//print matrix
template<class T>
void Matrix<T>::printmatrix()
{
	int i,j;
	for (j=0; j<rows; j++)
	{
		for (i=0; i<cols; i++)
		{
			cout<<matrix[j][i]<<"	";
		}
		cout<<endl;
	}
}

#endif // !defined(AFX_MATRIX_H__83AF816C_AA6B_4139_BE04_A2A0FFB0D15B__INCLUDED_)
