//
// Created by NeSai on 16/11/2024.
//

#include "ArgParser.h"
#include <regex>

using namespace ArgumentParser;

bool ArgParser::Parse(std::vector<std::string> args) {

    for (auto argument : _intArguments) {
        std::string temp = "-_=([^=]+)";
        temp[1] = argument->shortName;
        std::regex fullRegex("--" + argument->name + "=([^=]+)");
        std::regex shortRegex(temp);
        for (std::string arg : args) {
            if (!std::regex_match(arg, fullRegex) &&
                !std::regex_match(arg, shortRegex))
                continue;
            argument->value = std::stoi(arg.substr(arg.find('=')+1));
            argument->wasUpdated = true;
            break;
        }
    }

    for (auto& argument : _boolArguments) {
        std::regex fullRegex("--" + argument->name);
        std::regex shortRegex("-" + argument->shortName);
        for (std::string arg : args) {
            if (!std::regex_match(arg, fullRegex) &&
                !std::regex_match(arg, shortRegex))
                continue;
            argument->value = true;
            argument->wasUpdated = true;
            break;
        }
    }

    for (auto& argument : _stringArguments) {
        std::string temp = "-_=([^=]+)";
        temp[1] = argument->shortName;
        std::regex fullRegex("--" + argument->name + "=([^=]+)");
        std::regex shortRegex(temp);
        for (std::string arg : args) {
            if (!std::regex_match(arg, fullRegex) &&
                !std::regex_match(arg, shortRegex))
                continue;
            argument->value = arg.substr(arg.find('=')+1);
            argument->wasUpdated = true;
            break;
        }
    }

    for (auto argument : _intArguments)
        if (!argument->hasDefault && !argument->wasUpdated) {
            std::cout << argument->name << std::endl;
            return false;
        }

    for (auto argument : _boolArguments)
        if (!argument->hasDefault && !argument->wasUpdated) {
            std::cout << argument->name << std::endl;
            return false;
        }

    for (auto argument : _stringArguments)
        if (!argument->hasDefault && !argument->wasUpdated) {
            std::cout << argument->name << std::endl;
            return false;
        }

    return true;
}

ArgParser::IntArgument* ArgParser::AddIntArgument(std::string paramName) {
    auto* argument = new IntArgument;
    argument->name = paramName;
    _intArguments.push_back(argument);
    return argument;
}

ArgParser::IntArgument * ArgParser::AddIntArgument(char shortParamName, std::string paramName) {
    auto* argument = new IntArgument;
    argument->name = paramName;
    argument->shortName = shortParamName;
    _intArguments.push_back(argument);
    return argument;
}

ArgParser::BoolArgument * ArgParser::AddBoolArgument(std::string paramName) {
    auto* argument = new BoolArgument;
    argument->name = paramName;
    _boolArguments.push_back(argument);
    return argument;
}

ArgParser::BoolArgument * ArgParser::AddBoolArgument(char shortParamName, std::string paramName) {
    auto* argument = new BoolArgument;
    argument->name = paramName;
    argument->shortName = shortParamName;
    _boolArguments.push_back(argument);
    return argument;
}

ArgParser::StringArgument * ArgParser::AddStringArgument(std::string paramName) {
    auto* argument = new StringArgument;
    argument->name = paramName;
    _stringArguments.push_back(argument);
    return argument;
}

ArgParser::StringArgument * ArgParser::AddStringArgument(char shortParamName, std::string paramName) {
    auto* argument = new StringArgument;
    argument->name = paramName;
    argument->shortName = shortParamName;
    _stringArguments.push_back(argument);
    return argument;
}

int ArgParser::GetIntValue(std::string key) {
    return (*std::find_if(
        _intArguments.begin(),
        _intArguments.end(),
        [key](IntArgument* arg){return arg->name == key;}))->value;
}

bool ArgParser::GetBoolValue(std::string key) {
    return (*std::find_if(
        _boolArguments.begin(),
        _boolArguments.end(),
        [key](BoolArgument* arg){return arg->name == key;}))->value;
}

std::string ArgParser::GetStringValue(std::string key) {
    return (*std::find_if(
        _stringArguments.begin(),
        _stringArguments.end(),
        [key](StringArgument* arg){return arg->name == key;}))->value;
}

ArgParser::ArgParser(std::string name) {
    Name = name;
}
