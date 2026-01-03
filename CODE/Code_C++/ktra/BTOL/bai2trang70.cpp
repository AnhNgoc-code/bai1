#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
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
void traverseNLR(TNode *root)
{
    if(root==NULL)
        return ;
    printf("%4d", root->Info);
    traverseNLR(root->Left);
    traverseNLR(root->Right);
}
//cây nhị phân tìm kiếm
// tìm kiếm phần tử dạng đệ qui
TNode *findTNode(TNode *root, Itemtype x)
{
    if(root == NULL)
        return NULL;
    if(root->Info== x)
        return root;
    else if(root ->Info > x)
        return findTNode(root->Left, x);
    else
        return findTNode(root->Right,x);
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

    printf("Da tao cay BST tu dong với %d nút!\n", n);
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

// XÓA TNode
// nút con thế mạng
TNode *findTNodeReplace(TNode *p)
{
    TNode*f=p;
    TNode*q=p->Right;
    while(q->Left != NULL)
    {
        f =q;
        q = q->Left;
    }
    p->Info = q->Info;
    if(f==p)
        f->Right = q->Right;
    else
        f->Left=q->Left;
    return q;
}
int deleteTNodeX(TNode *&root, Itemtype x)
{
	if(root==NULL)
		return 0;
	if(root->Info > x)
		return deleteTNodeX(root->Left,x);
	else if(root->Info<x)
		return deleteTNodeX(root->Right,x);
	else
	{
		TNode *p = root;
		if(root->Left==NULL)
		{
			root = root->Right;
			delete p;
		}
		else if(root->Right == NULL)
		{
			root = root->Left;
			delete p;
		}
		else
		{
			TNode *q = findTNodeReplace(p);
			delete p;
		}
	}
	return 1;
}
// tìm node x có trên cây khôg
int isNodeExists(TNode *root, Itemtype x) {
    if (root == NULL) 
        return 0;  // Cây rỗng, không có nút nào

    if (root->Info == x) 
        return 1;  // Tìm thấy nút x trong cây

    if (x < root->Info) 
        return isNodeExists(root->Left, x);  // Tìm tiếp ở cây con trái

    return isNodeExists(root->Right, x);  // Tìm tiếp ở cây con phải
}
//hiển thị nội dung của node p
void showTNode(TNode *p) 
{
    if (p == NULL) 
    {
        printf("Nut khong ton tai.\n");
        return;
    }

    printf("gia tri cua nut: %d\n", p->Info);
}
// show BStree
void showBSTNode(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không hiển thị gì

    printf("%4d ", root->Info);  // Hiển thị giá trị nút gốc

    showBSTNode(root->Left);  // Duyệt cây con trái
    showBSTNode(root->Right); // Duyệt cây con phải
}
//các hàm kiểm  tra số nguyên tố, chính phương, hoàn hảo
//số nguyên tố
int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// số chính phương
int isPerfectSquare(int n) {
    int root = sqrt(n);
    return (root * root == n);
}

// số hoàn hảo
int isPerfectNumber(int n) {
    if (n < 2) return 0;
    int sum = 1; // 1 luôn là ước của mọi số

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return (sum == n); // Nếu tổng ước đúng bằng chính nó, là số hoàn hảo
}

//số thịnh vượng
int isAbundant(int n) {
    int sum = 1;  
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return (sum > n);
}

// số yếu
int isDeficient(int n) {
    int sum = 1;  
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return (sum < n);
}


// tìm 1 giá trị x trong cây
TNode *findTNodeX(TNode *root, Itemtype x) 
{
    if (root == NULL) 
        return NULL; // Không tìm thấy x trong cây

    if (root->Info == x) 
        return root; // Tìm thấy nút chứa x

    if (x < root->Info) 
        return findTNode(root->Left, x); // Tìm bên trái nếu x nhỏ hơn nút hiện tại

    return findTNode(root->Right, x); // Tìm bên phải nếu x lớn hơn nút hiện tại
}
// xóa nút con trái của 1 nút T
void deleteLeftChild(TNode *t) {
    if (t == NULL || t->Left == NULL) return;  // Kiểm tra nút tồn tại

    TNode *temp = t->Left;  // Lưu nút con trái
    t->Left = temp->Right;  // Nếu có cây con bên phải, nối vào vị trí nút trái
    delete temp;  // Giải phóng bộ nhớ
}

// xóa 1 nút con phải cảu 1 nút t
void deleteRightChild(TNode *t) {
    if (t == NULL || t->Right == NULL) return;  // Kiểm tra nút tồn tại

    TNode *temp = t->Right;  // Lưu nút con phải
    t->Right = temp->Left;   // Nếu có cây con bên trái, nối vào vị trí nút phải
    delete temp;  // Giải phóng bộ nhớ
}


// xuất các phần tử the thứ tự giảm dần
void traverseDescending(TNode *root) {
    if (root == NULL) return;

    traverseDescending(root->Right);  // Duyệt cây con phải trước (giá trị lớn hơn)
    printf("%4d ", root->Info);        // In giá trị của nút hiện tại
    traverseDescending(root->Left);   // Duyệt cây con trái sau (giá trị nhỏ hơn)
}
// tăng dần
void traverseAscending(TNode *root) {
    if (root == NULL) return;

    traverseAscending(root->Left);  // Duyệt cây con trái trước (giá trị nhỏ hơn)
    printf("%4d ", root->Info);      // In giá trị của nút hiện tại
    traverseAscending(root->Right); // Duyệt cây con phải sau (giá trị lớn hơn)
}
// các thao tác tính toán trên cây ==================================================ádasdasdasdasdasd
// đếm số giá trị lớn hơn x
int countGreaterThanX(TNode *root, Itemtype x) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    int count = (root->Info > x) ? 1 : 0;  // Nếu giá trị nút lớn hơn x, tăng biến đếm

    return count + countGreaterThanX(root->Left, x) + countGreaterThanX(root->Right, x);
}

