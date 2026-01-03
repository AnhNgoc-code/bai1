#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h> // For getch()

// Structure to represent a fraction
struct PhanSo
{
    int TuSo;   // Numerator
    int MauSo;  // Denominator
};
typedef struct PhanSo ItemType;

// Structure to represent a node in the singly linked list
struct SNode
{
    ItemType Info;
    struct SNode* Next;
};
typedef struct SNode SNode; // Using typedef for SNode

// Structure to represent the singly linked list
struct SList
{
    SNode *Head;
    SNode *Tail;
};
typedef struct SList SList; // Using typedef for SList

// Function prototypes
void doiDau(ItemType &ps);
int timUCLN(int a, int b);
void rutGonPS(ItemType &ps);
void nhapPS(ItemType &ps);
void taoPS(ItemType &ps);
void xuatPS(ItemType ps);
SNode* createSNode(ItemType x);
void showSNode(SNode* p);
void initSList(SList& sl);
int isEmpty(SList sl);
int insertHead(SList& sl, SNode* p);
int insertTail(SList& sl, SNode* p);
int insertAfter(SList& sl, SNode* q, SNode* p);
int insertBefore(SList& sl, SNode* q, SNode* p);
void createSList_InputByHand(SList& sl);
void createSList_Random(SList& sl);
void createSList_FromArray(SList& sl, ItemType a[], int n);
void createSList_FromTextFile(SList& sl, char inputFileName[]);
void swap(ItemType& x, ItemType& y);
int comparePhanSo(ItemType ps1, ItemType ps2); // Helper for comparing fractions
void interchangeSort_Ascending_SList(SList& sl); // Pass by reference for sorting
void selectionSort_SList_Descending(SList& sl); // Pass by reference for sorting
void showSList(SList sl);
SNode* findSNode(SList sl, ItemType x);
void Max_Min_SList(SList sl);
int checkSNT(int n); // Helper to check if a number is prime
int soluongSNT_SList(SList sl);
int checkSCP(int n); // Helper to check if a number is a perfect square
int tongSCP_SList(SList sl);
int soluongPT_lonhon2sauno_SList(SList sl);
void tao2DSChanle(SList sl); // Creates two new lists, not modifies the original
void showMenu();
void process();

//==============================================================
// Changes the sign of the fraction if the denominator is negative
void doiDau(ItemType &ps)
{
    if (ps.MauSo < 0)
    {
        ps.TuSo *= -1;
        ps.MauSo *= -1;
    }
}

//==============================================================
// Finds the Greatest Common Divisor (GCD) using Euclidean algorithm
int timUCLN(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
            b -= a;
    }
    return a;
}

//==============================================================
// Simplifies a fraction
void rutGonPS(ItemType &ps)
{
    if (ps.TuSo == 0) { // If numerator is 0, fraction is 0/1
        ps.MauSo = 1;
        return;
    }
    int tmp = timUCLN(ps.TuSo, ps.MauSo);
    ps.TuSo /= tmp;
    ps.MauSo /= tmp;
}

//==============================================================
// Inputs a fraction from the user
void nhapPS(ItemType &ps)
{
    printf("\nNhap tu so : ");
    scanf("%d", &ps.TuSo);
    do
    {
        printf("Nhap mau so : ");
        scanf("%d", &ps.MauSo);
        if (ps.MauSo == 0)
        {
            printf("Mau so khong the la 0! Vui long nhap lai.\n");
        }
    } while (ps.MauSo == 0);
    doiDau(ps);
    rutGonPS(ps);
}

//==============================================================
// Generates a random fraction
void taoPS(ItemType &ps)
{
    ps.TuSo = rand() % 100 - 50; // Random numerator between -50 and 49
    do
    {
        ps.MauSo = rand() % 100 - 50; // Random denominator between -50 and 49
    } while (ps.MauSo == 0);
    doiDau(ps);
    rutGonPS(ps);
}

//==============================================================
// Displays a fraction
void xuatPS(ItemType ps)
{
    if (ps.MauSo == 1) { // If denominator is 1, just print numerator
        printf("%d", ps.TuSo);
    } else {
        printf("%d/%d", ps.TuSo, ps.MauSo);
    }
}

//==============================================================
// Creates a new SNode
SNode* createSNode(ItemType x)
{
    SNode* p = (SNode*)malloc(sizeof(SNode)); // Use malloc for C
    if (p == NULL)
    {
        printf("Khong the cap phat bo nho !");
        getch(); // For console applications, waits for a key press
        return NULL;
    }
    p->Info = x;
    p->Next = NULL;
    return p;
}

