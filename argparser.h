//
// Created by NeSai on 16/11/2024.
//

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <vector>
#include <string>
#include <map>

class argparser {

    std::map<std::string, std::string> params;  // Дикшионари хранящий пары ключ значение

public:
    bool Parse(std::vector<std::string> args);      // Парсим аргументы
    int GetIntegerValue(std::string key);           // Возвращаем значение параметра интом
    bool GetBoolValue(std::string key);             // Возвращаем значение параметра булом
    std::string GetStringValue(std::string key);    // Возвращаем значение параметра строкой
    void PrintAll();
};



#endif //ARGPARSER_H
