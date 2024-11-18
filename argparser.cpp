//
// Created by NeSai on 16/11/2024.
//

#include "argparser.h"

#include <iostream>
#include <regex>
#include <exception>

bool argparser::Parse(std::vector<std::string> args) {

    const std::regex arg_expression(R"(--([^=]+)=([^=]+))");

    for (const auto& arg : args) {
        if (!std::regex_match(arg, arg_expression))
            continue;
        params[arg.substr(2, arg.find('=')-2)] = arg.substr(arg.find('=')+1);
    }

    return true;
}

int argparser::GetIntegerValue(std::string key) {
    return std::stoi(params[key]);
}

bool argparser::GetBoolValue(std::string key) {
    if (params[key] == "true")
        return true;
    return false;

}

std::string argparser::GetStringValue(std::string key) {
    return params[key];
}

void argparser::PrintAll() {
    for (auto &[key, value]: params) {
        std::cout << key << ": " << value << std::endl;
    }
}
