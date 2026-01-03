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
// Cấu trúc dữ liệu cho Bảng Băm (Phương pháp dò bậc hai)
// =======================================================

typedef struct HashEntry_QP
{
    int Key;
} HashEntry_QP;

HashEntry_QP hashTable_QP[KEYSIZE];

// =======================================================
// Hàm Băm (cho Quadratic Probing)
// =======================================================

int hashFunction_QP(int Key)
{
    return Key % KEYSIZE;
}

// =======================================================
// Các hàm cho Bảng băm Dò Bậc hai (Bài 4)
// =======================================================

// Khởi tạo bảng băm dò bậc hai
void initHashTable_QP()
{
    for (int i = 0; i < KEYSIZE; i++)
    {
        hashTable_QP[i].Key = EMPTY_KEY;
    }
    printf("Da khoi tao bang bam do bac hai rong.\n");
}

// Chèn một khóa vào bảng băm dò bậc hai
void insert_QP(int k)
{
    if (k == EMPTY_KEY || k == DELETED_KEY) {
        printf("Khong the su dung khoa %d. Day la cac khoa danh dau trang thai.\n", k);
        return;
    }

    int initialIndex = hashFunction_QP(k);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i * i) % KEYSIZE; // Công thức dò bậc hai

        if (hashTable_QP[currentIndex].Key == EMPTY_KEY || hashTable_QP[currentIndex].Key == DELETED_KEY)
        {
            hashTable_QP[currentIndex].Key = k;
            printf("Da them khoa %d vao vi tri %d (do bac hai).\n", k, currentIndex);
            return;
        }
        else if (hashTable_QP[currentIndex].Key == k)
        {
            printf("Khoa %d da ton tai. Khong the them.\n", k);
            return;
        }
        i++;
    } while (i < KEYSIZE); // Tránh vòng lặp vô hạn nếu bảng đầy

    printf("Bang bam day, khong the them khoa %d.\n", k);
}

// Tìm kiếm một khóa trong bảng băm dò bậc hai
int search_QP(int k)
{
    int initialIndex = hashFunction_QP(k);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i * i) % KEYSIZE; // Công thức dò bậc hai

        if (hashTable_QP[currentIndex].Key == EMPTY_KEY)
        {
            return FALSE; // Gặp ô trống, nghĩa là khóa không tồn tại
        }
        else if (hashTable_QP[currentIndex].Key == k)
        {
            return TRUE; // Tìm thấy khóa
        }
        i++;
    } while (i < KEYSIZE);

    return FALSE; // Không tìm thấy sau khi duyệt hết bảng
}

// Xóa một khóa khỏi bảng băm dò bậc hai
void remove_QP(int k)
{
    int initialIndex = hashFunction_QP(k);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i * i) % KEYSIZE; // Công thức dò bậc hai

        if (hashTable_QP[currentIndex].Key == EMPTY_KEY)
        {
            printf("Khong tim thay khoa %d de xoa.\n", k);
            return;
        }
        else if (hashTable_QP[currentIndex].Key == k)
        {
            hashTable_QP[currentIndex].Key = DELETED_KEY; // Đánh dấu là đã xóa
            printf("Da xoa khoa %d tai vi tri %d.\n", k, currentIndex);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Khong tim thay khoa %d de xoa.\n", k);
}

// Duyệt và hiển thị bảng băm dò bậc hai
void traverseHashTable_QP()
{
    printf("\n--- Bang Bam Do Bac Hai ---\n");
    for (int i = 0; i < KEYSIZE; i++)
    {
        printf("Vi tri [%d]: ", i);
        if (hashTable_QP[i].Key == EMPTY_KEY)
        {
            printf("TRONG\n");
        }
        else if (hashTable_QP[i].Key == DELETED_KEY)
        {
            printf("DA XOA\n");
        }
        else
        {
            printf("%d\n", hashTable_QP[i].Key);
        }
    }
    printf("------------------------------\n");
}

// Menu và chức năng chính cho Bài 4
void showMenu_Bai4() {
    printf("\n\n");
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM DO BAC HAI (BAI 4) *\n");
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
    initHashTable_QP();

    do
    {
        showMenu_Bai4();
        printf("Chuc nang ban chon: ");
        scanf("%d", &selectFunction);
        fflush(stdin);

        switch (selectFunction)
        {
        case 1:
            printf("Nhap gia tri khoa muon them: ");
            scanf("%d", &Key);
            fflush(stdin);
            insert_QP(Key);
            break;
        case 2:
            printf("So khoa ban muon them: ");
            scanf("%d", &n);
            fflush(stdin);
            srand(unsigned(time(NULL)));
            for (int i = 0; i < n; i++)
            {
                Key = rand() % 1000;
                insert_QP(Key);
            }
            printf("Da them %d khoa ngau nhien.\n", n);
            break;
        case 3:
            printf("Nhap khoa muon xoa: ");
            scanf("%d", &Key);
            fflush(stdin);
            remove_QP(Key);
            break;
        case 4:
            printf("Nhap khoa muon tim kiem: ");
            scanf("%d", &Key);
            fflush(stdin);
            if (search_QP(Key))
            {
                printf("Tim thay khoa %d trong bang bam.\n", Key);
            }
            else
            {
                printf("Khong tim thay khoa %d trong bang bam.\n", Key);
            }
            break;
        case 5:
            traverseHashTable_QP();
            break;
        case 0:
            printf("Thoat chuong trinh Bai 4.\n");
            break;
        default:
            printf("Chuc nang khong hop le. Vui long chon lai.\n");
            break;
        }
    } while (selectFunction != 0);

    _getch();
    return 0;
}