#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dịnh nghĩa cấu trúc StackNode và Stack
typedef int ItemType;
struct StackNode {
    ItemType Info;
    StackNode *Next;
};
struct Stack {
    StackNode *Top;
};

// Các hàm thao tác với Stack
void initstack(Stack &st) {
    st.Top = NULL;
}

int isEmpty(Stack st) {
    return (st.Top == NULL) ? 1 : 0;
}

StackNode* createStackNode(ItemType x) {
    StackNode *p = new StackNode;
    if (p == NULL) {
        printf("Không đủ bộ nhớ!\n");
        return NULL;
    }
    p->Info = x;
    p->Next = NULL;
    return p;
}

int push(Stack &st, StackNode *p) {
    if (p == NULL) {
        return 0;
    }
    p->Next = st.Top;
    st.Top = p;
    return 1;
}

int pop(Stack &st, ItemType &x) {
    if (isEmpty(st)) return 0;
    StackNode *p = st.Top;
    x = p->Info;
    st.Top = p->Next;
    delete p;
    return 1;
}

// a. Đổi cơ số (từ hệ 10 sang hệ a, với a >= 2)
void doiCoSo(int n, int a) {
    if (a < 2) {
        printf("Co so khong hop le.\n");
        return;
    }
    Stack st;
    initstack(st);
    while (n > 0) {
        int du = n % a;
        StackNode *p = createStackNode(du);
        push(st, p);
        n /= a;
    }
    printf("So o he co so %d la: ", a);
    while (!isEmpty(st)) {
        ItemType x;
        pop(st, x);
        if (x < 10)
            printf("%d", x);
        else
            printf("%c", x - 10 + 'A');
    }
    printf("\n");
}

// b. Đảo ngược chuỗi ký tự
void daoNguocChuoi(char str[]) {
    Stack st;
    initstack(st);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        StackNode *p = createStackNode(str[i]);
        push(st, p);
    }
    printf("Chuoi dao nguoc la: ");
    for (int i = 0; i < len; i++) {
        ItemType x;
        pop(st, x);
        printf("%c", x);
    }
    printf("\n");
}

// c. Khủ đệ quy cho bài toán tính giai thừa
unsigned long long giaiThuaKhongDeQuy(int n) {
    if (n == 0) return 1;
    Stack st;
    initstack(st);
    push(st, createStackNode(n));
    unsigned long long result = 1;

    while (!isEmpty(st)) {
        ItemType x;
        pop(st, x);
        result *= x;
        if (x > 1) {
            push(st, createStackNode(x - 1));
        }
    }
    return result;
}
