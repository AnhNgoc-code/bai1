#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#define LH -1
#define EH 0
#define RH 1
struct Itemtype {
    int tuSo;   // Tử số
    int mau;    // Mẫu số
};
// Hàm rút gọn phân số bằng cách chia cho UCLN
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}
Itemtype simplify(Itemtype p) {
    int ucln = gcd(p.tuSo, p.mau);
    p.tuSo /= ucln;
    p.mau /= ucln;
    return p;
}
// So sánh hai phân số
int compare(Itemtype a, Itemtype b) {
    return a.tuSo * b.mau - b.tuSo * a.mau;
}

int isEqual(Itemtype a, Itemtype b) {
    return (a.tuSo * b.mau == b.tuSo * a.mau);
}

struct TNode {
    Itemtype Info;
    TNode* Left;
    TNode* Right;
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
   if (isEqual(x, root->Info))
        return root;
    else if (isEqual(root->Info, x) > 0)
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
    if (isEqual(root->Info, x))
    {
        return 0;
    }
    if (compare(x, root->Info) < 0) // ✅ Đúng
        insertTNode(root->Left,x);
    else
        insertTNode(root->Right,x);
    return 1;
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
	if (compare(root->Info, x) > 0)
		return deleteTNodeX(root->Left,x);
	else if (compare(root->Info, x) < 0)

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
// Định nghĩa AVLNode cho phân số
struct AVLNode {
    Itemtype Info;  // Lưu phân số
    int balFactor;
    AVLNode* Left;
    AVLNode* Right;
};
// chuyển đổi TNode sang AVLNode
AVLNode* convertToAVLNode(TNode* p) {
    if (p == NULL)
        return NULL;

    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode != NULL) {
        newNode->Info = p->Info;
        newNode->balFactor = EH;  // Khởi tạo trạng thái cân bằng
        newNode->Left = NULL;
        newNode->Right = NULL;
    }
    return newNode;
}
struct AVLTree
{
	AVLNode *Root;
};
// Hàm tạo một nút mới cho cây AVL
// Hàm tạo một nút mới cho cây AVL chứa phân số
AVLNode* createAVLNode(Itemtype p) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode != NULL) {
        newNode->Info = simplify(p); // Rút gọn phân số trước khi lưu
        newNode->balFactor = EH;
        newNode->Left = NULL;
        newNode->Right = NULL;
    }
    return newNode;
}

// cân bằng lại Left-Left
void roteteLL(AVLNode *&T)
{
	AVLNode *T1 = T->Left;
	T->Left = T1->Left;
	T1->Right = T;
	switch(T1->balFactor)
	{
		case LH:
			T->balFactor= EH;
			T1->balFactor=EH;
			break;
		case EH:
			T->balFactor=LH;
			T1->balFactor=RH;
			break;
	}
	T=T1;
}
// cân bằng lại Left-Right
// Cân bằng lại Left-Right (LR)
void rotateLR(AVLNode *&T) {
    AVLNode *T1 = T->Left;
    AVLNode *T2 = T1->Right;

    // Xoay trái nút con T1
    T1->Right = T2->Left;
    T2->Left = T1;

    // Xoay phải nút gốc T
    T->Left = T2->Right;
    T2->Right = T;

    // Cập nhật hệ số cân bằng
    switch (T2->balFactor) {
        case LH:
            T->balFactor = RH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case RH:
            T->balFactor = EH;
            T1->balFactor = LH;
            break;
    }

    T2->balFactor = EH;
    T = T2;
}

// cân bằng lại Left - Balance
// Cân bằng lại Left-Balanced (LB)
void rotateLB(AVLNode *&T) {
    AVLNode *T1 = T->Left; // Nút con trái
    AVLNode *T2 = T1->Right; // Nút con phải của T1

    // Xoay phải nút gốc T
    T->Left = T2->Right;
    T2->Right = T;

    // Xoay trái nút con T1
    T1->Right = T2->Left;
    T2->Left = T1;

    // Cập nhật hệ số cân bằng
    switch (T2->balFactor) {
        case LH:
            T->balFactor = RH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case RH:
            T->balFactor = EH;
            T1->balFactor = LH;
            break;
    }

    T2->balFactor = EH;
    T = T2;
}

