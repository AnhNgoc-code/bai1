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


// duyệt cây theo chiều rộng QUEUE
// khai báo và các thao tác của QUEUE
typedef int Itemtype;

//==========================================
// Queue voi danh sach lien ket
struct QueueNode
{
	Itemtype Info;
	QueueNode *Next;
};
struct Queue
{
	QueueNode *Head;
	QueueNode *Tail;
};
void initQueue(Queue &q)
{
	q.Head = NULL;
	q.Tail = NULL;
}
int IsEmptyQueue(Queue q)
{
	if(q.Head == NULL)
		return 1;
	else
		return 0;
}
QueueNode *CreateNode(Itemtype x) {
    QueueNode *p = new QueueNode;
    if (p == NULL) {
        printf("khong the cap phat bo nho.\n");
        return NULL;
    }
    p->Info = x;
    p->Next = NULL;
    return p;
}
// them vao cuoi Queue
int InsertQueue(Queue &q, QueueNode *p)
{
	if(p == NULL)
		return 0;
	if(IsEmptyQueue(q)==1)
		{
			q.Head = p;
			q.Tail = p;
		}
	else
	{
		q.Tail->Next = p;
		q.Tail = p;
	}
	return 1;
}

// xoa dau Queue
int DeleteQueue(Queue &q, Itemtype &x)
{
	if(IsEmptyQueue(q)==1)
		return 0;
	QueueNode *p = q.Head;
	q.Head = q.Head->Next;
	if(q.Head== NULL)
		q.Tail = NULL;
	x = p->Info;
	delete(p);
	return 1;
}
int GetHead(Queue q, Itemtype &x)
{
	if(IsEmptyQueue(q)==1)
		return 0;
	x = q.Head->Info;
	return 1;
}
int GetTail(Queue q, Itemtype &x)
{
	if(IsEmptyQueue(q)==1)
		return 0;
	x = q.Tail->Info;
	return 1;
}
void ShowQueue(Queue q)
{
	if(IsEmptyQueue(q)==1)
		printf("danh sach rong");
	QueueNode *current =q.Head;
	while(current !=NULL)
		{
			printf("%4d",current->Info);
			current = current ->Next;
		}
}

void traverseBFS(TNode *root) {
    if (root == NULL) return;

    Queue q;
    initQueue(q);
    InsertQueue(q, CreateNode(root->Info));

    while (!IsEmptyQueue(q)) {
        Itemtype x;
        DeleteQueue(q, x);
        printf("%4d ", x);

        TNode *current = findTNode(root, x);
        if (current->Left) InsertQueue(q, CreateNode(current->Left->Info));
        if (current->Right) InsertQueue(q, CreateNode(current->Right->Info));
    }
}
// duyệt cây theo chiều sâu STACK
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
// hàm chính duyệt theo chiều sâu
void traverseDFS(TNode *root) {
    if (root == NULL) return;

    Stack s;
    InitStack(s);
    push(s, CreateStackNode(root->Info));

    while (!IsEmptyStack(s)) {
        Itemtype x;
        pop(s, x);
        printf("%4d ", x);

        TNode *current = findTNode(root, x);
        if (current->Right) push(s, CreateStackNode(current->Right->Info));
        if (current->Left) push(s, CreateStackNode(current->Left->Info));
    }
}
//đếm số node trên cây
int countNodes(TNode *root) {
    if (root == NULL) 
        return 0; // Nếu cây rỗng, số nút là 0

    return 1 + countNodes(root->Left) + countNodes(root->Right);
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
// đếm nút giá có trị lơn hơn x
int countNodesGreaterThanX(TNode *root, Itemtype x) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, số nút là 0

    int count = (root->Info > x) ? 1 : 0;  // Nếu giá trị nút lớn hơn x, tăng biến đếm

    return count + countNodesGreaterThanX(root->Left, x) + countNodesGreaterThanX(root->Right, x);
}
// CÁC THAO TÁC TÍNH TOÁN TRÊN CÂY

