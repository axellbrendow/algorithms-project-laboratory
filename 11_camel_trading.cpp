#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

const char *LPAREN = "LPAREN";
const char *RPAREN = "RPAREN";
const char *NUMBER = "NUMBER";
const char *PLUS = "PLUS";
const char *MINUS = "MINUS";
const char *MUL = "MUL";
const char *DIV = "DIV";
const char *EOFTOKEN = "EOF";

int invert_precedence = 0;

// -------------------- Class Token

typedef struct Token Token;

struct Token
{
    char type[30];
    double value;
};

Token *token_new(const char *type, double value)
{
    Token *token = (Token *) malloc(sizeof(Token));

    strcpy(token->type, type);
    token->value = value;

    return token;
}

int equals(const char *str1, const char *str2)
{
    return strcmp(str1, str2) == 0;
}

int isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

int isOnInterval(int lowerValue, int greaterValue, int value)
{
    return value >= lowerValue && value <= greaterValue;
}

int isDigit(char c)
{
    return isOnInterval('0', '9', c);
}

// -------------------- Class Lexer

typedef struct Lexer Lexer;

#define MAX_EXPRESSION_SIZE 10000

struct Lexer
{
    char expression[MAX_EXPRESSION_SIZE];
    int pos;
    int exprLength;
    char current_char;
};

Lexer* lexer_new(const char *expression)
{
    Lexer* lexer = (Lexer *) malloc(sizeof(Lexer));

    strcpy(lexer->expression, expression);
    lexer->pos = 0;
    lexer->exprLength = strlen(expression);
    lexer->current_char = expression[lexer->pos];

    return lexer;
}

void lexer_error(Lexer* lexer, const char *format, ...)
{
    char errorMsg[MAX_EXPRESSION_SIZE + 2];
    va_list args;
    va_start(args, format);
    vsprintf(errorMsg, format, args); // Sends the formatted string to errorMsg
    va_end(args);

    // Shows the error and the expression
    fprintf(stderr, "\nERROR: %s\n%s\n", errorMsg, lexer->expression);

    // Creates an array to store the string that will show where the compilation stopped
    char spaces[lexer->pos + 3];

    memset(spaces, ' ', lexer->pos); // Fill it with ' '

    spaces[lexer->pos] = '^'; // Put an indicator where compilation stopped
    spaces[lexer->pos + 1] = '\n';
    spaces[lexer->pos + 2] = '\0';
    fprintf(stderr, spaces);

    exit(1);
}

void lexer_advance(Lexer* lexer)
{
    lexer->pos++;
    lexer->current_char = ( lexer->pos >= lexer->exprLength ) ?
        EOF : lexer->expression[lexer->pos];
}

void lexer_skip_spaces(Lexer* lexer)
{
    while (lexer->current_char != EOF && isWhitespace(lexer->current_char))
    {
        lexer_advance(lexer);
    }
}

double lexer_get_double(Lexer* lexer)
{
    int numberOfDots = 0, offset = 0;
    char doubleStr[100];

    if (lexer->current_char == '.') lexer_error(lexer, ". (dot) before number");

    while (lexer->current_char != EOF && (isDigit(lexer->current_char) ||
        lexer->current_char == '.'))
    {
        if (lexer->current_char == '.' && ++numberOfDots > 1)
            lexer_error(lexer, "two . (dots) in a number");

        doubleStr[offset++] = lexer->current_char;
        lexer_advance(lexer);
    }

    doubleStr[offset] = '\0';

    return atof(doubleStr);
}

Token *lexer_next_token(Lexer* lexer)
{
    while (lexer->current_char != EOF)
    {
        if (isWhitespace(lexer->current_char))
        {
            lexer_skip_spaces(lexer);
            continue;
        }

        if (isDigit(lexer->current_char))
            return token_new(NUMBER, lexer_get_double(lexer));

        if (lexer->current_char == '(')
        {
            lexer_advance(lexer);
            return token_new(LPAREN, '(');
        }

        if (lexer->current_char == ')')
        {
            lexer_advance(lexer);
            return token_new(RPAREN, ')');
        }

        if (lexer->current_char == '+')
        {
            lexer_advance(lexer);
            return token_new(PLUS, '+');
        }

        if (lexer->current_char == '-')
        {
            lexer_advance(lexer);
            return token_new(MINUS, '-');
        }

        if (lexer->current_char == '*')
        {
            lexer_advance(lexer);
            return token_new(MUL, '*');
        }

        if (lexer->current_char == '/')
        {
            lexer_advance(lexer);
            return token_new(DIV, '/');
        }

        lexer_error(lexer, "undefined token '%c'", lexer->current_char);
    }

    return token_new(EOFTOKEN, EOF);
}

// -------------------- Class Interpreter

typedef struct Interpreter Interpreter;

struct Interpreter
{
    Lexer* lexer;
    Token* current_token;
};

void interpreter_eat(Interpreter* interpreter, const char* token_type);
double interpreter_factor(Interpreter *interpreter);
double interpreter_term(Interpreter* interpreter);
double interpreter_expr(Interpreter* interpreter);