//==============================================================
// Displays the content of a single node
void showSNode(SNode* p)
{
    if (p != NULL) {
        xuatPS(p->Info);
    } else {
        printf("Node rong!");
    }
}

//==============================================================
// Initializes an empty singly linked list
void initSList(SList& sl)
{
    sl.Head = NULL;
    sl.Tail = NULL;
}

//==============================================================
// Checks if the singly linked list is empty
int isEmpty(SList sl)
{
    return sl.Head == NULL ? 1 : 0;
}

//==============================================================
// Inserts a node at the beginning of the list
int insertHead(SList& sl, SNode* p)
{
    if (p == NULL)
        return 0;
    if (isEmpty(sl) == 1)
    {
        sl.Head = p;
        sl.Tail = p;
    }
    else
    {
        p->Next = sl.Head;
        sl.Head = p;
    }
    return 1;
}

//==============================================================
// Inserts a node at the end of the list
int insertTail(SList& sl, SNode* p)
{
    if (p == NULL)
        return 0;
    if (isEmpty(sl) == 1)
    {
        sl.Head = p;
        sl.Tail = p;
    }
    else
    {
        sl.Tail->Next = p;
        sl.Tail = p;
    }
    return 1;
}

//==============================================================
// Inserts a node 'p' after a node 'q' in the list
int insertAfter(SList& sl, SNode* q, SNode* p)
{
    if (q == NULL || p == NULL) // q must exist to insert after it
        return 0;
    
    // Check if q is actually in the list (optional, but good practice for robustness)
    SNode* current = sl.Head;
    int q_found = 0;
    while(current != NULL) {
        if (current == q) {
            q_found = 1;
            break;
        }
        current = current->Next;
    }

    if (!q_found) return 0; // q not found in the list

    p->Next = q->Next;
    q->Next = p;
    if (sl.Tail == q) // If q was the tail, p becomes the new tail
        sl.Tail = p;
    return 1;
}

//==============================================================
// Inserts a node 'p' before a node 'q' in the list
int insertBefore(SList& sl, SNode* q, SNode* p)
{
    if (q == NULL || p == NULL)
        return 0;

    if (sl.Head == q) // If q is the head, insert p at the head
    {
        return insertHead(sl, p);
    }

    SNode* k = sl.Head;
    while (k != NULL && k->Next != q) // Find the node before q
    {
        k = k->Next;
    }

    if (k == NULL) // q was not found in the list (or it's the head, which is handled)
        return 0;

    p->Next = q;
    k->Next = p;
    return 1;
}

//==============================================================
// Creates a singly linked list by user input
void createSList_InputByHand(SList& sl)
{
    initSList(sl);
    int n;
    do
    {
        printf("Nhap so luong phan tu cua danh sach : ");
        scanf("%d", &n);
        if (n <= 0) printf("Nhap sai roi! Vui long nhap lai.\n");
    } while (n <= 0);
    int i = 0;
    while (i < n)
    {
        ItemType x;
        printf("\nNhap phan tu thu %d:\n", i + 1);
        nhapPS(x);
        SNode* p = createSNode(x);
        int kq;
        if (rand() % 2 == 0) // Randomly insert at head or tail
            kq = insertHead(sl, p);
        else
            kq = insertTail(sl, p);
        if (kq == 1) i++;
    }
}

//==============================================================
// Creates a singly linked list with random elements
void createSList_Random(SList& sl)
{
    initSList(sl);
    int n;
    do
    {
        printf("Nhap so luong phan tu cua danh sach : ");
        scanf("%d", &n);
        if (n <= 0) printf("Nhap sai roi! Vui long nhap lai.\n");
    } while (n <= 0);
    srand((unsigned)time(NULL)); // Seed the random number generator
    int i = 0;
    while (i < n)
    {
        ItemType x;
        taoPS(x);
        SNode* p = createSNode(x);
        int kq;
        if (rand() % 2 == 0) // Randomly insert at head or tail
            kq = insertHead(sl, p);
        else
            kq = insertTail(sl, p);
        if (kq == 1) i++;
    }
}

//==============================================================
// Creates a singly linked list from an array
void createSList_FromArray(SList& sl, ItemType a[], int n)
{
    initSList(sl);
    int i = 0;
    while (i < n)
    {
        ItemType x;
        x = a[i];
        doiDau(x); // Ensure correct sign and simplification
        rutGonPS(x);
        SNode* p = createSNode(x);
        int kq;
        if (rand() % 2 == 0)
            kq = insertHead(sl, p);
        else
            kq = insertTail(sl, p);
        if (kq == 1) i++;
        else { // Handle memory allocation failure during creation
            printf("Error: Could not allocate memory for node from array element %d\n", i);
            break;
        }
    }
}

