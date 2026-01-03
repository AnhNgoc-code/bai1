#include <stdio.h>
#include <time.h>
#include <cstdlib>
struct PhanSo {
    int TuSo;   // Tử số
    int MauSo;  // Mẫu số
};
typedef PhanSo Itemtype;
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
TNode *createTNode(Itemtype x) {
    if (x.MauSo == 0) {
        printf("Loi: Mau so khong the bang 0!\n");
        return NULL;
    }

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
// duyệt cây NLR
void traverseNLR(TNode *root) {
    if (root == NULL) return;
    printf("%d/%d ", root->Info.TuSo, root->Info.MauSo);
    traverseNLR(root->Left);
    traverseNLR(root->Right);
}

//cây nhị phân tìm kiếm
// tìm kiếm phần tử dạng đệ qui
TNode *findTNode(TNode *root, Itemtype x) {
    if (root == NULL) return NULL;

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;
    float valueX = (float)x.TuSo / x.MauSo;

    if (valueX == valueRoot) return root;
    else if (valueX < valueRoot) return findTNode(root->Left, x);
    else return findTNode(root->Right, x);
}

// thêm phần tử x vào cây dạng đệ qui
int insertTNode(TNode *&root, Itemtype &x) {
    if (x.MauSo == 0) {
        printf("Loi: Mau so khong the bang 0!\n");
        return 0;
    }

    if (root == NULL) {
        root = createTNode(x);
        return 1;
    }

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;
    float valueX = (float)x.TuSo / x.MauSo;

    if (valueX < valueRoot) return insertTNode(root->Left, x);
    else if (valueX > valueRoot) return insertTNode(root->Right, x);

    return 1;
}

// XÓA TNode
// nút con thế mạng
TNode *findTNodeReplace(TNode *p)
{
    TNode *f = p;
    TNode *q = p->Right;
    while (q->Left != NULL)
    {
        f = q;
        q = q->Left;
    }
    
    p->Info = q->Info;  // Gán giá trị của nút cần thay thế

    if (f == p)
        f->Right = q->Right;
    else
        f->Left = q->Right;

    return q;
}
// xóa
int deleteTNodeX(TNode *&root, Itemtype x) {
    if (root == NULL) return 0;

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;
    float valueX = (float)x.TuSo / x.MauSo;

    if (valueX < valueRoot) return deleteTNodeX(root->Left, x);
    else if (valueX > valueRoot) return deleteTNodeX(root->Right, x);
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
            delete p;
        }
    }
    return 1;
}

// show BStree
void showBSTNode(TNode *root) {
    if (root == NULL) return;

    printf("%d/%d ", root->Info.TuSo, root->Info.MauSo);  // Hiển thị phân số

    showBSTNode(root->Left);
    showBSTNode(root->Right);
}
// tạo cây từ mảng có sẵn
void createBTreeFromArray(BTree &bt, Itemtype a[], int n) {
    initBtree(bt); // Khởi tạo cây

    for (int i = 0; i < n; i++) {
        if (a[i].MauSo == 0) {
            printf("Loi: Mau so cua phan so thu %d khong the bang 0!\n", i + 1);
            continue; // Bỏ qua phân số có mẫu số bằng 0
        }
        insertTNode(bt.Root, a[i]); // Truyền bt.Root thay vì bt
    }
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
        x.TuSo = (rand() % 199) - 99; // Sinh tử số ngẫu nhiên trong khoảng [-99, 99]
        x.MauSo = (rand() % 198) + 1; // Sinh mẫu số ngẫu nhiên tránh giá trị 0

        insertTNode(bt.Root, x); // Truyền đúng tham chiếu đến `bt.Root`
    }

    printf("Da tao cay BST tu dong voi %d nut!\n", n);
}
// Hàm tạo cây từ bàn phím
void createBTreeFromKeyboard(BTree &bt) {
    int n;
    Itemtype x;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);

    initBtree(bt);  // Khởi tạo cây

    for (int i = 0; i < n; i++) {
        do {
            printf("Nhap tu so va mau so phan tu %d: ", i + 1);
            scanf("%d%d", &x.TuSo, &x.MauSo);
            if (x.MauSo == 0)
                printf("Loi: Mau so khong the bang 0! Nhap lai.\n");
        } while (x.MauSo == 0); // Lặp lại nếu mẫu số bằng 0

        insertTNode(bt.Root, x);
    }
}
// đếm phân số có giá trị lớn hơn 1
int countPhanSoGreaterThanOne(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, số phân số > 1 là 0

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;
    int count = (valueRoot > 1) ? 1 : 0;  // Nếu phân số lớn hơn 1, tăng biến đếm

    return count + countPhanSoGreaterThanOne(root->Left) + countPhanSoGreaterThanOne(root->Right);
}

