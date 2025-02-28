#include <iostream>
#include <sstream>
#include <stdexcept>
#include <array>
#include <fstream>
#include <memory>
#include <iomanip>
#include <cmath>


const int MATRIX_SIZE = 3;

using MatrixRow = std::array<double, MATRIX_SIZE>;
using Matrix3x3d = std::array<MatrixRow, MATRIX_SIZE>;
using Matrix2x2d = std::array<std::array<double, 2>, 2>;

std::shared_ptr<std::istream> GetInput(int argc, char* argv[]);
Matrix3x3d GetMatrix(const std::shared_ptr<std::istream>& input);
Matrix3x3d GetInvertedMatrix(const Matrix3x3d& sourceMatrix);
Matrix3x3d GetAlgebraicAdditionMatrix(const Matrix3x3d& matrix);
Matrix3x3d GetTransposedMatrix(const Matrix3x3d& matrix);
Matrix3x3d MultiplyMatrix(const Matrix3x3d& matrix, double number);
Matrix2x2d GetMinor(const Matrix3x3d& matrix, int row, int column);
MatrixRow GetMatrixRow(const std::string& rowString);
double GetAlgebraicAddition(const Matrix3x3d& matrix, int row, int column);
double GetMatrixDet(const Matrix3x3d& matrix);
void PrintMatrix(const Matrix3x3d& matrix);
bool IsHelpFlag(int argc, char* argv[]);

void AssertArgCount(int argc);
void AssertMatrixElementIndex(int index);
void AssertFullMatrix(int index);
void AssertDeterminant(double det);
void AssertFileIsOpen(const std::shared_ptr<std::istream>& file);
void AssertStream(const std::istringstream& stream);
void PrintHelp();

int main(int argc, char* argv[])
{
	try
	{
		if (IsHelpFlag(argc, argv))
		{
			PrintHelp();
			return 0;
		}
		auto input = GetInput(argc, argv);

		Matrix3x3d matrix = GetMatrix(input);
		Matrix3x3d invertMatrix = GetInvertedMatrix(matrix);
		PrintMatrix(invertMatrix);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}

std::shared_ptr<std::istream> GetInput(int argc, char* argv[])
{
	const int argcNumber = 2;

	if (argc == argcNumber)
	{
		auto inputFile = std::make_shared<std::ifstream>(argv[1]);
		AssertFileIsOpen(inputFile);
		return inputFile;
	}
	return std::make_shared<std::istream>(std::cin.rdbuf());
}

Matrix3x3d GetMatrix(const std::shared_ptr<std::istream>& input)
{
	Matrix3x3d matrix;
	std::string row;

	int rowIndex = 0;
	while (std::getline(*input, row))
	{
		AssertMatrixElementIndex(rowIndex);
		matrix[rowIndex] = GetMatrixRow(row);
		rowIndex++;
	}
	AssertFullMatrix(rowIndex);
	return matrix;
}

Matrix3x3d GetInvertedMatrix(const Matrix3x3d& sourceMatrix)
{
	double determinant = GetMatrixDet(sourceMatrix);
	AssertDeterminant(determinant);

	Matrix3x3d algebraicAdditionMatrix = GetAlgebraicAdditionMatrix(sourceMatrix);
	Matrix3x3d transposedMatrix = GetTransposedMatrix(algebraicAdditionMatrix);
	return MultiplyMatrix(transposedMatrix, 1 / determinant);
}

MatrixRow GetMatrixRow(const std::string& rowString)
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
	AssertStream(iss);
	AssertFullMatrix(columnIndex);
	return row;
}

double GetMatrixDet(const Matrix3x3d& matrix)
{
	double firstMinorValue = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	double secondMinorValue = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0];
	double thirdMinorValue = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];

	return matrix[0][0] * firstMinorValue - matrix[0][1] * secondMinorValue + matrix[0][2] * thirdMinorValue;
}

Matrix3x3d GetAlgebraicAdditionMatrix(const Matrix3x3d& matrix)
{
	Matrix3x3d algebraicAdditionMatrix;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			algebraicAdditionMatrix[i][j] = GetAlgebraicAddition(matrix, i, j);
		}
	}
	return algebraicAdditionMatrix;
}

Matrix3x3d GetTransposedMatrix(const Matrix3x3d& matrix)
{
	Matrix3x3d transposedMatrix;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			transposedMatrix[i][j] = matrix[j][i];
		}
	}
	return transposedMatrix;
}

Matrix3x3d MultiplyMatrix(const Matrix3x3d& matrix, double number)
{
	Matrix3x3d multipliedMatrix;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			multipliedMatrix[i][j] = matrix[i][j] * number;
		}
	}
	return multipliedMatrix;
}

double GetAlgebraicAddition(const Matrix3x3d& matrix, int row, int column)
{
	Matrix2x2d minor = GetMinor(matrix, row, column);
	return minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];
}

Matrix2x2d GetMinor(const Matrix3x3d& matrix, int row, int column)
{
	Matrix2x2d minor;

	int minorRowIndex = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		if (i == row)
		{
			continue;
		}
		int minorColumnIndex = 0;
		for (int j = 0; j < matrix[i].size(); j++)
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

void PrintMatrix(const Matrix3x3d& matrix)
{
	const int digitsAfterPoint = 3;

	std::cout << std::fixed << std::setprecision(digitsAfterPoint);
	for (auto& row : matrix)
	{
		for (auto& element : row)
		{
			std::cout << element << '\t';
		}
		std::cout << std::endl;
	}
}

bool IsHelpFlag(int argc, char* argv[])
{
	const int argcNumber = 2;
	const std::string helpFlag = "-h";

	return argc == argcNumber && argv[1] == helpFlag;
}

void AssertFileIsOpen(const std::shared_ptr<std::istream>& file)
{
	if (file->fail())
	{
		throw std::ios_base::failure("ERROR");
	}
}

void AssertArgCount(int argc)
{
	const int argcNumber = 2;
	if (argc != argcNumber)
	{
		throw std::invalid_argument("Wrong argument number");
	}
}

void AssertMatrixElementIndex(int index)
{
	if (index >= MATRIX_SIZE)
	{
		throw std::runtime_error("Invalid matrix format");
	}
}

void AssertFullMatrix(int index)
{
	if (index < MATRIX_SIZE)
	{
		throw std::runtime_error("Invalid matrix format");
	}
}

void AssertDeterminant(double det)
{
	if (std::fpclassify(det) == FP_ZERO)
	{
		throw std::runtime_error("Non-invertible");
	}
}

void AssertStream(const std::istringstream& stream)
{
	if (stream.fail() && !stream.eof())
	{
		throw std::invalid_argument("Invalid matrix");
	}
}

void PrintHelp()
{
	std::cout << "The replace program replaces all occurrences of a substring in a text file with another string,"
				 " and writes the result to an right_output file (different from the input)\n"
				 "The program supports two modes of operation:\n"
				 "1. Command line input:\n"
				 "   replace.exe <input file> <right_output file> <search string> <replace string>\n"
				 "2. Input via stdin:\n"
				 " * The first line is the desired string\n"
				 " * The second line is the replacement string\n"
				 " * Then the replacement text\n";
}