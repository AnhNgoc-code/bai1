#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Itemtype;

struct Snode {
    Itemtype Info;
    Snode* next;
};

struct Slist {
    Snode* Head;
    Snode* Tail;
};

void initslist(Slist& sl) {
    sl.Head = NULL;
    sl.Tail = NULL;
}

int isEmpty(Slist sl) {
    return (sl.Head == NULL);
}

Snode* creatSnode(Itemtype x) {
    Snode* p = new Snode;
    if (p == NULL) {
        printf("Khong du cap phat bo nho\n");
        return NULL;
    }
    p->Info = x;
    p->next = NULL;
    return p;
}

void showsnode(Snode* p) {
    printf("%4d", p->Info);
}

void showslist(Slist sl) {
    if (isEmpty(sl)) {
        printf("Danh sach rong!\n");
        return;
    }
    for (Snode* p = sl.Head; p != NULL; p = p->next) {
        showsnode(p);
        printf("-->");
    }
    printf("NULL\n");
}
//==========================================================//
//tim 1 gia tri trong danh sach
Snode* findSnode(Slist sl, Itemtype x) {
    if (isEmpty(sl)) {
        return NULL;
    }
    for (Snode* p = sl.Head; p != NULL; p = p->next) {
        if (p->Info == x) {
            return p;
        }
    }
    return NULL;
}

int insertHead(Slist& sl, Snode* p) {
    if (p == NULL) return 0;
    if (isEmpty(sl)) {
        sl.Head = p;
        sl.Tail = p;
    } else {
        p->next = sl.Head;
        sl.Head = p;
    }
    return 1;
}

int insertTail(Slist& sl, Snode* p) {
    if (p == NULL) return 0;
    if (isEmpty(sl)) {
        sl.Head = p;
        sl.Tail = p;
    } else {
        sl.Tail->next = p;
        sl.Tail = p;
    }
    return 1;
}

int insertAfter(Slist& sl, Snode* p, Snode* q) {
    if (p == NULL || q == NULL) return 0;
    p->next = q->next;
    q->next = p;
    if (sl.Tail == q) {
        sl.Tail = p;
    }
    return 1;
}

int insertBefore(Slist& sl, Snode* p, Snode* q) {
    if (p == NULL || q == NULL || sl.Head == NULL) return 0;
    if (sl.Head == q) {
        return insertHead(sl,p);
    }
    for (Snode* k = sl.Head; k != NULL; k = k->next) {
        if (k->next == q) {
            k->next = p;
            p->next = q;
            return 1;
        }
    }
    return 0;
}

void creatslist_Inputbyhand(Slist& sl) {
    initslist(sl);
    int n;
    do {
        printf("Nhap so luong phan tu cua danh sach: ");
        scanf("%d", &n);
        if (n <= 0) printf("Nhap sai roi! Vui long nhap lai.\n");
    } while (n <= 0);

    for (int i = 0; i < n; i++) {
        Itemtype x;
        printf("Nhap gia tri cho Node thu %d: ", i + 1);
        scanf("%d", &x);
        Snode* p = creatSnode(x);
        insertTail(sl, p);
    }
}

void hamramdom(Slist& sl) {
    initslist(sl);
    int n;
    printf("Nhap so luong cua ban la: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        Itemtype x = rand() % 199 - 99;
        printf("NODE vua ms tao %d\n", x);
        Snode* p = creatSnode(x);
        if (rand() % 2 == 1) {
            insertTail(sl, p);
        } else {
            insertHead(sl, p);
        }
    }
}

int deleteHead(Slist& sl, Itemtype& x) {
    if (isEmpty(sl)) {
        return 0;  // Thất bại nếu danh sách rỗng
    }
    Snode* p = sl.Head;
    sl.Head = sl.Head->next;
    if (sl.Head == NULL) {
        sl.Tail = NULL;  // Nếu danh sách trở nên rỗng, cập nhật Tail
    }
    x = p->Info;  // Lưu giá trị của node bị xóa vào biến x
    delete p;     // Giải phóng bộ nhớ
    return 1;      // Thành công
}

int deleteTail(Slist& sl, Itemtype& x) {
    if (isEmpty(sl)) {
        return 0;  // Thất bại nếu danh sách rỗng
    }

    Snode* q = sl.Head;
    Snode* p = sl.Tail;

    // Trường hợp danh sách chỉ có một phần tử
    if (p == q) {
        sl.Head = sl.Tail = NULL;
    } else {
        // Duyệt đến phần tử trước phần tử cuối cùng
        while (q->next != p) {
            q = q->next;
        }
        // Cập nhật Tail của danh sách
        sl.Tail = q;
        sl.Tail->next = NULL;
    }

    x = p->Info;  // Lưu giá trị của node bị xóa vào biến x
    delete p;     // Giải phóng bộ nhớ

    return 1;      // Thành công
}