// tối giản tất cả các nút ( phân số ) của cây
// tìm UCLN

int UCLN(int a, int b) {
    if (b == 0) return a;
    return UCLN(b, a % b);
}
// tối giản
void ToiGian(TNode *root) {
    if (root == NULL) return;

    int ucln = UCLN(root->Info.TuSo, root->Info.MauSo);
    root->Info.TuSo /= ucln;
    root->Info.MauSo /= ucln;

    ToiGian(root->Left);
    ToiGian(root->Right);
}

// tím kiếm có phân số nào bằng x hay không
TNode *findPhanSo(TNode *root, PhanSo x) {
    if (root == NULL) 
        return NULL;  // Nếu cây rỗng, không tìm thấy
    
    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;
    float valueX = (float)x.TuSo / x.MauSo;

    if (valueX == valueRoot) 
        return root;  // Tìm thấy phân số trên cây

    if (valueX < valueRoot) 
        return findPhanSo(root->Left, x);  // Tìm tiếp bên trái

    return findPhanSo(root->Right, x);  // Tìm tiếp bên phải
}

// hàm main

int main() {
    BTree bt;
    initBtree(bt);
    int choice, n;
    PhanSo x, a[100];

    do {
        printf("\n===== MENU CAY BST PHAN SO =====");
        printf("\n1. Tao cay tu mang co san");
        printf("\n2. Tao cay bang tay");
        printf("\n3. Tao cay ngau nhien");
        printf("\n4. Hien thi cay BST");
        printf("\n5. Duyet cay theo NLR");
        printf("\n6. Them phan so vao cay");
        printf("\n7. Tim kiem phan so trong cay");
        printf("\n8. Xoa phan so khoi cay");
        printf("\n9. Dem so luong phan so > 1");
        printf("\n10. Toi gian tat ca phan so tren cay");
        printf("\n11. Thoat");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong phan tu cua mang: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    do {
                        printf("Nhap tu so va mau so phan tu %d: ", i + 1);
                        scanf("%d%d", &a[i].TuSo, &a[i].MauSo);
                        if (a[i].MauSo == 0)
                            printf("Loi: Mau so khong the bang 0! Nhap lai.\n");
                    } while (a[i].MauSo == 0);
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
                printf("Cay BST Phan So:\n");
                showBSTNode(bt.Root);
                printf("\n");
                break;

            case 5:
                printf("Duyet cay theo NLR: ");
                traverseNLR(bt.Root);
                printf("\n");
                break;

            case 6:
                do {
                    printf("Nhap tu so va mau so: ");
                    scanf("%d%d", &x.TuSo, &x.MauSo);
                    if (x.MauSo == 0)
                        printf("Loi: Mau so khong the bang 0! Nhap lai.\n");
                } while (x.MauSo == 0);
                insertTNode(bt.Root, x);
                printf("Da them phan so %d/%d vao cay BST!\n", x.TuSo, x.MauSo);
                break;

            case 7:
                printf("Nhap tu so va mau so can tim: ");
                scanf("%d%d", &x.TuSo, &x.MauSo);
                if (findPhanSo(bt.Root, x))
                    printf("Tim thay phan so %d/%d trong cay BST!\n", x.TuSo, x.MauSo);
                else
                    printf("Khong tim thay phan so %d/%d.\n", x.TuSo, x.MauSo);
                break;

            case 8:
                printf("Nhap tu so va mau so can xoa: ");
                scanf("%d%d", &x.TuSo, &x.MauSo);
                if (deleteTNodeX(bt.Root, x))
                    printf("Da xoa phan so %d/%d khoi cay BST.\n", x.TuSo, x.MauSo);
                else
                    printf("Khong tim thay phan so %d/%d de xoa.\n", x.TuSo, x.MauSo);
                break;

            case 9:
                printf("So phan so > 1 trong cay: %d\n", countPhanSoGreaterThanOne(bt.Root));
                break;

            case 10:
                ToiGian(bt.Root);
                printf("Da toi gian tat ca phan so trong cay!\n");
                break;

            case 11:
                printf("Ket thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 11);

    return 0;
}






