//
// Created by NeSai on 16/11/2024.
//

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <vector>
#include <string>

namespace ArgumentParser {

    class ArgParser {

        class IntArgument {
        public:
            std::string name;
            char shortName = '_';
            int value = 0;
            bool hasDefault = false;
            bool wasUpdated = false;

            IntArgument* StoreValue(int newValue) {
                value = newValue;
                hasDefault = true;
                return this;
            }
        };

        class BoolArgument {
        public:
            std::string name;
            char shortName = '_';
            bool value = false;
            bool hasDefault = true;
            bool wasUpdated = false;

            BoolArgument* StoreValue(bool newValue) {
                value = newValue;
                hasDefault = true;
                return this;
            }
        };

        class StringArgument {
        public:
            std::string name;
            char shortName = '_';
            std::string value;
            bool hasDefault = false;
            bool wasUpdated = false;

            StringArgument* StoreValue(std::string newValue) {
                value = newValue;
                hasDefault = true;
                return this;
            }
        };

        std::vector<IntArgument> _intArguments;
        std::vector<BoolArgument> _boolArguments;
        std::vector<StringArgument> _stringArguments;

    public:
        std::string Name;

        bool Parse(std::vector<std::string> args);

        IntArgument* AddIntArgument(std::string paramName);
        IntArgument* AddIntArgument(char shortParamName, std::string paramName);

        BoolArgument* AddBoolArgument(std::string paramName);
        BoolArgument* AddBoolArgument(char shortParamName, std::string paramName);

        StringArgument* AddStringArgument(std::string paramName);
        StringArgument* AddStringArgument(char shortParamName, std::string paramName);

        int GetIntValue(std::string key);

        bool GetBoolValue(std::string key);

        std::string GetStringValue(std::string key);

        ArgParser(std::string name);
    };

}

#endif //ARGPARSER_H
