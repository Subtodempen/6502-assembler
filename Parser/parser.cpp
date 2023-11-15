#include"parser.hpp"

#include<iostream>
#include <cstdlib>

Parser::Parser(std::vector<Tokens> tokens) : tokens(tokens){
    indexStart();
}

Parser::~Parser(){}


std::vector<Instruction> Parser::Parse(){
    std::vector<Instruction> instructions;
    instructions.reserve(tokens.size());    
    
    checkSyntax(); //checks token syntax
    
    for (auto& instruction : instructions) {
        getOperator(instruction);
    
        if (getOperand(instruction))
            getRegisters(instruction);

        nextLine();
    }   

    return instructions;
}

void Parser::indexStart(){
    lineIndex = 0;
    tokenIndex = 0;
}

Token Parser::getCurr(){
    return tokens[lineIndex][tokenIndex];  
}

bool Parser::inBound(){
    return(tokenIndex <= tokens[lineIndex].size() - 1);
}

bool Parser::isKeyword(){
    return (
        getCurr().tokenEnum != TokenType::INT &&
        getCurr().tokenEnum != TokenType::HEX &&
        getCurr().tokenEnum != TokenType::CHAR &&
        getCurr().tokenEnum != TokenType::STRING
    );
}

bool Parser::isValid(){
    return(
        getCurr().tokenEnum == TokenType::INT || 
        getCurr().tokenEnum == TokenType::HEX || 
        getCurr().charValue == 'x' ||
        getCurr().charValue == 'y' 
    );
}

bool Parser::isNext(){
    //checks if u can fetch next value
    return ((tokenIndex + 1) <= (tokens[lineIndex].size() - 1));
}

void Parser::next(){
    if(tokenIndex < tokens.at(lineIndex).size())
        tokenIndex++;
    else
        return;
}

void Parser::nextLine(){
    if(lineIndex < tokens.size()){
        lineIndex++;

        tokenIndex = 0;
    }
    else
        return;
}

void Parser::errorExit(const std::string error){
    std::cerr << "\033[1;31mSyntax error: "<<error << "\nOn line " << lineIndex + 1<<"\033[0m"; // turns color red

    std::cout<<std::endl;
    
    exit(EXIT_FAILURE);
}

void Parser::checkSyntax(){
    indexStart();

    for(size_t i = 0; i < tokens.size(); i++){
        if(!isKeyword())
            errorExit("Keyword needs to be first");
        
        if(isNext()) 
            next();
        else{
            nextLine();

            continue;
        }

        if(!isValid())
            //syntax error
            errorExit("not valid");
        
        if(isNext()){
            //check if next is comma else syntax all good
            next();

            if(getCurr().charValue == ','){

                if(isNext()){
                    next(); 

                    if(!isValid()){
                        errorExit("Operand after , is bad");
                    }
                }else
                    errorExit("Need operand after ,");
            }else
                errorExit("Need ,");
        }

        nextLine();
    }

    indexStart();
}

void Parser::getOperator(Instruction& instruction){
    instruction.keyword = getCurr().tokenEnum;

    next();
}

bool Parser::getOperand(Instruction& instruction){
    if(!inBound()){
        instruction.operand = 0;

        return false;
    }
    
    if((getCurr().tokenEnum == TokenType::INT)  || (getCurr().tokenEnum == TokenType::HEX)){
        instruction.operand = getCurr().intValue;
    }

    next();
    return true;
}

void Parser::getRegisters(Instruction& instruction){
    //if(getCurr().charValue == ',')
    next();

    if(getCurr().charValue == 'x'){
        instruction.x = true;
        instruction.y = false;
    }else if(getCurr().charValue == 'y'){
        instruction.y = true;
        instruction.x = false;
    }
}