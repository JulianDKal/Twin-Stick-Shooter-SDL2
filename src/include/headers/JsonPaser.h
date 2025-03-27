#pragma once
#include <string>

class JsonPaser{
public:
    JsonPaser(std::string filePath);
    ~JsonPaser();
    void parseJson(std::string filePath);
    void writeJson(std::string filePath);
};