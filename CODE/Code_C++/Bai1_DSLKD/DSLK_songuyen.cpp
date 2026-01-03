
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

typedef int ItemType;
struct SNode
{//Tạo 1 node
	ItemType Info;
	SNode* Next;
};
//==============================================================
struct SList
{//Tạo 1 danh sách các Node
	SNode *Head;
	SNode *Tail;
};
//==============================================================
SNode* createSNode(ItemType x)
{//Tạo 1 node mới
	SNode* p = new SNode;
	if (p == NULL)
	{
		printf("Khong the cap phat bo nho !");
		getch();
		return NULL;
	}
	p->Info = x; // Gán giá trị 
	p->Next = NULL;// Giá địa chỉ (mặc dịnh là node)
	return p;
}
//==============================================================
void showSNode(SNode* p)
{//Hiển thị 1 Node
	printf("%d", p->Info);
}
//==============================================================
void initSList(SList& sl)
{//Set địa chỉ Head - Tail
	sl.Head = NULL;
	sl.Tail = NULL;
}
//==============================================================
int isEmpty(SList sl)
{// Check SList rỗng hay không 
	//C1 : return sl.Head == NULL ? 1 : 0;
	//C2 :
	if (sl.Head == NULL)
		return 1; // Có
	else
		return 0; // Không
}
//==============================================================
int insertHead(SList& sl, SNode* p)
{//Chèn lên đầu SList
	if (p == NULL)
		return 0;
	if (isEmpty(sl) == 1) //Mặc định ở đầu và cuối nếu SNode đầu tiên
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
int insertTail(SList& sl, SNode* p)
{//Chèn vào cuối SList
	if (p == NULL)
		return 0;
	if (isEmpty(sl) == 1)//Mặc định ở đầu và cuối nếu SNode đầu tiên
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
int insertAfter(SList& sl, SNode* q, SNode* p)
{//Chèn SNode vào sau
	if (q == NULL || p == NULL)
		return 0;
	p->Next = q->Next;
	q->Next = p;
	if (sl.Tail == q) // Trường hợp nó chèn ở Tail
		sl.Tail = p;
	return 1;
}
//==============================================================
int insertBefore(SList& sl, SNode* q, SNode* p)
{//Chèn SNode vào trước
	if (q == NULL || p == NULL)
		return 0;
	p->Next = q;
	for (SNode* k = sl.Head; k != NULL; k = k->Next)
	{
		if (k->Next == q)
		{
			k->Next = p;
			break;
		}
	}
	if (sl.Head == q) // Trường hợp nó chèn ở Head
		sl.Head = p;
	return 1;
}
//==============================================================
void createSList_InputByHand(SList& sl)
{//tạo thủ công SList
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
		printf("Nhap gia tri cho Node thu %d: ", i + 1);
		scanf("%d", &x);
		SNode* p = createSNode(x);
		//int kq = insertHead(sl, p);
		int kq = insertTail(sl, p);
		if (kq == 1) i++;
	}
}
//==============================================================
void createSList_Random(SList& sl)
{//Chèn ngẫu nhiên SList
	initSList(sl);
	int n;
	do
	{
		printf("Nhap so luong phan tu cua danh sach : ");
		scanf("%d", &n);
		if (n <= 0) printf("Nhap sai roi! Vui long nhap lai.\n");
	} while (n <= 0);
	srand((unsigned)time(NULL));
	int i = 0;
	while (i < n)
	{
		ItemType x;
		x = rand() % 199 - 99;
		printf("\nSo vua tao la : %d", x);
		SNode* p = createSNode(x);
		int kq;
		if (rand() % 2 == 1)
			kq = insertHead(sl, p);
		else
			kq = insertTail(sl, p);
		if (kq == 1) i++;
	}
}
//==============================================================
void createSList_FromArray(SList& sl, ItemType a[], int n)
{//Chèn từ mảng vào SList
	initSList(sl);
	int i = 0;
	while (i < n)
	{
		ItemType x;
		x = a[i];
		SNode* p = createSNode(x);
		//int kq = insertHead(sl, p);
		int kq = insertTail(sl, p);
		if (kq == 1) i++;
	}
}
//==============================================================
void createSList_FromTextFile(SList& sl, char inputFileName[])
{//Chèn từ file Text vào SList
	initSList(sl);
	int n;
	FILE* fi = fopen(inputFileName, "rt");
	if (fi == NULL)
	{
		printf("Loi mo file : %s", inputFileName);
		return;
	}
	fscanf(fi, "%d\n", &n);
	int i = 0;
	while (i < n)
	{
		ItemType x;
		fscanf(fi, "%d", &x);
		SNode* p = createSNode(x);
		//int kq = insertHead(sl, p);
		int kq = insertTail(sl, p);
		if (kq == 1) i++;
	}
	fclose(fi);
}
//==============================================================
void swap(ItemType& x, ItemType& y)
{//Hoán đổi 2 giá trị
	ItemType tmp;
	tmp = x;
	x = y;
	y = tmp;
}
//==============================================================
void interchangeSort_Ascending_SList(SList sl)
{//Sắp xếp tăng dần
	for (SNode* p = sl.Head; p->Next != NULL; p = p->Next)
	{
		for (SNode* q = p->Next; q != NULL; q = q->Next)
		{
			if (p->Info > q->Info)
			{
				swap(p->Info, q->Info);
			}
		}
	}
}
//==============================================================
void selectionSort_SList_Decending(SList sl)
{// Sắp xếp giảm dần
	if (isEmpty(sl) == 1 || sl.Head == sl.Tail) return;
	for (SNode *p = sl.Head; p != NULL; p = p->Next)
	{
		SNode *min = p;
		for (SNode *q = p->Next; q != NULL; q = q->Next)
			if (min->Info < q->Info)
				min = q;
		if (min != p)
			swap(min->Info, p->Info);
	}
}
//==============================================================
void showSList(SList sl)
{//Hiển thị SList
	if (isEmpty(sl) == 1)
	{
		printf("Danh sach rong !");
		return;
	}
	//printf("\nNOI DUNG CUA DANH SACH LA : \n");
	for (SNode* p = sl.Head; p != NULL; p = p->Next)
	{
		showSNode(p);
		printf(" -> ");
	}
	printf("NULL");
}
//==============================================================
SNode* findSNode(SList sl, ItemType x)
{// Tìm SNode
	if (isEmpty(sl) == 1)
	{
		return NULL;
	}
	for (SNode* p = sl.Head; p != NULL; p = p->Next)
	{
		if (p->Info == x)
			return p;
	}
	return NULL;
}
//==============================================================
int checkSNT(ItemType x)
{ //Kiểm tra số nguyên tố
	if (x < 2) return 0;
	else
	{
		for (ItemType i = 2; i < (ItemType)sqrt((float)x); i++)
		{
			if (x % i == 0) return 0;
		}
		return 1;
	}
}
//==============================================================
int checkSCP(ItemType x)
{// Kiểm tra số chính phương
	if (x <= 1) return 0;
	else
	{
		int squareroot = sqrt((float)x);
		if (squareroot * squareroot == x)
			return 1;
		else
			return 0;
	}
}
//==============================================================
int soluongSNT_SList(SList sl)
{//Đếm số lượng số nguyên tố trong SList
	ItemType Dem = 0;
	SNode *p;
	for (p = sl.Head; p != NULL;p=p->Next)
	if (checkSNT(p->Info) == 1)
		Dem++;
	return Dem;
}
//==============================================================
int tongSCP_SList(SList sl)
{// Tổng các số chính phương trong SList
	ItemType Sum = 0;
	SNode *p;
	for (p = sl.Head; p != NULL; p = p->Next)
	if (checkSCP(p->Info) == 1)
		Sum += p->Info;
	return Sum;
}
//==============================================================
void Max_Min_SList(SList sl)
{ // Tìm Max - Min
	//C1 : Su dung Interchange Sort
	interchangeSort_Ascending_SList(sl);
	printf("Min = %d\n", sl.Head->Info);
	printf("Max = %d\n", sl.Tail->Info);
	/*C2 : Su dung Selection Sort
	selectionSort_SList_Decending(sl);
	printf("Min = %d\n", sl.Tail->Info);
	printf("Max = %d\n", sl.Head->Info);*/
}
//==============================================================
int soluongPT_lonhon2sauno_SList(SList sl)
{
	int Dem = 0;
	for (SNode *p = sl.Head; p != NULL; p = p->Next)
	{
		if (p->Next == NULL) break;
		else
			if (p->Info / (p->Next)->Info >= 2)
				Dem++;
	}
	return Dem;
}
//==============================================================
void tao2DSChanle(SList sl)
{//Danh sách chẵn - lẻ
	SList sll, slc;
	initSList(sll); initSList(slc);
	for (SNode *p = sl.Head; p != NULL; p = p->Next)
	{
		SNode *q = createSNode(p->Info);
		if (p->Info % 2 == 0)
			insertTail(slc, q);
		else
			insertTail(sll, q);
	}
	printf("\nNOI DUNG DANH SACH CAC SO CHAN : \n");
	showSList(slc);
	printf("\nNOI DUNG DANH SACH CAC SO LE : \n");
	showSList(sll);
}
//==============================================================
void showMenu()
{
	printf("\n******************************************************************");
	printf("\n*                              MENU                              *");
	printf("\n******************************************************************");
	printf("\n* 0. Thoat chuong trinh                                          *");
	printf("\n* 1. Nhap - Xuat 1 Node                                          *");
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
	printf("\n* 12. Tim phan tu x trong danh sach ?                            *");
	printf("\n* 13. Bao nhieu so nguyen to trong danh sach                     *");
	printf("\n* 14. Tong cac so chinh phuong trong danh sach                   *");
	printf("\n* 15. Tim Max - Min trong danh sach                              *");
	printf("\n* 16. So phan tu lon gap doi sau phan tu do trong danh sach      *");
	printf("\n* 17. Tao 2 danh sach Chan - Le                                  *");
	printf("\n******************************************************************");
}
//==============================================================
void process()
{
	int luaChon, kq;
	SNode* P, *Q;
	SList SL;
	ItemType X, Y;
	ItemType A[] = { 15, -27, 43, 23, -35, 48, 97, -76, 91, 13 };
	int N = 10;
	char tenFile[] = "inputFile_SoNguyen.txt";
	do
	{
		showMenu();
		printf("\nBan hay lua chon mot chuc nang : ");
		scanf("%d", &luaChon);
		switch (luaChon)
		{
		case 1:
			printf("Ban hay nhap mot so nguyen bat ky : ");
			scanf("%d", &X);
			P = createSNode(X);
			showSNode(P);
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
			createSList_FromTextFile(SL, tenFile);
			printf("\nNOI DUNG DANH SACH VUA TAO TU FILE TEXT LA : \n");
			showSList(SL);
			break;
		case 6:
			printf("Ban hay cho biet gia tri node muon them vao dau danh sach : ");
			scanf("%d", &X);
			P = createSNode(X);
			kq = insertHead(SL, P);
			if (kq == 1)
			{
				printf("\nNOI DUNG DANH SACH SAU KHI THEM %d VAO DAU LA : \n", X);
				showSList(SL);
			}
			else
			{
				printf("\nKhong the them %d vao dau danh sach.", X);
			}
			break;
		case 7:
			printf("Ban hay cho biet gia tri node muon them vao cuoi danh sach : ");
			scanf("%d", &X);
			P = createSNode(X);
			kq = insertTail(SL, P);
			if (kq == 1)
			{
				printf("\nNOI DUNG DANH SACH SAU KHI THEM %d VAO CUOI LA : \n", X);
				showSList(SL);
			}
			else
			{
				printf("\nKhong the them %d vao cuoi danh sach.", X);
			}
			break;
		case 8:
			printf("Ban hay cho biet gia tri node muon them vao danh sach : ");
			scanf("%d", &Y);
			P = createSNode(Y);
			printf("Ban hay cho biet gia tri node ke truoc trong danh sach : ");
			scanf("%d", &X);
			Q = findSNode(SL, X);
			kq = insertAfter(SL, Q, P);
			if (kq == 1)
			{
				printf("\nNOI DUNG DANH SACH SAU KHI THEM %d VAO SAU %d LA : \n", Y, X);
				showSList(SL);
			}
			else
			{
				printf("\nKhong the them %d vao sau %d trong danh sach.", Y, X);
			}
			break;
		case 9:
			printf("Ban hay cho biet gia tri node muon them vao danh sach : ");
			scanf("%d", &Y);
			P = createSNode(Y);
			printf("Ban hay cho biet gia tri node ke sau trong danh sach : ");
			scanf("%d", &X);
			Q = findSNode(SL, X);
			kq = insertBefore(SL, Q, P);
			if (kq == 1)
			{
				printf("\nNOI DUNG DANH SACH SAU KHI THEM %d VAO TRUOC %d LA : \n", Y, X);
				showSList(SL);
			}
			else
			{
				printf("\nKhong the them %d vao truoc %d trong danh sach.", Y, X);
			}
			break;
		case 10:
			interchangeSort_Ascending_SList(SL);
			printf("\nNOI DUNG DANH SACH SAU KHI SAP XEP TANG DAN VOI INTERCHANGE SORT LA : \n");
			showSList(SL);
			break;
		case 11:
			selectionSort_SList_Decending(SL);
			printf("\nNOI DUNG DANH SACH SAU KHI SAP XEP GIAM DAN VOI SELECTION SORT LA : \n");
			showSList(SL);
			break;
		case 12:
			printf("Ban hay cho biet gia tri node can tim trong danh sach : ");
			scanf("%d", &X);
			P = findSNode(SL, X);
			if (P == NULL)
				printf("Khong tim thay %d trong danh sach.", X);
			else
				printf("Da tim thay %d trong danh sach tai dia chi %d", X, P);
			break;
		case 13:
			kq = soluongSNT_SList(SL);
			if (kq == 0)
				printf("Khong tim thay so nguyen to trong danh sach.");
			else
				printf("Da tim thay %d so nguyen to trong danh sach.",kq);
			break;
		case 14:
			kq = tongSCP_SList(SL);
			printf("Tong cua cac so chinh phuong trong danh sach = %d", kq);
			break;
		case 15:
			Max_Min_SList(SL);
			break;
		case 16:
			kq = soluongPT_lonhon2sauno_SList(SL);
			if (kq == 0)
				printf("Khong co phan tu nao lon hon gap doi phan tu sau no.");
			else
				printf("Co %d phan tu lon hon gap hai phan tu sau no.", kq);
			break;
		case 17:
			tao2DSChanle(SL);
			break;
		}
	} while (luaChon != 0);
}
//==============================================================
int main()
{
	process();
    return 0;
}