// đếm số giá trị nhỏ hơn x
int countInRange(TNode *root, Itemtype x, Itemtype y) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    int count = (root->Info >= x && root->Info <= y) ? 1 : 0;  // Nếu giá trị nằm trong khoảng [x, y], tăng biến đếm

    return count + countInRange(root->Left, x, y) + countInRange(root->Right, x, y);
}

//đếm số node trên cây
int countNodes(TNode *root) {
    if (root == NULL) 
        return 0; // Nếu cây rỗng, số nút là 0

    return 1 + countNodes(root->Left) + countNodes(root->Right);
}

// đếm số nút lá
int countLeafNodes(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, không có nút lá nào

    if (root->Left == NULL && root->Right == NULL) 
        return 1;  // Nếu nút hiện tại không có con, đây là nút lá

    return countLeafNodes(root->Left) + countLeafNodes(root->Right);
} 

//đếm nút lá là số chẵn
int countEvenLeafNodes(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    if (root->Left == NULL && root->Right == NULL) {  
        return (root->Info % 2 == 0) ? 1 : 0;  // Nếu là nút lá và giá trị là số chẵn, tăng biến đếm
    }// số lẻ thì %2 != 0

    return countEvenLeafNodes(root->Left) + countEvenLeafNodes(root->Right);
}


// đếm nút có 1 con
int countNodesWithOneChild(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, không có nút nào

    int count = ((root->Left == NULL && root->Right != NULL) || (root->Left != NULL && root->Right == NULL)) ? 1 : 0;

    return count + countNodesWithOneChild(root->Left) + countNodesWithOneChild(root->Right);
}
// đếm nút có 1 con và là số nguyên tố
int countNodesWithOneChild_Prime(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    int count = ((root->Left == NULL && root->Right != NULL) || (root->Left != NULL && root->Right == NULL))
                && isPrime(root->Info) ? 1 : 0;  // Nếu nút có đúng 1 con và là số nguyên tố, tăng biến đếm

    return count + countNodesWithOneChild_Prime(root->Left) + countNodesWithOneChild_Prime(root->Right);
}
// tổng các nút có 1 con là số nguyên tố
int sumNodesWithOneChild_Prime(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = ((root->Left == NULL && root->Right != NULL) || (root->Left != NULL && root->Right == NULL))
              && isPrime(root->Info) ? root->Info : 0;  // Nếu nút có đúng 1 con và là số nguyên tố, cộng vào tổng

    return sum + sumNodesWithOneChild_Prime(root->Left) + sumNodesWithOneChild_Prime(root->Right);
}


