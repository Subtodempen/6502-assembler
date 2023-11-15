#pragma once

#include "expr.hpp"

class Parser{
    public:
        Parser(std::vector<Tokens> tokens); 
        ~Parser();

        std::vector<Instruction> Parse();
    private:
        std::vector<Tokens> tokens;
        
        unsigned int lineIndex;
        unsigned int tokenIndex;
        
        void indexStart();

        inline Token getCurr();
        inline bool isKeyword();
        
        inline bool inBound();
        inline bool isValid();
        inline bool isNext();

        void next();
        void nextLine();
        
        void checkSyntax(); //if syntax error it exits // put in a try catch 
        void errorExit(const std::string error);
        
        void getOperator(Instruction& instruction); // fils in TokenType in the struct 
        bool getOperand(Instruction& instruction); 

        void getRegisters(Instruction& instruction);

};