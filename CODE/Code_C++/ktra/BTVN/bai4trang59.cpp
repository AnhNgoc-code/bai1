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
//=======================================bắt đầu bái 4 (bt về nhà)=============================================

// tính tổng các phân số
PhanSo sumPhanSo(TNode *root) {
    if (root == NULL) 
        return {0, 1};  // Nếu cây rỗng, tổng là 0/1

    PhanSo leftSum = sumPhanSo(root->Left);
    PhanSo rightSum = sumPhanSo(root->Right);

    // Quy đồng mẫu số để cộng các phân số
    int commonDenominator = leftSum.MauSo * rightSum.MauSo * root->Info.MauSo;
    int newNumerator = leftSum.TuSo * rightSum.MauSo * root->Info.MauSo +
                       rightSum.TuSo * leftSum.MauSo * root->Info.MauSo +
                       root->Info.TuSo * leftSum.MauSo * rightSum.MauSo;

    PhanSo result = {newNumerator, commonDenominator};

    // Tối giản kết quả
    int ucln = UCLN(result.TuSo, result.MauSo);
    result.TuSo /= ucln;
    result.MauSo /= ucln;

    return result;
}

//tìm phân số nhỏ nhất
TNode *findMinPhanSo(TNode *root) {
    if (root == NULL) 
        return NULL;  // Nếu cây rỗng, không có phân số nào

    TNode *minNode = root;
    float minValue = (float)root->Info.TuSo / root->Info.MauSo;

    TNode *leftMin = findMinPhanSo(root->Left);
    TNode *rightMin = findMinPhanSo(root->Right);

    if (leftMin != NULL) {
        float leftValue = (float)leftMin->Info.TuSo / leftMin->Info.MauSo;
        if (leftValue < minValue) {
            minNode = leftMin;
            minValue = leftValue;
        }
    }

    if (rightMin != NULL) {
        float rightValue = (float)rightMin->Info.TuSo / rightMin->Info.MauSo;
        if (rightValue < minValue) {
            minNode = rightMin;
            minValue = rightValue;
        }
    }

    return minNode;
}

// tìm phân số lớn nhất
TNode *findMaxPhanSo(TNode *root) {
    if (root == NULL) 
        return NULL;  // Nếu cây rỗng, không có phân số nào

    TNode *maxNode = root;
    float maxValue = (float)root->Info.TuSo / root->Info.MauSo;

    TNode *leftMax = findMaxPhanSo(root->Left);
    TNode *rightMax = findMaxPhanSo(root->Right);

    if (leftMax != NULL) {
        float leftValue = (float)leftMax->Info.TuSo / leftMax->Info.MauSo;
        if (leftValue > maxValue) {
            maxNode = leftMax;
            maxValue = leftValue;
        }
    }

    if (rightMax != NULL) {
        float rightValue = (float)rightMax->Info.TuSo / rightMax->Info.MauSo;
        if (rightValue > maxValue) {
            maxNode = rightMax;
            maxValue = rightValue;
        }
    }

    return maxNode;
}

//hàm liệt kê các phân số có tử số lớn hơn mẫu số
void listPhanSoTuLonHonMau(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không hiển thị gì

    float valueRoot = (float)root->Info.TuSo / root->Info.MauSo;

    if (root->Info.TuSo > root->Info.MauSo) // Kiểm tra điều kiện
        printf("%d/%d ", root->Info.TuSo, root->Info.MauSo);

    listPhanSoTuLonHonMau(root->Left);  // Duyệt cây con trái
    listPhanSoTuLonHonMau(root->Right); // Duyệt cây con phải
}

//hàm tìm phân số nhỏ hơn mẫu số
void listPhanSoTuBeHonMau(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không hiển thị gì

    if (root->Info.TuSo < root->Info.MauSo) // Kiểm tra điều kiện
        printf("%d/%d ", root->Info.TuSo, root->Info.MauSo);

    listPhanSoTuBeHonMau(root->Left);  // Duyệt cây con trái
    listPhanSoTuBeHonMau(root->Right); // Duyệt cây con phải
}

//liệt kê các phân số có đồng thời tử số và mẫu số là số nguyên tố// có thể đổi
int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
void listPhanSoNguyenTo(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không hiển thị gì

    if (isPrime(root->Info.TuSo) && isPrime(root->Info.MauSo)) // Kiểm tra điều kiện
        printf("%d/%d ", root->Info.TuSo, root->Info.MauSo);

    listPhanSoNguyenTo(root->Left);  // Duyệt cây con trái
    listPhanSoNguyenTo(root->Right); // Duyệt cây con phải
}