// đếm nút có 2 con
int countNodesWithTwoChildren(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, không có nút nào

    int count = (root->Left != NULL && root->Right != NULL) ? 1 : 0;  // Kiểm tra nút có cả 2 con

    return count + countNodesWithTwoChildren(root->Left) + countNodesWithTwoChildren(root->Right);
}
// đếm nút có 2 con và là số chính phương
int countNodesWithTwoChildren_PerfectSquare(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    int count = (root->Left != NULL && root->Right != NULL) && isPerfectSquare(root->Info) ? 1 : 0;  

    return count + countNodesWithTwoChildren_PerfectSquare(root->Left) + countNodesWithTwoChildren_PerfectSquare(root->Right);
}

// hàm tính tổng nút có 2 con là số chính phương
int sumNodesWithTwoChildren_PerfectSquare(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = (root->Left != NULL && root->Right != NULL) && isPerfectSquare(root->Info) ? root->Info : 0;  

    return sum + sumNodesWithTwoChildren_PerfectSquare(root->Left) + sumNodesWithTwoChildren_PerfectSquare(root->Right);
}

// hàm tính chiều cao của cây
int highTree(TNode *root) {
    if (root == NULL) 
        return -1; // Nếu cây rỗng, chiều cao là -1 (không có nút nào)

    int leftHeight = highTree(root->Left);  // Tính chiều cao cây con trái
    int rightHeight = highTree(root->Right); // Tính chiều cao cây con phải

    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

// nút có giá trị lớn nhất
TNode *findMaxNode(TNode *root) {
    if (root == NULL) return NULL; // Nếu cây rỗng, không có nút nào

    while (root->Right != NULL) { // Đi về phía bên phải đến cuối cùng
        root = root->Right;
    }
    return root; // Trả về nút có giá trị lớn nhất
}


// nút có giá trị nhỏ nhất 
TNode *findMinNode(TNode *root) {
    if (root == NULL) return NULL; // Nếu cây rỗng, không có nút nào

    while (root->Left != NULL) { // Đi về phía bên trái đến cuối cùng
        root = root->Left;
    }
    return root; // Trả về nút có giá trị nhỏ nhất
}

// xuất nội dung các nút ở mức k
void printNodesAtLevelK(TNode *root, int k) {
    if (root == NULL) return;

    if (k == 0) {
        printf("%4d ", root->Info);  // Khi đạt đúng mức `k`, in giá trị nút
    } else {
        printNodesAtLevelK(root->Left, k - 1);  // Giảm `k`, đi xuống cây con trái
        printNodesAtLevelK(root->Right, k - 1); // Giảm `k`, đi xuống cây con phải
    }
}
//xuất nội dung các nút lá ở mức k
void printLeafNodesAtLevelK(TNode *root, int k) {
    if (root == NULL) return;

    if (k == 0 && root->Left == NULL && root->Right == NULL) {
        printf("%4d ", root->Info);  // Nếu là nút lá và ở đúng mức `k`, in giá trị
    } else {
        printLeafNodesAtLevelK(root->Left, k - 1);  // Giảm `k`, đi xuống cây con trái
        printLeafNodesAtLevelK(root->Right, k - 1); // Giảm `k`, đi xuống cây con phải
    }
}

//đếm số nút ở mức k
int countNodesAtLevelK(TNode *root, int k) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    if (k == 0) return 1;  // Khi đạt đúng mức `k`, đếm nút hiện tại

    return countNodesAtLevelK(root->Left, k - 1) + countNodesAtLevelK(root->Right, k - 1);
}
// đếm số nút thấp hơn tầng k
int countNodesBelowLevelK(TNode *root, int k, int currentLevel) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    if (currentLevel >= k) return 0;  // Nếu đạt tầng `k` hoặc cao hơn, dừng đếm

    return 1 + countNodesBelowLevelK(root->Left, k, currentLevel + 1) 
             + countNodesBelowLevelK(root->Right, k, currentLevel + 1);
}
/*int sumNodesBelowLevelK(TNode *root, int k, int currentLevel) {// tổng các nút thấp hơn tầng k chọn 0 cho curr
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    if (currentLevel >= k) return 0;  // Nếu đạt tầng `k` hoặc cao hơn, dừng tính tổng

    return root->Info + sumNodesBelowLevelK(root->Left, k, currentLevel + 1) 
                      + sumNodesBelowLevelK(root->Right, k, currentLevel + 1);
}*/

