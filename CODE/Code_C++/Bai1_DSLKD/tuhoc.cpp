#include<stdio.h>
#include<stdlib.h>

typedef int ItemType;

struct SNode {
    ItemType Info;
    SNode *next;
};

struct SList {
    SNode *head;
    SNode *tail;
};

void initSList(SList &sl) {
    sl.head = NULL;
    sl.tail = NULL;
}

int isEmpty(SList sl) {
    return (sl.head == NULL);
}

SNode *createSNode(ItemType x) {
    SNode *p = new SNode;
    if (p == NULL) {
        printf("Khong du cap phat bo nho\n");
        return NULL;
    }
    p->Info = x;
    p->next = NULL;
    return p;
}

void showSNode(SNode *p) {
    printf("%d ", p->Info);
}

int insertHead(SList &sl, SNode *p) {
    if (p == NULL) return 0;
    if (isEmpty(sl)) {
        sl.head = p;
        sl.tail = p;
    } else {
        p->next = sl.head;
        sl.head = p;
    }
    return 1;
}

int insertTail(SList &sl, SNode *p) {
    if (p == NULL) return 0;
    if (isEmpty(sl)) {
        sl.head = p;
        sl.tail = p;
    } else {
        sl.tail->next = p;
        sl.tail = p;
    }
    return 1;
}

int insertAfter(SList &sl, SNode *p, SNode *q) {
    if (p == NULL || q == NULL) return 0;
    p->next = q->next;
    q->next = p;
    if (sl.tail == q) {
        sl.tail = p;
    }
    return 1;
}

int insertBefore(SList &sl, SNode *p, SNode *q) {
    if (p == NULL || q == NULL || sl.head == NULL) return 0;

    if (sl.head == q) {  // Nếu q là phần tử đầu tiên
        return insertHead(sl, p);
    }

    SNode *prev = NULL;
    for (SNode *k = sl.head; k != NULL; k = k->next) {
        if (k->next == q) {
            prev = k;
            break;
        }
    }
    if (prev == NULL) return 0;  // Không tìm thấy phần tử trước q

    prev->next = p;
    p->next = q;
    return 1;
}

SNode *findSNode(SList sl, int x) {
    if (isEmpty(sl)) return NULL;
    SNode *p = sl.head;
    while (p != NULL && p->Info != x) {
        p = p->next;
    }
    return p;
}

void printSList(SList sl) {
    if (isEmpty(sl)) {
        printf("Danh sach rong\n");
        return;
    }
    SNode *current = sl.head;
    while (current != NULL) {
        printf("%d -> ", current->Info);
        current = current->next;
    }
    printf("NULL\n");
}
void ShowSlist(SList &sl){
    if(isEmpty(sl)==1){
        printf("Danh sach rong !");
        return;
    }
    for(SNode *p=sl.head;p!=NULL;p=p->next){
        printf("%d ->",p->Info);

    }
    printf("NULL");
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
    printf("9. Xoa node dau\n");
    printf("10. Xoa node cuoi\n");
    printf("11. Xoa node sau 1 node khac\n");
    printf("12. Xoa node truoc 1 node khac\n");
    printf("0. Thoat\n");
    printf("========================\n");
}


int main() {
    int choice, value, x;
    SList sl;
    SNode *q, *p;
    initSList(sl); // Initialize the list

    do {
        menu();
        printf("Nhap chuong trinh muon thuc thi: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Nhap phan tu muon them: ");
                scanf("%d", &value);
                q = createSNode(value);
                if (insertHead(sl, q)) {
                    printf("Them phan tu %d thanh cong\n", value);
                    printSList(sl);}
                else
                    printf("Them khong thanh cong\n");
                break;
            case 2:
                printf("Nhap phan tu muon them: ");
                scanf("%d", &value);
                q = createSNode(value);
                if (insertTail(sl, q))
                    printf("Them phan tu %d thanh cong\n", value);
                else
                    printf("Them khong thanh cong\n");
                break;
            case 3:
                printf("Nhap phan tu q: ");
                scanf("%d", &x);
                q = findSNode(sl, x);
                if (q == NULL) {
                    printf("Khong tim thay phan tu q\n");
                    break;
                }
                printf("Nhap phan tu muon them sau q: ");
                scanf("%d", &value);
                p = createSNode(value);
                if (insertAfter(sl, p, q))
                    printf("Them thanh cong\n");
                else
                    printf("Them that bai\n");
                break;
            case 4:
                printf("Nhap phan tu q: ");
                scanf("%d", &x);
                q = findSNode(sl, x);
                if (q == NULL) {
                    printf("Khong tim thay phan tu q\n");
                    break;
                }
                printf("Nhap phan tu muon them truoc q: ");
                scanf("%d", &value);
                p = createSNode(value);
                if (insertBefore(sl, p, q))
                    printf("Them thanh cong\n");
                else
                    printf("Them that bai\n");
                break;
            case 5:
                printSList(sl);
                break;
            
        }
    } while (choice != 0);

    return 0;
}
