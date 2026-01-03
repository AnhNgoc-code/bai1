#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // For rand(), srand()
#include <time.h>   // For time()

#define TRUE 1
#define FALSE 0
#define KEYSIZE 100 // Kích thước bảng băm
#define EMPTY_KEY -1 // Giá trị đặc biệt để đánh dấu ô trống
#define DELETED_KEY -2 // Giá trị đặc biệt để đánh dấu ô đã xóa

// =======================================================
// Cấu trúc dữ liệu cho Bảng Băm (Phương pháp dò tuyến tính)
// =======================================================

typedef struct HashEntry_LP
{
    int Key;
} HashEntry_LP;

HashEntry_LP hashTable_LP[KEYSIZE];

// =======================================================
// Hàm Băm (cho Linear Probing)
// =======================================================

int hashFunction_LP(int Key)
{
    return Key % KEYSIZE;
}

// =======================================================
// Các hàm cho Bảng băm Dò Tuyến tính (Bài 5 - giống Bài 3)
// =======================================================

void initHashTable_LP()
{
    for (int i = 0; i < KEYSIZE; i++)
    {
        hashTable_LP[i].Key = EMPTY_KEY;
    }
    printf("Da khoi tao bang bam do tuyen tinh rong (Bai 5).\n");
}

void insert_LP(int k)
{
    if (k == EMPTY_KEY || k == DELETED_KEY) {
        printf("Khong the su dung khoa %d. Day la cac khoa danh dau trang thai.\n", k);
        return;
    }

    int initialIndex = hashFunction_LP(k);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i) % KEYSIZE;

        if (hashTable_LP[currentIndex].Key == EMPTY_KEY || hashTable_LP[currentIndex].Key == DELETED_KEY)
        {
            hashTable_LP[currentIndex].Key = k;
            printf("Da them khoa %d vao vi tri %d (do tuyen tinh - Bai 5).\n", k, currentIndex);
            return;
        }
        else if (hashTable_LP[currentIndex].Key == k)
        {
            printf("Khoa %d da ton tai. Khong the them.\n", k);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Bang bam day, khong the them khoa %d.\n", k);
}

int search_LP(int k)
{
    int initialIndex = hashFunction_LP(k);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i) % KEYSIZE;

        if (hashTable_LP[currentIndex].Key == EMPTY_KEY)
        {
            return FALSE;
        }
        else if (hashTable_LP[currentIndex].Key == k)
        {
            return TRUE;
        }
        i++;
    } while (i < KEYSIZE);

    return FALSE;
}

void remove_LP(int k)
{
    int initialIndex = hashFunction_LP(k);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i) % KEYSIZE;

        if (hashTable_LP[currentIndex].Key == EMPTY_KEY)
        {
            printf("Khong tim thay khoa %d de xoa.\n", k);
            return;
        }
        else if (hashTable_LP[currentIndex].Key == k)
        {
            hashTable_LP[currentIndex].Key = DELETED_KEY;
            printf("Da xoa khoa %d tai vi tri %d (Bai 5).\n", k, currentIndex);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Khong tim thay khoa %d de xoa.\n", k);
}

void traverseHashTable_LP()
{
    printf("\n--- Bang Bam Do Tuyến Tính (Bài 5) ---\n");
    for (int i = 0; i < KEYSIZE; i++)
    {
        printf("Vi tri [%d]: ", i);
        if (hashTable_LP[i].Key == EMPTY_KEY)
        {
            printf("TRONG\n");
        }
        else if (hashTable_LP[i].Key == DELETED_KEY)
        {
            printf("DA XOA\n");
        }
        else
        {
            printf("%d\n", hashTable_LP[i].Key);
        }
    }
    printf("------------------------------\n");
}

// Menu và chức năng chính cho Bài 5
void showMenu_Bai5() {
    printf("\n\n");
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM DO TUYEN TINH (BAI 5) *\n");
    printf("****************************************\n");
    printf("* 1: Them mot khoa                 *\n");
    printf("* 2: Them ngau nhien nhieu khoa    *\n");
    printf("* 3: Xoa mot khoa                  *\n");
    printf("* 4: Tim kiem mot khoa             *\n");
    printf("* 5: Duyet bang bam                *\n");
    printf("* 0: Thoat chuong trinh            *\n");
    printf("****************************************\n");
    printf("\n");
}

int main()
{
    int Key, n, selectFunction;
    initHashTable_LP();

    do
    {
        showMenu_Bai5();
        printf("Chuc nang ban chon: ");
        scanf("%d", &selectFunction);
        fflush(stdin);

        switch (selectFunction)
        {
        case 1:
            printf("Nhap gia tri khoa muon them: ");
            scanf("%d", &Key);
            fflush(stdin);
            insert_LP(Key);
            break;
        case 2:
            printf("So khoa ban muon them: ");
            scanf("%d", &n);
            fflush(stdin);
            srand(unsigned(time(NULL)));
            for (int i = 0; i < n; i++)
            {
                Key = rand() % 1000;
                insert_LP(Key);
            }
            printf("Da them %d khoa ngau nhien.\n", n);
            break;
        case 3:
            printf("Nhap khoa muon xoa: ");
            scanf("%d", &Key);
            fflush(stdin);
            remove_LP(Key);
            break;
        case 4:
            printf("Nhap khoa muon tim kiem: ");
            scanf("%d", &Key);
            fflush(stdin);
            if (search_LP(Key))
            {
                printf("Tim thay khoa %d trong bang bam.\n", Key);
            }
            else
            {
                printf("Khong tim thay khoa %d trong bang bam.\n", Key);
            }
            break;
        case 5:
            traverseHashTable_LP();
            break;
        case 0:
            printf("Thoat chuong trinh Bai 5.\n");
            break;
        default:
            printf("Chuc nang khong hop le. Vui long chon lai.\n");
            break;
        }
    } while (selectFunction != 0);

    _getch();
    return 0;
}