// đếm số nút cao hơn tầng k
int countNodesAboveLevelK(TNode *root, int k, int currentLevel) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    if (currentLevel <= k) return 0;  // Nếu tầng hiện tại thấp hơn hoặc bằng `k`, không đếm

    return 1 + countNodesAboveLevelK(root->Left, k, currentLevel + 1) 
             + countNodesAboveLevelK(root->Right, k, currentLevel + 1);
}

/*int sumNodesAboveLevelK(TNode *root, int k, int currentLevel) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    if (currentLevel <= k) return 0;  // Nếu tầng hiện tại thấp hơn hoặc bằng `k`, không tính tổng

    return root->Info + sumNodesAboveLevelK(root->Left, k, currentLevel + 1) 
                      + sumNodesAboveLevelK(root->Right, k, currentLevel + 1);
}*/
// đếm số nút là ở mức k
int countLeafNodesAtLevelK(TNode *root, int k) {
    if (root == NULL) return 0;  // Nếu cây rỗng, số nút là 0

    if (k == 0 && root->Left == NULL && root->Right == NULL) return 1;  // Nếu là nút lá và ở đúng mức `k`, đếm

    return countLeafNodesAtLevelK(root->Left, k - 1) + countLeafNodesAtLevelK(root->Right, k - 1);
}
/*int sumNodesAtLevelK(TNode *root, int k) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    if (k == 0) return root->Info;  // Nếu đúng mức `k`, cộng giá trị nút vào tổng

    return sumNodesAtLevelK(root->Left, k - 1) + sumNodesAtLevelK(root->Right, k - 1);
}*/


//tìm phần tử có khoảng cách về giá trị gần nhất với phần tử x trong cây nếu rổng trả về -1
int findClosestValue(TNode *root, Itemtype x) {
    if (root == NULL) return -1;  // Nếu cây rỗng, trả về -1

    TNode *closest = root;  // Bắt đầu với giá trị gốc
    while (root != NULL) {
        if (abs(root->Info - x) < abs(closest->Info - x)) {
            closest = root;  // Cập nhật nếu tìm thấy giá trị gần hơn
        }

        // Duyệt tiếp xuống nhánh phù hợp
        root = (x < root->Info) ? root->Left : root->Right;
    }

    return closest->Info;  // Trả về giá trị gần nhất với x
}

////tìm phần tử có khoảng cách về giá trị xa nhất với phần tử x trong cây nếu rổng trả về -1
int findFarthestValue(TNode *root, Itemtype x) {
    if (root == NULL) return -1;  // Nếu cây rỗng, trả về -1

    TNode *farthest = root;  // Bắt đầu với giá trị gốc
    while (root != NULL) {
        if (abs(root->Info - x) > abs(farthest->Info - x)) {
            farthest = root;  // Cập nhật nếu tìm thấy giá trị xa hơn
        }

        // Duyệt tiếp xuống nhánh phù hợp
        root = (x < root->Info) ? root->Left : root->Right;
    }

    return farthest->Info;  // Trả về giá trị xa nhất với x
}

// tổng các nút trên cây
int sumNodes(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, tổng là 0

    return root->Info + sumNodes(root->Left) + sumNodes(root->Right);
}