// đếm số nút lá
int countLeafNodes(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, không có nút lá nào

    if (root->Left == NULL && root->Right == NULL) 
        return 1;  // Nếu nút hiện tại không có con, đây là nút lá

    return countLeafNodes(root->Left) + countLeafNodes(root->Right);
}

// đếm nút có 1 con
int countNodesWithOneChild(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, không có nút nào

    int count = ((root->Left == NULL && root->Right != NULL) || (root->Left != NULL && root->Right == NULL)) ? 1 : 0;

    return count + countNodesWithOneChild(root->Left) + countNodesWithOneChild(root->Right);
}
// đếm nút có 2 con
int countNodesWithTwoChildren(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, không có nút nào

    int count = (root->Left != NULL && root->Right != NULL) ? 1 : 0;  // Kiểm tra nút có cả 2 con

    return count + countNodesWithTwoChildren(root->Left) + countNodesWithTwoChildren(root->Right);
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
// tổng các số nguyê tố
int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int sumPrimeNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isPrime(root->Info) ? root->Info : 0;
    return sum + sumPrimeNodes(root->Left) + sumPrimeNodes(root->Right);
}

// tổng số chính phương
int isPerfectSquare(int n) {
    int root = sqrt(n);
    return (root * root == n);
}

int sumPerfectSquareNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isPerfectSquare(root->Info) ? root->Info : 0;
    return sum + sumPerfectSquareNodes(root->Left) + sumPerfectSquareNodes(root->Right);
}

// tính tổng số thịnh vượng
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

int sumAbundantNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isAbundant(root->Info) ? root->Info : 0;
    return sum + sumAbundantNodes(root->Left) + sumAbundantNodes(root->Right);
}

// tính tổng các số yếu
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

int sumDeficientNodes(TNode *root) {
    if (root == NULL) return 0;
    int sum = isDeficient(root->Info) ? root->Info : 0;
    return sum + sumDeficientNodes(root->Left) + sumDeficientNodes(root->Right);
}


// tỉnh tổng các nút có 1 con
int sumNodesWithOneChild(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, tổng là 0

    int sum = ((root->Left == NULL && root->Right != NULL) || (root->Left != NULL && root->Right == NULL)) ? root->Info : 0;

    return sum + sumNodesWithOneChild(root->Left) + sumNodesWithOneChild(root->Right);
}

