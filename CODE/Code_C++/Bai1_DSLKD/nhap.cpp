#include <stdio.h>
#include <string.h>

struct BaiHat {
    char ten[51];
    char tacGia[41];
    char caSi[41];
    int thoiLuong;
};
typedef BaiHat Itemtype;

struct SNode {
    Itemtype info;
    SNode* next;
};

struct SList {
    SNode* head;
    SNode* tail;
};

SNode* createSNode(Itemtype x) {
    SNode* p = new SNode;
    if (p == NULL) {
        printf("Loi du lieu\n");
        return NULL;
    }
    p->info = x;
    p->next = NULL;
    return p;
}

void initSList(SList& sl) {
    sl.head = NULL;
    sl.tail = NULL;
}

int isEmpty(SList sl) {
    return (sl.head == NULL);
}

void nhapThongTin(Itemtype& bh) {
    printf("Nhap ten bai hat: ");
    fgets(bh.ten, 51, stdin);
    bh.ten[strcspn(bh.ten, "\n")] = 0;  // Loại bỏ ký tự '\n' ở tên

    printf("Nhap ten tac gia: ");
    fgets(bh.tacGia, 41, stdin);
    bh.tacGia[strcspn(bh.tacGia, "\n")] = 0;  // Loại bỏ '\n' ở tác giả

    printf("Nhap ten ca si: ");
    fgets(bh.caSi, 41, stdin);
    bh.caSi[strcspn(bh.caSi, "\n")] = 0;  // Loại bỏ '\n' ở ca sĩ

    printf("Nhap thoi luong: ");
    scanf("%d", &bh.thoiLuong);
    
   
}

void xuatThongTin(Itemtype bh) {
    printf("Ten bai hat: %s\n", bh.ten);
    printf("Ten tac gia: %s\n", bh.tacGia);
    printf("Ten ca si: %s\n", bh.caSi);
    printf("Thoi luong: %d\n", bh.thoiLuong);
}

int insertHead(SList& sl, SNode* p) {
    if (p == NULL) return 0;
    if (isEmpty(sl)) {
        sl.head = sl.tail = p;
    } else {
        p->next = sl.head;
        sl.head = p;
    }
    return 1;
}

int insertTail(SList& sl, SNode* p) {
    if (p == NULL) return 0;
    if (isEmpty(sl)) {
        sl.head = sl.tail = p;
    } else {
        sl.tail->next = p;
        sl.tail = p;
    }
    return 1;
}

void nhapSList(SList& sl, int n) {
    for (int i = 0; i < n; i++) {
        Itemtype bh;
        nhapThongTin(bh);
        SNode* p = createSNode(bh);
        if (p == NULL) {
            printf("Loi du lieu!\n");
            i--;
            continue;
        }
        insertTail(sl, p);
    }
}

void printSList(SList sl) {
    if (isEmpty(sl)) {
        printf("Danh sach rong!\n");
        return;
    }
    int stt = 1;
    for (SNode* cur = sl.head; cur != NULL; cur = cur->next) {
        printf("Bai hat #%d:\n", stt++);
        xuatThongTin(cur->info);
        printf("------------------------\n");
    }
}

int totalTime(SList sl) {
    int total = 0;
    for (SNode* cur = sl.head; cur != NULL; cur = cur->next) {
        total += cur->info.thoiLuong;
    }
    return total;
}



int deleteAfter(SList& sl, SNode* q, Itemtype& x) {
    if (q == NULL || q->next == NULL) return 0;
    SNode* p = q->next;
    q->next = p->next;
    if (sl.tail == p) sl.tail = q;
    x = p->info;
    delete p;
    return 1;
}

int deleteHead(SList& sl, Itemtype& x) {
    if (isEmpty(sl)) return 0;
    SNode* p = sl.head;
    sl.head = sl.head->next;
    
    // Nếu danh sách trở nên rỗng sau khi xóa phần tử đầu
    if (sl.head == NULL) {
        sl.tail = NULL;  // Cập nhật tail về NULL khi danh sách rỗng
    }
    
    x = p->info;
    delete p;
    return 1;
}

int deleteByName(SList& sl, char ten[]) {
    if (isEmpty(sl)) return 0;
    SNode* current = sl.head;
    SNode* prev = NULL;
    
    // Tìm bài hát cần xóa
    while (current != NULL && strcmp(current->info.ten, ten) != 0) {
        prev = current;
        current = current->next;
    }
    
    // Nếu không tìm thấy bài hát
    if (current == NULL) return 0;
    
    // Nếu bài hát cần xóa là bài hát đầu tiên
    if (current == sl.head) {
        return deleteHead(sl, current->info);
    }
    
    // Nếu bài hát cần xóa là bài hát khác đầu danh sách
    if (current == sl.tail) {  // Trường hợp xóa phần tử cuối cùng
        sl.tail = prev;
    }
    
    return deleteAfter(sl, prev, current->info);
}