//==============================================================
// Creates a singly linked list from a text file
void createSList_FromTextFile(SList& sl, char inputFileName[])
{
    initSList(sl);
    int n;
    FILE* fi = fopen(inputFileName, "rt");
    if (fi == NULL)
    {
        printf("Loi mo file : %s\n", inputFileName);
        return;
    }
    fscanf(fi, "%d\n", &n); // Read the number of elements (if specified in file)

    for (int i = 0; i < n; i++) { // Assuming file contains n pairs of numerator and denominator
        ItemType x;
        if (fscanf(fi, "%d %d", &x.TuSo, &x.MauSo) == 2) { // Read numerator and denominator
            if (x.MauSo == 0) {
                printf("Warning: Invalid fraction (denominator is 0) in file. Skipping.\n");
                continue;
            }
            doiDau(x);
            rutGonPS(x);
            SNode* p = createSNode(x);
            if (p != NULL) {
                // You can choose to insert at head or tail consistently, or randomly
                insertTail(sl, p); // Insert at tail for order preservation from file
            } else {
                printf("Error: Could not allocate memory for node from file.\n");
                break; // Stop processing if memory allocation fails
            }
        } else {
            printf("Warning: Malformed data in file at element %d. Stopping read.\n", i);
            break;
        }
    }
    fclose(fi);
}

//==============================================================
// Swaps two ItemType values (fractions)
void swap(ItemType& x, ItemType& y)
{
    ItemType tmp;
    tmp = x;
    x = y;
    y = tmp;
}

//==============================================================
// Compares two fractions (returns 1 if ps1 > ps2, -1 if ps1 < ps2, 0 if equal)
int comparePhanSo(ItemType ps1, ItemType ps2) {
    // Convert to common denominator to compare
    long long val1 = (long long)ps1.TuSo * ps2.MauSo;
    long long val2 = (long long)ps2.TuSo * ps1.MauSo;

    if (val1 > val2) return 1;
    if (val1 < val2) return -1;
    return 0; // Equal
}

//==============================================================
// Sorts the list in ascending order using Interchange Sort
void interchangeSort_Ascending_SList(SList& sl)
{
    if (isEmpty(sl) || sl.Head == sl.Tail) return;

    for (SNode* p = sl.Head; p->Next != NULL; p = p->Next)
    {
        for (SNode* q = p->Next; q != NULL; q = q->Next)
        {
            if (comparePhanSo(p->Info, q->Info) > 0) // if p > q, swap
            {
                swap(p->Info, q->Info);
            }
        }
    }
}

//==============================================================
// Sorts the list in descending order using Selection Sort
void selectionSort_SList_Descending(SList& sl)
{
    if (isEmpty(sl) == 1 || sl.Head == sl.Tail) return;

    for (SNode *p = sl.Head; p != NULL; p = p->Next)
    {
        SNode *maxNode = p; // Changed from min to max for descending
        for (SNode *q = p->Next; q != NULL; q = q->Next)
        {
            if (comparePhanSo(maxNode->Info, q->Info) < 0) // If maxNode < q, then q is new max
                maxNode = q;
        }
        if (maxNode != p)
            swap(maxNode->Info, p->Info);
    }
}

//==============================================================
// Displays the content of the singly linked list
void showSList(SList sl)
{
    if (isEmpty(sl) == 1)
    {
        printf("Danh sach rong !\n");
        return;
    }
    //printf("\nNOI DUNG CUA DANH SACH LA : \n");
    for (SNode* p = sl.Head; p != NULL; p = p->Next)
    {
        xuatPS(p->Info);
        printf(" -> ");
    }
    printf("NULL\n"); // Indicate end of list
}

//==============================================================
// Finds a node with a specific fraction value in the list
SNode* findSNode(SList sl, ItemType x)
{
    if (isEmpty(sl) == 1)
    {
        return NULL;
    }
    
    // Normalize the target fraction first for accurate comparison
    ItemType normalized_x = x;
    doiDau(normalized_x);
    rutGonPS(normalized_x);

    for (SNode* p = sl.Head; p != NULL; p = p->Next)
    {
        // Normalize the current node's fraction before comparing
        ItemType current_info_normalized = p->Info;
        doiDau(current_info_normalized);
        rutGonPS(current_info_normalized);

        if (current_info_normalized.TuSo == normalized_x.TuSo && current_info_normalized.MauSo == normalized_x.MauSo)
            return p;
    }
    return NULL;
}

