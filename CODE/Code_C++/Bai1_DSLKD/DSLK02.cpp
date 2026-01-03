#include <stdio.h>
#include <string.h>
struct baihat
{
	char ten[51];
	char tacgia[41];
	char casi[41];
	int thoiluong;
};
typedef baihat Itemtype;
struct SNode
{
	Itemtype Info;
	SNode *Next;
};
struct SList 
{
	SNode *Head;
	SNode *Tail;
};
SNode *CreateSNode(Itemtype x)
{
	SNode *p = new SNode;
	if(p == NULL)
		{
			printf("loi du lieu");
			return NULL;
		}
	p->Info = x;
	p->Next = NULL;
	return p;
}
void InitSNode(SList &sl)
{
	sl.Head = NULL;
	sl.Tail = NULL;
}
int IsEmpty(SList sl)
{
	if(sl.Head==NULL)
		return  1;
	else
		return 0;
}
void Nhapthongtin(Itemtype &bh)
{
	printf("nhap ten hai hat: ");
	fgets(bh.ten,51,stdin);
	printf("nhap ten tac gia: ");
	fgets(bh.tacgia,51,stdin);
	printf("nhap ten ca si: ");
	fgets(bh.casi,51,stdin);
	printf("nhap thoi luong: ");
	scanf("%d", &bh.thoiluong);
	getchar();
}
void Xuatthongtin(Itemtype bh)
{
	printf("ten bai hat: %s", bh.ten);
	printf("\nTen tac gia: %s", bh.tacgia);
	printf("\nTen ca si: %s", bh.casi);
	printf("\nThoi luong: %d\n", bh.thoiluong);
}
int InsertHead(SList &sl, SNode *p)
{
	if(p == NULL);
	return 0;
	if(IsEmpty(sl)==1)
	{
		sl.Head = p;
		sl.Tail=p;
	}
	else
	{
		p ->Next = sl.Head;
		sl.Head = p;
	}
	return 1;
}
int  InsertTail(SList &sl, SNode *p)
{
	if( p== NULL)
		return 0;
	if(IsEmpty(sl)==1)
		{
			sl.Head = p;
			sl.Tail = p;
		}
	else
		{
			sl.Tail ->Next = p;
			sl.Tail= p;
		}
	return 1;
}

void nhapSList(SList &sl, int n)
{
	for ( int i =0; i < n; i++)
	{
		Itemtype bh;
		Nhapthongtin(bh);
		SNode *p = CreateSNode(bh);
		if(p==NULL)
			{
				printf("loi du lieu!");
				i--;
				continue;
			}
		InsertTail(sl,p);
	}
}
void PrintSList(SList sl) {
    if (IsEmpty(sl)) {
        printf("Danh sách rỗng!\n");
        return;
    }

    int stt = 1;
    for (SNode* cur = sl.Head; cur != NULL; cur = cur->Next) {
        printf("Bài hát #%d:\n", stt++);
        Xuatthongtin(cur->Info);
        printf("------------------------\n");
    }
}

int Totaltimetolisen(SList sl)
{
	int total = 0;
	SNode *current = sl.Head;
	while(current!=NULL)
	{
		total = total + current ->Info.thoiluong;
		current = current ->Next;
	}
	return total;
}

int DeleteHead(SList &sl, Itemtype &x)
{
	if(IsEmpty(sl)==1)
		return 0;
	SNode *p = sl.Head;
	sl.Head = sl.Head ->Next;
	if(sl.Head == NULL)
		sl.Tail == NULL;
	x=p->Info;
	delete(p);
	return 1;
}
int DeleteAfter(SList &sl, SNode *q, Itemtype &x)
{
	if( q == NULL || q->Next == NULL)
		return 0;
	SNode *p = q->Next;
	q->Next = p->Next;
	if(sl.Tail == p)
		sl.Tail =q;
	x = p ->Info;
	delete(p);
	return 1;
}
int DeleteSongname(SList &sl, char ten[])
{
	if(IsEmpty(sl)==1)
		return 0;
	SNode *current = sl.Head;
	SNode *prev = NULL;
	while (current !=NULL && strcmp(current ->Info.ten, ten)!=0)
	{
		current = prev;
		current = current->Next;
	}
	if(current == NULL)
		return 0;
	if(current == sl.Head)
		DeleteHead(sl,current ->Info);
	else
		DeleteAfter(sl,prev,current->Info);
	return 1;
}
void swap(Itemtype &x, Itemtype &y)
{
	Itemtype temp = x;
	x = y;
	y = temp;
}
int sapxep(SList &sl)
{
	if(IsEmpty(sl)==1)
		return 0;
	for ( SNode *q = sl.Head; q!=NULL;q= q ->Next)
	{
		for(SNode *p = q->Next; p !=NULL;p = p ->Next)
			{
				if(strcmp(q->Info.ten,p->Info.ten)>0)
					{
						swap(q->Info, p->Info);
					}
			}
	}
	return 1;
}
int MoveSongtoHead(SList &sl, char ten[])
{
    if (IsEmpty(sl) == 1) 
    {
        return 0;
    }
    SNode *current = sl.Head;
    SNode *prev = NULL;
    while (current != NULL && strcmp(current->Info.ten, ten) != 0)
    {
        prev = current;
        current = current->Next;
    }

    if (current == NULL) 
    {
        return 0;
    }
    if (current == sl.Head)
    {
        printf("bai hat da o dau.\n");
        return 1;
    }
    if (prev != NULL)
    {
        prev->Next = current->Next;
    }
    if (current == sl.Tail) 
    {
        sl.Tail = prev;
    }
    current->Next = sl.Head;
    sl.Head = current;
    return 1;
}

