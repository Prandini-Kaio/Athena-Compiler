#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "parser.c"

Token current_token;
// DEFAULT
void consume_token(FILE *source);
bool expect_token(TokenType expected_type);
bool match_operator(char op);
bool match_keyworld(char keyworld[]);
bool match_identifier(char identifier);
// EXPRESSIONS
bool factor(FILE *source);
bool term(FILE *source);
bool expression(FILE *source);
// FUNCTIONS
bool function_call(FILE *source);
bool argument_list(FILE *source);
bool declaration(FILE *source);
