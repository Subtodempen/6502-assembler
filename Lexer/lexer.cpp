#include"lexer.hpp"

// Initialize and populate the static map in the source file
std::map<std::string, TokenType> Lexer::lookupTable = {
    {"mov", TokenType::MOV},
    {"inc", TokenType::INC},
    {"jmp", TokenType::JMP},
	{"add", TokenType::ADD},

};

Lexer::Lexer(const std::vector<std::string> lines) : lines(lines), lineIndex(0), charIndex(0) {}

Lexer::~Lexer(){}

std::vector<Tokens> Lexer::Tokenize(){
	std::vector<Tokens> ret;

	for(auto string : lines){ 
		Tokens temp;

		charIndex = 0;
		temp.clear();

		while(inBound()){
			if(isDigit())
				temp.push_back(tokenizeDigit());
		
			else if(isChar())
				temp.push_back(tokenizeChar());
		

			next(); // ???
		}

		nextLine();
		ret.push_back(temp);
	}

	return ret;
}

inline char Lexer::getCurr(){
	if(inBound()) //safety 👍
		return lines[lineIndex][charIndex];

	return ' ';
}

inline void Lexer::next(){
	charIndex++;
}

inline void Lexer::back(){
	charIndex--;
}

inline void Lexer::nextLine(){
	lineIndex++;
}

inline bool Lexer::inBound(){
	return (charIndex < lines[lineIndex].length());
}

bool Lexer::isDigit(){
	return std::isdigit(static_cast<unsigned char>(getCurr()));
}

bool Lexer::isWhiteSpace(){
	return std::isspace(static_cast<unsigned char>(getCurr()));
}

bool Lexer::isChar(){
	return (!isDigit() && !isWhiteSpace());
}


Token Lexer::tokenizeChar(){
	if(getCurr() == ','){
		return Token(TokenType::CHAR, ',');
	}
	
	if(getCurr() == 'x' || getCurr() == 'y'){ //check if register
		return Token(TokenType::CHAR, getCurr());
	}
	next(); //makes sure its not a string if so dont do it
	
	if(isChar()){
		back();

		return tokenizeKeyword();	// recursive descent : )
	}

	back();
	return Token(TokenType::CHAR, getCurr());
}

Token Lexer::tokenizeKeyword(){
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
		while(isChar() && charIndex != 0)
			back();
		next();
		
		return tokenizeString();
	}	

}

Token Lexer::tokenizeString(){
	std::string string = "";

	while(isChar() && inBound()){
		string += getCurr();

		next();
	}

	return Token(TokenType::STRING, string);
}


Token Lexer::tokenizeDigit(){
	next();

	if(isChar() && getCurr() == 'x')
		return tokenizeHex();
	
	back();

	return tokenizeInt();
}

Token Lexer::tokenizeInt(){
	//get digit size
	int total = 0;
	std::string temp = "";

	while(isDigit() && inBound()){
		temp += getCurr();

		next();
	}

	total = std::stoi(temp); // removew
	back();

	return Token(TokenType::INT, total);
}

Token Lexer::tokenizeHex(){ //whole function might bige erors
	//get digit size
	int total = 0;

	std::vector<int> nums;

	while(isDigit() || isChar()){
		nums.push_back(static_cast<int>(getCurr()));
		
		next();
	}
	
	for(int hexDigit : nums)
		total = (total << 4) | hexDigit;

	return Token(TokenType::HEX, total);
}