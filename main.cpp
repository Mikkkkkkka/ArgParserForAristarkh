#include <iostream>
#include "ArgParser.h"

// Пример програмных аргументов
// --name=Alexander --age=17 --single

int main(int argc, char** argv) {

    // Собираем аргументы в вектор
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
        args.emplace_back(argv[i]);

    ArgumentParser::ArgParser parser("DaBlyat'");
    parser.AddStringArgument("name");
    parser.AddIntArgument("age");
    parser.AddBoolArgument("single");
    if (!parser.Parse(args))
        return 5318008;


    // Пользуемся классом
    std::cout << "Hi " << parser.GetStringValue("name") << "!" << std::endl;
    std::cout << "You're " << parser.GetIntValue("age") << ", ";
    std::cout << "and " << (parser.GetBoolValue("single") ? "still don't " : "already ") << "have a girlfriend?" << std::endl;


    std::cout << std::endl;

    return 0;
}
