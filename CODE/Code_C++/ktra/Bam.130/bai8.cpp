#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For strcmp, strcpy, strtok, strcspn

#define TRUE 1
#define FALSE 0
#define KEYSIZE 100 // Kích thước bảng băm
#define MAX_LINE_LENGTH 256 // Độ dài tối đa của một dòng trong file

// =======================================================
// Cấu trúc dữ liệu cho Bảng Băm Sinh viên (Phương pháp dò tuyến tính)
// =======================================================

// Trạng thái của một ô trong bảng băm
typedef enum {
    EMPTY,      // Ô trống
    OCCUPIED,   // Ô đang được sử dụng
    DELETED     // Ô đã bị xóa (quan trọng cho việc tìm kiếm)
} EntryStatus;

// Một ô trong bảng băm
typedef struct HashEntry_Student_LP
{
    char MSSV[15];
    char HoTen[50];
    float Diem;
    EntryStatus Status;
} HashEntry_Student_LP;

// Mảng bảng băm
HashEntry_Student_LP hashTable_Student_LP[KEYSIZE];

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
// Các hàm cho Bảng băm Sinh viên Dò Tuyến tính (Bài 8)
// =======================================================

// Khởi tạo bảng băm
void initHashTable_Student_LP()
{
    for (int i = 0; i < KEYSIZE; i++)
    {
        hashTable_Student_LP[i].Status = EMPTY;
    }
    printf("Da khoi tao bang bam sinh vien do tuyen tinh rong.\n");
}

// Chèn một sinh viên vào bảng băm
void insert_Student_LP(const char *mssv, const char *hoTen, float diem)
{
    int initialIndex = hashFunction_MSSV(mssv);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i) % KEYSIZE;

        if (hashTable_Student_LP[currentIndex].Status == EMPTY || hashTable_Student_LP[currentIndex].Status == DELETED)
        {
            // Kiểm tra trùng lặp MSSV trước khi thêm vào ô trống/đã xóa
            // Cần tìm kiếm toàn bộ bảng để đảm bảo không trùng lặp nếu MSSV đã bị xóa
            for (int j = 0; j < KEYSIZE; j++) {
                if (hashTable_Student_LP[j].Status == OCCUPIED && strcmp(hashTable_Student_LP[j].MSSV, mssv) == 0) {
                    printf("MSSV %s da ton tai. Khong the them.\n", mssv);
                    return;
                }
            }

            strcpy(hashTable_Student_LP[currentIndex].MSSV, mssv);
            strcpy(hashTable_Student_LP[currentIndex].HoTen, hoTen);
            hashTable_Student_LP[currentIndex].Diem = diem;
            hashTable_Student_LP[currentIndex].Status = OCCUPIED;
            printf("Da them sinh vien %s vao vi tri %d (do tuyen tinh).\n", mssv, currentIndex);
            return;
        }
        else if (hashTable_Student_LP[currentIndex].Status == OCCUPIED && strcmp(hashTable_Student_LP[currentIndex].MSSV, mssv) == 0)
        {
            printf("MSSV %s da ton tai. Khong the them.\n", mssv);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Bang bam day, khong the them sinh vien %s.\n", mssv);
}

// Tìm kiếm sinh viên theo MSSV
HashEntry_Student_LP* search_Student_LP(const char *mssv)
{
    int initialIndex = hashFunction_MSSV(mssv);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i) % KEYSIZE;

        if (hashTable_Student_LP[currentIndex].Status == EMPTY)
        {
            return NULL; // Gặp ô trống, nghĩa là sinh viên không tồn tại
        }
        else if (hashTable_Student_LP[currentIndex].Status == OCCUPIED && strcmp(hashTable_Student_LP[currentIndex].MSSV, mssv) == 0)
        {
            return &hashTable_Student_LP[currentIndex]; // Tìm thấy sinh viên
        }
        i++;
    } while (i < KEYSIZE);

    return NULL; // Không tìm thấy sau khi duyệt hết bảng
}

// Xóa một sinh viên khỏi bảng băm theo MSSV
void remove_Student_LP(const char *mssv)
{
    int initialIndex = hashFunction_MSSV(mssv);
    int i = 0;
    int currentIndex;

    do
    {
        currentIndex = (initialIndex + i) % KEYSIZE;

        if (hashTable_Student_LP[currentIndex].Status == EMPTY)
        {
            printf("Khong tim thay sinh vien voi MSSV %s de xoa.\n", mssv);
            return; // Gặp ô trống, sinh viên không tồn tại
        }
        else if (hashTable_Student_LP[currentIndex].Status == OCCUPIED && strcmp(hashTable_Student_LP[currentIndex].MSSV, mssv) == 0)
        {
            hashTable_Student_LP[currentIndex].Status = DELETED; // Đánh dấu là đã xóa
            printf("Da xoa sinh vien voi MSSV %s tai vi tri %d.\n", mssv, currentIndex);
            return;
        }
        i++;
    } while (i < KEYSIZE);

    printf("Khong tim thay sinh vien voi MSSV %s de xoa.\n", mssv);
}

// Duyệt và hiển thị tất cả sinh viên trong bảng băm
void traverseHashTable_Student_LP()
{
    printf("\n--- Danh sach tat ca sinh vien trong bang bam (Do tuyen tinh) ---\n");
    int empty_or_deleted_count = 0;
    for (int i = 0; i < KEYSIZE; i++)
    {
        printf("Vi tri [%d]: ", i);
        if (hashTable_Student_LP[i].Status == EMPTY)
        {
            printf("TRONG\n");
            empty_or_deleted_count++;
        }
        else if (hashTable_Student_LP[i].Status == DELETED)
        {
            printf("DA XOA\n");
            empty_or_deleted_count++;
        }
        else // OCCUPIED
        {
            printf("MSSV: %s, Ho Ten: %s, Diem: %.2f\n",
                   hashTable_Student_LP[i].MSSV,
                   hashTable_Student_LP[i].HoTen,
                   hashTable_Student_LP[i].Diem);
        }
    }
    if (empty_or_deleted_count == KEYSIZE) {
        printf("Bang bam hien tai rong.\n");
    }
    printf("-----------------------------------------------------------------\n");
}

// Menu và chức năng chính cho Bài 8
void showMenu_Bai8()
{
    printf("\n\n");
    printf("****************************************\n");
    printf("* UNG DUNG BANG BAM SINH VIEN (BAI 8)  *\n"); //
    printf("* (Phuong phap do tuyen tinh)        *\n");
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
    HashEntry_Student_LP *foundStudent;

    initHashTable_Student_LP();

    do {
        showMenu_Bai8();
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
                                insert_Student_LP(mssv, hoTen, diem);
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
                insert_Student_LP(mssv, hoTen, diem);
                break;

            case 3: // Xóa một sinh viên
                printf("Nhap MSSV can xoa: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                remove_Student_LP(mssv);
                break;

            case 4: // Xem thông tin về một sinh viên
                printf("Nhap MSSV can tim: "); fgets(mssv, sizeof(mssv), stdin); mssv[strcspn(mssv, "\n")] = 0;
                foundStudent = search_Student_LP(mssv);
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
                traverseHashTable_Student_LP();
                break;

            case 0: // Thoát
                printf("Ket thuc chuong trinh Bai 8.\n");
                // Không cần giải phóng bộ nhớ động nếu không dùng malloc/free trong LP
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
                break;
        }
    } while (selectFunction != 0);

    _getch();
    return 0;
}