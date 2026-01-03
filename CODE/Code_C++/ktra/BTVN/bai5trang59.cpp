#include <stdio.h>
#include <time.h>
#include <cstdlib>
typedef int Itemtype;

struct StackNode {
    Itemtype Info;
    StackNode *Next;
};

struct Stack {
    StackNode *Top;
};

void initStack(Stack &s) {
    s.Top = NULL;
}

int isEmptyStack(Stack s) {
    return s.Top == NULL;
}

// Hàm `push()` thêm phần tử vào đầu Stack
int push(Stack &s, StackNode *q) {
    if (q == NULL) return 0;
    q->Next = s.Top;
    s.Top = q;
    return 1;
}

// Hàm `pop()` xóa phần tử đầu Stack
int pop(Stack &s, Itemtype &x) {
    if (isEmptyStack(s)) return 0;
    StackNode *q = s.Top;
    s.Top = s.Top->Next;
    x = q->Info;
    delete q;
    return 1;
}

// Hàm tạo một phần tử mới
StackNode* createNode(Itemtype x) {
    StackNode *q = new StackNode;
    if (q != NULL) {
        q->Info = x;
        q->Next = NULL;
    }
    return q;
}

// Hàm hiển thị Stack
void showStack(Stack s) {
    if (isEmptyStack(s)) {
        printf("Ngăn xếp rỗng.\n");
        return;
    }
    printf("Các phần tử trong ngăn xếp:\n");
    StackNode *current = s.Top;
    while (current != NULL) {
        printf("%d ", current->Info);
        current = current->Next;
    }
    printf("\n");
}

// cây BSTree
typedef int Itemtype;
struct TNode
{
    Itemtype Info;
    TNode*Left;
    TNode*Right;
};
struct BTree
{
    TNode*Root;
};
void initBtree(BTree &bt)
{
    bt.Root = NULL;
}
int isEmpty(BTree bt)
{
    if(bt.Root == NULL)
        return 1;
    else
        return 0;
}
TNode *createTNode(Itemtype x)
{
    TNode*p = new TNode;
    if(p==NULL)
        {
            printf("loi du lieu");
            return NULL;
        }
    p ->Info=x;
    p->Left = NULL;
    p->Right = NULL;
    return p;
}
// thêm phần tử x vào cây dạng đệ qui
int insertTNode(TNode*&root, Itemtype &x)
{
    if(root == NULL)
    {
        root = createTNode(x);
        return 0;
    }
    if(root ->Info==x)
    {
        return 0;
    }
    if(x < root->Info)
        insertTNode(root->Left,x);
    else
        insertTNode(root->Right,x);
    return 1;
}
// tạo cây từ mảng có sẵn
void createBTreeFromArray(BTree &bt, Itemtype a[], int n) {
    initBtree(bt); // Khởi tạo cây
    
    for (int i = 0; i < n; i++) {
        insertTNode(bt.Root, a[i]); // Truyền bt.Root thay vì bt
    }
}
// show BStree
void showBSTNode(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không hiển thị gì

    printf("%4d ", root->Info);  // Hiển thị giá trị nút gốc

    showBSTNode(root->Left);  // Duyệt cây con trái
    showBSTNode(root->Right); // Duyệt cây con phải
}
// tọa mạng tử động
void createAutomaticBTree(BTree &bt) {
    int n;
    Itemtype x;
    printf("Cho biet so nut cua cay: ");
    scanf("%d", &n);

    initBtree(bt); // Gọi đúng hàm khởi tạo cây

    srand((unsigned)time(NULL)); // Sử dụng đúng thư viện <time.h>

    for (int i = 1; i <= n; i++) {
        x = (rand() % 199) - 99;
        insertTNode(bt.Root, x);  // Truyền đúng tham chiếu đến `bt.Root`
    }

    printf("Da tao cay BST tu dong với %d nut !\n", n);
}

// Hàm tạo cây từ bàn phím
void createBTreeFromKeyboard(BTree &bt) {
    int n, x;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);

    initBtree(bt);  // Khởi tạo cây

    for (int i = 0; i < n; i++) {
        printf("Nhap gia tri phan tu %d: ", i + 1);
        scanf("%d", &x);
        insertTNode(bt.Root, x);
    }
}
//================================
//Hàm duyệt NLR (Tiền thứ tự) với Stack
void traverseNLR_Stack(TNode *root) {
    if (root == NULL) return;

    Stack s;
    initStack(s);
    push(s, createNode((Itemtype)root));

    while (!isEmptyStack(s)) {
        Itemtype temp;
        pop(s, temp);
        TNode *node = (TNode*)temp;

        printf("%d ", node->Info);

        if (node->Right != NULL) push(s, createNode((Itemtype)node->Right));
        if (node->Left != NULL) push(s, createNode((Itemtype)node->Left));
    }
}

//Hàm duyệt LNR (Trung thứ tự) với Stack
void traverseLNR_Stack(TNode *root) {
    if (root == NULL) return;

    Stack s;
    initStack(s);
    TNode *node = root;

    while (node != NULL || !isEmptyStack(s)) {
        while (node != NULL) {
            push(s, createNode((Itemtype)node));
            node = node->Left;
        }

        Itemtype temp;
        pop(s, temp);
        node = (TNode*)temp;
        printf("%d ", node->Info);

        node = node->Right;
    }
}

//Hàm duyệt LRN (Hậu thứ tự) với Stack
void traverseLRN_Stack(TNode *root) {
    if (root == NULL) return;

    Stack s1, s2;
    initStack(s1);
    initStack(s2);
    push(s1, createNode((Itemtype)root));

    while (!isEmptyStack(s1)) {
        Itemtype temp;
        pop(s1, temp);
        TNode *node = (TNode*)temp;
        push(s2, createNode((Itemtype)node));

        if (node->Left != NULL) push(s1, createNode((Itemtype)node->Left));
        if (node->Right != NULL) push(s1, createNode((Itemtype)node->Right));
    }

    while (!isEmptyStack(s2)) {
        Itemtype temp;
        pop(s2, temp);
        printf("%d ", ((TNode*)temp)->Info);
    }
}
int main() {
    BTree bt;
    initBtree(bt);
    int choice, n;
    Itemtype x, a[100];

    do {
        printf("\n===== MENU CAY BST =====");
        printf("\n1. Tao cay tu mang co san");
        printf("\n2. Tao cay bang tay");
        printf("\n3. Tao cay ngau nhien");
        printf("\n4. Hien thi cay BST");
        printf("\n5. Duyet NLR (Stack)");
        printf("\n6. Duyet LNR (Stack)");
        printf("\n7. Duyet LRN (Stack)");
        printf("\n8. Thoat");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong phan tu cua mang: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Nhap phan tu %d: ", i + 1);
                    scanf("%d", &a[i]);
                }
                createBTreeFromArray(bt, a, n);
                printf("Da tao cay tu mang!\n");
                break;

            case 2:
                createBTreeFromKeyboard(bt);
                break;

            case 3:
                createAutomaticBTree(bt);
                break;

            case 4:
                printf("Cay BST:\n");
                showBSTNode(bt.Root);
                printf("\n");
                break;

            case 5:
                printf("Duyet NLR (Stack): ");
                traverseNLR_Stack(bt.Root);
                printf("\n");
                break;

            case 6:
                printf("Duyet LNR (Stack): ");
                traverseLNR_Stack(bt.Root);
                printf("\n");
                break;

            case 7:
                printf("Duyet LRN (Stack): ");
                traverseLRN_Stack(bt.Root);
                printf("\n");
                break;

            case 8:
                printf("Ket thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 8);

    return 0;
}
