#include <iostream>
#include <fstream>
#include <queue>
#include <array>
#include <memory>
#include <string>


const int FIELD_SIZE = 100;
const int NEIGHBOURS_COUNT = 4;
using Field = std::array<std::array<char, FIELD_SIZE>, FIELD_SIZE>;

struct IOParams
{
	std::shared_ptr<std::istream> input;
	std::shared_ptr<std::ostream> output;
};

struct Point
{
	int x;
	int y;
};

using NeighbourPoints = std::array<Point, NEIGHBOURS_COUNT>;

IOParams GetIOParams(int argc, char* argv[]);
IOParams GetIOFromFiles(char* argv[]);
Field GetField(std::istream& input);
void FillField(Field& field);
std::queue<Point> FillQueueByStartPoints(const Field& field);
NeighbourPoints GetNeighbourPoints(const Point& point);
bool IsPointEmpty(const Field& field, const Point& point);
bool IsHelpFlag(int argc, char* argv[]);
void AssertFileIsOpen(const std::istream& file);
void PrintHelp();

void PrintField(std::ostream& output, const Field& field);

int main(int argc, char* argv[])
{
	try
	{
		if (IsHelpFlag(argc, argv))
		{
			PrintHelp();
			return 0;
		}
		IOParams ioParams = GetIOParams(argc, argv);
		Field field = GetField(*ioParams.input);
		FillField(field);
		PrintField(*ioParams.output, field);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}

IOParams GetIOParams(int argc, char* argv[])
{
	const int console = 1;
	const int file = 3;

	switch (argc)
	{
	case console:
		return {
			std::make_shared<std::istream>(std::cin.rdbuf()),
			std::make_shared<std::ostream>(std::cout.rdbuf())
		};
	case file:
		return GetIOFromFiles(argv);
	default:
		throw std::invalid_argument("Wrong argument number");
	}
}

Field GetField(std::istream& input)
{
	const char eoln = '\n';
	const std::string allowedChars = "#O ";

	Field field{};
	Point point = {0, 0};
	char ch;
	while (input.get(ch) and point.y < FIELD_SIZE)
	{
		if (ch == eoln)
		{
			point.x = 0;
			point.y++;
			continue;
		}
		if (point.x >= FIELD_SIZE)
		{
			continue;
		}
		if (allowedChars.find(ch) == std::string::npos)
		{
			throw std::invalid_argument("ERROR");
		}
		field[point.y][point.x] = ch;
		point.x++;
	}
	return field;
}

void FillField(Field& field)
{
	const char filled = '.';

	std::queue<Point> queue = FillQueueByStartPoints(field);
	while (!queue.empty())
	{
		auto currentPoint = queue.front();
		NeighbourPoints neighborPoints = GetNeighbourPoints(currentPoint);

		for (auto& point : neighborPoints)
		{
			if (!IsPointEmpty(field, point))
			{
				continue;
			}
			field[point.y][point.x] = filled;
			queue.push(point);
		}
		queue.pop();
	}
}

std::queue<Point> FillQueueByStartPoints(const Field& field)
{
	const char startChar = 'O';
	std::queue<Point> queue;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (field[i][j] != startChar)
			{
				continue;
			}
			queue.push({j, i});
		}
	}
	return queue;
}

NeighbourPoints GetNeighbourPoints(const Point& point)
{
	return {{
		{point.x - 1, point.y},
		{point.x + 1, point.y},
		{point.x, point.y - 1},
		{point.x, point.y + 1}
	}};
}

bool IsPointEmpty(const Field& field, const Point& point)
{
	bool inLimits = point.x >= 0 and point.x < FIELD_SIZE and
					point.y >= 0 and point.y < FIELD_SIZE;
	if (!inLimits)
	{
		return false;
	}
	return field[point.y][point.x] == 0 or field[point.y][point.x] == ' ';
}

IOParams GetIOFromFiles(char* argv[])
{
	auto inputFile = std::make_shared<std::ifstream>(argv[1]);
	AssertFileIsOpen(*inputFile);
	auto outputFile = std::make_shared<std::ofstream>(argv[2]);

	return {
		inputFile,
		outputFile
	};
}

void PrintField(std::ostream& output, const Field& field)
{
	for (auto line : field)
	{
		for (auto ch : line)
		{
			if (ch == 0)
			{
				continue;
			}
			output << ch;
		}
		output << std::endl;
	}
}

bool IsHelpFlag(int argc, char* argv[])
{
	const int argcNumber = 2;
	const std::string helpFlag = "-h";

	return argc == argcNumber and argv[1] == helpFlag;
}

void AssertFileIsOpen(const std::istream& file)
{
	if (file.fail())
	{
		throw std::invalid_argument("Wrong input file");
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