// cân bằng lại RL
// Cân bằng lại Right-Left (RL)
void rotateRL(AVLNode *&T) {
    AVLNode *T1 = T->Right;  // Nút con phải
    AVLNode *T2 = T1->Left;  // Nút con trái của T1

    // Xoay phải nút con phải (T1)
    T1->Left = T2->Right;
    T2->Right = T1;

    // Xoay trái nút gốc (T)
    T->Right = T2->Left;
    T2->Left = T;

    // Cập nhật hệ số cân bằng
    switch (T2->balFactor) {
        case LH:
            T->balFactor = EH;
            T1->balFactor = RH;
            break;
        case EH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case RH:
            T->balFactor = LH;
            T1->balFactor = EH;
            break;
    }

    T2->balFactor = EH;
    T = T2;
}

// Cân bằng lại Right-Right (RR)
void rotateRR(AVLNode *&T) {
    AVLNode *T1 = T->Right;  // Nút con phải

    // Xoay trái nút gốc
    T->Right = T1->Left;
    T1->Left = T;

    // Cập nhật hệ số cân bằng
    switch (T1->balFactor) {
        case RH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = LH;
            T1->balFactor = RH;
            break;
    }

    T = T1;
}

// Cân bằng lại Right-Balanced (RB)
void rotateRB(AVLNode *&T) {
    if (T == NULL || T->Right == NULL) return; // Ngăn lỗi khi T hoặc cây con phải rỗng

    AVLNode *T1 = T->Right;
    if (T1->Left == NULL) return; // Đảm bảo T1 có cây con trái

    AVLNode *T2 = T1->Left;  // Nút con trái của T1

    // Xoay trái nút con phải (T1)
    T1->Left = T2->Right;
    T2->Right = T1;

    // Xoay phải nút gốc (T)
    T->Right = T2->Left;
    T2->Left = T;

    // Cập nhật hệ số cân bằng
    switch (T2->balFactor) {
        case LH:
            T->balFactor = EH;
            T1->balFactor = RH;
            break;
        case EH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case RH:
            T->balFactor = LH;
            T1->balFactor = EH;
            break;
    }

    T2->balFactor = EH;
    T = T2;
}
// Cân bằng lại khi cây bị lệch trái (Balance Left)
void rotateRight(AVLNode*& T) {
    AVLNode* T1 = T->Left;
    T->Left = T1->Right;
    T1->Right = T;

    switch (T1->balFactor) {
        case LH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = RH;
            T1->balFactor = LH;
            break;
    }

    T = T1;
}

void balanceLeft(AVLNode *&T) {
    AVLNode *T1 = T->Left;  // Nút con trái

    // Kiểm tra hệ số cân bằng của cây con trái để xác định kiểu xoay
    if (T1->balFactor == LH) {
        // Mất cân bằng dạng Left-Left (LL) → Xoay phải
        rotateRight(T);
    } else {
        // Mất cân bằng dạng Left-Right (LR) → Xoay trái trên cây con, sau đó xoay phải
        rotateLR(T);
    }
}

// Cân bằng lại khi cây bị lệch phải (Balance Right)
void rotateLeft(AVLNode*& T) {
    AVLNode* T1 = T->Right;
    T->Right = T1->Left;
    T1->Left = T;

    switch (T1->balFactor) {
        case RH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = LH;
            T1->balFactor = RH;
            break;
    }

    T = T1;
}

void balanceRight(AVLNode *&T) {
    AVLNode *T1 = T->Right;  // Nút con phải

    // Kiểm tra hệ số cân bằng của cây con phải để xác định kiểu xoay
    if (T1->balFactor == RH) {
        // Mất cân bằng dạng Right-Right (RR) → Xoay trái
        rotateLeft(T);
    } else {
        // Mất cân bằng dạng Right-Left (RL) → Xoay phải trên cây con, sau đó xoay trái
        rotateRL(T);
    }
}
// Hàm rút gọn phân số
void simplifyAllFractions(AVLNode* root) {
    if (root == NULL) return;

    root->Info = simplify(root->Info); // Rút gọn phân số ở nút hiện tại
    simplifyAllFractions(root->Left);  // Duyệt cây con trái
    simplifyAllFractions(root->Right); // Duyệt cây con phải
}