// tổng các nút dương
int sumPositiveNodes(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = (root->Info > 0) ? root->Info : 0;  // Nếu giá trị nút dương, cộng vào tổng

    return sum + sumPositiveNodes(root->Left) + sumPositiveNodes(root->Right);
}

// tổng các nút âm
int sumNegativeNodes(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = (root->Info < 0) ? root->Info : 0;  // Nếu giá trị nút âm, cộng vào tổng

    return sum + sumNegativeNodes(root->Left) + sumNegativeNodes(root->Right);
}
// tổng các nút lẻ
int sumOddNodes(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = (root->Info % 2 != 0) ? root->Info : 0;  // Nếu nút có giá trị lẻ, cộng vào tổng

    return sum + sumOddNodes(root->Left) + sumOddNodes(root->Right);
}

//tổng các nút chẵn
int sumEvenNodes(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = (root->Info % 2 == 0) ? root->Info : 0;  // Nếu nút có giá trị chẵn, cộng vào tổng

    return sum + sumEvenNodes(root->Left) + sumEvenNodes(root->Right);
}


// tổng các số nguyê tố

int sumPrimeNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isPrime(root->Info) ? root->Info : 0;
    return sum + sumPrimeNodes(root->Left) + sumPrimeNodes(root->Right);
}
// tổng số chính phương
int sumPerfectSquareNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isPerfectSquare(root->Info) ? root->Info : 0;
    return sum + sumPerfectSquareNodes(root->Left) + sumPerfectSquareNodes(root->Right);
}
// tính tổng các số hoàn hảo
int sumPerfectNumberNodes(TNode *root) {
    if (root == NULL) return 0;  // Nếu cây rỗng, tổng là 0

    int sum = isPerfectNumber(root->Info) ? root->Info : 0;  // Nếu là số hoàn hảo, cộng vào tổng

    return sum + sumPerfectNumberNodes(root->Left) + sumPerfectNumberNodes(root->Right);
}

// tính tổng số thịnh vượng
int sumAbundantNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isAbundant(root->Info) ? root->Info : 0;
    return sum + sumAbundantNodes(root->Left) + sumAbundantNodes(root->Right);
}

// tính tổng các số yếu
int sumDeficientNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isDeficient(root->Info) ? root->Info : 0;
    return sum + sumDeficientNodes(root->Left) + sumDeficientNodes(root->Right);
}
// duyệt cây theo ứng dung stack NLR
// khai báo Stack
typedef int Itemtype;

// Stack sử dụng danh sách liên kết đơn
struct StackNode {
    Itemtype Info;
    StackNode *Next;
};

struct Stack {
    StackNode *Top;
};

// Khởi tạo Stack
void InitStack(Stack &s) {
    s.Top = NULL;
}

// Kiểm tra Stack rỗng
int IsEmptyStack(Stack s) {
    return (s.Top == NULL);
}

// Thêm phần tử vào đỉnh Stack (Push)
int push(Stack &s, StackNode *q) {
    if (q == NULL) return 0;

    q->Next = s.Top;
    s.Top = q;
    return 1;
}

// Lấy phần tử khỏi đỉnh Stack (Pop)
int pop(Stack &s, Itemtype &x) {
    if (IsEmptyStack(s)) return 0;

    StackNode *q = s.Top;
    s.Top = s.Top->Next;
    x = q->Info;
    delete q;
    return 1;
}

// Tạo một nút mới
StackNode* CreateStackNode(Itemtype x)
{
    StackNode *q = new StackNode;
    if (q != NULL) {
        q->Info = x;
        q->Next = NULL;
    }
    return q;
}

