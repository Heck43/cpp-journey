#include "Matrix.h"
#include <stdexcept>

void Matrix::allocate()
{
	data = new int* [rows];
	for (int i = 0; i < rows; i++) {
		data[i] = new int[cols];
		for (int j = 0; j < cols; j++) {
			data[i][j] = 0;
		}
	}
}

void Matrix::freeMemory()
{
	if (data != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		data = nullptr;
	}
}



void Matrix::copyFrom(const Matrix& other)
{
	rows = other.rows;
	cols = other.cols;

	allocate();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
}

void Matrix::checkSameSize(const Matrix& other) const
{
	if (rows != other.rows || cols != other.cols)
	{
		throw invalid_argument("Размеры матриц не равны!");
	}
}


Matrix::Matrix(int rows, int cols)
{
	if (rows <= 0 || cols <= 0)
	{
		throw invalid_argument("Размер матрицы должен быть положительным!!");
	}
	this->rows = rows;
	this->cols = cols;
	this->data = nullptr;


	allocate();
}

Matrix::Matrix(const Matrix& other)
{
	data = nullptr;
	copyFrom(other);
}

Matrix::~Matrix()
{
	freeMemory();
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		freeMemory();
		copyFrom(other);
	}

	return *this;
}

int Matrix::getRows() const
{
	return rows;
}


int Matrix::getCols() const
{
	return cols;
}
int& Matrix::operator()(int row, int col)
{
	if (row < 0 || row >= rows || col < 0 || col > cols)
	{
		throw out_of_range("индекс матрицы выходит за пределы допустимого диапазона");
	}
	return data[row][col];
}
int Matrix::operator()(int row, int col) const 
{
	if (row < 0 || row >= rows || col < 0 || col > cols)
	{
		throw out_of_range("индекс матрицы выходит за пределы допустимого диапазона");	}
	return data[row][col];
}

Matrix Matrix::operator+(const Matrix& other) const
{
	checkSameSize(other);

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.data[i][j] = data[i][j] + other.data[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other) const 
{
	checkSameSize(other);

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.data[i][j] = data[i][j] - other.data[i][j];
		}
	}
	return result;
}
Matrix Matrix::operator*(const Matrix& other) const
{
	if(cols != other.rows)
	{
		throw invalid_argument("Размеры матриц несовместимы для умножения");
	}

	Matrix result(rows, other.cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < other.cols; j++)
		{
			result.data[i][j] = 0;
			for (int k = 0; k < cols; k++)
			{
				result.data[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::operator*(int value) const 
{
	Matrix result(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.data[i][j] = data[i][j] * value;
		}
	}
	return result;
}


Matrix Matrix::operator!() const
{
	Matrix result(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.data[i][j] = data[i][j];
		}
	}
	return result;
}

bool Matrix::operator==(const Matrix& other) const
{
	if (rows != other.rows || cols != other.cols)
	{
		return false;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (rows != other.rows || cols != other.cols)
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
	return !(*this == other);
}

Matrix operator*(int value, const Matrix& matrix)
{
	return matrix * value;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			os << matrix.data[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			is >> matrix.data[i][j];
		}
		return is;
	}
}