//==============================================================
// Helper function to check if a number is prime
int checkSNT(int n) {
    if (n < 2) return 0; // Numbers less than 2 are not prime
    if (n == 2) return 1; // 2 is prime
    if (n % 2 == 0) return 0; // Even numbers greater than 2 are not prime
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

//==============================================================
// Counts the number of prime numerators in the SList
int soluongSNT_SList(SList sl)
{
    int Dem = 0;
    SNode *p;
    for (p = sl.Head; p != NULL; p = p->Next)
    {
        if (checkSNT(p->Info.TuSo) == 1) // Check the numerator for primality
            Dem++;
    }
    return Dem;
}

//==============================================================
// Helper function to check if a number is a perfect square
int checkSCP(int n) {
    if (n < 0) return 0; // Negative numbers are not perfect squares
    int root = (int)sqrt(n);
    return (root * root == n);
}

//==============================================================
// Calculates the sum of perfect square numerators in the SList
int tongSCP_SList(SList sl)
{
    int sum = 0;
    SNode *p;
    for (p = sl.Head; p != NULL; p = p->Next)
    {
        if (checkSCP(p->Info.TuSo) == 1) // Check the numerator for perfect square
            sum += p->Info.TuSo;
    }
    return sum;
}

//==============================================================
// Finds Max and Min fractions in the list
void Max_Min_SList(SList sl)
{
    if (isEmpty(sl) == 1) {
        printf("Danh sach rong, khong co Max - Min.\n");
        return;
    }

    ItemType max_ps = sl.Head->Info;
    ItemType min_ps = sl.Head->Info;

    SNode* p = sl.Head->Next;
    while (p != NULL) {
        if (comparePhanSo(p->Info, max_ps) > 0) { // If p > max_ps
            max_ps = p->Info;
        }
        if (comparePhanSo(p->Info, min_ps) < 0) { // If p < min_ps
            min_ps = p->Info;
        }
        p = p->Next;
    }

    printf("Min = ");
    xuatPS(min_ps);
    printf("\n");
    printf("Max = ");
    xuatPS(max_ps);
    printf("\n");
}

//==============================================================
// Counts elements whose numerator is twice the numerator of the next element
int soluongPT_lonhon2sauno_SList(SList sl)
{
    int count = 0;
    if (isEmpty(sl) || sl.Head->Next == NULL) // Need at least two elements
        return 0;

    SNode* current = sl.Head;
    while (current->Next != NULL) {
        // Compare current numerator with the next node's numerator
        if (current->Info.TuSo == 2 * current->Next->Info.TuSo) {
            count++;
        }
        current = current->Next;
    }
    return count;
}

//==============================================================
// Creates two new lists: one for even numerators, one for odd numerators
void tao2DSChanle(SList sl)
{
    SList evenList, oddList;
    initSList(evenList);
    initSList(oddList);

    SNode* p = sl.Head;
    while (p != NULL) {
        SNode* newNode = createSNode(p->Info);
        if (newNode != NULL) {
            if (p->Info.TuSo % 2 == 0) { // Even numerator
                insertTail(evenList, newNode);
            } else { // Odd numerator
                insertTail(oddList, newNode);
            }
        } else {
            printf("Loi cap phat bo nho khi tao danh sach chan/le.\n");
            // Optionally, free already allocated nodes in evenList and oddList
            // and return or handle error appropriately.
            break;
        }
        p = p->Next;
    }

    printf("\n--- Danh sach Phan so Chan ---\n");
    showSList(evenList);
    printf("\n--- Danh sach Phan so Le ---\n");
    showSList(oddList);

    // Free memory of the new lists when done if they are not needed further
    // (This part is often handled by a clearSList function, not included here)
}


//=======================================//
// Displays the main menu options
void showMenu()
{
    printf("\n******************************************************************");
    printf("\n* MENU                                  *");
    printf("\n******************************************************************");
    printf("\n* 0. Thoat chuong trinh                                          *");
    printf("\n* 1. Nhap - Xuat 1 Phan So                                       *"); // Changed from Node to Phan So for clarity
    printf("\n* 2. Nhap danh sach truc tiep tu ban phim                        *");
    printf("\n* 3. Tao danh sach phat sinh ngau nhien                          *");
    printf("\n* 4. Tao danh sach tu mang 1 chieu                               *");
    printf("\n* 5. Tao danh sach tu text file                                  *");
    printf("\n* 6. Them 1 node moi vao dau danh sach                           *");
    printf("\n* 7. Them 1 node moi vao cuoi danh sach                          *");
    printf("\n* 8. Them 1 node moi p vao sau q cua danh sach                   *");
    printf("\n* 9. Them 1 node moi p vao truoc q cua danh sach                 *");
    printf("\n* 10. Sap xep danh sach tang dan voi Interchange Sort            *");
    printf("\n* 11. Sap xep danh sach giam dan voi Selection Sort              *");
    printf("\n* 12. Tim phan tu X trong danh sach                              *");
    printf("\n* 13. Bao nhieu so nguyen to trong tu so cua cac phan so         *"); // Clarified the meaning
    printf("\n* 14. Tong cac so chinh phuong trong tu so cua cac phan so       *"); // Clarified the meaning
    printf("\n* 15. Tim Max - Min trong danh sach                              *");
    printf("\n* 16. So phan tu co tu so lon gap doi tu so sau phan tu do       *"); // Clarified the meaning
    printf("\n* 17. Tao 2 danh sach Phan So Chan - Le theo tu so               *"); // Clarified the meaning
    printf("\n******************************************************************");
}

//==============================================================
// Main processing logic for the menu
void process()
{
    int luaChon, kq;
    SNode* P, *Q;
    SList SL;
    ItemType X, Y;
    // Example array of fractions
    ItemType A[] = { { 15, -27 }, { 43, 23 }, { -35, 48 }, { 97, -76 }, { 91, 13 } };
    int N = sizeof(A) / sizeof(A[0]); // Correctly calculate array size
    char tenFile[] = "inputFile_PhanSo.txt"; // Changed filename for clarity

    initSList(SL); // Initialize the main list once

    do
    {
        showMenu();
        printf("\nBan hay lua chon mot chuc nang : ");
        scanf("%d", &luaChon);

        switch (luaChon)
        {
            case 1:
                printf("\n--- Nhap va Xuat mot phan so ---\n");
                nhapPS(X);
                printf("Phan so vua nhap la: ");
                xuatPS(X);
                printf("\n");
                break;
            case 2:
                createSList_InputByHand(SL);
                printf("\nNOI DUNG DANH SACH VUA NHAP LA : \n");
                showSList(SL);
                break;
            case 3:
                createSList_Random(SL);
                printf("\nNOI DUNG DANH SACH VUA TAO NGAU NHIEN LA : \n");
                showSList(SL);
                break;
            case 4:
                createSList_FromArray(SL, A, N);
                printf("\nNOI DUNG DANH SACH VUA TAO TU MANG MOT CHIEU LA : \n");
                showSList(SL);
                break;
            case 5:
                printf("\n--- Tao danh sach tu file text ---\n");
                // For this to work, create a file named "inputFile_PhanSo.txt"
                // with content like:
                // 5
                // 1 2
                // 3 4
                // -5 6
                // 7 -8
                // 9 1
                createSList_FromTextFile(SL, tenFile);
                printf("\nNOI DUNG DANH SACH VUA TAO TU FILE TEXT LA : \n");
                showSList(SL);
                break;
            case 6:
                printf("Ban hay cho biet tu so va mau so cua phan so muon them vao dau danh sach:\n");
                nhapPS(X); // Get full fraction input
                P = createSNode(X);
                kq = insertHead(SL, P);
                if (kq == 1)
                {
                    printf("\nNOI DUNG DANH SACH SAU KHI THEM ");
                    xuatPS(X);
                    printf(" VAO DAU LA : \n");
                    showSList(SL);
                }
                else
                {
                    printf("\nKhong the them phan so vao dau danh sach.\n");
                }
                break;
            case 7:
                printf("Ban hay cho biet tu so va mau so cua phan so muon them vao cuoi danh sach:\n");
                nhapPS(X);
                P = createSNode(X);
                kq = insertTail(SL, P);
                if (kq == 1)
                {
                    printf("\nNOI DUNG DANH SACH SAU KHI THEM ");
                    xuatPS(X);
                    printf(" VAO CUOI LA : \n");
                    showSList(SL);
                }
                else
                {
                    printf("\nKhong the them phan so vao cuoi danh sach.\n");
                }
                break;
            case 8:
                printf("Ban hay cho biet tu so va mau so cua phan so Y muon them vao danh sach : \n");
                nhapPS(Y);
                P = createSNode(Y);
                printf("Ban hay cho biet tu so va mau so cua phan so X ke truoc trong danh sach : \n");
                nhapPS(X);
                Q = findSNode(SL, X); // Find the node with value X
                if (Q == NULL) {
                    printf("Khong tim thay phan so ke truoc trong danh sach.\n");
                    // Free P if not inserted
                    free(P);
                    break;
                }
                kq = insertAfter(SL, Q, P);
                if (kq == 1)
                {
                    printf("\nNOI DUNG DANH SACH SAU KHI THEM ");
                    xuatPS(Y);
                    printf(" VAO SAU ");
                    xuatPS(X);
                    printf(" LA : \n");
                    showSList(SL);
                }
                else
                {
                    printf("\nKhong the them phan so ");
                    xuatPS(Y);
                    printf(" vao sau ");
                    xuatPS(X);
                    printf(" trong danh sach.\n");
                }
                break;
            case 9:
                printf("Ban hay cho biet tu so va mau so cua phan so Y muon them vao danh sach : \n");
                nhapPS(Y);
                P = createSNode(Y);
                printf("Ban hay cho biet tu so va mau so cua phan so X ke sau trong danh sach : \n");
                nhapPS(X);
                Q = findSNode(SL, X); // Find the node with value X
                if (Q == NULL) {
                    printf("Khong tim thay phan so ke sau trong danh sach.\n");
                    // Free P if not inserted
                    free(P);
                    break;
                }
                kq = insertBefore(SL, Q, P);
                if (kq == 1)
                {
                    printf("\nNOI DUNG DANH SACH SAU KHI THEM ");
                    xuatPS(Y);
                    printf(" VAO TRUOC ");
                    xuatPS(X);
                    printf(" LA : \n");
                    showSList(SL);
                }
                else
                {
                    printf("\nKhong the them phan so ");
                    xuatPS(Y);
                    printf(" vao truoc ");
                    xuatPS(X);
                    printf(" trong danh sach.\n");
                }
                break;
            case 10:
                interchangeSort_Ascending_SList(SL);
                printf("\nNOI DUNG DANH SACH SAU KHI SAP XEP TANG DAN VOI INTERCHANGE SORT LA : \n");
                showSList(SL);
                break;
            case 11:
                selectionSort_SList_Descending(SL);
                printf("\nNOI DUNG DANH SACH SAU KHI SAP XEP GIAM DAN VOI SELECTION SORT LA : \n");
                showSList(SL);
                break;
            case 12:
                printf("Ban hay cho biet tu so va mau so cua phan so can tim trong danh sach : \n");
                nhapPS(X);
                P = findSNode(SL, X);
                if (P == NULL)
                    printf("Khong tim thay ");
                else
                    printf("Da tim thay ");
                xuatPS(X);
                if (P != NULL) {
                    printf(" trong danh sach tai dia chi %p\n", (void*)P); // Print address
                } else {
                    printf(" trong danh sach.\n");
                }
                break;
            case 13:
                kq = soluongSNT_SList(SL);
                if (kq == 0)
                    printf("Khong tim thay tu so nguyen to nao trong danh sach.\n");
                else
                    printf("Da tim thay %d tu so nguyen to trong danh sach.\n", kq);
                break;
            case 14:
                kq = tongSCP_SList(SL);
                printf("Tong cua cac tu so chinh phuong trong danh sach = %d\n", kq);
                break;
            case 15:
                Max_Min_SList(SL);
                break;
            case 16:
                kq = soluongPT_lonhon2sauno_SList(SL);
                if (kq == 0)
                    printf("Khong co phan tu nao co tu so lon hon gap doi tu so phan tu sau no.\n");
                else
                    printf("Co %d phan tu co tu so lon hon gap hai tu so phan tu sau no.\n", kq);
                break;
            case 17:
                tao2DSChanle(SL);
                break;
            case 0:
                printf("Dang thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                break;
        }
        printf("\nNhan phim bat ky de tiep tuc...");
        getch(); // Wait for a key press before clearing screen/showing menu again
        system("cls"); // Clear screen for cleaner output (Windows specific)
        // For Linux/macOS, use system("clear");
    } while (luaChon != 0);

    // Free the memory allocated for the main linked list before exiting
    SNode* current = SL.Head;
    while (current != NULL) {
        SNode* next = current->Next;
        free(current);
        current = next;
    }
    SL.Head = NULL;
    SL.Tail = NULL;
}

//==============================================================
int main()
{
    process();
return 0; 
}