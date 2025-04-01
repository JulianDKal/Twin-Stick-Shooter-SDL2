#pragma once
#include <unordered_map>
#include <string>
#include "Animation.h"
#include <fstream>
#include <iostream>
#include <memory>

enum TokenType {
    CURLY_OPEN,
    CURLY_CLOSE,
    QUOTES,
    COLON,
    STRING,
    NUMBER,
    UNKNOWN
};

struct Token
{
    std::string value;
    TokenType type;
    std::string toString() const
    {
        switch (type)
        {
            case CURLY_OPEN: return "CURLY_OPEN";
            case CURLY_CLOSE: return "CURLY_CLOSE";
            case QUOTES: return "QUOTES";
            case COLON: return "COLON";
            case STRING: return "STRING";
            case NUMBER: return "NUMBER";
            default: return "UNKNOWN";
        }
    }

    Token() : value(""), type(UNKNOWN) {}
};

class JsonParser{
private:
    std::string key;
    std::string value;
    int level = 0;
    char current;
    Token currentToken;
    std::shared_ptr<Animation> currentAnimation;
    std::ifstream file;
public:
    JsonParser();
    ~JsonParser();

    std::unordered_map<std::string, std::shared_ptr<Animation>> parse(const std::string& filePath);
    void getNextToken();
    void skipWhiteSpace();
    void printParsedData(std::unordered_map<std::string, std::shared_ptr<Animation>>& map) const;
    int getIntFromString(const std::string& str) const;
};