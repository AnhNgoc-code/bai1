#include <stdio.h>
#include <time.h>
#include <cstdlib>
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
        insertTNode(bt.Root, a[i]); // Truyền đúng tham chiếu đến `bt.Root`
    }
}

void createAutomaticBTree(BTree &bt) {
    int n;
    Itemtype x;
    printf("Cho biet so nut cua cay: ");
    scanf("%d", &n);

    initBtree(bt); // Gọi đúng hàm khởi tạo cây

    srand((unsigned)time(NULL)); // Khởi tạo seed cho bộ sinh số ngẫu nhiên

    for (int i = 1; i <= n; i++) {
        x = (rand() % 199) - 99; // Sinh số ngẫu nhiên trong khoảng [-99, 99]
        insertTNode(bt.Root, x); // Thêm giá trị vào cây BST
    }

    printf("Da tao cay BST tu dong voi %d nut!\n", n);
}

//đếm số node trên cây
int countNodes(TNode *root) {
    if (root == NULL) 
        return 0; // Nếu cây rỗng, số nút là 0

    return 1 + countNodes(root->Left) + countNodes(root->Right);
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
        printf("Nút không tồn tại.\n");
        return;
    }

    printf("Giá trị của nút: %d\n", p->Info);
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
// duyệt cây NLR
void showBSTNode(TNode *root) {
    if (root == NULL) 
        return;

    printf("%4d", root->Info);  // Hiển thị giá trị nút gốc
    showBSTNode(root->Left);    // Duyệt cây con trái
    showBSTNode(root->Right);   // Duyệt cây con phải
}

// hàm main
int main() {
    BTree bt;
    initBtree(bt);
    int choice, x;

    do {
        printf("\n====== MENU BST ======");
        printf("\n1. Thêm phần tử vào cây");
        printf("\n2. Duyệt cây (NLR)");
        printf("\n3. Tìm kiếm phần tử");
        printf("\n4. Xóa phần tử");
        printf("\n5. Tính chiều cao của cây");
        printf("\n6. Thoát");
        printf("\nChọn chức năng: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập giá trị cần thêm: ");
                scanf("%d", &x);
                insertTNode(bt.Root, x);
                break;
            case 2:
                printf("Nội dung cây BST: ");
                showBSTNode(bt.Root);
                printf("\n");
                break;
            case 3:
                printf("Nhập giá trị cần tìm: ");
                scanf("%d", &x);
                if (findTNode(bt.Root, x) != NULL)
                    printf("Tìm thấy phần tử %d trong cây!\n", x);
                else
                    printf("Không tìm thấy phần tử %d.\n", x);
                break;
            case 4:
                printf("Nhập giá trị cần xóa: ");
                scanf("%d", &x);
                if (deleteTNodeX(bt.Root, x))
                    printf("Đã xóa %d khỏi cây BST.\n", x);
                else
                    printf("Không tìm thấy %d để xóa.\n", x);
                break;
            case 5:
                printf("Chiều cao của cây BST: %d\n", highTree(bt.Root));
                break;
            case 6:
                printf("Kết thúc chương trình!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (choice != 6);

    return 0;
}