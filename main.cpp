#include <iostream>
#include "argparser.h"

// Пример програмных аргументов
// --name=Alexander --age=17 -- single=true

int main(int argc, char** argv) {

    // Собираем аргументы в вектор
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
        args.emplace_back(argv[i]);

    argparser parser;
    parser.Parse(args);

    // Пользуемся классом
    std::cout << "Hi " << parser.GetStringValue("name") << "!" << std::endl;
    std::cout << "You're " << parser.GetIntegerValue("age") << ", ";
    std::cout << "and " << (parser.GetBoolValue("single") ? "still don't " : "already ") << "have a girlfriend?" << std::endl;


    std::cout << std::endl;
    parser.PrintAll();

    return 0;
}