SNode *FindSNode(SList sl,char ten[])
{
	if(IsEmpty(sl)==1)
		return 0;
	SNode *q = sl.Head;
	while(q != NULL && strcmp(q->Info.ten,ten)!=0)
		{
			q = q->Next;
		}
	return q;
}
void menu()
{
	printf("1.nhap thong tin 1 bai hat va xuat ra man hinh\n");
	printf("2.nhap mot danh sach bai hat\n");
		printf("3.in danh sach\n");
			printf("4.thoi gian nghe het danh sach\n");
				printf("5.them bai hat vao dau\n");
					printf("6.them bai hat vao cuoi\n");
						printf("7.xoa bai hat khoi danh sach\n");
							printf("8.tim bai hat co trong danh sach khong\n");
								printf("9.sap xep thu tu theo ten cua bai hay\n");
									printf("10.dua 1 bai hat len dau\n");
}
int main()
{
	int choice,value,x;
	SList sl;
	InitSNode(sl);
	SNode *q;
	SNode *p;
	Itemtype bh;
	do
	{
		menu();
		printf("chon chuong trinh muon thuc thi: ");
		scanf("%d", &choice);
		getchar();
		switch(choice)
		{
			case 1:
				Nhapthongtin(bh);
				Xuatthongtin(bh);
				break;
			case 2:
				{
					int n;
					printf("nhap so luong bai hat: ");
					scanf("%d", &n);
					getchar();
					nhapSList(sl,n);
					break;
				}
			case 3:
				PrintSList(sl);
				break;
			case 4:
				{
				int kq = Totaltimetolisen(sl);
				printf("tong thoi gian: %d\n", kq);
				break;
			}
			case 5:
				{
					Itemtype bh;
					Nhapthongtin(bh);
					q = CreateSNode(bh);
					if(InsertHead(sl,q))
						printf("them thanh cong\n");
					else
						printf("them that bai\n");
					break;
				}
			case 6:
				{
						Itemtype bh;
					Nhapthongtin(bh);
					q = CreateSNode(bh);
					if(InsertTail(sl,q))
						printf("them thanh cong\n");
					else
						printf("them that bai\n");
					break;
				}
			case 7:
				{
					char ten[51];
					printf("nhap ten bai hat muon xoa: ");
					fgets(ten,51,stdin);
					if(DeleteSongname(sl,ten))
					{
						printf("xoa thanh cong\n");
					}
					else
						printf("xoa that bai\n");
					break;
				}
			case 8:
				{
					char ten[51];
					printf("nhap ten bai hat muuon tim: ");
					fgets(bh.ten,51,stdin);
					q = FindSNode(sl,ten);
					if(q != NULL)
						printf("co trong danh sach\n");
					else
						printf("khong co trong danh sach\n");
					break;
				}
			case 9:
				{
					printf("danh sach truoc khi sap xep\n");
					PrintSList(sl);
					printf("danh sach sau khi sao xep\n");
					sapxep(sl);
					PrintSList(sl);
					break;
				}
			case 10:
				{
				    char ten[51];
				    printf("nhap ten bai hat: ");
				    fgets(ten, 51, stdin);
				    ten[strcspn(ten, "\n")] = 0; // Loại bỏ ký tự xuống dòng
				
				    if (MoveSongtoHead(sl, ten))
				    {
				        printf("them thanh cong.\n", ten);
				        PrintSList(sl); // In danh sách để kiểm tra
				    }
				    else
				    {
				        printf("khong tim thay.\n", ten);
				    }
				    break;
				}

					
		}
	}while(choice != 0);
}