#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
	TOKEN_NUMBER,
    TOKEN_KEYWORLD,
	TOKEN_OPERATOR,
	TOKEN_IDENTIFIER,
	TOKEN_EOF,
	TOKEN_ERROR
} TokenType;

typedef struct{
	TokenType type;
	int value;
	char operador;
	char identifier[100];
    char lexame[100];
} Token;

Token current_token;

Token parser(FILE *source);

