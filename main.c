#include "mcc.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    // トークナイズする
    user_input = argv[1];
    token = tokenize(user_input);
    Node *node = expr();

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // 抽象構文木を下る
    gen(node);

    // スタックトップに式全体の値が残っているため
    //　それをraxにロードして関数からの返り値とする
    printf("  pop rax\n");
    printf("  ret\n");
    return 0;
}