Interpreter* interpreter_new(const char *expression)
{
    Interpreter* interpreter = (Interpreter*) malloc(sizeof(Interpreter));

    interpreter->lexer = lexer_new(expression);
    interpreter->current_token = lexer_next_token(interpreter->lexer);

    return interpreter;
}

/**
 * Consumes the current token and goes to the next.
 * 
 * @param interpreter Expression interpreter.
 * @param token_type Expected token type.
 */
void interpreter_eat(Interpreter* interpreter, const char* token_type)
{
    if (equals(interpreter->current_token->type, token_type))
    {
        free(interpreter->current_token);
        interpreter->current_token = lexer_next_token(interpreter->lexer);
    }

    else if (equals(interpreter->current_token->type, EOFTOKEN))
        lexer_error(interpreter->lexer, "End-of-file, expected (%s)", token_type);

    else lexer_error(interpreter->lexer, "invalid token type, expected (%s)", token_type);
}

/**
 * Try to get a number from where the interpreter is.
 * 
 * @param interpreter Expression interpreter.
 * 
 * @return double Numeric value of this factor.
 */
double interpreter_factor(Interpreter *interpreter)
{
    // factor : NUMBER | LPAREN expr RPAREN
    double value = EOF;

    if (equals(interpreter->current_token->type, NUMBER))
    {
        value = interpreter->current_token->value;
        interpreter_eat(interpreter, NUMBER);
    }

    else if (equals(interpreter->current_token->type, LPAREN))
    {
        interpreter_eat(interpreter, LPAREN);
        value = interpreter_expr(interpreter);
        interpreter_eat(interpreter, RPAREN);
    }

    else lexer_error(interpreter->lexer, "invalid token, expected NUMBER or LPAREN");

    return value;
}

/**
 * Try to search for an expression like:
 * 
 * number or
 * number * number or
 * number / number
 * 
 * @param interpreter Expression interpreter.
 * 
 * @return double Numeric value of this term.
 */
double interpreter_term(Interpreter* interpreter)
{
    // term : factor ((MUL | DIV) factor)*
    double result;
    if (invert_precedence) result = interpreter_expr(interpreter);
    else result = interpreter_factor(interpreter);
    Token* token;

    while (equals(interpreter->current_token->type, MUL) ||
        equals(interpreter->current_token->type, DIV))
    {
        token = interpreter->current_token;

        if (equals(token->type, MUL))
        {
            interpreter_eat(interpreter, MUL);
            if (invert_precedence) result = result * interpreter_expr(interpreter);
            else result = result * interpreter_factor(interpreter);
        }

        if (equals(token->type, DIV))
        {
            interpreter_eat(interpreter, DIV);
            if (invert_precedence) result = result / interpreter_expr(interpreter);
            else result = result / interpreter_factor(interpreter);
        }
    }

    return result;
}

double interpreter_expr(Interpreter* interpreter)
{
    /*
    expr   : term ((PLUS | MINUS) term)*
    term   : factor ((MUL | DIV) factor)*
    factor : NUMBER | LPAREN expr RPAREN
    */

    double result;
    if (invert_precedence) result = interpreter_factor(interpreter);
    else result = interpreter_term(interpreter);
    Token* token;

    while (equals(interpreter->current_token->type, PLUS) ||
        equals(interpreter->current_token->type, MINUS))
    {
        token = interpreter->current_token;

        if (equals(token->type, PLUS))
        {
            interpreter_eat(interpreter, PLUS);
            if (invert_precedence) result = result + interpreter_factor(interpreter);
            else result = result + interpreter_term(interpreter);
        }

        if (equals(token->type, MINUS))
        {
            interpreter_eat(interpreter, MINUS);
            if (invert_precedence) result = result - interpreter_factor(interpreter);
            else result = result - interpreter_term(interpreter);
        }
    }
    
    return result;
}

double interpreter_run(Interpreter* interpreter)
{
    double result;
    if (invert_precedence) result = interpreter_term(interpreter);
    else result = interpreter_expr(interpreter);

    free(interpreter->lexer);
    free(interpreter->current_token);

    return result;
}


int main()
{
    int numTestCases;
    scanf("%d%*c", &numTestCases);

    for (size_t i = 0; i < numTestCases; i++)
    {
        char expression[MAX_EXPRESSION_SIZE];
        // strcpy(expression, "1 + 2 * 3");
        
//         printf("Enter an expression. Ex.:  (4 * (1 + 3)) + 2 * 2   or\n\
// exit to exit: ");

        fgets(expression, MAX_EXPRESSION_SIZE, stdin);
        expression[strlen(expression) - 1] = '\0';

        invert_precedence = 1;
        Interpreter* interpreter = interpreter_new(expression);
        printf("The maximum and minimum are %d", (int) interpreter_run(interpreter));
        free(interpreter);

        invert_precedence = 0;
        interpreter = interpreter_new(expression);
        printf(" and %d.\n", (int) interpreter_run(interpreter));
        free(interpreter);
    }

    return 0;
}
