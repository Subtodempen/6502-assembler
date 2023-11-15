#include "../Lexer/lexer.hpp"
#include "../Parser/parser.hpp"

class Compiler{
    public:
        Compiler();
        ~Compiler();

        unsigned int generateBinary(std::string Fname);
    private:
        std::vector<std::string> readFile(std::string fName);
};
