#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// khai báo cấu trúc cây biểu thức
typedef char Itemtype;

struct TNode
{
    Itemtype Info;
    TNode *Left, *Right;
};

struct BTree {
    TNode *Root;
};
// hàm ktr toán tử
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

TNode *createTNode(Itemtype x) {
    TNode *p = new TNode;
    if (p == NULL) {
        printf("loi bo nho!\n");
        return NULL;
    }
    p->Info = x;
    p->Left = p->Right = NULL;
    return p;
}

//xây dựng cây biểu thức từ hậu tố (postfix)
TNode *buildExpressionTree(char postfix[]) {
    TNode *stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        TNode *node = createTNode(postfix[i]);

        if (isdigit(postfix[i])) {
            stack[++top] = node;
        } else if (isOperator(postfix[i])) {
            node->Right = stack[top--];
            node->Left = stack[top--];
            stack[++top] = node;
        }
    }
    return stack[top];
}

//Hàm tính toán giá trị của cây biểu thức
int evaluateExpressionTree(TNode *root) {
    if (root == NULL) return 0;

    if (!isOperator(root->Info))
        return root->Info - '0';

    int leftVal = evaluateExpressionTree(root->Left);
    int rightVal = evaluateExpressionTree(root->Right);

    switch (root->Info) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
    }
    return 0;
}

