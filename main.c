#include "sintaticAnaly.c"

bool test_parser(FILE *source);
bool test_sintatic(FILE *source);

int main() {
    FILE *source = fopen("../source.txt", "r");

    if (source == NULL) {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    if(test_parser(source))printf("Lexic Test: OK!\n");
    else printf("Lexic Test: FAILED!\n");

    fclose(source);

    source = fopen("../source.txt", "r");

    if(test_sintatic(source))printf("Syntax Test: OK!\n");
    else printf("Syntax Test: FAILED!\n");

    fclose(source);
    return 0;
}

bool test_parser(FILE *source){
    Token token;

    do{
        token = parser(source);

        /*if(token.type == TOKEN_NUMBER){
            printf("TOKEN: NUMBER VALUE: %d \n", token.value);
        }
        else if(token.type == TOKEN_KEYWORLD) {
            printf("TOKEN: KEYWORLD VALUE: %s\n", token.lexame);
        }else if(token.type == TOKEN_OPERATOR) {
            printf("TOKEN: OPERATOR VALUE: %c\n", token.operador);
        }else if(token.type == TOKEN_IDENTIFIER){
            printf("TOKEN: IDENTIFIER VALUE: %c\n", token.identifier);
        }else if(token.type == TOKEN_ERROR){
            return false;
        }
        printf("\n------------------------------\n");*/
        if(token.type == TOKEN_NUMBER){
            printf("%d", token.value);
        }
        else if(token.type == TOKEN_KEYWORLD) {
            printf("%s", token.lexame);
        }else if(token.type == TOKEN_OPERATOR) {
            printf("%c", token.operador);
        }else if(token.type == TOKEN_IDENTIFIER){
            printf("%s", token.identifier);
        }else if(token.type == TOKEN_ERROR){
            return false;
        }
    }while(token.type != TOKEN_EOF);

    printf("\n");
    return true;
}

bool test_sintatic(FILE *source){
    consume_token(source);
    bool is_syntax_correct = expression(source) && expect_token(TOKEN_EOF);

    if (is_syntax_correct) {
        return true;
    } else {
        return false;
    }
}