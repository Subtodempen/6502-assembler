#ifndef EXPR_HPP
#define EXPR_HPP

#include <cstdint>
#include "../Lexer/tokens.hpp"


//defines the Instruction Struct

struct Instruction{
    TokenType keyword;
    uint16_t operand;

    bool x; // is x register being used
    bool y; // is y register being used
};

#endif