// thêm 1 phân tử vào cây AVL
int insertAVLNode(AVLNode*& T, TNode* p) {
    if (p == NULL)
        return -1;  // Nút không tồn tại

    AVLNode* newNode = convertToAVLNode(p);
    if (newNode == NULL)
        return -1;  // Không thể tạo nút AVL từ `TNode`

    if (T == NULL) {
        T = newNode;
        return 2;  // Thêm thành công
    }

    int result;
   if (isEqual(T->Info, newNode->Info))
        return 0;  // Không thêm được vì nút đã tồn tại

   if (compare(T->Info, newNode->Info) > 0) 
{
        // Thêm nút vào cây con trái
        result = insertAVLNode(T->Left, p);
        if (result < 2)
            return result;

        switch (T->balFactor) {
            case RH:
                T->balFactor = EH;
                return 1;
            case EH:
                T->balFactor = LH;
                return 2;
            case LH:
                balanceLeft(T);  // Xử lý mất cân bằng trái
                return 1;
        }
}
    
	 else {
        // Thêm nút vào cây con phải
        result = insertAVLNode(T->Right, p);
        if (result < 2)
            return result;

        switch (T->balFactor) {
            case LH:
                T->balFactor = EH;
                return 1;
            case EH:
                T->balFactor = RH;
                return 2;
            case RH:
                balanceRight(T);  // Xử lý mất cân bằng phải
                return 1;
        }
    }

    return result;
}
// Hàm chèn một phân số vào cây AVL
AVLNode* insertAVL(AVLNode*& root, Itemtype p) {
    if (root == NULL) {
        return createAVLNode(p);
    }

    if (compare(p, root->Info) < 0) {
        root->Left = insertAVL(root->Left, p);
    } else if (compare(p, root->Info) > 0) {
        root->Right = insertAVL(root->Right, p);
    }

    return root;
}
// xóa 1 phần tử khỏi cây AVL
// Tìm nút có giá trị nhỏ nhất trong cây con phải
int searchStandFor(AVLNode* &p, AVLNode* &q) {
    int result;
    if (q->Left != NULL) {
        result = searchStandFor(p, q->Left);
        if (result < 2)
            return result;

        switch (q->balFactor) {
            case LH:
                q->balFactor = EH;
                return 2;
            case EH:
                q->balFactor = RH;
                return 1;
            case RH:
                balanceRight(q); // Gọi hàm mà không dùng return
				return 2;        // Trả về giá trị phù hợp

        }
    } else {
        p->Info = q->Info;
        p = q;
        q = q->Right;
    }
    return 2;
}

// Xóa một phần tử khỏi cây AVL
int deleteAVLNode(AVLNode* &T, Itemtype x) {
    int result;
    if (T == NULL)
        return 0; // Không tìm thấy phần tử để xóa

    if (compare(x, T->Info) < 0) {
        result = deleteAVLNode(T->Left, x);
        if (result < 2)
            return result;

        switch (T->balFactor) {
            case LH:
                T->balFactor = EH;
                return 2;
            case EH:
                T->balFactor = RH;
                return 1;
            case RH:
               balanceRight(T); 
				return 2;     

        }
    } else if (compare(x, T->Info) > 0) {
        result = deleteAVLNode(T->Right, x);
        if (result < 2)
            return result;

        switch (T->balFactor) {
            case RH:
                T->balFactor = EH;
                return 2;
            case EH:
                T->balFactor = LH;
                return 1;
            case LH:
                balanceLeft(T);
                return 2;
        }
    } else {
        AVLNode* p = T;
        if (T->Left == NULL) {
            T = T->Right;
            free(p);
            return 2;
        } else if (T->Right == NULL) {
            T = T->Left;
            free(p);
            return 2;
        } else {
            result = searchStandFor(p, T->Right);
            if (result < 2)
                return result;

            switch (T->balFactor) {
                case RH:
                    T->balFactor = EH;
                    return 2;
                case EH:
                    T->balFactor = LH;
                    return 1;
                case LH:
                    balanceLeft(T);  
					return 2;        
            }
        }
    }
    return 1;
}

// Hàm duyệt cây theo thứ tự trung tố (In-order)
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->Left);
        printf("%d/%d ", root->Info.tuSo, root->Info.mau);
        inorderTraversal(root->Right);
    }
}

