#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Lexer {
	public:
    	enum TokenType {
        	INT,
        	CHAR,
        	STRING,
        	MOV,
        	INC,
        	JMP
    	};

    	struct Token {
        	TokenType tokenEnum;
            
			int intValue;
            char charValue;
            std::string stringValue;
        
        	// Constructors for Token
        	Token(TokenType type) : tokenEnum(type) {}

        	Token(TokenType type, int value) : tokenEnum(type), intValue(value) {}
        	Token(TokenType type, char value) : tokenEnum(type), charValue(value) {}
        	Token(TokenType type, const std::string& value) : tokenEnum(type), stringValue(value) {}

			~Token() {
        		if (tokenEnum == TokenType::STRING) {
            		stringValue.~basic_string();
        		}
    		}
    	};

    	typedef std::vector<Token> Tokens;

    	Lexer(const std::string& line);
    	~Lexer();

    	Tokens Tokenize();

	private:
    	std::string line;
    	int index;

    	static std::map<std::string, TokenType> lookupTable;

    	char getCurr();
    
		void next();
    	void back();
    
		bool inBound();
    	bool isDigit();
    	bool isChar();
    	bool isWhiteSpace();
    
	
		Token tokenizeKeyword();
		Token tokenizeChar();
		Token tokenizeString();
};