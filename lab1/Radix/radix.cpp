#include <iostream>
#include <string>
#include <cctype>


struct InputParams
{
    std::string inputBase;
    std::string outputBase;
    std::string value;
};


InputParams ParseArgs(int argc, char* argv[]);
InputParams GetInputParams(char* argv[]);
int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);
void AssertArgCount(int argc);
void AssertBase(std::string base);
void ExitWithMessage(int exitCode = 1, const std::string& message = "ERROR");

int main(int argc, char* argv[])
{
}

InputParams ParseArgs(int argc, char* argv[])
{
    AssertArgCount(argc);
    return GetInputParams(argv);
}

InputParams GetInputParams(char* argv[])
{
    InputParams inputParams;

    AssertBase(argv[1]);
    inputParams.inputBase = argv[1];

    AssertBase(argv[2]);
    inputParams.outputBase = argv[2];
    inputParams.value = argv[3];

    return inputParams;
}


int StringToInt(const std::string& str, int radix, bool& wasError)
{
    return 0;
}

std::string IntToString(int n, int radix, bool& wasError)
{
    return "";
}

void AssertArgCount(int argc)
{
    const int argcNumber = 4;
    if (argc != argcNumber)
    {
        ExitWithMessage();
    }
}

void AssertBase(std::string base)
{

}

void ExitWithMessage(int exitCode, const std::string& message)
{
    std::cout << message << std::endl;
    exit(exitCode);
}
