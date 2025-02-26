#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>


struct InputParams
{
    std::string searchString;
    std::string replacementString;
    std::istream& input;
    std::ostream& output;
};


InputParams ParseArgs(int argc, char* argv[]);
InputParams GetInputParamsFromStdin(std::istream& input);
InputParams GetInputParamsFromArgv(char* argv[]);
std::string ReplaceString(const std::string& subject,
                          const std::string& searchString,
                          const std::string& replacementString);
void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString);
void AssertHelpFlag(const std::string& flag);
void AssertFileIsOpen(std::ifstream& file);
void PrintHelp();


// TODO: exceptions
int main(int argc, char* argv[])
{
	try
	{
		auto inputParams = ParseArgs(argc, argv);

		CopyStreamWithReplacement(inputParams.input, inputParams.output,
									inputParams.searchString, inputParams.replacementString);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}

InputParams ParseArgs(int argc, char* argv[])
{
    const int stdinArgumentsCount = 1;
    const int helpArgumentsCount = 2;
    const int cliArgumentsCount = 5;

	if (argc == stdinArgumentsCount)
    {
        return GetInputParamsFromStdin(std::cin);
    }
	else if (argc == helpArgumentsCount)
    {
        AssertHelpFlag(argv[1]);
        PrintHelp();
		throw std::exception();
    }
	else if (argc != cliArgumentsCount)
    {
		throw std::invalid_argument("ERROR");
    }
    return GetInputParamsFromArgv(argv);
}

InputParams GetInputParamsFromStdin(std::istream& input)
{
	// TODO: избавиться от enum и цикла
    std::string searchString;
	std::string replacementString;

    if (!std::getline(input, searchString) ||
		!std::getline(input, replacementString))
    {
		throw std::runtime_error("ERROR");
    }

    return {
		searchString,
		replacementString,
		std::cin,
		std::cout
	};
}

InputParams GetInputParamsFromArgv(char* argv[])
{
	std::ifstream inputFile(argv[1]);
	std::ofstream outputFile( argv[2]);
	AssertFileIsOpen(inputFile);

	std::string searchString = argv[3];
	std::string replacementString = argv[4];

    return {
		searchString,
		replacementString,
		inputFile,
		outputFile
	};
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString)
{
	// TODO: избавиться от "cin" и "cout"
    std::string line;
    if (!std::getline(input, line))
    {
        throw std::runtime_error("ERROR");
    }
    do
    {
        output << ReplaceString(line, searchString, replacementString) << std::endl;
    } while (std::getline(input, line));
}

std::string ReplaceString(const std::string& subject,
                          const std::string& searchString,
                          const std::string& replacementString)
{
    if (searchString.empty())
    {
        return subject;
    }

    size_t pos = 0;
    std::string result;
    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        result.append(subject, pos, foundPos - pos);
        if (foundPos == std::string::npos)
        {
            return result;
        }
        result.append(replacementString);
        pos = foundPos + searchString.length();
    }
    return result;
}

void AssertHelpFlag(const std::string& flag)
{
    const std::string helpFlag = "-h";
    if (flag != helpFlag)
    {
		throw std::invalid_argument("ERROR");
    }
}

void AssertFileIsOpen(std::ifstream& file)
{
    if (file.fail())
    {
		throw std::ios_base::failure("ERROR");
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
