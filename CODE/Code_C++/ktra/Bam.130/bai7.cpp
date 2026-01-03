#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For strcmp, strcpy, strtok, strcspn

#define TRUE 1
#define FALSE 0
#define KEYSIZE 100 // Kích thước bảng băm (số bucket)
#define MAX_LINE_LENGTH 256 // Độ dài tối đa của một dòng trong file

// =======================================================
// Cấu trúc dữ liệu cho Bảng Băm Sinh viên (Phương pháp nối kết trực tiếp)
// =======================================================

// Định nghĩa kiểu dữ liệu cho 1 nut của Bảng băm (chứa thông tin sinh viên)
typedef struct HashNode_Student
{
    char MSSV[15]; // Mã số sinh viên (khóa)
    char HoTen[50]; //
    float Diem; //
    struct HashNode_Student *Next;
} HashNode_Student;

// Khai báo mảng bucket toàn cục
HashNode_Student *bucket[KEYSIZE];

// =======================================================
// Hàm Băm (cho chuỗi MSSV)
// =======================================================

// Hàm băm cho chuỗi MSSV (djb2 hash algorithm)
int hashFunction_MSSV(const char *mssv)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *mssv++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % KEYSIZE;
}

// =======================================================
// Các hàm thao tác với Bảng băm Sinh viên
// =======================================================

// Khai báo nguyên mẫu hàm search_Student để khắc phục lỗi "not declared"
HashNode_Student* search_Student(const char *mssv); // KHẮC PHỤC LỖI TRONG ẢNH CHỤP MÀN HÌNH

// Khởi tạo bảng băm (đặt tất cả các bucket về NULL)
void initHashTable_Student()
{
    for (int b = 0; b < KEYSIZE; b++)
    {
        bucket[b] = NULL;
    }
    printf("Da khoi tao bang bam sinh vien rong.\n");
}

// Kiểm tra một bucket có rỗng hay không?
int isEmptyBucket_Student(int b)
{
    return (bucket[b] == NULL) ? TRUE : FALSE;
}

// Kiểm tra bảng băm có rỗng hay không?
int isEmptyHashTable_Student()
{
    for (int b = 0; b < KEYSIZE; b++)
    {
        if (bucket[b] != NULL)
            return FALSE;
    }
    return TRUE;
}

// Xóa một nút (giải phóng bộ nhớ)
void deleteHashNode_Student(HashNode_Student *p)
{
    if (p != NULL)
    {
        free(p);
    }
}

// Xóa toàn bộ các nút trong một bucket
void ClearBucket_Student(int b)
{
    HashNode_Student *q = NULL;
    HashNode_Student *p = bucket[b];
    while (p != NULL)
    {
        q = p;
        p = p->Next;
        deleteHashNode_Student(q);
    }
    bucket[b] = NULL;
}

// Xóa toàn bộ bảng băm sinh viên
void ClearHashTable_Student()
{
    for (int b = 0; b < KEYSIZE; b++)
    {
        ClearBucket_Student(b);
    }
    printf("Da xoa toan bo bang bam sinh vien thanh cong.\n");
}

// Thêm một sinh viên vào đầu bucket
void push_Student(int b, const char *mssv, const char *hoTen, float diem) //
{
    HashNode_Student *newNode = (HashNode_Student *)malloc(sizeof(HashNode_Student)); //
    if (newNode == NULL)
    {
        printf("Loi cap phat bo nho!\n"); //
        return; //
    }
    strcpy(newNode->MSSV, mssv); //
    strcpy(newNode->HoTen, hoTen); //
    newNode->Diem = diem; //
    newNode->Next = bucket[b]; //
    bucket[b] = newNode; //
}

// Thêm một sinh viên vào bảng băm
void insert_Student(const char *mssv, const char *hoTen, float diem) //
{
    int b = hashFunction_MSSV(mssv); //
    // Kiểm tra trùng lặp MSSV trước khi thêm
    if (search_Student(mssv) != NULL) { //
        printf("MSSV %s da ton tai. Khong the them.\n", mssv); //
        return; //
    }
    push_Student(b, mssv, hoTen, diem); //
    printf("Da them sinh vien %s vao bucket %d.\n", mssv, b);
}

// Tìm kiếm sinh viên theo MSSV
HashNode_Student* search_Student(const char *mssv)
{
    int b = hashFunction_MSSV(mssv);
    HashNode_Student *p = bucket[b];
    while (p != NULL)
    {
        if (strcmp(p->MSSV, mssv) == 0)
        {
            return p; // Found
        }
        p = p->Next;
    }
    return NULL; // Not found
}