int deleteAfter(Slist& sl, Snode* q, Itemtype& x) {
    if (q == NULL || q->next == NULL) {
        return 0;  // Thất bại nếu node q là NULL hoặc không có node sau
    }
    Snode* p = q->next;
    q->next = p->next;
    if (sl.Tail == p) {
        sl.Tail = q;  // Cập nhật Tail nếu xóa node cuối cùng
    }
    x = p->Info;  // Lưu giá trị của node bị xóa vào biến x
    delete p;     // Giải phóng bộ nhớ
    return 1;      // Thành công
}
int deleteBefore(Slist &sl, Snode *q, Itemtype &x) {
    if (q == NULL || sl.Head == NULL) {
        return 0; // Xử lý danh sách rỗng hoặc q là NULL
    }
    if (sl.Head == q) {
        return 0; // Không có nút nào trước Head
    }
    if (sl.Head->next == q) {
        return deleteHead(sl, x); // Xóa Head nếu cần
    }

    Snode *prev = sl.Head;
    Snode *curr = sl.Head->next;

    // Tìm nút trước nút trước q
    while (curr != NULL && curr->next != q) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return 0; // q không có trong danh sách
    }

    prev->next = q;
    x = curr->Info;
    delete curr;


    return 1;
}
int deleteSnodeX(Slist& sl, Itemtype x) {
    if (isEmpty(sl)) {
        return 0;  // Thất bại nếu danh sách rỗng
    }
    Snode* p = sl.Head;
    Snode* q = NULL;
    while (p != NULL && p->Info != x) {
        q = p;
        p = p->next;
    }
    if (p == NULL) {
        return 0;  // Không tìm thấy node có giá trị x
    }
    if (p == sl.Head) {
        return deleteHead(sl, x);  // Xóa node đầu
    } else {
        return deleteAfter(sl, q, x);  // Xóa node sau node q
    }
}

void menu() {
    printf("========= MENU =========\n");
    printf("1. Tao 1 node va in ra\n");
    printf("2. Them dau danh sach\n");
    printf("3. Them cuoi danh sach\n");
    printf("4. Them node truoc 1 node khac\n");
    printf("5. Them node sau 1 node khac\n");
    printf("6. Tao danh sach bang ham random\n");
    printf("7. Nhap danh sach bang tay\n");
    printf("8. Xoa dau danh sach\n");
    printf("9. Xoa cuoi danh sach\n");
    printf("10.Xoa 1 node p sau q\n");
    printf("11.Xoa 1 node p truoc q\n");
    printf("12. Xoa node co gia tri x\n");
    printf("0. Thoat\n");
    printf("========================\n");
}

void procsse() {
    Slist sl;
    initslist(sl);
    Itemtype X, Y;
    int lc;
    do {
        menu();
        printf("\nLua chon chuc nang cua ban la: ");
        scanf("%d", &lc);

        switch (lc) {
            case 1: {
                printf("Nhap gia tri cho node: ");
                scanf("%d", &X);
                Snode* p = creatSnode(X);
                showsnode(p);
                break;
            }
            case 2: {
                printf("Nhap gia tri can chen dau: ");
                scanf("%d", &X);
                Snode* p = creatSnode(X);
                insertHead(sl, p);
                showslist(sl);
                break;
            }
            case 3: {
                printf("Nhap gia tri can chen cuoi: ");
                scanf("%d", &X);
                Snode* p = creatSnode(X);
                insertTail(sl, p);
                showslist(sl);
                break;
            }
            case 4: {
                printf("Nhap gia tri node moi: ");
                scanf("%d", &X);
                printf("Nhap gia tri node muon chen truoc: ");
                scanf("%d", &Y);
                Snode* p = creatSnode(X);
                Snode* q = findSnode(sl, Y);
                if (insertBefore(sl, p, q))
                    printf("Chen thanh cong!\n");
                else
                    printf("Chen that bai!\n");
                showslist(sl);
                break;
            }
            case 5: {
                printf("Nhap gia tri node moi: ");
                scanf("%d", &X);
                printf("Nhap gia tri node muon chen sau: ");
                scanf("%d", &Y);
                Snode* p = creatSnode(X);
                Snode* q = findSnode(sl, Y);
                if (insertAfter(sl, p, q))
                    printf("Chen thanh cong!\n");
                else
                    printf("Chen that bai!\n");
                showslist(sl);
                break;
            }
            case 6: {
                hamramdom(sl);
                showslist(sl);
                break;
            }
            case 7: {
                creatslist_Inputbyhand(sl);
                showslist(sl);
                break;
            }
            case 8: {
                if (deleteHead(sl, X)) {
                    printf("Xoa dau danh sach thanh cong! Gia tri xoa: %d\n", X);
                } else {
                    printf("Xoa dau danh sach that bai!\n");
                }
                showslist(sl);
                break;
            }
            case 9: {
                if (deleteTail(sl, X)) {
                    printf("Xoa cuoi danh sach thanh cong! Gia tri xoa: %d\n", X);
                } else {
                    printf("Xoa cuoi danh sach that bai!\n");
                }
                showslist(sl);
                break;
            }
            case 10: {
                printf("Nhap gia tri node sau muon xoa : ");
                scanf("%d", &X);
                Snode* q = findSnode(sl, X);
                if (q != NULL && deleteAfter(sl, q, Y)) {
                    printf("Xoa node sau thanh cong! Gia tri xoa: %d\n", Y);
                } else {
                    printf("Xoa node sau that bai!\n");
                }
                showslist(sl);
                break;
            }
            case 11: {
                printf("Nhap gia tri cua node muon xoa truoc ");
                scanf("%d", &X);
                Snode *q = findSnode(sl, X);
                if (q != NULL && deleteBefore(sl, q, Y)) {
                    printf("Da xoa thanh cong %d ra khoi danh sach\n", Y);
                } else {
                    printf("Xoa node truoc that bai!\n");
                }
                showslist(sl);
                break;
            }

            case 12: {
                printf("Nhap gia tri node muon xoa: ");
                scanf("%d", &X);
                if (deleteSnodeX(sl, X)) {
                    printf("Xoa node co gia tri %d thanh cong!\n", X);
                } else {
                    printf("Xoa node co gia tri %d that bai!\n", X);
                }
                showslist(sl);
                break;
            }
            case 0: {
                printf("Thoat chuong trinh!\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le!\n");
                break;
            }
        }
        printf("\n\n");
    } while (lc != 0);
}

int main() {
    procsse();
    return 0;
}
