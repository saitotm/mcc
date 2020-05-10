#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
// container.c
//

// トークンの種類
typedef enum
{
    TK_RESERVED, // 記号
    TK_NUM,      // 整数トークン
    TK_EOF,      // End of file
} TokenKind;

typedef struct Token Token;
// トークン型
struct Token
{
    TokenKind kind; // トークンの型
    Token *next;    // 次の入力トークン
    int val;        // kindがTK_NUMの場合、その数値
    char *str;      // トークン文字列
    int len;
};

void error_at(char *loc, char *fmt, ...);
void error(char *fmt, ...);
bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();
Token *tokenize();

// 現在着目しているトークン
extern Token *token;
// 入力プログラム
extern char *user_input;

//
// parse.c
//

typedef enum
{
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_EQ,  // ==
    ND_NE,  // !=
    ND_LT,  // <
    ND_LE,  // <=
    ND_NUM, // 整数

} NodeKind;

typedef struct Node Node;

struct Node
{
    NodeKind kind; // ノード型
    Node *lhs;     // 左辺
    Node *rhs;     // 右辺
    int val;       // kindがND_NUMの時に整数値が格納される
};

Node *expr();

//
// codegen.c
//

void gen(Node *node);