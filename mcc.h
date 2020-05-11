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
    TK_IDENT,    // 識別子
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
    int len;        // トークン文字列の長さ
};

typedef struct LVar LVar;
// ローカル変数の型
struct LVar
{
    LVar *next; // 次の変数かNULL
    char *name; // 変数の名前
    int len;    // 名前の長さ
    int offset; // RBPからのオフセット
};

void error_at(char *loc, char *fmt, ...);
void error(char *fmt, ...);
bool consume(char *op);
Token *consume_ident();
void expect(char *op);
int expect_number();
bool at_eof();
void tokenize();

// 現在着目しているトークン
extern Token *token;
// 入力プログラム
extern char *user_input;
// ローカル変数リスト
extern LVar *locals;
//
// parse.c
//

typedef enum
{
    ND_ADD,    // +
    ND_SUB,    // -
    ND_MUL,    // *
    ND_DIV,    // /
    ND_ASSIGN, // =
    ND_EQ,     // ==
    ND_NE,     // !=
    ND_LT,     // <
    ND_LE,     // <=
    ND_LVAR,   // ローカル変数
    ND_NUM,    // 整数
} NodeKind;

typedef struct Node Node;

struct Node
{
    NodeKind kind; // ノード型
    Node *lhs;     // 左辺
    Node *rhs;     // 右辺
    int val;       // kindがND_NUMの時に整数値が格納される
    int offset;    // kingがND_LVARの時にベースポインタからのオフセットが格納される
};

void program();

extern Node *code[100];

//
// codegen.c
//

void codegen();