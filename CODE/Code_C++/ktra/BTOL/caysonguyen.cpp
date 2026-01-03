

#include <stdio.h>
#include <time.h>
#include <cstdlib>

struct Itemtype {
    int value;
};

struct TNode {
    Itemtype Info;
    TNode *Left;
    TNode *Right;
};

struct BTree {
    TNode *Root;
};

void initBtree(BTree &bt) {
    bt.Root = NULL;
}

int isEmpty(BTree bt) {
    return bt.Root == NULL;
}

TNode *createTNode(Itemtype x) {
    TNode *p = new TNode;
    if (p == NULL) {
        printf("Loi cap phat bo nho!\n");
        return NULL;
    }
    p->Info = x;
    p->Left = NULL;
    p->Right = NULL;
    return p;
}

void traverseNLR(TNode *root) {
    if (root == NULL) return;
    printf("%d ", root->Info.value);
    traverseNLR(root->Left);
    traverseNLR(root->Right);
}

TNode *findTNode(TNode *root, Itemtype x) {
    if (root == NULL) return NULL;

    if (x.value == root->Info.value) return root;
    else if (x.value < root->Info.value) return findTNode(root->Left, x);
    else return findTNode(root->Right, x);
}

int insertTNode(TNode *&root, Itemtype &x) {
    if (root == NULL) {
        root = createTNode(x);
        return 1;
    }

    if (x.value < root->Info.value) return insertTNode(root->Left, x);
    else if (x.value > root->Info.value) return insertTNode(root->Right, x);

    return 1;
}

TNode *findTNodeReplace(TNode *p) {
    TNode *f = p;
    TNode *q = p->Right;
    while (q->Left != NULL) {
        f = q;
        q = q->Left;
    }
    p->Info = q->Info;
    if (f == p)
        f->Right = q->Right;
    else
        f->Left = q->Right;
    return q;
}

int deleteTNodeX(TNode *&root, Itemtype x) {
    if (root == NULL) return 0;

    if (x.value < root->Info.value) return deleteTNodeX(root->Left, x);
    else if (x.value > root->Info.value) return deleteTNodeX(root->Right, x);
    else {
        TNode *p = root;
        if (root->Left == NULL) {
            root = root->Right;
            delete p;
        } else if (root->Right == NULL) {
            root = root->Left;
            delete p;
        } else {
            TNode *q = findTNodeReplace(p);
            delete q;
        }
    }
    return 1;
}

void showBSTNode(TNode *root) {
    if (root == NULL) return;
    printf("%d ", root->Info.value);
    showBSTNode(root->Left);
    showBSTNode(root->Right);
}

void createBTreeFromArray(BTree &bt, Itemtype a[], int n) {
    initBtree(bt);
    for (int i = 0; i < n; i++) {
        insertTNode(bt.Root, a[i]);
    }
}

void createAutomaticBTree(BTree &bt) {
    int n;
    Itemtype x;
    printf("Cho biet so nut cua cay: ");
    scanf("%d", &n);
    initBtree(bt);
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        x.value = rand() % 200 - 100;
        insertTNode(bt.Root, x);
    }
    printf("Da tao cay BST tu dong voi %d nut!\n", n);
}

void createBTreeFromKeyboard(BTree &bt) {
    int n;
    Itemtype x;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);
    initBtree(bt);
    for (int i = 0; i < n; i++) {
        printf("Nhap gia tri phan tu %d: ", i + 1);
        scanf("%d", &x.value);
        insertTNode(bt.Root, x);
    }
}

int countGreaterThanX(TNode *root, int x) {
    if (root == NULL) return 0;
    int count = (root->Info.value > x) ? 1 : 0;
    return count + countGreaterThanX(root->Left, x) + countGreaterThanX(root->Right, x);
}

int main() {
    BTree bt;
    initBtree(bt);
    int choice, n;
    Itemtype x, a[100];

    do {
        printf("\n===== MENU CAY BST SO NGUYEN =====");
        printf("\n1. Tao cay tu mang co san");
        printf("\n2. Tao cay bang tay");
        printf("\n3. Tao cay ngau nhien");
        printf("\n4. Hien thi cay BST");
        printf("\n5. Duyet cay theo NLR");
        printf("\n6. Them so vao cay");
        printf("\n7. Tim kiem so trong cay");
        printf("\n8. Xoa so khoi cay");
        printf("\n9. Dem so luong phan tu > x");
        printf("\n10. Thoat");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong phan tu cua mang: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Nhap gia tri phan tu %d: ", i + 1);
                    scanf("%d", &a[i].value);
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
                printf("Cay BST: ");
                showBSTNode(bt.Root);
                printf("\n");
                break;

            case 5:
                printf("Duyet cay theo NLR: ");
                traverseNLR(bt.Root);
                printf("\n");
                break;

            case 6:
                printf("Nhap gia tri: ");
                scanf("%d", &x.value);
                insertTNode(bt.Root, x);
                printf("Da them %d vao cay BST!\n", x.value);
                break;

            case 7:
                printf("Nhap gia tri can tim: ");
                scanf("%d", &x.value);
                if (findTNode(bt.Root, x))
                    printf("Tim thay %d trong cay BST!\n", x.value);
                else
                    printf("Khong tim thay %d.\n", x.value);
                break;

            case 8:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &x.value);
                if (deleteTNodeX(bt.Root, x))
                    printf("Da xoa %d khoi cay BST.\n", x.value);
                else
                    printf("Khong tim thay %d de xoa.\n", x.value);
                break;

            case 9:
                printf("Nhap x: ");
                scanf("%d", &n);
                printf("So luong gia tri > %d trong cay: %d\n", n, countGreaterThanX(bt.Root, n));
                break;

            case 10:
                printf("Ket thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 10);

    return 0;
}
