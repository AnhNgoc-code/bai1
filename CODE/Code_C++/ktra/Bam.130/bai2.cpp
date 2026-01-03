#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // For rand(), srand(), malloc, free
#include <time.h>   // For time()

#define TRUE 1
#define FALSE 0
#define KEYSIZE 100 // Kích thước bảng băm (số bucket)

// =======================================================
// Cấu trúc dữ liệu cho Bảng Băm (Phuong phap ket noi truc tiep)
// =======================================================

// Định nghĩa kiểu dữ liệu cho 1 nut của Bảng băm (chỉ chứa số nguyên)
typedef struct HashNode_Int
{
    int Key; //
    struct HashNode_Int *Next; //
} HashNode_Int;

// Khai báo mảng bucket toàn cục
HashNode_Int *bucket[KEYSIZE]; //

// =======================================================
// Hàm Băm (cho số nguyên)
// =======================================================

int hashFunction_Int(int Key) //
{
    return Key % KEYSIZE; //
}

// =======================================================
// Các hàm thao tác với Bảng băm số nguyên
// =======================================================

// Khởi tạo bảng băm (đặt tất cả các bucket về NULL)
void initHashTable_Int()
{
    for (int b = 0; b < KEYSIZE; b++) //
    {
        bucket[b] = NULL; //
    }
    printf("Da khoi tao bang bam rong.\n");
}

// Kiểm tra một bucket có rỗng hay không?
int isEmptyBucket_Int(int b) //
{
    return (bucket[b] == NULL) ? TRUE : FALSE; //
}

// Kiểm tra bảng băm có rỗng hay không?
int isEmptyHashTable_Int() //
{
    for (int b = 0; b < KEYSIZE; b++) //
    {
        if (bucket[b] != NULL) //
            return FALSE; //
    }
    return TRUE; //
}

// Xóa một nút (giải phóng bộ nhớ)
void deleteHashNode_Int(HashNode_Int *p) //
{
    if (p != NULL) //
    {
        free(p); //
    }
}

// Xóa toàn bộ các nút trong một bucket
void ClearBucket_Int(int b) //
{
    HashNode_Int *q = NULL; //
    HashNode_Int *p = bucket[b]; //
    while (p != NULL) //
    {
        q = p; //
        p = p->Next; //
        deleteHashNode_Int(q); //
    }
    bucket[b] = NULL; //
}

// Xóa toàn bộ bảng băm (yêu cầu của Bài 2)
void ClearHashTable_Int() //
{
    for (int b = 0; b < KEYSIZE; b++) //
    {
        ClearBucket_Int(b); //
    }
    printf("Da xoa toan bo bang bam thanh cong.\n");
}

// Thêm một nút số nguyên vào đầu bucket
void push_Int(int b, int x) //
{
    HashNode_Int *p = (HashNode_Int *)malloc(sizeof(HashNode_Int)); //
    if (p == NULL) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    p->Key = x; //
    p->Next = bucket[b]; //
    bucket[b] = p; //
}

// Thêm một nút số nguyên vào bảng băm
void insert_Int(int k) //
{
    int b = hashFunction_Int(k); //
    push_Int(b, k); //
    printf("Da them khoa %d vao bucket %d.\n", k, b);
}

// Tìm kiếm một khóa số nguyên trên bảng băm
int search_Int(int k) //
{
    int b = hashFunction_Int(k); //
    HashNode_Int *p = bucket[b]; //
    while (p != NULL) //
    {
        if (p->Key == k) //
        {
            return TRUE; // Found
        }
        p = p->Next; //
    }
    return FALSE; // Not found
}

// Xóa một phần tử có khóa k ra khỏi bảng băm (số nguyên)
void remove_Int(int k) //
{
    int b = hashFunction_Int(k); //
    HashNode_Int *current = bucket[b];
    HashNode_Int *prev = NULL;

    while (current != NULL && current->Key != k)
    {
        prev = current;
        current = current->Next;
    }

    if (current == NULL)
    {
        printf("Khong tim thay %d trong bang bam!\n", k);
        return;
    }

    if (prev == NULL) // Node to be removed is the head
    {
        bucket[b] = current->Next;
    }
    else
    {
        prev->Next = current->Next;
    }
    deleteHashNode_Int(current);
    printf("Da xoa %d khoi vi tri bucket %d.\n", k, b);
}

