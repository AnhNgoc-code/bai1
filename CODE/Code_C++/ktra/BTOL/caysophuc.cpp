#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct SoPhuc {
    float thuc;
    float ao;
};
typedef SoPhuc Itemtype;

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

float modulus(Itemtype x) {
    return x.thuc * x.thuc + x.ao * x.ao;
}

int insertTNode(TNode *&root, Itemtype x) {
    if (root == NULL) {
        root = createTNode(x);
        return 1;
    }
    float modRoot = modulus(root->Info);
    float modX = modulus(x);
    if (modX < modRoot)
        return insertTNode(root->Left, x);
    else if (modX > modRoot)
        return insertTNode(root->Right, x);
    return 1;
}

TNode *findTNode(TNode *root, Itemtype x) {
    if (root == NULL) return NULL;
    float modRoot = modulus(root->Info);
    float modX = modulus(x);
    if (modX == modRoot) return root;
    else if (modX < modRoot) return findTNode(root->Left, x);
    else return findTNode(root->Right, x);
}

TNode *findTNodeReplace(TNode *p) {
    TNode *f = p;
    TNode *q = p->Right;
    while (q->Left != NULL) {
        f = q;
        q = q->Left;
    }
    p->Info = q->Info;
    if (f == p) f->Right = q->Right;
    else f->Left = q->Right;
    return q;
}

int deleteTNodeX(TNode *&root, Itemtype x) {
    if (root == NULL) return 0;
    float modRoot = modulus(root->Info);
    float modX = modulus(x);
    if (modX < modRoot) return deleteTNodeX(root->Left, x);
    else if (modX > modRoot) return deleteTNodeX(root->Right, x);
    else {
        TNode *p = root;
        if (root->Left == NULL)
            root = root->Right;
        else if (root->Right == NULL)
            root = root->Left;
        else {
            TNode *q = findTNodeReplace(p);
            delete q;
            return 1;
        }
        delete p;
        return 1;
    }
}

void traverseNLR(TNode *root) {
    if (root == NULL) return;
    printf("%.2f + %.2fi\n", root->Info.thuc, root->Info.ao);
    traverseNLR(root->Left);
    traverseNLR(root->Right);
}

int countModulusGreaterThanOne(TNode *root) {
    if (root == NULL) return 0;
    float mod = modulus(root->Info);
    int count = (mod > 1.0f) ? 1 : 0;
    return count + countModulusGreaterThanOne(root->Left) + countModulusGreaterThanOne(root->Right);
}

void createAutomaticBTree(BTree &bt) {
    int n;
    printf("Nhap so luong so phuc: ");
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    initBtree(bt);
    for (int i = 0; i < n; i++) {
        Itemtype x;
        x.thuc = (float)(rand() % 200 - 100);
        x.ao = (float)(rand() % 200 - 100);
        insertTNode(bt.Root, x);
    }
    printf("Da tao cay BST tu dong voi %d nut!\n", n);
}

void createBTreeFromKeyboard(BTree &bt) {
    int n;
    Itemtype x;
    printf("Nhap so luong so phuc: ");
    scanf("%d", &n);
    initBtree(bt);
    for (int i = 0; i < n; i++) {
        printf("Nhap phan thuc va ao cua so phuc thu %d: ", i + 1);
        scanf("%f%f", &x.thuc, &x.ao);
        insertTNode(bt.Root, x);
    }
}

int main() {
    BTree bt;
    initBtree(bt);
    int choice;
    Itemtype x;

    do {
        printf("\n===== MENU CAY BST SO PHUC =====\n");
        printf("1. Tao cay bang tay\n");
        printf("2. Tao cay ngau nhien\n");
        printf("3. Duyet cay theo NLR\n");
        printf("4. Them so phuc vao cay\n");
        printf("5. Tim so phuc trong cay\n");
        printf("6. Xoa so phuc khoi cay\n");
        printf("7. Dem so phuc co modulus > 1\n");
        printf("8. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createBTreeFromKeyboard(bt);
                break;
            case 2:
                createAutomaticBTree(bt);
                break;
            case 3:
                printf("Cay BST So Phuc:\n");
                traverseNLR(bt.Root);
                break;
            case 4:
                printf("Nhap phan thuc va ao: ");
                scanf("%f%f", &x.thuc, &x.ao);
                insertTNode(bt.Root, x);
                break;
            case 5:
                printf("Nhap phan thuc va ao can tim: ");
                scanf("%f%f", &x.thuc, &x.ao);
                if (findTNode(bt.Root, x))
                    printf("Tim thay so phuc %.2f + %.2fi trong cay!\n", x.thuc, x.ao);
                else
                    printf("Khong tim thay!\n");
                break;
            case 6:
                printf("Nhap phan thuc va ao can xoa: ");
                scanf("%f%f", &x.thuc, &x.ao);
                if (deleteTNodeX(bt.Root, x))
                    printf("Da xoa so phuc %.2f + %.2fi khoi cay!\n", x.thuc, x.ao);
                else
                    printf("Khong tim thay de xoa!\n");
                break;
            case 7:
                printf("So luong so phuc co modulus > 1: %d\n", countModulusGreaterThanOne(bt.Root));
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
