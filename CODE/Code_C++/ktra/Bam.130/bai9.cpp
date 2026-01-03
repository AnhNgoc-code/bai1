#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For strcmp, strcpy, strtok, strcspn

#define TRUE 1
#define FALSE 0
#define KEYSIZE 100 // Kích thước bảng băm
#define MAX_LINE_LENGTH 256 // Độ dài tối đa của một dòng trong file

// =======================================================
// Cấu trúc dữ liệu cho Bảng Băm Sinh viên (Phương pháp dò bậc hai)
// =======================================================

// Trạng thái của một ô trong bảng băm
typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} EntryStatus;

// Một ô trong bảng băm
typedef struct HashEntry_Student_QP
{
    char MSSV[15];
    char HoTen[50];
    float Diem;
    EntryStatus Status;
} HashEntry_Student_QP;

// Mảng bảng băm
HashEntry_Student_QP hashTable_Student_QP[KEYSIZE];

// =======================================================
// Hàm Băm (cho chuỗi MSSV)
// =======================================================

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
// Các hàm cho Bảng băm Sinh viên Dò Bậc hai (Bài 9)
// =======================================================

// Khởi tạo bảng băm
void initHashTable_Student_QP()
{
    for (int i = 0; i < KEYSIZE; i++)
    {
        hashTable_Student_QP[i].Status = EMPTY;
    }
    printf("Da khoi tao bang bam sinh vien do bac hai rong.\n");
}

// Chèn một sinh viên vào bảng băm
void insert_Student_QP(const char *mssv, const char *hoTen, float diem)
{
    int initialIndex = hashFunction_MSSV(mssv);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i * i) % KEYSIZE; // Công thức dò bậc hai

        if (hashTable_Student_QP[currentIndex].Status == EMPTY || hashTable_Student_QP[currentIndex].Status == DELETED)
        {
            // Kiểm tra trùng lặp MSSV trước khi thêm vào ô trống/đã xóa
            for (int j = 0; j < KEYSIZE; j++) {
                if (hashTable_Student_QP[j].Status == OCCUPIED && strcmp(hashTable_Student_QP[j].MSSV, mssv) == 0) {
                    printf("MSSV %s da ton tai. Khong the them.\n", mssv);
                    return;
                }
            }

            strcpy(hashTable_Student_QP[currentIndex].MSSV, mssv);
            strcpy(hashTable_Student_QP[currentIndex].HoTen, hoTen);
            hashTable_Student_QP[currentIndex].Diem = diem;
            hashTable_Student_QP[currentIndex].Status = OCCUPIED;
            printf("Da them sinh vien %s vao vi tri %d (do bac hai).\n", mssv, currentIndex);
            return;
        }
        else if (hashTable_Student_QP[currentIndex].Status == OCCUPIED && strcmp(hashTable_Student_QP[currentIndex].MSSV, mssv) == 0)
        {
            printf("MSSV %s da ton tai. Khong the them.\n", mssv);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Bang bam day, khong the them sinh vien %s.\n", mssv);
}

// Tìm kiếm sinh viên theo MSSV
HashEntry_Student_QP* search_Student_QP(const char *mssv)
{
    int initialIndex = hashFunction_MSSV(mssv);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i * i) % KEYSIZE; // Công thức dò bậc hai

        if (hashTable_Student_QP[currentIndex].Status == EMPTY)
        {
            return NULL;
        }
        else if (hashTable_Student_QP[currentIndex].Status == OCCUPIED && strcmp(hashTable_Student_QP[currentIndex].MSSV, mssv) == 0)
        {
            return &hashTable_Student_QP[currentIndex];
        }
        i++;
    } while (i < KEYSIZE);

    return NULL;
}