void swap(Itemtype& x, Itemtype& y) {
    Itemtype temp = x;
    x = y;
    y = temp;
}

int sortList(SList& sl) {
    if (isEmpty(sl)) return 0;
    for (SNode* q = sl.head; q != NULL; q = q->next) {
        for (SNode* p = q->next; p != NULL; p = p->next) {
            if (strcmp(q->info.ten, p->info.ten) > 0) {
                swap(q->info, p->info);
            }
        }
    }
    return 1;
}

int moveSongToHead(SList& sl, char ten[]) {
    if (isEmpty(sl)) return 0;
    SNode* current = sl.head;
    SNode* prev = NULL;
    while (current != NULL && strcmp(current->info.ten, ten) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return 0;
    if (current == sl.head) {
        printf("Bai hat da o dau.\n");
        return 1; 
    }
    if (prev != NULL) {
        prev->next = current->next;
    }
    if (current == sl.tail) {
        sl.tail = prev;
    }
    current->next = sl.head;
    sl.head = current;
    return 1;
}

SNode* findSong(SList sl, char ten[]) {
    for (SNode* q = sl.head; q != NULL; q = q->next) {
        if (strcmp(q->info.ten, ten) == 0) return q;
    }
    return NULL;
}

void menu() {
    printf("1. Nhap thong tin 1 bai hat va xuat ra man hinh\n");
    printf("2. Nhap mot danh sach bai hat\n");
    printf("3. In danh sach\n");
    printf("4. Tong thoi gian nghe het danh sach\n");
    printf("5. Them bai hat vao dau\n");
    printf("6. Them bai hat vao cuoi\n");
    printf("7. Xoa bai hat khoi danh sach\n");
    printf("8. Tim bai hat trong danh sach\n");
    printf("9. Sap xep danh sach theo ten bai hat\n");
    printf("10. Dua 1 bai hat len dau\n");
    printf("0. Thoat\n");
}

int main() {
    int choice;
    SList sl;
    initSList(sl);
    SNode* q;
    Itemtype bh;

    do {
        menu();
        printf("Chon chuong trinh: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                nhapThongTin(bh);
                xuatThongTin(bh);
                break;

            case 2: {
                int n;
                printf("Nhap so luong bai hat: ");
                scanf("%d", &n);
                getchar();
                nhapSList(sl, n);
                break;
            }

            case 3:
                printSList(sl);
                break;

            case 4:
                printf("Tong thoi gian: %d\n", totalTime(sl));
                break;

            case 5:
                nhapThongTin(bh);
                q = createSNode(bh);
                printf(insertHead(sl, q) ? "Them thanh cong\n" : "Them that bai\n");
                break;

            case 6:
                nhapThongTin(bh);
                q = createSNode(bh);
                printf(insertTail(sl, q) ? "Them thanh cong\n" : "Them that bai\n");
                break;

            
            case 7: {
                char ten[51];
                printf("Nhap ten bai hat muon xoa: ");
                fgets(ten, 51, stdin);
                ten[strcspn(ten, "\n")] = 0;
                if (deleteByName(sl, ten)) {
                    printf("Xoa thanh cong.\n");
                } else {
                    printf("Xoa that bai.\n");
                }
                break;
            }

            case 8: {
                char ten[51];
                printf("Nhap ten bai hat muon tim: ");
                fgets(ten, 51, stdin);
                ten[strcspn(ten, "\n")] = 0;
                printf(findSong(sl, ten) ? "Co trong danh sach\n" : "Khong co trong danh sach\n");
                break;
            }

            case 9:
                printf("Danh sach truoc khi sap xep:\n");
                printSList(sl);
                sortList(sl);
                printf("Danh sach sau khi sap xep:\n");
                printSList(sl);
                break;

            case 10: {
                char ten[51];
                printf("Nhap ten bai hat: ");
                fgets(ten, 51, stdin);
                ten[strcspn(ten, "\n")] = 0;
                printf(moveSongToHead(sl, ten) ? "Di chuyen thanh cong.\n" : "Khong tim thay.\n");
                break;
            }
            case 0: printf(" 0. Thoat\n");
        }
    } while (choice != 0);
    return 0;
}