// tạo cây nhị phân cân bằng
void createSVLTree(AVLNode*& T, int n)
{
    Itemtype x;
    int Result, i = 1;
    
    do {
        printf("Tao nut thu %d co gia tri: ", i);
        scanf("%d", &x);
        
        TNode* newNode = createTNode(x); // ✅ Chuyen doi Itemtype thanh TNode*
        Result = insertAVLNode(T, newNode); // ✅ Truyen dung kieu du lieu
        
        if (Result != 0)
            i++;
    } while (i <= n);
}
// Hàm tạo cây AVL từ mảng có n phần tử
void createAVLTreeFromArray(AVLNode*& root, Itemtype a[], int n) {
    for (int i = 0; i < n; i++) {
        TNode* tempNode = createTNode(a[i]); // Tạo nút từ phần tử mảng
        insertAVLNode(root, tempNode);       // Chèn vào cây AVL
    }
}

//tạo cây từ bàn phím
void createAVLTreeFromInput(AVLNode*& root, int n) {
    Itemtype x;
    for (int i = 0; i < n; i++) {
        printf("Nhập phần tử thứ %d: ", i + 1);
        scanf("%d", &x);
        root = insertAVL(root, x);
    }
}

// Hàm tạo cây AVL tự động với n phần tử ngẫu nhiên
void createAVLAuto(AVLNode*& root, int n) {
    srand(time(NULL)); // Khởi tạo bộ sinh số ngẫu nhiên
    for (int i = 0; i < n; i++) {
        Itemtype x;
        x.tuSo = rand() % 100; // Sinh số ngẫu nhiên từ 0-99
        x.mau = 1; // Đặt mẫu số hợp lệ
        
        printf("Them phan tu: %d/%d\n", x.tuSo, x.mau);
        
        TNode* newNode = createTNode(x); // ✅ Chuyển Itemtype thành TNode*
        insertAVLNode(root, newNode); // ✅ Truyền đúng kiểu dữ liệu
    }
}

//==============
// Hàm kiểm tra xem phân số có lớn hơn 1 không
int isGreaterThanOne(Itemtype p) {
    return p.tuSo > p.mau; // Nếu tử số lớn hơn mẫu số thì phân số > 1
}

// Hàm đếm số lượng phân số lớn hơn 1 trong cây AVL ^
int countFractionsGreaterThanOne(AVLNode* root) {
    if (root == NULL) 
        return 0;

    int count = 0;
    if (isGreaterThanOne(root->Info)) 
        count++;

    count += countFractionsGreaterThanOne(root->Left);
    count += countFractionsGreaterThanOne(root->Right);

    return count;
}

//===================
// Hàm tìm kiếm phân số x trên cây AVL
AVLNode* searchFractionAVL(AVLNode* root, Itemtype x) {
    if (root == NULL) 
        return NULL;

    int cmp = compare(x, root->Info); // So sánh phân số
    if (cmp == 0) 
        return root;  // ✅ Tìm thấy phân số trong cây

    if (cmp < 0) 
        return searchFractionAVL(root->Left, x); // 🔎 Tìm tiếp bên trái
    else 
        return searchFractionAVL(root->Right, x); // 🔎 Tìm tiếp bên phải
}


//=================================
// Hàm tìm và liệt kê các phân số có cùng mẫu số với phân số x
void listSameDenominator(AVLNode* root, int mauX) {
    if (root == NULL)
        return;

    listSameDenominator(root->Left, mauX); // Duyệt cây con trái

    // Kiểm tra nếu mẫu số của nút hiện tại bằng mẫu số cần tìm
    if (root->Info.mau == mauX) {
        printf("%d/%d ", root->Info.tuSo, root->Info.mau);
    }

    listSameDenominator(root->Right, mauX); // Duyệt cây con phải
}

/*// Hàm tính tổng các phân số có cùng mẫu số với phân số x
Itemtype sumFractionsWithSameDenominator(AVLNode* root, int mauX) {
    Itemtype sum = {0, mauX}; // Khởi tạo tổng với mẫu số là mauX

    if (root == NULL)
        return sum;

    Itemtype leftSum = sumFractionsWithSameDenominator(root->Left, mauX);
    Itemtype rightSum = sumFractionsWithSameDenominator(root->Right, mauX);

    if (root->Info.mau == mauX) {
        sum.tuSo += root->Info.tuSo;
    }

    sum.tuSo += leftSum.tuSo + rightSum.tuSo;
    return sum;
*/