// Xóa một sinh viên khỏi bảng băm theo MSSV
void remove_Student(const char *mssv)
{
    int b = hashFunction_MSSV(mssv);
    HashNode_Student *current = bucket[b];
    HashNode_Student *prev = NULL;

    while (current != NULL && strcmp(current->MSSV, mssv) != 0)
    {
        prev = current;
        current = current->Next;
    }

    if (current == NULL)
    {
        printf("Khong tim thay sinh vien voi MSSV %s trong bang bam!\n", mssv);
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
    deleteHashNode_Student(current);
    printf("Da xoa sinh vien voi MSSV %s khoi bucket %d.\n", mssv, b);
}

// Duyệt và in thông tin sinh viên trong một bucket
void traverseBucket_Student(int b)
{
    HashNode_Student *p = bucket[b];
    while (p != NULL)
    {
        printf("  MSSV: %s, Ho Ten: %s, Diem: %.2f\n", p->MSSV, p->HoTen, p->Diem);
        p = p->Next;
    }
}

// Duyệt và in thông tin tất cả sinh viên trong bảng băm
void traverseHashTable_Student()
{
    printf("\n--- Danh sach tat ca sinh vien trong bang bam ---\n");
    int empty_count = 0;
    for (int b = 0; b < KEYSIZE; b++)
    {
        if (bucket[b] != NULL) {
            printf("\nBucket[%d]:\n", b);
            traverseBucket_Student(b);
        } else {
            empty_count++;
        }
    }
    if (empty_count == KEYSIZE) {
        printf("Bang bam hien tai rong.\n");
    }
    printf("-------------------------------------------------\n");
}


// =======================================================
// Menu và Chức năng Chính của Chương trình Bài 7
// =======================================================

void showMenu_Bai7() //
{
    printf("\n\n");
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM SINH VIEN (BAI 7)  *\n"); //
    printf("****************************************\n");
    printf("* 1: Nhap du lieu sinh vien tu file    *\n"); //
    printf("* 2: Them mot sinh vien moi            *\n"); //
    printf("* 3: Xoa mot sinh vien                 *\n"); //
    printf("* 4: Xem thong tin ve mot sinh vien    *\n"); //
    printf("* 5: Xem tat ca sinh vien              *\n"); //
    printf("* 0: Thoat chuong trinh                *\n"); //
    printf("****************************************\n");
    printf("\n");
}

int main()
{
    FILE *f;
    char line[MAX_LINE_LENGTH];
    char mssv[15], hoTen[50];
    float diem;
    int selectFunction;
    HashNode_Student *foundStudent;

    initHashTable_Student(); // Khởi tạo bảng băm cho sinh viên

    do {
        showMenu_Bai7();
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &selectFunction);
        fflush(stdin); // Xóa bộ đệm bàn phím

        switch (selectFunction) {
            case 1: // Nhập dữ liệu sinh viên từ file
                f = fopen("sinhvien.txt", "r"); // Giả định file có tên sinhvien.txt
                if (f == NULL) {
                    printf("Khong the mo file 'sinhvien.txt'. Vui long tao file 'sinhvien.txt' trong cung thu muc voi dinh dang: MSSV,HoTen,Diem\n");
                    printf("Vi du:\n2022001,Nguyen Van A,8.5\n2022002,Tran Thi B,7.0\n");
                    break;
                }
                while (fgets(line, sizeof(line), f) != NULL) {
                    line[strcspn(line, "\n")] = 0; // Loại bỏ ký tự xuống dòng

                    char *token;
                    char temp_line[MAX_LINE_LENGTH];
                    strcpy(temp_line, line); // Copy line để strtok không thay đổi bản gốc

                    token = strtok(temp_line, ",");
                    if (token != NULL) {
                        strcpy(mssv, token);
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            strcpy(hoTen, token);
                            token = strtok(NULL, ",");
                            if (token != NULL) {
                                diem = atof(token);
                                insert_Student(mssv, hoTen, diem);
                            } else {
                                printf("Loi doc file: Khong co diem cho MSSV '%s'. Bo qua dong.\n", mssv);
                            }
                        } else {
                            printf("Loi doc file: Khong co ho ten cho MSSV '%s'. Bo qua dong.\n", mssv);
                        }
                    } else {
                        printf("Loi doc file: Dong trong hoac khong co MSSV. Bo qua dong.\n");
                    }
                }
                fclose(f);
                printf("Da nhap du lieu sinh vien tu file 'sinhvien.txt'.\n");
                break;

            case 2: // Thêm một sinh viên mới
                printf("Nhap MSSV: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                printf("Nhap Ho Ten: "); fgets(hoTen, sizeof(hoTen), stdin); hoTen[strcspn(hoTen, "\n")] = 0;
                printf("Nhap Diem: "); scanf("%f", &diem); fflush(stdin);
                insert_Student(mssv, hoTen, diem);
                break;

            case 3: // Xóa một sinh viên
                printf("Nhap MSSV can xoa: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                remove_Student(mssv);
                break;

            case 4: // Xem thông tin về một sinh viên
                printf("Nhap MSSV can tim: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                foundStudent = search_Student(mssv);
                if (foundStudent != NULL) {
                    printf("\n--- Thong tin sinh vien ---\n");
                    printf("MSSV: %s\n", foundStudent->MSSV);
                    printf("Ho Ten: %s\n", foundStudent->HoTen);
                    printf("Diem: %.2f\n", foundStudent->Diem);
                } else {
                    printf("Khong tim thay sinh vien voi MSSV %s.\n", mssv);
                }
                break;

            case 5: // Xem tất cả sinh viên
                traverseHashTable_Student();
                break;

            case 0: // Thoát
                printf("Ket thuc chuong trinh Bai 7.\n");
                ClearHashTable_Student(); // Giải phóng bộ nhớ khi thoát
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
                break;
        }
    } while (selectFunction != 0);

    _getch(); // Giữ cửa sổ console mở (chỉ hoạt động trên Windows với conio.h)
    return 0;
}