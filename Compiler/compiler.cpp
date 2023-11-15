#include "compiler.hpp"
#include <fstream>

Compiler::Compiler(){}
Compiler::~Compiler(){}

std::vector<std::string> Compiler::readFile(std::string fName){
    //read file
    std::vector<std::string> buf;
    
    std::ifstream file(fName);
    std::string temp;
    
    if(!file.is_open()){
        std::cerr<<"Can not open file";

        exit(0);
    }

    while (getline(file, temp))
        buf.push_back(temp);

    return buf;
}


unsigned int Compiler::generateBinary(std::string Fname){
    std::vector<std::string> stringVec = readFile(Fname);

    Lexer lexer(stringVec);
    Parser parser(lexer.Tokenize());
    
    parser.Parse();

    return 1;
}
