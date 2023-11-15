#ifndef TOKENS_HPP
#define TOKENS_HPP

#include<string>
#include<vector>

enum TokenType {
    INT,    //0
	HEX,    //1
    CHAR,   //2
    STRING, //3
    
    MOV,    //4
    INC,    //5
    JMP,    //6
    ADD     //7
};


struct Token {
    TokenType tokenEnum;
            
	int intValue;
    char charValue;
    std::string stringValue;
        
    // Constructors for Token
    Token() : tokenEnum(TokenType::INT), stringValue(""), charValue('\0'), intValue(0) {}

    Token(TokenType type, const std::string& value) : tokenEnum(type), stringValue(value), charValue('\0'), intValue(0) {} 
    Token(TokenType type, char value) : tokenEnum(type), charValue(value), intValue(0) {}
    Token(TokenType type, int value) : tokenEnum(type), intValue(value) {} 
    Token(TokenType type) : tokenEnum(type), stringValue(""), charValue('\0'), intValue(0) {}

	~Token() {
        if (tokenEnum == TokenType::STRING) {
            stringValue.~basic_string();
        }
    }
};

typedef std::vector<Token> Tokens;

#endif // TOKENS_H
