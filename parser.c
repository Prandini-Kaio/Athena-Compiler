#include "parser.h"

const char *keyworlds = {"func", "if", "else"};

Token parser(FILE *source){
	char chr = fgetc(source);

	while(isspace(chr)){
		chr = fgetc(source); // Ignora os espacos em branco
	}

	// Valida o TOKEN

    // TOKEN_NUMBER
	if(isdigit(chr)){ // Numeros
		int value = chr - '0'; // Subtrai o numero pelo valor ASCII do '0' dando seu valor real
		chr = fgetc(source);
		while(isdigit(chr)){
			value = value * 10 + (chr - '0');
			chr = fgetc(source);
		}
		ungetc(chr, source);
		return (Token){TOKEN_NUMBER, value};
	}// TOKEN_OPERATOR
    else if(chr == '+' || chr == '-' || chr == '/' || chr == '*' || chr == ',' || chr == '(' || chr == ')' || chr == '{' || chr == '}') { // Operadores
        return (Token) {TOKEN_OPERATOR, 0, chr};

	}// TOKEN_KEYWORLD
    else if(isalpha(chr)){
        int index = 0;
        while(isalnum(chr) || chr == '_'){
            current_token.lexame[index++] = chr;
            chr = fgetc(source);
        }
        ungetc(chr, source);
        current_token.lexame[index] = '\0';

        if(strcmp(current_token.lexame, "func") == 0 || strcmp(current_token.lexame, "if") == 0){
            Token t = (Token){TOKEN_KEYWORLD, 0, '\0', '\0'};
            strcpy(t.lexame, current_token.lexame);
            return t;
        }

        // TOKEN IDENTIFIER
        Token token = (Token){TOKEN_IDENTIFIER, 0, '\0', .lexame='\0'};
        strcpy(token.identifier, current_token.lexame);

        return token;
    }// TOKEN_EOF
    else if(chr == EOF){
		return (Token){TOKEN_EOF, 0, '\0', '\0', '\0'};
	}
    // Erro lexico
	return (Token){TOKEN_ERROR, 0, '\0', '\0', '\0'};
}

