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

            if (argument->multiValue != -1) {
                argument->values.push_back(std::stoi(arg.substr(arg.find('=')+1)));
                if (argument->storedValues)
                    argument->storedValues->push_back(argument->values.back());
            }
            else {
                argument->value = std::stoi(arg.substr(arg.find('=')+1));
                if (argument->storedValue)
                    *argument->storedValue = argument->value;
            }

            argument->wasUpdated = true;
        }
    }

    for (auto& argument : _boolArguments) {
        std::regex fullRegex("--" + argument->name);
        std::regex shortRegex("-" + argument->shortName);
        for (std::string arg : args) {
            if (!std::regex_match(arg, fullRegex) &&
                !std::regex_match(arg, shortRegex))
                continue;

            if (argument->multiValue != -1) {
                argument->values.push_back(true);
                if (argument->storedValues)
                    argument->storedValues->push_back(argument->values.back());
            }
            else {
                argument->value = true;
                if (argument->storedValue)
                    *argument->storedValue = argument->value;
            }

            argument->wasUpdated = true;
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
            if (argument->multiValue != -1) {
                argument->values.push_back(arg.substr(arg.find('=')+1));
                if (argument->storedValues)
                    argument->storedValues->push_back(argument->values.back());
            }
            else {
                argument->value = arg.substr(arg.find('=')+1);
                if (argument->storedValue)
                    *argument->storedValue = argument->value;
            }

            argument->wasUpdated = true;
        }
    }

    for (auto argument : _intArguments) {
        if (!argument->hasDefault && !argument->wasUpdated)
            return false;
        if (argument->multiValue != -1 &&
            argument->multiValue > argument->values.size())
            return false;
    }

    for (auto argument : _boolArguments) {
        if (!argument->hasDefault && !argument->wasUpdated)
            return false;
        if (argument->multiValue != -1 &&
            argument->multiValue > argument->values.size())
            return false;
    }

    for (auto argument : _stringArguments) {
        if (!argument->hasDefault && !argument->wasUpdated)
            return false;
        if (argument->multiValue != -1 &&
            argument->multiValue > argument->values.size())
            return false;
    }

    return true;
}

ArgParser::Argument<int>& ArgParser::AddIntArgument(std::string paramName) {
    auto* argument = new Argument<int>;
    argument->name = paramName;
    _intArguments.push_back(argument);
    return *argument;
}

ArgParser::Argument<int>&  ArgParser::AddIntArgument(char shortParamName, std::string paramName) {
    auto* argument = new Argument<int>;
    argument->name = paramName;
    argument->shortName = shortParamName;
    _intArguments.push_back(argument);
    return *argument;
}

ArgParser::Argument<bool>& ArgParser::AddBoolArgument(std::string paramName) {
    auto* argument = new Argument<bool>;
    argument->name = paramName;
    _boolArguments.push_back(argument);
    return *argument;
}

ArgParser::Argument<bool>& ArgParser::AddBoolArgument(char shortParamName, std::string paramName) {
    auto* argument = new Argument<bool>;
    argument->name = paramName;
    argument->shortName = shortParamName;
    _boolArguments.push_back(argument);
    return *argument;
}

ArgParser::Argument<std::string>& ArgParser::AddStringArgument(std::string paramName) {
    auto* argument = new Argument<std::string>;
    argument->name = paramName;
    _stringArguments.push_back(argument);
    return *argument;
}

ArgParser::Argument<std::string>& ArgParser::AddStringArgument(char shortParamName, std::string paramName) {
    auto* argument = new Argument<std::string>;
    argument->name = paramName;
    argument->shortName = shortParamName;
    _stringArguments.push_back(argument);
    return *argument;
}

int ArgParser::GetIntValue(std::string key) {
    return (*std::find_if(
        _intArguments.begin(),
        _intArguments.end(),
        [key](Argument<int>* arg){return arg->name == key;}))->value;
}

int ArgParser::GetIntValue(std::string key, int index) {
    return (*std::find_if(
        _intArguments.begin(),
        _intArguments.end(),
        [key](Argument<int>* arg){return arg->name == key;}))->values.at(index);
}

bool ArgParser::GetBoolValue(std::string key) {
    return (*std::find_if(
        _boolArguments.begin(),
        _boolArguments.end(),
        [key](Argument<bool>* arg){return arg->name == key;}))->value;
}

bool ArgParser::GetBoolValue(std::string key, int index) {
    return (*std::find_if(
        _boolArguments.begin(),
        _boolArguments.end(),
        [key](Argument<bool>* arg){return arg->name == key;}))->values.at(index);
}

std::string ArgParser::GetStringValue(std::string key) {
    return (*std::find_if(
        _stringArguments.begin(),
        _stringArguments.end(),
        [key](Argument<std::string>* arg){return arg->name == key;}))->value;
}

std::string ArgParser::GetStringValue(std::string key, int index) {
    return (*std::find_if(
        _stringArguments.begin(),
        _stringArguments.end(),
        [key](Argument<std::string>* arg){return arg->name == key;}))->values.at(index);
}

ArgParser::ArgParser(std::string name) {
    Name = name;
}
