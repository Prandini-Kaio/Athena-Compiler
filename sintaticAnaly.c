#include "sintaticAnaly.h"

// Consome o token e vai para o próximo
void consume_token(FILE *source){
	current_token = parser(source);
}

// Verifica se o TOken e esperado
bool expect_token(TokenType expected_type){
	return current_token.type == expected_type;
}

// Verifica o operador
bool match_operator(char op){
	return current_token.type == TOKEN_OPERATOR && current_token.operador == op;
}

bool match_keyworld(char keyworld[]){
    return current_token.type == TOKEN_KEYWORLD && strcmp(current_token.lexame, keyworld) == 0;
}

bool match_identifier(char identifier){
    return current_token.type == TOKEN_IDENTIFIER && current_token.identifier == identifier;
}

//


// Fatora a expressao e verifica se esta dentro dos operadores ou e um numero
bool factor(FILE *source){
	if(expect_token(TOKEN_NUMBER)){
		consume_token(source);
		return true;
	}else if(match_keyworld("func")){
        consume_token(source);
        //if(function_call(source)){
        if(declaration(source)){
            consume_token(source);
            return true;
        }
	}
	return false;
}

bool term(FILE * source){
	if(factor(source)){
		while(match_operator('*') || match_operator('/')){
			consume_token(source);
			if(!factor(source)){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool expression(FILE *source){
	if(term(source)){
		while(match_operator('+') || match_operator('-') || match_operator(',')){
			consume_token(source);
			if(!term(source)){
				return false;
			}
		}
		return true;
	}
	return false;
}

// Expression

bool function_call(FILE *source){
    if(expect_token(TOKEN_IDENTIFIER)){
        consume_token(source);
        if(match_operator('(')){
            consume_token(source);
            if(argument_list(source) && match_operator(')')){
                consume_token(source);
                return true;
            }
        }
    }
    return false;
}

bool argument_list(FILE *source){
    if(expression(source)){
        while(match_operator(',')){
            consume_token(source);
            if(!expression(source)){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool declaration(FILE *source) {
    /*if(match_keyworld("func")){
        consume_token(source);
        if(expect_token(TOKEN_IDENTIFIER)){
            consume_token(source);
            if(match_operator('(')){
                consume_token(source);
                if(expect_token(TOKEN_IDENTIFIER)){
                    consume_token(source);
                    if(match_operator(')') && match_operator('{')){
                        consume_token(source);
                        if(expression(source) && match_operator('}')){
                            consume_token(source);
                            return true;
                        }
                    }
                }
            }
        }
    }*/

    if(expect_token(TOKEN_IDENTIFIER)){
        consume_token(source);
        if(match_operator('(')){
            consume_token(source);
            if(expression(source)){
                //consume_token(source);
                if(match_operator(')')) {
                    consume_token(source);
                    if (match_operator('{')){
                        consume_token(source);
                        if (expression(source) && match_operator('}')) {
                            consume_token(source);
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}