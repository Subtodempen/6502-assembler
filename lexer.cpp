#include"lexer.hpp"

// Initialize and populate the static map in the source file
std::map<std::string, Lexer::TokenType> Lexer::lookupTable = {
    {"mov", TokenType::MOV},
    {"inc", TokenType::INC},
    {"jmp", TokenType::JMP},
};

Lexer::Lexer(const std::string& line) : line(line), index(0) {}

Lexer::~Lexer(){}

Lexer::Tokens Lexer::Tokenize(){
	Lexer::Tokens temp;
	
	while(inBound()){
		if(isDigit()){
			std::cout<<"digit";
		}
	
		if(isChar()){
			temp.push_back(tokenizeChar());
		}
	}

	return temp;
}

inline char Lexer::getCurr(){
	if(inBound()) //safety 👍
		return line[index];

	return ' ';
}

inline void Lexer::next(){
	index++;
}

inline void Lexer::back(){
	index--;
}

inline bool Lexer::inBound(){
	return (index < line.length());
}

bool Lexer::isDigit(){
	return std::isdigit(static_cast<unsigned char>(line[index]));
}

bool Lexer::isWhiteSpace(){
	return std::isspace(static_cast<unsigned char>(line[index]));
}

bool Lexer::isChar(){
	return (!isDigit() && !isWhiteSpace());
}


Lexer::Token Lexer::tokenizeChar(){
	next(); //makes sure its not a string if so dont do it
	
	if(isChar()){
		back();

		return tokenizeKeyword();	// recursive descent : )
	}

	return Lexer::Token(TokenType::CHAR, getCurr());
}

Lexer::Token Lexer::tokenizeKeyword(){
	std::string keyword = "";

	while(isChar() && inBound()){
		keyword += getCurr();

		next();
	}

	if(lookupTable.count(keyword) != 0){
		// is in the table so its in the syntax
		
		return Token(Lexer::lookupTable[keyword]); //change
	}
	else{
		// not in syntax so must be a string 
		//CHANGE THIS ASAP THIS IS BAD
		while(!isChar())
			back();
		next();
		
		return tokenizeString();
	}	

}

Lexer::Token Lexer::tokenizeString(){
	std::string string = "";

	while(isChar() && inBound()){
		string += getCurr();

		next();
	}

	return Token(TokenType::STRING, string);
}
