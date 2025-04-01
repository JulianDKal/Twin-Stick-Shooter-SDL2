#include "JsonParser.h"

using JsonObject = std::unordered_map<std::string, int>;

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

std::unordered_map<std::string, std::shared_ptr<Animation>> JsonParser::parse(const std::string &filePath)
{
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations;
    file.open(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return animations;
    }

    while (file.peek() != EOF)
    {
        skipWhiteSpace();
        getNextToken();
        switch (currentToken.type)
        {
        case CURLY_OPEN:
            level++;
            std::cout << "Level: " << level << std::endl;
            break;
        case CURLY_CLOSE:
            level--;
            std::cout << "Level: " << level << std::endl;
            if (level < 0)
            {
                std::cerr << "Error: Unmatched curly brace" << std::endl;
                return animations;
            }
            break;
        case QUOTES:
            if(level == 1){ //At animation name level, e.g. "ghost_animation"
                std::string key;
                while (file.peek() != '"')
                {
                    key += file.get();
                }
                file.get(); // consume the closing quote
                animations[key] = std::make_shared<Animation>(); //create animation for with entry name key
                currentAnimation = animations[key];
            }
            else if(level == 2){ //at value level, e.g. "frameTime" : "20"
                std::string key;
                while (file.peek() != '"')
                {
                    key += file.get();
                }
                file.get(); // consume the closing quote
                skipWhiteSpace();
                getNextToken(); // should be COLON
                if (currentToken.type == COLON)
                {
                    skipWhiteSpace(); //The next token should be NUMBER
                    //In case I add string values later
                    // if (currentToken.type == STRING)
                    // {
                    //     std::string value;
                    //     while (file.peek() != '"')
                    //     {
                    //         value += file.get();
                    //     }
                    //     file.get(); // consume the closing quote
                    //     animations[key] = std::make_shared<Animation>();
                    // }
                    
                    int value = 0;
                    while (isdigit(file.peek()))
                    {
                        value = value * 10 + (file.get() - '0');
                    }
                    if(key == "totalFrames") currentAnimation.get()->totalFrames = value;
                    else if(key == "frameTime") currentAnimation.get()->frameTime = value;                    
                }
            }
        case COLON:
            break;
        case STRING:
            break;
        case NUMBER:
            break;
        case UNKNOWN:
            break;
        default:
            SDL_LogError(0, "Critical Error parsing Json (JsonParser.cpp): Unknown token type at position %d", file.tellg());
            exit(1);
            break;
        }
    } 

    printParsedData(animations);
    return animations;
    
}

void JsonParser::getNextToken()
{
    current = file.get();
    switch (current)
    {
    case '{':
        currentToken.type = CURLY_OPEN;
        currentToken.value = "{";
        break;
    case '}':
        currentToken.type = CURLY_CLOSE;
        currentToken.value = "}";
        break;
    case '"':
        currentToken.type = QUOTES;
        currentToken.value = "\"";
        break;
    case ':':
        currentToken.type = COLON;
        currentToken.value = ":";
        break;
    case ',':
        currentToken.type = COLON;
        currentToken.value = ",";
        break;
    default:
        currentToken.type = UNKNOWN;
        break;
    }
    if(isdigit(current)) {
        currentToken.type = NUMBER;
        currentToken.value = current;
    }
    else if(isalpha(current)){
        currentToken.type = STRING;
        currentToken.value = current;
    }
}

void JsonParser::skipWhiteSpace()
{
    while (file.peek() == ' ' || file.peek() == '\n' || file.peek() == '\r' || file.peek() == '\t')
    {
        file.get();
    }
}

void JsonParser::printParsedData(std::unordered_map<std::string, std::shared_ptr<Animation>>& map) const
{
    for (const auto& pair : map)
    {
        std::cout << "Animation Name: " << pair.first << std::endl;
        if (pair.second)
        {
            std::cout << "  Total Frames: " << pair.second->totalFrames << std::endl;
            std::cout << "  Frame Time: " << pair.second->frameTime << std::endl;
        }
        else
        {
            std::cout << "  Error: Null Animation Pointer" << std::endl;
        }
    }
}

int JsonParser::getIntFromString(const std::string &str) const
{
    int value = 0;
    for(char c : str){
        if(isdigit(c)){
            value = value * 10 + (c - '0');
        }
        else{
            std::cerr << "Error: Invalid character in string: " << str << std::endl;
            return -1;
        }
    }
    return value;
}