// liệt kê các phân số ở mức k (k nhập từ bàn phím)
void listPhanSoAtLevelK(TNode *root, int k, int currentLevel) {
    if (root == NULL) return;  // Nếu cây rỗng, không hiển thị gì

    if (currentLevel == k)  // Kiểm tra nếu nút đang xét nằm ở mức `k`
        printf("%d/%d ", root->Info.TuSo, root->Info.MauSo);

    listPhanSoAtLevelK(root->Left, k, currentLevel + 1);  // Duyệt cây con trái
    listPhanSoAtLevelK(root->Right, k, currentLevel + 1); // Duyệt cây con phải
}

//đếm số lượng phân số ở mức k
int countPhanSoAtLevelK(TNode *root, int k, int currentLevel) {
    if (root == NULL) return 0;  // Nếu cây rỗng, không có phân số nào

    int count = (currentLevel == k) ? 1 : 0;  // Nếu nút đang xét ở mức `k`, tăng biến đếm

    return count + countPhanSoAtLevelK(root->Left, k, currentLevel + 1) 
                 + countPhanSoAtLevelK(root->Right, k, currentLevel + 1);
}

//tình tổng các phân số ở mức k
PhanSo sumPhanSoAtLevelK(TNode *root, int k, int currentLevel) {
    if (root == NULL) 
        return {0, 1};  // Nếu cây rỗng, tổng là 0/1

    PhanSo leftSum = sumPhanSoAtLevelK(root->Left, k, currentLevel + 1);
    PhanSo rightSum = sumPhanSoAtLevelK(root->Right, k, currentLevel + 1);

    if (currentLevel == k) {  
        // Quy đồng mẫu số trước khi cộng
        int commonDenominator = leftSum.MauSo * rightSum.MauSo * root->Info.MauSo;
        int newNumerator = leftSum.TuSo * rightSum.MauSo * root->Info.MauSo +
                           rightSum.TuSo * leftSum.MauSo * root->Info.MauSo +
                           root->Info.TuSo * leftSum.MauSo * rightSum.MauSo;

        PhanSo result = {newNumerator, commonDenominator};

        // Tối giản kết quả
        int ucln = UCLN(result.TuSo, result.MauSo);
        result.TuSo /= ucln;
        result.MauSo /= ucln;

        return result;
    }

    return {leftSum.TuSo + rightSum.TuSo, leftSum.MauSo}; // Nếu không phải mức k, bỏ qua
}

// hàm main

int main() {
    BTree bt;
    initBtree(bt);
    int choice, n, k;
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
        printf("\n11. Tinh tong cac phan so");
        printf("\n12. Tim phan so nho nhat");
        printf("\n13. Tim phan so lon nhat");
        printf("\n14. Liet ke phan so co tu so > mau so");
        printf("\n15. Liet ke phan so co tu so < mau so");
        printf("\n16. Liet ke phan so co ca tu so va mau so la so nguyen to");
        printf("\n17. Liet ke phan so o muc k");
        printf("\n18. Dem so luong phan so o muc k");
        printf("\n19. Tinh tong cac phan so o muc k");
        printf("\n20. Thoat");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
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
                showBSTNode(bt.Root);
                printf("\n");
                break;
            case 5:
                traverseNLR(bt.Root);
                printf("\n");
                break;
            case 6:
                insertTNode(bt.Root, x);
                break;
            case 7:
                findPhanSo(bt.Root, x);
                break;
            case 8:
                deleteTNodeX(bt.Root, x);
                break;
            case 9:
                countPhanSoGreaterThanOne(bt.Root);
                break;
            case 10:
                ToiGian(bt.Root);
                break;
            case 11:
                sumPhanSo(bt.Root);
                break;
            case 12:
                findMinPhanSo(bt.Root);
                break;
            case 13:
                findMaxPhanSo(bt.Root);
                break;
            case 14:
                listPhanSoTuLonHonMau(bt.Root);
                break;
            case 15:
                listPhanSoTuBeHonMau(bt.Root);
                break;
            case 16:
                listPhanSoNguyenTo(bt.Root);
                break;
            case 17:
                listPhanSoAtLevelK(bt.Root, k, 0);
                break;
            case 18:
                countPhanSoAtLevelK(bt.Root, k, 0);
                break;
            case 19:
                sumPhanSoAtLevelK(bt.Root, k, 0);
                break;
            case 20:
                printf("Ket thuc chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 20);

    return 0;
}