// Xóa một sinh viên khỏi bảng băm theo MSSV
void remove_Student_QP(const char *mssv)
{
    int initialIndex = hashFunction_MSSV(mssv);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i * i) % KEYSIZE; // Công thức dò bậc hai

        if (hashTable_Student_QP[currentIndex].Status == EMPTY)
        {
            printf("Khong tim thay sinh vien voi MSSV %s de xoa.\n", mssv);
            return;
        }
        else if (hashTable_Student_QP[currentIndex].Status == OCCUPIED && strcmp(hashTable_Student_QP[currentIndex].MSSV, mssv) == 0)
        {
            hashTable_Student_QP[currentIndex].Status = DELETED;
            printf("Da xoa sinh vien voi MSSV %s tai vi tri %d.\n", mssv, currentIndex);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Khong tim thay sinh vien voi MSSV %s de xoa.\n", mssv);
}

// Duyệt và hiển thị tất cả sinh viên trong bảng băm
void traverseHashTable_Student_QP()
{
    printf("\n--- Danh sach tat ca sinh vien trong bang bam (Do bac hai) ---\n");
    int empty_or_deleted_count = 0;
    for (int i = 0; i < KEYSIZE; i++)
    {
        printf("Vi tri [%d]: ", i);
        if (hashTable_Student_QP[i].Status == EMPTY)
        {
            printf("TRONG\n");
            empty_or_deleted_count++;
        }
        else if (hashTable_Student_QP[i].Status == DELETED)
        {
            printf("DA XOA\n");
            empty_or_deleted_count++;
        }
        else // OCCUPIED
        {
            printf("MSSV: %s, Ho Ten: %s, Diem: %.2f\n",
                   hashTable_Student_QP[i].MSSV,
                   hashTable_Student_QP[i].HoTen,
                   hashTable_Student_QP[i].Diem);
        }
    }
    if (empty_or_deleted_count == KEYSIZE) {
        printf("Bang bam hien tai rong.\n");
    }
    printf("--------------------------------------------------------------\n");
}

// Menu và chức năng chính cho Bài 9
void showMenu_Bai9()
{
    printf("\n\n");
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM SINH VIEN (BAI 9)  *\n"); //
    printf("* (Phuong phap do bac hai)           *\n");
    printf("****************************************\n");
    printf("* 1: Nhap du lieu sinh vien tu file    *\n");
    printf("* 2: Them mot sinh vien moi            *\n");
    printf("* 3: Xoa mot sinh vien                 *\n");
    printf("* 4: Xem thong tin ve mot sinh vien    *\n");
    printf("* 5: Xem tat ca sinh vien              *\n");
    printf("* 0: Thoat chuong trinh                *\n");
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
    HashEntry_Student_QP *foundStudent;

    initHashTable_Student_QP();

    do {
        showMenu_Bai9();
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &selectFunction);
        fflush(stdin);

        switch (selectFunction) {
            case 1: // Nhập dữ liệu sinh viên từ file
                f = fopen("sinhvien.txt", "r");
                if (f == NULL) {
                    printf("Khong the mo file 'sinhvien.txt'. Vui long tao file 'sinhvien.txt' trong cung thu muc voi dinh dang: MSSV,HoTen,Diem\n");
                    printf("Vi du:\n2022001,Nguyen Van A,8.5\n2022002,Tran Thi B,7.0\n");
                    break;
                }
                while (fgets(line, sizeof(line), f) != NULL) {
                    line[strcspn(line, "\n")] = 0;

                    char *token;
                    char temp_line[MAX_LINE_LENGTH];
                    strcpy(temp_line, line);

                    token = strtok(temp_line, ",");
                    if (token != NULL) {
                        strcpy(mssv, token);
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            strcpy(hoTen, token);
                            token = strtok(NULL, ",");
                            if (token != NULL) {
                                diem = atof(token);
                                insert_Student_QP(mssv, hoTen, diem);
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
                insert_Student_QP(mssv, hoTen, diem);
                break;

            case 3: // Xóa một sinh viên
                printf("Nhap MSSV can xoa: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                remove_Student_QP(mssv);
                break;

            case 4: // Xem thông tin về một sinh viên
                printf("Nhap MSSV can tim: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                foundStudent = search_Student_QP(mssv);
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
                traverseHashTable_Student_QP();
                break;

            case 0: // Thoát
                printf("Ket thuc chuong trinh Bai 9.\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
                break;
        }
    } while (selectFunction != 0);

    _getch();
    return 0;
}