// Duyệt từng bucket (số nguyên)
void traverseBucket_Int(int b) //
{
    HashNode_Int *p = bucket[b]; //
    while (p != NULL) //
    {
        printf("%4d", p->Key); //
        p = p->Next; //
    }
}

// Duyệt bảng băm (số nguyên)
void traverseHashTable_Int() //
{
    printf("\n--- Duyet Bang Bam So Nguyen ---\n");
    int empty_count = 0;
    for (int b = 0; b < KEYSIZE; b++) //
    {
        printf("Bucket[%d]=", b); //
        if (isEmptyBucket_Int(b)) {
            printf("TRONG");
            empty_count++;
        } else {
            traverseBucket_Int(b); //
        }
        printf("\n");
    }
    if (empty_count == KEYSIZE) {
        printf("Bang bam hien tai rong.\n");
    }
    printf("--------------------------------\n");
}


// =======================================================
// Menu và Chức năng Chính của Chương trình Bài 2
// =======================================================

void showMenu_Bai2() //
{
    printf("\n\n"); //
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM SO NGUYEN (BAI 2)  *\n");
    printf("****************************************\n");
    printf("* 1: Them mot nut vao bang             *\n"); //
    printf("* 2: Them ngau nhien nhieu nut vao bang bam*\n"); //
    printf("* 3: Xoa mot nut trong bang bam        *\n"); //
    printf("* 4: Xoa toan bo bang bam              *\n"); // Bài 2
    printf("* 5: Duyet bang bam                    *\n"); //
    printf("* 6: Tim kiem tren bang bam            *\n"); //
    printf("* 0: Thoat chuong trinh                *\n"); //
    printf("****************************************\n");
    printf("\n");
}

int main()
{
    int Key, i, n, selectFunction; //
    initHashTable_Int(); // Khởi tạo bảng băm cho số nguyên

    do
    {
        showMenu_Bai2(); //
        printf("Chuc nang ban chon: "); //
        scanf("%d", &selectFunction); //
        fflush(stdin); // Xóa bộ đệm bàn phím

        switch (selectFunction) //
        {
        case 1: //
            printf("\nNhap gia tri khoa muon them: "); //
            scanf("%d", &Key); //
            fflush(stdin);
            insert_Int(Key); //
            break; //
        case 2: //
            printf("\nSo nut ban muon them: "); //
            scanf("%d", &n); //
            fflush(stdin);
            srand(unsigned(time(NULL))); //
            for (i = 0; i < n; i++) //
            {
                Key = rand() % 1000; // tao 1 so nguyen ngau nhien [0, 999]
                insert_Int(Key); //
            }
            printf("Da them %d nut ngau nhien.\n", n);
            break; //
        case 3: //
            printf("\nNhap vao khoa muon xoa: "); //
            scanf("%d", &Key); //
            fflush(stdin);
            remove_Int(Key); //
            break; //
        case 4: // Bài 2: Xóa toàn bộ bảng băm
            ClearHashTable_Int();
            break;
        case 5:
            traverseHashTable_Int();
            break;
        case 6:
            printf("\nNhap khoa muon tim kiem: ");
            scanf("%d", &Key);
            fflush(stdin);
            if (search_Int(Key))
            {
                printf("Tim thay %d trong bang bam.\n", Key);
            }
            else
            {
                printf("Khong tim thay %d trong bang bam.\n", Key);
            }
            break;
        case 0:
            printf("Ket thuc chuong trinh Bai 2.\n");
            ClearHashTable_Int(); // Đảm bảo giải phóng bộ nhớ khi thoát
            break;
        default:
            printf("Chuc nang khong hop le. Vui long chon lai.\n");
            break;
        }
    } while (selectFunction != 0); //

    _getch(); // Giữ cửa sổ console mở (chỉ hoạt động trên Windows với conio.h)
    return 0;
}