// Hàm xóa toàn bộ cây AVL bằng đệ quy
void deleteAVLTree(AVLNode*& root) {
    if (root == NULL) 
        return;

    // Xóa cây con trái và cây con phải trước
    deleteAVLTree(root->Left);
    deleteAVLTree(root->Right);

    // Xóa nút hiện tại
    free(root);
    root = NULL;
}
void showTree(AVLNode* root, int level) {
    if (root == NULL) 
        return;

    // Duyệt cây con phải trước để in theo cấu trúc cây
    showTree(root->Right, level + 1);

    // In khoảng trắng theo cấp độ để thể hiện cấu trúc cây
    for (int i = 0; i < level; i++) 
        printf("\t");

    // Hiển thị giá trị phân số tại nút hiện tại
    printf("%d/%d\n", root->Info.tuSo, root->Info.mau);

    // Duyệt cây con trái sau
    showTree(root->Left, level + 1);
}

// Hàm hiển thị menu
void showMenu() {
    printf("\n=========== MENU ===========\n");
    printf("1. Tao cay AVL tu mang co san\n");
    printf("2. Tao cay AVL tu ban phim\n");
    printf("3. Tao cay AVL tu dong\n");
    printf("4. Duyet cay theo trung to (LNR)\n");
    printf("5. Them phan so vao cay\n");
    printf("6. Dem phan so > 1\n");
    printf("7. Toi gian tat ca phan so\n");
    printf("8. Tim phan so x trong cay\n");
    printf("9. Liet ke phan so co cung mau so voi x\n");
    printf("10. Xoa phan so x khoi cay AVL\n");
    printf("11. Xoa toan bo cay AVL\n");
	printf("12. show cây\n");
    printf("0.Thoat\n");
    printf("============================\n");
}

// Hàm thực hiện chức năng dựa trên lựa chọn
void executeOption(AVLNode*& root, int option) {
    Itemtype x;
    int n;
    
    switch (option) {
       case 1: {
		    printf("Nhap so luong phan so trong mang: ");
		    scanf("%d", &n);
		    Itemtype a[n]; // ✅ Đúng: Biến cục bộ nằm trong phạm vi {}
		
		    for (int i = 0; i < n; i++) {
		        printf("Nhap tu so va mau so cho phan so %d: ", i + 1);
		        scanf("%d%d", &a[i].tuSo, &a[i].mau);
		    }
		    createAVLTreeFromArray(root, a, n);
		}
		break;
        case 2:
            printf("Nhap so luong phan so: ");
            scanf("%d", &n);
            createAVLTreeFromInput(root, n);
            break;
        case 3:
            printf("Nhap so luong phan so tu dong: ");
            scanf("%d", &n);
            createAVLAuto(root, n);
            break;
        case 4:
            printf("Duyet cay theo trung to (LNR):\n");
            inorderTraversal(root);
            printf("\n");
            break;
        case 5:
            printf("Nhap tu so va mau so: ");
            scanf("%d%d", &x.tuSo, &x.mau);
            root = insertAVL(root, x);
            break;
        case 6:
            printf("So phan so lon hon 1: %d\n", countFractionsGreaterThanOne(root));
            break;
        case 7:
            simplifyAllFractions(root);
            break;
        case 8:
            printf("Nhap tu so va mau so: ");
            scanf("%d%d", &x.tuSo, &x.mau);
            searchFractionAVL(root, x) ? 
                printf("Phan so ton tai trong cay.\n") : 
                printf("Khong tim thay phan so.\n");
            break;
        case 9:
            printf("Nhap mau so can tim: ");
            scanf("%d", &x.mau);
            listSameDenominator(root, x.mau);
            break;
        case 10:
            printf("Nhap phan so can xoa: ");
            scanf("%d%d", &x.tuSo, &x.mau);
            deleteAVLNode(root, x);
            break;
        case 11:
            deleteAVLTree(root);
            printf("Cay AVL da duoc xoa hoan toan.\n");
            break;
        case 12:
		    printf("Cau truc cay AVL:\n");
		    showTree(root, 0);
		    break;
        case 0:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }
}

// Hàm chính
int main() {
    AVLNode* root = NULL;
    int option;

    do {
        showMenu();
        printf("Chon chuc nang: ");
        scanf("%d", &option);
        executeOption(root, option);
    } while (option != 0);

    return 0;
}
