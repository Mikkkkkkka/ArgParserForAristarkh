//
// Created by NeSai on 16/11/2024.
//

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <vector>
#include <string>

namespace ArgumentParser {

    class ArgParser {

        template<typename T>
        class Argument {
        public:
            std::string name;
            char shortName = '_';
            T value;
            std::vector<T> values;
            T* storedValue = nullptr;
            std::vector<T>* storedValues = nullptr;
            int multiValue = -1;
            bool hasDefault = false;
            bool wasUpdated = false;

            Argument<T>& SetDefault(T defaultValue) {
                value = defaultValue;
                hasDefault = true;
                return *this;
            }

            Argument<T>& StoreValue(T& value) {
                storedValue = &value;
                return *this;
            }

            Argument<T>& MultiValue(size_t minArgsCount = 1) {
                multiValue = minArgsCount;
                return *this;
            }

            Argument<T>& StoreValues(std::vector<T>& values) {
                storedValues = &values;
                return *this;
            }
        };

        std::vector<Argument<int>*> _intArguments;
        std::vector<Argument<bool>*> _boolArguments;
        std::vector<Argument<std::string>*> _stringArguments;

    public:
        std::string Name;

        bool Parse(std::vector<std::string> args);

        Argument<int>& AddIntArgument(std::string paramName);
        Argument<int>& AddIntArgument(char shortParamName, std::string paramName);

        Argument<bool>& AddBoolArgument(std::string paramName);
        Argument<bool>& AddBoolArgument(char shortParamName, std::string paramName);

        Argument<std::string>& AddStringArgument(std::string paramName);
        Argument<std::string>& AddStringArgument(char shortParamName, std::string paramName);

        int GetIntValue(std::string key);
        int GetIntValue(std::string key, int index);

        bool GetBoolValue(std::string key);
        bool GetBoolValue(std::string key, int index);

        std::string GetStringValue(std::string key);
        std::string GetStringValue(std::string key, int index);

        ArgParser(std::string name);
    };

}

#endif //ARGPARSER_H