// Hiển thị Stack
void ShowStack(Stack s) {
    if (IsEmptyStack(s)) {
        printf("Stack rong.\n");
        return;
    }

    printf("Cac phan tu trong ngan xep:\n");
    StackNode *current = s.Top;
    while (current != NULL) {
        printf("%d ", current->Info);
        current = current->Next;
    }
    printf("\n");
}
// hàm chính duyệt theo chiều NLR
void traverseNLR_Stack(TNode *root) {
    if (root == NULL) return;

    Stack s;
    InitStack(s);
    push(s, CreateStackNode(root->Info));  // Đẩy nút gốc vào Stack

    while (!IsEmptyStack(s)) {
        Itemtype x;
        pop(s, x);
        printf("%4d ", x);  // In giá trị nút gốc trước

        TNode *current = findTNode(root, x);

        // Đẩy nút phải vào Stack trước, sau đó nút trái (để đảm bảo thứ tự NLR)
        if (current->Right) push(s, CreateStackNode(current->Right->Info));
        if (current->Left) push(s, CreateStackNode(current->Left->Info));
    }
}
// xóa toàn bộ cây
void deleteTree(TNode *&root) {
    if (root == NULL) return;  // Nếu cây rỗng, không cần làm gì

    deleteTree(root->Left);  // Xóa cây con trái
    deleteTree(root->Right); // Xóa cây con phải

    delete root;  // Xóa nút hiện tại
    root = NULL;  // Đặt lại root thành NULL
}
// bài 4/70============================================================
// in số hoàn hảo
void printPerfectNumbers(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không có gì để xuất

    if (isPerfectNumber(root->Info)) {
        printf("%4d ", root->Info);  // Nếu nút là số hoàn hảo, in giá trị
    }

    printPerfectNumbers(root->Left);  // Duyệt cây con trái
    printPerfectNumbers(root->Right); // Duyệt cây con phải
}

// xuất theo thứ tự từ tầng đến tầng h=1 h là chiều cao cảu cây
void printNodesByLevels(TNode *root) {
    if (root == NULL) return;  // Nếu cây rỗng, không có gì để xuất

    int h = highTree(root);  // Tính chiều cao của cây BST
    for (int k = 0; k <= h; k++) {  
        printf("Cac nut o muc %d: ", k);
        printNodesAtLevelK(root, k);  // Xuất các nút ở tầng k
        printf("\n");
    }
}

// các hàm kiểm tra====================================================================================
// ktr cây nhị phân tìm kiếm
int isBST(TNode *root, Itemtype min, Itemtype max) {
    if (root == NULL) return 1;  // Cây rỗng vẫn là BST

    if (root->Info < min || root->Info > max) return 0;  // Vi phạm quy tắc BST

    return isBST(root->Left, min, root->Info - 1) && isBST(root->Right, root->Info + 1, max);
}

void checkBST(TNode *root) {
    if (isBST(root, INT_MIN, INT_MAX)) {
        printf("Cay nay la cay nhi phan tim kiem (BST).\n");
    } else {
        printf("Cay nay KHONG phai la cay nhi phan tim kiem (BST).\n");
    }
}


// kiểm tra cây nhị phân cân bằng
int isBalanced(TNode *root) {
    if (root == NULL) return 1;  // Cây rỗng vẫn là cây cân bằng

    int leftHeight = highTree(root->Left);
    int rightHeight = highTree(root->Right);

    if (abs(leftHeight - rightHeight) > 1) return 0;  // Nếu độ chênh lệch lớn hơn 1, không cân bằng

    return isBalanced(root->Left) && isBalanced(root->Right);
}

void checkBalanced(TNode *root) {
    if (isBalanced(root)) {
        printf("Cay nay la cay nhi phan can bang.\n");
    } else {
        printf("Cay nay KHONG phai la cay nhi phan can bang.\n");
    }
}

//// kiểm tra cây nhị phân hoàn toàn cân bằng
int isFullBalanced(TNode *root) {
    if (root == NULL) return 1;  // Cây rỗng vẫn là cây cân bằng hoàn toàn

    if ((root->Left == NULL && root->Right != NULL) || (root->Left != NULL && root->Right == NULL)) 
        return 0;  // Nếu một nút có đúng 1 con, không phải cây cân bằng hoàn toàn

    return isFullBalanced(root->Left) && isFullBalanced(root->Right);
}

void checkFullBalanced(TNode *root) {
    if (isFullBalanced(root)) {
        printf("Cay nay la cay nhi phan can bang hoan toan.\n");
    } else {
        printf("Cay nay KHONG phai la cay nhi phan can bang hoan toan.\n");
    }
}


