#include <iostream>
#include <sstream>
#include <stdexcept>
#include <array>


const int matrixSize = 3;

using MatrixRow = std::array<double, matrixSize>;
using Matrix3x3d = std::array<MatrixRow, matrixSize>;
using Matrix2x2d = std::array<std::array<double, 2>, 2>;

Matrix3x3d GetMatrix(std::istream& input);
Matrix3x3d GetInvertMatrix(Matrix3x3d sourceMatrix);
MatrixRow GetMatrixRow(std::string rowString);
Matrix2x2d GetMinor(Matrix3x3d matrix, int row, int column);
double GetMatrixDet(Matrix3x3d matrix);
void PrintMatrix(Matrix3x3d matrix);
void AssertMatrixElementIndex(int index);
void AssertFullMatrix(int index);

int main(int argc, char* argv[])
{
	try
	{
		Matrix3x3d matrix = GetMatrix(std::cin);
		Matrix3x3d invertMatrix = GetInvertMatrix(matrix);
		PrintMatrix(invertMatrix);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}

Matrix3x3d GetMatrix(std::istream& input)
{
	Matrix3x3d matrix;
	std::string row;

	int rowIndex = 0;
	while (std::getline(input, row))
	{
		AssertMatrixElementIndex(rowIndex);

		matrix[rowIndex] = GetMatrixRow(row);
		rowIndex++;
	}
	AssertFullMatrix(rowIndex);
	return matrix;
}

MatrixRow GetMatrixRow(std::string rowString)
{
	MatrixRow row;
	int columnIndex = 0;
	double number;

	std::istringstream iss(rowString);
	while (iss >> number)
	{
		AssertMatrixElementIndex(columnIndex);
		row[columnIndex] = number;
		if (iss.peek() == '\t')
		{
			iss.ignore();
		}
		columnIndex++;
	}
	AssertFullMatrix(columnIndex);
	return row;
}

double GetAlgebraicAddition(Matrix3x3d matrix, int row, int column)
{
	Matrix2x2d minor = GetMinor(matrix, row, column);
	return minor[0][0] + minor[1][1] - minor[0][1] - minor[1][0];
}

Matrix3x3d GetInvertMatrix(Matrix3x3d sourceMatrix)
{
	Matrix3x3d invertMatrix;

	double determinant = GetMatrixDet(sourceMatrix);
	std::cout << "Det A = " << determinant << std::endl;
	for (size_t i = 0; i < sourceMatrix.size(); i++)
	{
		for (size_t j = 0; j < sourceMatrix[i].size(); j++)
		{
			int addition = GetAlgebraicAddition(sourceMatrix, i, j);
			invertMatrix[j][i] = addition / determinant;
		}
	}
	return invertMatrix;
}

double GetMatrixDet(Matrix3x3d matrix)
{
	// TODO: переписать
	double firstMinor = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	double secondMinor = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0];
	double thirdMinor = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];

	return matrix[0][0] * firstMinor - matrix[0][1] * secondMinor + matrix[0][2] * thirdMinor;
}

Matrix2x2d GetMinor(Matrix3x3d matrix, int row, int column)
{
	Matrix2x2d minor;

	int minorRowIndex = 0;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		if (i == row)
		{
			continue;
		}
		int minorColumnIndex = 0;
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (j == column)
			{
				continue;
			}
			minor[minorRowIndex][minorColumnIndex] = matrix[i][j];
			minorColumnIndex++;
		}
		minorRowIndex++;
	}
	return minor;
}

void AssertMatrixElementIndex(int index)
{
	if (index >= matrixSize)
	{
		throw std::runtime_error("ERROR");
	}
}

void AssertFullMatrix(int index)
{
	if (index < matrixSize)
	{
		throw std::runtime_error("ERROR");
	}
}

void PrintMatrix(Matrix3x3d matrix)
{
	for (auto& row : matrix)
	{
		for (auto& element : row)
		{
			std::cout << element << '\t';
		}
		std::cout << std::endl;
	}
}