// tổng các nút có 2 con
int sumNodesWithTwoChildren(TNode *root) {
    if (root == NULL) 
        return 0;  // Nếu cây rỗng, tổng là 0

    int sum = (root->Left != NULL && root->Right != NULL) ? root->Info : 0;  // Nếu nút có 2 con, cộng giá trị vào tổng

    return sum + sumNodesWithTwoChildren(root->Left) + sumNodesWithTwoChildren(root->Right);
}
int main() {
    BTree bt;
    initBtree(bt);
    int choice, x, n;
    Itemtype a[100];

    do {
        printf("\n====== MENU CAY BST ======");
        printf("\n1. Tao cay tu mang co san");
        printf("\n2. Tao cay bang tay");
        printf("\n3. Tao cay ngau nhien");
        printf("\n4. Hien thi cay BST");
        printf("\n5. Duyet cay theo NLR");
        printf("\n6. Duyet cay theo chieu rong (BFS)");
        printf("\n7. Duyet cay theo chieu sau (DFS)");
        printf("\n8. Them nut x vao cay");
        printf("\n9. Xoa nut x khoi cay");
        printf("\n10. Tim nut co gia tri lon nhat");
        printf("\n11. Tim nut co gia tri nho nhat");
        printf("\n12. Dem so nut tren cay");
        printf("\n13. Kiem tra nut x co tren cay khong");
        printf("\n14. Tinh chieu cao cua cay");
        printf("\n15. Dem so nut la");
        printf("\n16. Dem so nut co 1 con");
        printf("\n17. Dem so nut co 2 con");
        printf("\n18. Tinh tong gia tri nut co 1 con");
        printf("\n19. Tinh tong gia tri nut co 2 con");
        printf("\n20. Tinh tong cac nut duong");
        printf("\n21. Tinh tong cac nut am");
        printf("\n22. Tinh tong cac so nguyen to");
        printf("\n23. Tinh tong cac so chinh phuong");
        printf("\n24. Tinh tong cac so thinh vuong");
        printf("\n25. Tinh tong cac so yeu");
        printf("\n26. Thoat");
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
                printf("Nhap so luong phan tu can them vao cay: ");
                scanf("%d", &n);
                initBtree(bt);
                for (int i = 0; i < n; i++) {
                    printf("Nhap gia tri phan tu %d: ", i + 1);
                    scanf("%d", &x);
                    insertTNode(bt.Root, x);
                }
                printf("Da tao cay bang tay!\n");
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
                showTNode(bt.Root);
                printf("\n");
                break;

            case 6:
                printf("Duyet cay theo chieu rong (BFS): ");
                traverseBFS(bt.Root);
                printf("\n");
                break;

            case 7:
                printf("Duyet cay theo chieu sau (DFS): ");
                traverseDFS(bt.Root);
                printf("\n");
                break;

            case 8:
                printf("Nhap gia tri can them vao cay: ");
                scanf("%d", &x);
                insertTNode(bt.Root, x);
                printf("Da them %d vao cay BST!\n", x);
                break;

            case 9:
                printf("Nhap gia tri nut can xoa: ");
                scanf("%d", &x);
                if (deleteTNodeX(bt.Root, x))
                    printf("Da xoa nut %d khoi cay BST.\n", x);
                else
                    printf("Khong tim thay nut %d trong cay BST.\n", x);
                break;

            case 10:
                if (bt.Root) {
                    printf("Nut co gia tri lon nhat: %d\n", findMaxNode(bt.Root)->Info);
                } else {
                    printf("Cay BST dang rong.\n");
                }
                break;

            case 11:
                if (bt.Root) {
                    printf("Nut co gia tri nho nhat: %d\n", findMinNode(bt.Root)->Info);
                } else {
                    printf("Cay BST dang rong.\n");
                }
                break;

            case 12:
                printf("So nut trong cay BST: %d\n", countNodes(bt.Root));
                break;

            case 13:
                printf("Nhap gia tri can kiem tra: ");
                scanf("%d", &x);
                if (isNodeExists(bt.Root, x))
                    printf("Tim thay %d trong cay BST!\n", x);
                else
                    printf("Khong tim thay %d.\n", x);
                break;

            case 14:
                printf("Chieu cao cua cay BST: %d\n", highTree(bt.Root));
                break;

            case 15:
                printf("So nut la trong cay BST: %d\n", countLeafNodes(bt.Root));
                break;

            case 16:
                printf("So nut co dung 1 con: %d\n", countNodesWithOneChild(bt.Root));
                break;

            case 17:
                printf("So nut co dung 2 con: %d\n", countNodesWithTwoChildren(bt.Root));
                break;

            case 18:
                printf("Tong gia tri cac nut co 1 con: %d\n", sumNodesWithOneChild(bt.Root));
                break;

            case 19:
                printf("Tong gia tri cac nut co 2 con: %d\n", sumNodesWithTwoChildren(bt.Root));
                break;

            case 20:
                printf("Tong gia tri cac nut duong: %d\n", sumPositiveNodes(bt.Root));
                break;

            case 21:
                printf("Tong gia tri cac nut am: %d\n", sumNegativeNodes(bt.Root));
                break;

            case 22:
                printf("Tong gia tri cac so nguyen to: %d\n", sumPrimeNodes(bt.Root));
                break;

            case 23:
                printf("Tong gia tri cac so chinh phuong: %d\n", sumPerfectSquareNodes(bt.Root));
                break;

            case 24:
                printf("Tong gia tri cac so thinh vuong: %d\n", sumAbundantNodes(bt.Root));
                break;

            case 25:
                printf("Tong gia tri cac so yeu: %d\n", sumDeficientNodes(bt.Root));
                break;

            case 26:
                printf("Ket thuc chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 26);

    return 0;
}

