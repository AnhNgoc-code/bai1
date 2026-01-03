#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // For rand(), srand()
#include <time.h>   // For time()

#define TRUE 1
#define FALSE 0
#define KEYSIZE 100 // Kích thước bảng băm
#define EMPTY_KEY -1 // Giá trị đặc biệt để đánh dấu ô trống
#define DELETED_KEY -2 // Giá trị đặc biệt để đánh dấu ô đã xóa (để tìm kiếm vẫn hoạt động)

// =======================================================
// Cấu trúc dữ liệu cho Bảng Băm (Phuong phap do tuyen tinh)
// =======================================================

// Một ô trong bảng băm
typedef struct HashEntry_LP
{
    int Key;
    // Để quản lý trạng thái, bạn có thể dùng enum:
    // enum { EMPTY, OCCUPIED, DELETED } status;
    // Ở đây, chúng ta dùng giá trị của Key để đánh dấu trạng thái.
} HashEntry_LP;

// Mảng bảng băm (không dùng con trỏ Next)
HashEntry_LP hashTable_LP[KEYSIZE];

// =======================================================
// Hàm Băm (cho Linear Probing)
// =======================================================

// Hàm băm đơn giản (cho số nguyên)
int hashFunction_LP(int Key)
{
    return Key % KEYSIZE;
}

// =======================================================
// Các hàm cho Bảng băm Dò Tuyến tính (Bài 3)
// =======================================================

// Khởi tạo bảng băm dò tuyến tính
void initHashTable_LP()
{
    for (int i = 0; i < KEYSIZE; i++)
    {
        hashTable_LP[i].Key = EMPTY_KEY; // Đánh dấu tất cả các ô là trống
    }
    printf("Da khoi tao bang bam do tuyen tinh rong.\n");
}

// Chèn một khóa vào bảng băm dò tuyến tính
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

        // Nếu tìm thấy ô trống hoặc ô đã xóa
        if (hashTable_LP[currentIndex].Key == EMPTY_KEY || hashTable_LP[currentIndex].Key == DELETED_KEY)
        {
            hashTable_LP[currentIndex].Key = k;
            printf("Da them khoa %d vao vi tri %d (do tuyen tinh).\n", k, currentIndex);
            return;
        }
        // Nếu khóa đã tồn tại (kiểm tra trước khi chèn)
        else if (hashTable_LP[currentIndex].Key == k)
        {
            printf("Khoa %d da ton tai. Khong the them.\n", k);
            return;
        }
        i++;
    } while (i < KEYSIZE); // Tránh vòng lặp vô hạn nếu bảng đầy

    printf("Bang bam day, khong the them khoa %d.\n", k);
}

// Tìm kiếm một khóa trong bảng băm dò tuyến tính
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
            return FALSE; // Gặp ô trống, nghĩa là khóa không tồn tại
        }
        else if (hashTable_LP[currentIndex].Key == k)
        {
            return TRUE; // Tìm thấy khóa
        }
        i++;
    } while (i < KEYSIZE); // Tránh vòng lặp vô hạn nếu đã duyệt hết bảng

    return FALSE; // Không tìm thấy sau khi duyệt hết bảng
}

// Xóa một khóa khỏi bảng băm dò tuyến tính
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
            return; // Gặp ô trống, khóa không tồn tại
        }
        else if (hashTable_LP[currentIndex].Key == k)
        {
            hashTable_LP[currentIndex].Key = DELETED_KEY; // Đánh dấu là đã xóa
            printf("Da xoa khoa %d tai vi tri %d.\n", k, currentIndex);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Khong tim thay khoa %d de xoa.\n", k);
}

// Duyệt và hiển thị bảng băm dò tuyến tính
void traverseHashTable_LP()
{
    printf("\n--- Bang Bam Do Tuyen Tinh ---\n");
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

// Menu và chức năng chính cho Bài 3
void showMenu_Bai3() {
    printf("\n\n");
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM DO TUYEN TINH (BAI 3) *\n");
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
        showMenu_Bai3();
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
            printf("Thoat chuong trinh Bai 3.\n");
            // Không cần giải phóng bộ nhớ động nếu không dùng malloc/free trong LP
            break;
        default:
            printf("Chuc nang khong hop le. Vui long chon lai.\n");
            break;
        }
    } while (selectFunction != 0);

    _getch();
    return 0;
}