int main() {
    BTree bt;
    initBtree(bt);
    int choice, x, n, k;
    Itemtype a[100];

    do {
        printf("\n====== MENU CAY BST ======");
        printf("\n1. Tao cay tu mang co san");
        printf("\n2. Tao cay bang tay");
        printf("\n3. Tao cay ngau nhien");
        printf("\n4. Hien thi cay BST");
        printf("\n5. Duyet cay theo NLR (Duyet truoc)");
        printf("\n6. Them nut x vao cay");
        printf("\n7. Xoa nut x khoi cay");
        printf("\n8. Tim nut x trong cay");
        printf("\n9. Dem so nut tren cay");
        printf("\n10. Tinh chieu cao cua cay");
        printf("\n11. Tim nut co gia tri lon nhat");
        printf("\n12. Tim nut co gia tri nho nhat");
        printf("\n13. Dem so nut la");
        printf("\n14. Dem so nut co 1 con");
        printf("\n15. Dem so nut co 2 con");
        printf("\n16. Xuat cac nut o muc k");
        printf("\n17. Xuat cac nut la o muc k");
        printf("\n18. Dem so nut o muc k");
        printf("\n19. Dem so nut la o muc k");
        printf("\n20. Tim gia tri gan nhat voi x");
        printf("\n21. Tim gia tri xa nhat voi x");
        printf("\n22. Tinh tong cac nut tren cay");
        printf("\n23. Tinh tong cac nut duong");
        printf("\n24. Tinh tong cac nut am");
        printf("\n25. Tinh tong cac so nguyen to");
        printf("\n26. Tinh tong cac so chinh phuong");
        printf("\n27. Tinh tong cac so hoan hao");
        printf("\n28. Tinh tong cac so thinh vuong");
        printf("\n29. Tinh tong cac so yeu");
        printf("\n30. Duyet cay theo NLR (su dung Stack)");
        printf("\n31. Xoa toan bo cay");
        printf("\n32. Thoat");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);

                switch (choice) {
            case 1:
                printf("Nhap so luong phan tu cua mang: ");
                scanf("%d", &n);
                printf("Nhap cac phan tu cua mang: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &a[i]);
                }
                createBTreeFromArray(bt, a, n);
                printf("Da tao cay tu mang!\n");
                break;

            case 2:
                createBTreeFromKeyboard(bt);
                printf("Da tao cay BST tu ban phim!\n");
                break;

            case 3:
                createAutomaticBTree(bt);
                printf("Da tao cay BST ngau nhien!\n");
                break;

            case 4:
                printf("Noi dung cay BST:\n");
                showBSTNode(bt.Root);
                printf("\n");
                break;

            case 5:
                printf("Duyet cay theo NLR:\n");
                traverseNLR(bt.Root);
                printf("\n");
                break;

            case 6:
                printf("Nhap gia tri can them vao cay: ");
                scanf("%d", &x);
                insertTNode(bt.Root, x);
                printf("Da them %d vao cay BST!\n", x);
                break;

            case 7:
                printf("Nhap gia tri nut can xoa: ");
                scanf("%d", &x);
                if (deleteTNodeX(bt.Root, x))
                    printf("Da xoa nut %d khoi cay BST.\n", x);
                else
                    printf("Khong tim thay nut %d trong cay BST.\n", x);
                break;

            case 8:
                printf("Nhap gia tri nut can tim: ");
                scanf("%d", &x);
                if (findTNode(bt.Root, x))
                    printf("Tim thay nut %d trong cay BST!\n", x);
                else
                    printf("Khong tim thay nut %d trong cay BST.\n", x);
                break;

            case 9:
                printf("So nut trong cay BST: %d\n", countNodes(bt.Root));
                break;

            case 10:
                printf("Chieu cao cua cay BST: %d\n", highTree(bt.Root));
                break;

            case 11:
                printf("Nut co gia tri lon nhat: %d\n", findMaxNode(bt.Root)->Info);
                break;

            case 12:
                printf("Nut co gia tri nho nhat: %d\n", findMinNode(bt.Root)->Info);
                break;

            case 13:
                printf("So nut la trong cay BST: %d\n", countLeafNodes(bt.Root));
                break;

            case 14:
                printf("So nut co 1 con trong cay BST: %d\n", countNodesWithOneChild(bt.Root));
                break;

            case 15:
                printf("So nut co 2 con trong cay BST: %d\n", countNodesWithTwoChildren(bt.Root));
                break;

            case 16:
                printf("Nhap muc k muon xuat cac nut: ");
                scanf("%d", &k);
                printNodesAtLevelK(bt.Root, k);
                break;

            case 17:
                printf("Nhap muc k muon xuat cac nut la: ");
                scanf("%d", &k);
                printLeafNodesAtLevelK(bt.Root, k);
                break;

            case 18:
                printf("Nhap muc k de dem so nut: ");
                scanf("%d", &k);
                printf("So nut o muc %d: %d\n", k, countNodesAtLevelK(bt.Root, k));
                break;

            case 19:
                printf("Nhap muc k de dem so nut la: ");
                scanf("%d", &k);
                printf("So nut la o muc %d: %d\n", k, countLeafNodesAtLevelK(bt.Root, k));
                break;

            case 20:
                printf("Nhap gia tri x can tim gia tri gan nhat: ");
                scanf("%d", &x);
                printf("Gia tri gan nhat voi %d la %d\n", x, findClosestValue(bt.Root, x));
                break;

            case 21:
                printf("Nhap gia tri x can tim gia tri xa nhat: ");
                scanf("%d", &x);
                printf("Gia tri xa nhat voi %d la %d\n", x, findFarthestValue(bt.Root, x));
                break;

            case 22:
                printf("Tong gia tri cac nut tren cay BST: %d\n", sumNodes(bt.Root));
                break;

            case 23:
                printf("Tong cac nut duong: %d\n", sumPositiveNodes(bt.Root));
                break;

            case 24:
                printf("Tong cac nut am: %d\n", sumNegativeNodes(bt.Root));
                break;

            case 25:
                printf("Tong cac nut le: %d\n", sumOddNodes(bt.Root));
                break;

            case 26:
                printf("Tong cac nut chan: %d\n", sumEvenNodes(bt.Root));
                break;

            case 27:
                printf("Tong cac so nguyen to: %d\n", sumPrimeNodes(bt.Root));
                break;

            case 28:
                printf("Tong cac so chinh phuong: %d\n", sumPerfectSquareNodes(bt.Root));
                break;

            case 29:
                printf("Tong cac so hoan hao: %d\n", sumPerfectNumberNodes(bt.Root));
                break;

            case 30:
                printf("Tong cac so thinh vuong: %d\n", sumAbundantNodes(bt.Root));
                break;

            case 31:
                printf("Tong cac so yeu: %d\n", sumDeficientNodes(bt.Root));
                break;

            case 32:
                printf("Duyet cay theo NLR su dung Stack:\n");
                traverseNLR_Stack(bt.Root);
                printf("\n");
                break;

            case 33:
                printf("Xuat cac nut theo tung muc tu goc den la:\n");
                printNodesByLevels(bt.Root);
                printf("\n");
                break;

            case 34:
                printf("Xuat cac so hoan hao trong cay BST:\n");
                printPerfectNumbers(bt.Root);
                printf("\n");
                break;

            case 35:
                checkBST(bt.Root);
                break;

            case 36:
                checkBalanced(bt.Root);
                break;

            case 37:
                checkFullBalanced(bt.Root);
                break;

            case 38:
                printf("Tong cac nut co 1 con va la so nguyen to: %d\n", sumNodesWithOneChild_Prime(bt.Root));
                break;

            case 39:
                printf("Tong cac nut co 2 con va la so chinh phuong: %d\n", sumNodesWithTwoChildren_PerfectSquare(bt.Root));
                break;

            case 40:
                deleteTree(bt.Root);
                printf("Da xoa toan bo cay BST!\n");
                break;

            case 41:
                printf("Ket thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 32);

    return 0;
}

