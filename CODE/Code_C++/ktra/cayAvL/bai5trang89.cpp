#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <string.h>
#define LH -1
#define EH 0
#define RH 1
struct Word {
    char english[50];  // Từ tiếng Anh
    char vietnamese[100];  // Nghĩa tiếng Việt
};

typedef Word Itemtype;
int compare(Word a, Word b) {
    return strcmp(a.english, b.english);
}
// nhập dữ liệu từ người dung
void inputWord(Word &w) {
    printf("Nhap tu tieng Anh: ");
    gets(w.english);
    printf("Nhap nghia tieng Viet: ");
    gets(w.vietnamese);
}
void printBook(Word w) {
    printf("%s - %s\n", w.english, w.vietnamese);
}

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
// cây AVL
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
// thêm từ mới vào cây
void addWordToDictionary(AVLNode*& root) {
    Word newWord;
    printf("Nhap tu tieng Anh: ");
    gets(newWord.english);
    printf("Nhap nghia tieng Viet: ");
    gets(newWord.vietnamese);

    TNode* tempNode = createTNode(newWord);
    if (tempNode) {
        int result = insertAVLNode(root, tempNode);
        if (result == 2) {
            printf("Da them tu \"%s\" vao tu dien.\n", newWord.english);
        } else {
            printf("Tu \"%s\" da ton tai trong tu dien!\n", newWord.english);
        }
    }
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
void removeWord(AVLNode*& root) {
    Word targetWord;
    printf("Nhap tu tieng Anh can xoa: ");
    gets(targetWord.english); // ✅ Lưu vào biến kiểu `Word`

    int result = deleteAVLNode(root, targetWord); // ✅ Truyền đúng kiểu dữ liệu
    if (result == 2) {
        printf("Da xoa tu \"%s\" khoi tu dien.\n", targetWord.english);
    } else {
        printf("Tu \"%s\" khong ton tai trong tu dien!\n", targetWord.english);
    }
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
        Word x; // ✅ Đổi `Itemtype` thành `Word` để phù hợp với từ điển

        sprintf(x.english, "Word_%d", rand() % 1000); // ✅ Sinh từ tiếng Anh ngẫu nhiên
        sprintf(x.vietnamese, "Nghia_%d", rand() % 1000); // ✅ Sinh nghĩa ngẫu nhiên

        printf("Them tu vung: %s - %s\n", x.english, x.vietnamese);

        TNode* tempNode = createTNode(x); // ✅ Tạo nút từ `Word`
        if (tempNode) {
            insertAVLNode(root, tempNode); // ✅ Chèn vào cây AVL
        }
    }
}

// tìm nghĩa của từ
AVLNode* searchWord(AVLNode* root, const char* english) {
    if (root == NULL) return NULL;

    int cmp = strcmp(english, root->Info.english); // So sánh từ vựng
    if (cmp == 0) return root;  // ✅ Tìm thấy từ

    if (cmp < 0) return searchWord(root->Left, english);
    else return searchWord(root->Right, english);
}

void findWordMeaning(AVLNode* root) {
    char english[50];
    printf("Nhap tu tieng Anh can tim: ");
    gets(english);

    AVLNode* result = searchWord(root, english);
    if (result) {
        printf("Nghia cua tu \"%s\" la: %s\n", result->Info.english, result->Info.vietnamese);
    } else {
        printf("Khong tim thay tu \"%s\" trong tu dien.\n", english);
    }
}
//đọc file 
void readDictionaryFromFile(AVLNode*& root) {
    FILE* file = fopen("dictionary.txt", "r");
    if (!file) {
        printf("Loi: Khong the mo file \"dictionary.txt\"! Kiem tra ten file hoac duong dan.\n");
        return;
    }

    char line[200]; // Bộ đệm để đọc từng dòng từ file

    while (fgets(line, sizeof(line), file)) {
        Word x;
        char* token = strtok(line, "|"); // Tách từ tiếng Anh
        if (token) strcpy(x.english, token);

        token = strtok(NULL, "|"); // Tách nghĩa tiếng Việt
        if (token) strcpy(x.vietnamese, token);

        // Tạo nút từ từ vựng và thêm vào cây AVL
        TNode* tempNode = createTNode(x);
        if (tempNode) {
            insertAVLNode(root, tempNode);
        }
    }

    fclose(file);
    printf("Danh sach tu vung tu file \"dictionary.txt\" da duoc nap vao tu dien.\n");
}
//show cây
void showTree(AVLNode* root) {
    if (root != NULL) {
       showTree(root->Left);
        printf("%s - %s\n", root->Info.english, root->Info.vietnamese); // ✅ In từ vựng
        showTree(root->Right);
    }
}

int main() {
    AVLNode* root = NULL; 
    int option;

    do {
        printf("\n=========== TU DIEN ANH - VIET ===========\n");
        printf("1. Them tu moi\n");
        printf("2. Tim nghia cua tu\n");
        printf("3. Xoa tu\n");
        printf("4. Hien thi danh sach tu vung\n");
        printf("5. Doc tu vung tu file\n");
        printf("0. Thoat\n");
        printf("=========================================\n");

        printf("Chon chuc nang: ");
        scanf("%d", &option);
        getchar(); // Loại bỏ ký tự '\n' để tránh lỗi nhập chuỗi

        switch (option) {
            case 1: 
                addWordToDictionary(root);
                break;

            case 2: 
                findWordMeaning(root);
                break;

            case 3: 
                removeWord(root);
                break;

            case 4: 
               showTree(root);
                break;

            case 5: 
                readDictionaryFromFile(root);
                break;

            case 0: 
                printf("Thoat chuong trinh.\n");
                break;

            default: 
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (option != 0);

    return 0;
}
