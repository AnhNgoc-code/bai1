#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <string.h>
#define LH -1
#define EH 0
#define RH 1
struct Book {
    char MaS[10];   // Mã sách
    char TenS[100]; // Tên sách
    int NamXB;      // Năm xuất bản
};
typedef Book Itemtype;
// so sanh 2 cuốn sách
int compare(Book a, Book b) {
    return strcmp(a.MaS, b.MaS);  // So sánh theo mã sách
}
//nhập dữ liệu
void inputBook(Book &b) {
    printf("Nhap ma sach: ");
    scanf("%s", b.MaS);
    printf("Nhap ten sach: ");
    getchar(); // Loại bỏ ký tự '\n' trước khi nhập chuỗi
    gets(b.TenS);
    printf("Nhap nam xuat ban: ");
    scanf("%d", &b.NamXB);
}

void printBook(Book b) {
    printf("MaS: %s - TenS: %s - NamXB: %d\n", b.MaS, b.TenS, b.NamXB);
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
    if (compare(root->Info, x) == 0)
        return root;
	else if(compare(root->Info, x) > 0) // ✅ Dùng compare()

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
    if(compare(root->Info, x) == 0)
    {
        return 0;
    }
   if (compare(x, root->Info) < 0)
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
	else if (compare(root->Info, x) < 0) // ✅ Đúng

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
struct AVLNode
{
	int balFactor;
	Itemtype Info;
	AVLNode *Left;
	AVLNode *Right;
};
struct AVLTree
{
	AVLNode *Root;
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

// Hàm tạo một nút mới cho cây AVL
AVLNode* createAVLNode(Itemtype x) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode != NULL) {
        newNode->Info = x;
        newNode->balFactor = EH; // Mặc định hệ số cân bằng là 0 (cân bằng)
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
    AVLNode *T1 = T->Right;  // Nút con phải
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
   if (compare(T->Info, newNode->Info) == 0)
        return 0;  // Không thêm được vì nút đã tồn tại

    if (compare(T->Info, newNode->Info) > 0) {
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
    } else {
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
                balanceRight(q);
                return 2;
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

   if (compare(x, T->Info) < 0)
 {
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
    } else if (compare(x, T->Info) > 0) 
 {
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

// Hàm kiểm tra cây bằng duyệt trung tố (In-order) ^
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->Left);
        printBook(root->Info); // In thông tin sách
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
        TNode* tempNode = createTNode(x); // ✅ Tạo một `TNode` từ `Itemtype`
		if (tempNode) {
    	insertAVLNode(root, tempNode); // ✅ Truyền đúng kiểu dữ liệu vào hàm
		}
    }
}

void createAVLAuto(AVLNode*& root, int n) {
    srand(time(NULL)); // Khởi tạo bộ sinh số ngẫu nhiên
    for (int i = 0; i < n; i++) {
        Itemtype x;
        sprintf(x.MaS, "%d", rand() % 1000); // ✅ Sinh mã sách ngẫu nhiên
        x.NamXB = 2000 + rand() % 25; // ✅ Sinh năm xuất bản ngẫu nhiên
        strcpy(x.TenS, "Sach Ngau Nhien"); // ✅ Gán tên sách mặc định

        printf("Them sach: MaS=%s - TenS=%s - NamXB=%d\n", x.MaS, x.TenS, x.NamXB);

        TNode* tempNode = createTNode(x);
        if (tempNode) {
            insertAVLNode(root, tempNode);
        }
    }
}
// từ fuile
void createAVLTreeFromFile(AVLNode*& root) {
    FILE* file = fopen("books.txt", "r"); // ✅ Mở trực tiếp file books.txt
    if (!file) {
       perror("Loi mo file"); 
        return;
    }

    char line[200]; // Bộ đệm để đọc từng dòng từ file
    int count = 0; // Đếm số sách đã nhập vào cây AVL

    while (fgets(line, sizeof(line), file)) {
        Book x;
        char* token = strtok(line, "|"); // Tách mã sách
        if (token) strcpy(x.MaS, token);

        token = strtok(NULL, "|"); // Tách tên sách
        if (token) strcpy(x.TenS, token);

        token = strtok(NULL, "|"); // Tách năm xuất bản
        if (token) x.NamXB = atoi(token);

        TNode* tempNode = createTNode(x);
        if (tempNode) {
            insertAVLNode(root, tempNode);
            count++; // Tăng số lượng sách đã nhập
        }
    }

    fclose(file);
    printf("Da nap %d cuon sach vao cay AVL tu file \"books.txt\".\n", count);
}


// dếm sách có năm xb là x
int countBooksByYear(AVLNode* root, int x) {
    if (root == NULL) 
        return 0;

    int count = 0;
    if (root->Info.NamXB == x) 
        count++;

    count += countBooksByYear(root->Left, x);
    count += countBooksByYear(root->Right, x);

    return count;
}


// tìm sách tên y
AVLNode* searchBookByTitle(AVLNode* root, const char* title) {
    if (root == NULL) 
        return NULL;

    if (strcmp(root->Info.TenS, title) == 0) 
        return root;

    AVLNode* leftSearch = searchBookByTitle(root->Left, title);
    if (leftSearch) 
        return leftSearch;

    return searchBookByTitle(root->Right, title);
}

void findBookByTitle(AVLNode* root) {
    char y[100];
    printf("Nhap ten sach can tim: ");
    getchar(); // Loại bỏ ký tự '\n' trước khi nhập chuỗi
    gets(y);

    AVLNode* result = searchBookByTitle(root, y); // ✅ Đúng nếu `searchBookByTitle()` đã được định nghĩa đúng cách

    if (result) {
        printf("Tim thay sach: MaS: %s - TenS: %s - NamXB: %d\n", 
               result->Info.MaS, result->Info.TenS, result->Info.NamXB);
    } else {
        printf("Khong tim thay sach \"%s\" trong cay AVL.\n", y);
    }
}
// tìm sách theo ma so
AVLNode* searchAVL(AVLNode* root, const char* maSach) {
    if (root == NULL) 
        return NULL;

    int cmp = strcmp(maSach, root->Info.MaS); // So sánh mã sách
    if (cmp == 0) 
        return root;  // ✅ Tìm thấy sách

    if (cmp < 0) 
        return searchAVL(root->Left, maSach);
    else 
        return searchAVL(root->Right, maSach);
}

AVLNode* deleteBookByMaS(AVLNode* root, const char* x) {
    if (root == NULL) 
        return NULL; // Không tìm thấy sách để xóa

    int cmp = strcmp(x, root->Info.MaS);
    if (cmp < 0) {
        root->Left = deleteBookByMaS(root->Left, x);
    } else if (cmp > 0) {
        root->Right = deleteBookByMaS(root->Right, x);
    } else {
        // Đã tìm thấy sách có mã số x cần xóa
        AVLNode* temp;
        if (root->Left == NULL) {
            temp = root->Right;
            free(root);
            return temp;
        } else if (root->Right == NULL) {
            temp = root->Left;
            free(root);
            return temp;
        } else {
            // Tìm nút thay thế từ cây con phải
            AVLNode* standFor = root->Right;
            while (standFor->Left != NULL)
                standFor = standFor->Left;

            root->Info = standFor->Info; // Sao chép dữ liệu từ nút thay thế
            root->Right = deleteBookByMaS(root->Right, standFor->Info.MaS);
        }
    }
    return root;
}
// xóa cây
void deleteAVLTree(AVLNode*& root) {
    if (root == NULL) return;

    deleteAVLTree(root->Left);  // Xóa cây con trái
    deleteAVLTree(root->Right); // Xóa cây con phải

    free(root); // Giải phóng bộ nhớ của nút hiện tại
    root = NULL;
}//show cây
void showTree(AVLNode* root, int level) {
    if (root == NULL) return;

    // Duyệt cây con phải trước để in theo cấu trúc cây
    showTree(root->Right, level + 1);

    // In khoảng trắng theo cấp độ để thể hiện cấu trúc cây
    for (int i = 0; i < level; i++) 
        printf("\t");

    // Hiển thị thông tin sách tại nút hiện tại
    printf("%s - %s - %d\n", root->Info.MaS, root->Info.TenS, root->Info.NamXB);

    // Duyệt cây con trái sau
    showTree(root->Left, level + 1);
}

void showMenu() {
    printf("\n=========== QUAN LY SACH ===========\n");
    printf("1. Them sach vao cay AVL\n");
    printf("2. Duyet cay theo thu tu trung to\n");
    printf("3. Tim sach theo ten\n");
    printf("4. Tim sach theo ma so\n");
    printf("5. Dem so sach xuat ban nam x\n");
    printf("6. Xoa sach theo ma so\n");
    printf("7. Doc danh sach sach tu file\n");
    printf("8. Xoa toan bo cay AVL\n");
    printf("9. Hien thi cau truc cay AVL\n"); // ✅ Đã thêm chức năng mới
    printf("0. Thoat chuong trinh\n");
    printf("====================================\n");
}

int main() {
    AVLNode* root = NULL;
    int option;

    do {
        showMenu();
        printf("Chon chuc nang: ");
        scanf("%d", &option);
        getchar(); // Loại bỏ ký tự '\n' tránh lỗi nhập chuỗi

        switch (option) {
            case 1: { // ✅ Thêm sách vào cây AVL
                Book x;
                printf("Nhap ma sach: ");
                gets(x.MaS);
                printf("Nhap ten sach: ");
                gets(x.TenS);
                printf("Nhap nam xuat ban: ");
                scanf("%d", &x.NamXB);
                
                TNode* tempNode = createTNode(x);
                if (tempNode) {
                    insertAVLNode(root, tempNode);
                }
                printf("Da them sach \"%s\" vao cay AVL.\n", x.TenS);
            } break;

            case 2: { // ✅ Duyệt cây theo trung tố
                printf("Danh sach sach theo thu tu trung to:\n");
                inorderTraversal(root);
            } break;

            case 3: { // ✅ Tìm sách theo tên
                findBookByTitle(root);
            } break;

            case 4: { // ✅ Tìm sách theo mã số
                char x[10];
                printf("Nhap ma sach can tim: ");
                scanf("%s", x);
                AVLNode* result = searchAVL(root, x);
                if (result) {
                    printBook(result->Info);
                } else {
                    printf("Khong tim thay sach co ma \"%s\".\n", x);
                }
            } break;

            case 5: { // ✅ Đếm số sách xuất bản theo năm
                int x;
                printf("Nhap nam xuat ban can tim: ");
                scanf("%d", &x);
                int total = countBooksByYear(root, x);
                printf("Co %d sach xuat ban nam %d.\n", total, x);
            } break;

            case 6: { // ✅ Xóa sách theo mã số
                char x[10];
                printf("Nhap ma sach can xoa: ");
                scanf("%s", x);
                root = deleteBookByMaS(root, x);
                printf("Sach co MaS \"%s\" da duoc xoa (neu ton tai).\n", x);
            } break;

            case 7: { // ✅ Đọc danh sách sách từ file
                createAVLTreeFromFile(root);


            } break;

            case 8: { // ✅ Xóa toàn bộ cây AVL
                deleteAVLTree(root);
                printf("Cay AVL da duoc xoa hoan toan.\n");
            } break;
            case 9:
			    printf("Cau truc cay AVL:\n");
			    showTree(root, 0);
			    break;
            case 0: { // ✅ Thoát chương trình
                printf("Thoat chuong trinh.\n");
            } break;

            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (option != 0);

    return 0;
}
