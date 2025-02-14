#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>


struct InputParams
{
    std::string searchString;
    std::string replacementString;
    std::string input;
    std::string output;
};


InputParams ParseArgs(int argc, char* argv[]);
InputParams GetInputParamsFromStdin(std::istream& input);
InputParams GetInputParamsFromArgv(char* argv[]);
std::string ReplaceString(const std::string& subject,
                          const std::string& searchString,
                          const std::string& replacementString);
void CopyFileWithReplacement(std::string& input, std::string& output,
                             const std::string& searchString, const std::string& replacementString);
void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString);
void ExitWithMessage(int exitCode = 1, const std::string& message = "ERROR");
void AssertHelpFlag(const std::string& flag);
void AssertFileIsOpen(std::ifstream& file);
void PrintHelp();


int main(int argc, char* argv[])
{
    auto inputParams = ParseArgs(argc, argv);

    CopyFileWithReplacement(inputParams.input,
                            inputParams.output,
                            inputParams.searchString,
                            inputParams.replacementString);
    return 0;
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
        ExitWithMessage(0, "");
    }
    else if (argc != cliArgumentsCount)
    {
        ExitWithMessage();
    }
    return GetInputParamsFromArgv(argv);
}

InputParams GetInputParamsFromStdin(std::istream& input)
{
    enum InputState
    {
        searchString,
        replacementString,
    };

    InputParams inputParams;
    inputParams.input = "cin";
    inputParams.output = "cout";

    InputState inputState = searchString;
    std::string line;
    if (!std::getline(input, line))
    {
        ExitWithMessage(0);
    }
    do
    {
        switch (inputState)
        {
            case searchString:
                inputParams.searchString = line;
                inputState = replacementString;
                break;
            case replacementString:
                inputParams.replacementString = line;
                return inputParams;
        }
    } while (std::getline(input, line));

    ExitWithMessage(0);
    return inputParams;
}

InputParams GetInputParamsFromArgv(char* argv[])
{
    InputParams inputParams;

    inputParams.input = argv[1];
    inputParams.output = argv[2];
    inputParams.searchString = argv[3];
    inputParams.replacementString = argv[4];
    return inputParams;
}

void CopyFileWithReplacement(std::string& input, std::string& output,
                             const std::string& searchString, const std::string& replacementString)
{
    if (input == "cin" && output == "cout")
    {
        CopyStreamWithReplacement(std::cin, std::cout, searchString, replacementString);
        return;
    }
    std::ifstream inputFile(input);
    AssertFileIsOpen(inputFile);
    std::ofstream outputFile(output);

    CopyStreamWithReplacement(inputFile,outputFile,
                              searchString, replacementString);
    outputFile.flush();
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString)
{
    std::string line;

    if (!std::getline(input, line))
    {
        ExitWithMessage(0);
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
        ExitWithMessage();
    }
}

void AssertFileIsOpen(std::ifstream& file)
{
    if (file.fail())
    {
        ExitWithMessage();
    }
}

void ExitWithMessage(int exitCode, const std::string& message)
{
    std::cout << message << std::endl;
    exit(exitCode);
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
