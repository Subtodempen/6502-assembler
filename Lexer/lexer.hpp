#pragma once

#include"tokens.hpp"

#include <iostream>
#include <map>

class Lexer {
	public:
    	Lexer(const std::vector<std::string> lines);
    	~Lexer();

    	std::vector<Tokens> Tokenize();

	private:
		std::vector<std::string> lines;
		
		int lineIndex;
		int charIndex;

    	static std::map<std::string, TokenType> lookupTable;

    	char getCurr();

		void nextLine();

		void next();
    	void back();
    
		bool inBound();
    	bool isDigit();
    	bool isChar();
    	bool isWhiteSpace();
    
		Token tokenizeDigit();
		Token tokenizeInt();
		Token tokenizeHex();
		//token binary soon

		Token tokenizeKeyword();
		Token tokenizeChar();
		Token tokenizeString();
};
