#include <stdio.h>
#include <stdlib.h>

// ======= Định nghĩa Phân số ======= //
struct PhanSo {
    int TuSo;
    int MauSo;
};

typedef PhanSo Itemtype;

// ======= Định nghĩa Node cây ======= //
struct TNode {
    Itemtype Info;
    TNode *Left;
    TNode *Right;
};

// ======= Định nghĩa Cây ======= //
struct BSTree {
    TNode *Root;
};

// ======= Hàm xử lý phân số ======= //
Itemtype inputFraction(){
    Itemtype ps;
    printf("Nhap tu so: ");
    scanf("%d", &ps.TuSo);
    do {
        printf("Nhap mau so (khac 0): ");
        scanf("%d", &ps.MauSo);
        if(ps.MauSo == 0) printf("Mau so phai khac 0!\n");
    } while(ps.MauSo == 0);
    return ps;
}

void outputFraction(Itemtype ps){
    printf("%d/%d", ps.TuSo, ps.MauSo);
}

// So sánh hai phân số
int compareFraction(Itemtype a, Itemtype b){
    int left = a.TuSo * b.MauSo;
    int right = b.TuSo * a.MauSo;
    if(left > right) return 1;
    else if(left < right) return -1;
    else return 0;
}

// ======= Các hàm cơ bản cho Node, Cây ======= //
TNode* createTNode(Itemtype x){
    TNode* p = new TNode;
    if(p == NULL){
        printf("Khong du bo nho!\n");
        return NULL;
    }
    p->Info = x;
    p->Left = NULL;
    p->Right = NULL;
    return p;
}

void initBSTree(BSTree &bt){
    bt.Root = NULL;
}

// Chèn Node vào cây
int insertTNode(TNode *&root, TNode *p){
    if(p == NULL) return 0;
    if(root == NULL){
        root = p;
        return 1;
    }
    if(compareFraction(root->Info, p->Info) == 0) return 0; // trùng
    if(compareFraction(root->Info, p->Info) > 0)
        return insertTNode(root->Left, p);
    else
        return insertTNode(root->Right, p);
}

// ======= Các thao tác trên cây ======= //

// Duyệt NLR (Node Left Right)
void traverseNLR(TNode* root){
    if(root == NULL) return;
    outputFraction(root->Info);
    printf(" ");
    traverseNLR(root->Left);
    traverseNLR(root->Right);
}

// Tìm kiếm Node có giá trị x
TNode* findTNode(TNode *root, Itemtype x){
    if(root == NULL) return NULL;
    int cmp = compareFraction(root->Info, x);
    if(cmp == 0) return root;
    else if(cmp > 0)
        return findTNode(root->Left, x);
    else
        return findTNode(root->Right, x);
}

// Xóa toàn bộ cây
void deleteTree(TNode* &root){
    if(root == NULL) return;
    deleteTree(root->Left);
    deleteTree(root->Right);
    delete root;
    root = NULL;
}

// ======= Hàm chính để test ======= //
int main(){
    BSTree bt;
    initBSTree(bt);

    int n;
    printf("Nhap so luong phan so: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        printf("Nhap phan so thu %d:\n", i+1);
        Itemtype ps = inputFraction();
        TNode* p = createTNode(ps);
        insertTNode(bt.Root, p);
    }

    printf("\nCay duyet theo NLR: ");
    traverseNLR(bt.Root);

    printf("\n\nTim kiem phan so x trong cay: \n");
    Itemtype x = inputFraction();
    TNode* found = findTNode(bt.Root, x);
    if(found != NULL){
        printf("Tim thay: ");
        outputFraction(found->Info);
    } else {
        printf("Khong tim thay phan so!\n");
    }

    printf("\n\nXoa toan bo cay!\n");
    deleteTree(bt.Root);

    if(bt.Root == NULL) printf("Cay da bi xoa xong.\n");

    return 0;
}
int countGreaterThan1(TNode* root){
    if(root == NULL) return 0;
    int count = 0;
    if(root->Info.TuSo > root->Info.MauSo) count++;
    count += countGreaterThan1(root->Left);
    count += countGreaterThan1(root->Right);
    return count;
}
void sumFractionTree(TNode* root, int &Tu, int &Mau){
    if(root == NULL) return;
    
    Tu = Tu * root->Info.MauSo + root->Info.TuSo * Mau;
    Mau = Mau * root->Info.MauSo;
    
    sumFractionTree(root->Left, Tu, Mau);
    sumFractionTree(root->Right, Tu, Mau);
}
