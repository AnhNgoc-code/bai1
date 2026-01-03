#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

typedef int Itemtype;

struct StackNode {
    Itemtype Info;
    StackNode *Next;
};

struct Stack {
    StackNode *Top;
};

void initstack(Stack &st) {
    st.Top = NULL;
}

int isEmpty(Stack st) {
    return (st.Top == NULL) ? 1 : 0;
}
//=================================================================//

StackNode* createStackNode(Itemtype x) {
    StackNode *p = new StackNode;
    if (p == NULL) {
        printf("Không đủ bộ nhớ!\n");
        return NULL;
    }
    p->Info = x;
    p->Next = NULL;
    return p;
}
//=================================================================//
void showStackNode(StackNode *p) {
    if (p != NULL)
        printf("%d", p->Info);
}
//=================================================================//
void showStack(Stack st) {
    if (isEmpty(st)) {
        printf("Danh sách rỗng!\n");
        return;
    }
    printf("TOP   ->");
    for (StackNode *p = st.Top; p != NULL; p = p->Next) {
        showStackNode(p);
        printf("\n");
        printf("-> ");
    }
    printf("NULL\n");
}
//=================================================================//
int push(Stack &st, StackNode *p) {
    if (p == NULL) {
        return 0;
    }
    p->Next = st.Top;
    st.Top = p;
    return 1;
}
//=================================================================//
void createstackNode_Inputbyhand(Stack &st) {
    int n;
    do {
        printf("Nhập số lượng phần tử của danh sách: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Vui lòng nhập n > 0\n");
        }
    } while (n <= 0);

    for (int i = 0; i < n; i++) {
        Itemtype x;
        printf("Nhập phần tử node thứ %d: ", i + 1);
        scanf("%d", &x);
        StackNode *p = createStackNode(x);
        push(st, p);
    }
}
//=================================================================//
void createStackNode_random(Stack &st) {
    int n;
    do {
        printf("Nhập số lượng phần tử của danh sách: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Vui lòng nhập n > 0\n");
        }
    } while (n <= 0);

    for (int i = 0; i < n; i++) {
        Itemtype x = rand() % 199 - 99;
        StackNode *p = createStackNode(x);
        push(st, p);
    }
}
//=================================================================//
void swap(Itemtype &x, Itemtype &y) {
    Itemtype tmp = x;
    x = y;
    y = tmp;
}
//=================================================================//
StackNode* findStackNode(Stack &st, Itemtype &x) {
    for (StackNode *p = st.Top; p != NULL; p = p->Next) {
        if (p->Info == x) {
            return p;
        }
    }
    return NULL;
}
//=================================================================//

void sortStack_Ascending(Stack &st) {
    for (StackNode *p = st.Top; p != NULL && p->Next != NULL; p = p->Next) {
        for (StackNode *q = p->Next; q != NULL; q = q->Next) {
            if (p->Info > q->Info) {
                swap(p->Info, q->Info);
            }
        }
    }
}
//=================================================================//

int pop(Stack &st, Itemtype &x) {
    if (isEmpty(st)) {
        return 0;
    }
    StackNode *p = st.Top;
    st.Top = st.Top->Next;
    x = p->Info;
    delete p;
    return 1;
}

//=================================================================//
void createStackNode_Array(Stack &st, Itemtype a[], int n) {
    initstack(st);
    for (int i = 0; i < n; i++) {
        StackNode *p = createStackNode(a[i]);
        push(st, p);
    }
}
//=================================================================//
int Gettop(Stack &st, Itemtype &x) {
    if (isEmpty(st)) {
        return 0;
    }
    x = st.Top->Info;
    return 1;
}
//=================================================================//
void FromtextFile(Stack &st, char inputfilename[]) {
    initstack(st);
    FILE *fi = fopen(inputfilename, "rt");
    if (fi == NULL) {
        printf("Lỗi mở file %s\n", inputfilename);
        return;
    }
    int n;
    fscanf(fi, "%d", &n);
    for (int i = 0; i < n; i++) {
        Itemtype x;
        fscanf(fi, "%d", &x);
        StackNode *p = createStackNode(x);
        push(st, p);
    }
    fclose(fi);
}
//=================================================================//

void popAll(Stack &st) {
    Itemtype x;
    printf("Các phần tử được lấy ra từ stack (từ đỉnh đến đáy):\n");
    while (!isEmpty(st)) {
        pop(st, x);
        printf("%d ", x);
    }
    printf("\n");
}
//=================================================================//
void menu() {
    printf("=================================\n");
    printf("0. Thoát chương trình\n");
    printf("1. Nhập và xuất thông tin của 1 node\n");
    printf("2. Nhập ngăn xếp từ bàn phím\n");
    printf("3. Tạo ngăn xếp ngẫu nhiên\n");
    printf("4. Tạo danh sách từ mảng một chiều\n");
    printf("5. Tạo ngăn xếp từ file\n");
    printf("6. Tìm kiếm phần tử trong ngăn xếp\n");
    printf("7. Thêm vào đầu ngăn xếp\n");
    printf("8. Xóa node ở đỉnh ngăn xếp\n");
    printf("9. Xem giá trị đỉnh ngăn xếp\n");
    printf("10. Xem toàn bộ ngăn xếp\n");
    printf("11.Lấy stack đỉnh đến cuối stackstack\n");
    printf("=================================\n");
}

void process() {
    Stack st;
    Itemtype x;
    Itemtype A[] = {1,2,3,4,5,6,7,8,9,10};
    int lc;
    int N = 10;
    char tenfile[] = "input_dssonnguyen.txt";

    initstack(st);

    do {
        menu();
        printf("Nhập lựa chọn: ");
        scanf("%d", &lc);
        switch (lc) {
            case 1:{
                printf("Nhập giá trị node: ");
                scanf("%d", &x);
                StackNode *p=createStackNode(x);
                showStackNode(p);
                break;}
            case 2:
                createstackNode_Inputbyhand(st);
                showStack(st);
                break;
            case 3:
                createStackNode_random(st);
                showStack(st);
                break;
            case 4:
                createStackNode_Array(st, A, N);
                showStack(st);
                break;
            case 5:
                FromtextFile(st, tenfile);
                showStack(st);
                break;
            case 6:
                printf("Nhập node cần tìm: ");
                scanf("%d", &x);
                {
                    StackNode *found = findStackNode(st, x);
                    if (found == NULL) {
                        printf("Không tìm thấy %d\n", x);
                    } else {
                        printf("Đã tìm thấy %d tại địa chỉ %p\n", x, (void*)found);
                    }
                }
                break;
            case 7:
                printf("Nhập giá trị muốn thêm: ");
                scanf("%d", &x);
                push(st, createStackNode(x));
                showStack(st);
                break;
            case 8:
                if (pop(st, x)) {
                    printf("Đã xóa phần tử: %d\n", x);
                } else {
                    printf("Stack rỗng, không thể xóa!\n");
                }
                showStack(st);
                break;
            case 9:
                if (Gettop(st, x)) {
                    printf("Giá trị đỉnh là: %d\n", x);
                } else {
                    printf("Stack rỗng!\n");
                }
                break;
            case 10:
                showStack(st);
                break;
                case 11:
                popAll(st);
                break;
        }
    } while (lc != 0);
}

int main() {
    process();
    return 0;
}
