#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
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
//tìm phân số x có trên cây không
TNode *findFraction(TNode *root, Itemtype x) {
    if (root == NULL) return NULL;  // Nếu cây rỗng, không tìm thấy

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;
    float valueX = (float)x.TuSo / x.MauSo;

    if (valueX == valueRoot) return root;  // Nếu tìm thấy, trả về nút
    else if (valueX < valueRoot) return findFraction(root->Left, x);  // Tìm ở cây con trái
    else return findFraction(root->Right, x);  // Tìm ở cây con phải
}

//hàm xóa những phân số có giá trị > hơn 2
void deleteGreaterThanTwo(TNode *&root) {
    if (root == NULL) return;  // Nếu cây rỗng, không cần làm gì

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;

    // Duyệt cây con trước để đảm bảo không mất thông tin khi xóa nút gốc
    deleteGreaterThanTwo(root->Left);
    deleteGreaterThanTwo(root->Right);

    if (valueRoot > 2) {  // Nếu giá trị phân số lớn hơn 2, tiến hành xóa
        deleteTNodeX(root, root->Info);
    }
}
// xóa phân số có mẫu là số nguyên tố
int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void deleteFractionWithPrimeDenominator(TNode *&root) {
    if (root == NULL) return;  // Nếu cây rỗng, không cần làm gì

    // Duyệt cây con trước để đảm bảo không mất thông tin khi xóa nút gốc
    deleteFractionWithPrimeDenominator(root->Left);
    deleteFractionWithPrimeDenominator(root->Right);

    if (isPrime(root->Info.MauSo)) {  // Nếu mẫu số là số nguyên tố, tiến hành xóa
        deleteTNodeX(root, root->Info);
    }
}

//hàm xóa phân số có mẫu số là số chính phương
int isPerfectSquare(int n) {
    int root = sqrt(n);
    return (root * root == n);
}

void deleteFractionWithPerfectSquareDenominator(TNode *&root) {
    if (root == NULL) return;

    deleteFractionWithPerfectSquareDenominator(root->Left);
    deleteFractionWithPerfectSquareDenominator(root->Right);

    if (isPerfectSquare(root->Info.MauSo)) {
        deleteTNodeX(root, root->Info);
    }
}
//hàm xóa phân số có mẫu số là số hoàn hảo
int isPerfectNumber(int n) {
    if (n < 2) return 0;
    int sum = 1; // 1 luôn là ước của mọi số

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return (sum == n); // Nếu tổng ước bằng chính nó, là số hoàn hảo
}
void deleteFractionWithPerfectNumberDenominator(TNode *&root) {
    if (root == NULL) return;  // Nếu cây rỗng, không cần làm gì

    deleteFractionWithPerfectNumberDenominator(root->Left);
    deleteFractionWithPerfectNumberDenominator(root->Right);

    if (isPerfectNumber(root->Info.MauSo)) {  // Nếu mẫu số là số hoàn hảo, tiến hành xóa
        deleteTNodeX(root, root->Info);
    }
}
// xóa cây
void deleteTree(TNode *&root) {
    if (root == NULL) return;  // Nếu cây rỗng, không cần làm gì

    deleteTree(root->Left);  // Xóa cây con trái
    deleteTree(root->Right); // Xóa cây con phải

    delete root;  // Xóa nút hiện tại
    root = NULL;  // Đặt lại root thành NULL
}
int main() {
    BTree bt;
    initBtree(bt);
    int choice, n;
    Itemtype x, a[100];

    do {
        printf("\n====== MENU CAY BST ======");
        printf("\n1. Tao cay tu mang co san");
        printf("\n2. Tao cay bang tay");
        printf("\n3. Tao cay ngau nhien");
        printf("\n4. Hien thi cay BST");
        printf("\n5. Duyet cay theo NLR");
        printf("\n6. Them phan so vao cay");
        printf("\n7. Xoa phan so khoi cay");
        printf("\n8. Tim phan so x trong cay");
        printf("\n9. Xoa phan so co gia tri > 2");
        printf("\n10. Xoa phan so co mau so la so nguyen to");
        printf("\n11. Xoa phan so co mau so la so chinh phuong");
        printf("\n12. Xoa phan so co mau so la so hoan hao");
        printf("\n13. Xoa toan bo cay");
        printf("\n14. Thoat");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong phan tu cua mang: ");
                scanf("%d", &n);
                printf("Nhap cac phan so (tu so/mau so):\n");
                for (int i = 0; i < n; i++) {
                    printf("Phan so %d: ", i + 1);
                    scanf("%d%d", &a[i].TuSo, &a[i].MauSo);
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
                printf("Noi dung cay BST:\n");
                showBSTNode(bt.Root);
                printf("\n");
                break;

            case 5:
                printf("Duyet cay theo NLR: ");
                traverseNLR(bt.Root);
                printf("\n");
                break;

            case 6:
                printf("Nhap phan so can them vao cay (tu so/mau so): ");
                scanf("%d%d", &x.TuSo, &x.MauSo);
                insertTNode(bt.Root, x);
                printf("Da them phan so %d/%d vao cay BST!\n", x.TuSo, x.MauSo);
                break;

            case 7:
                printf("Nhap phan so can xoa (tu so/mau so): ");
                scanf("%d%d", &x.TuSo, &x.MauSo);
                if (deleteTNodeX(bt.Root, x))
                    printf("Da xoa phan so %d/%d khoi cay BST.\n", x.TuSo, x.MauSo);
                else
                    printf("Khong tim thay phan so %d/%d trong cay BST.\n", x.TuSo, x.MauSo);
                break;

            case 8:
                printf("Nhap phan so can tim (tu so/mau so): ");
                scanf("%d%d", &x.TuSo, &x.MauSo);
                if (findTNode(bt.Root, x))
                    printf("Tim thay phan so %d/%d trong cay BST!\n", x.TuSo, x.MauSo);
                else
                    printf("Khong tim thay phan so %d/%d trong cay BST.\n", x.TuSo, x.MauSo);
                break;

            case 9:
                deleteGreaterThanTwo(bt.Root);
                printf("Da xoa tat ca phan so co gia tri > 2!\n");
                break;

            case 10:
                deleteFractionWithPrimeDenominator(bt.Root);
                printf("Da xoa tat ca phan so co mau so la so nguyen to!\n");
                break;

            case 11:
                deleteFractionWithPerfectSquareDenominator(bt.Root);
                printf("Da xoa tat ca phan so co mau so la so chinh phuong!\n");
                break;

            case 12:
                deleteFractionWithPerfectNumberDenominator(bt.Root);
                printf("Da xoa tat ca phan so co mau so la so hoan hao!\n");
                break;

            case 13:
                deleteTree(bt.Root);
                printf("Da xoa toan bo cay!\n");
                break;

            case 14:
                printf("Ket thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 14);

    return 0;
}
