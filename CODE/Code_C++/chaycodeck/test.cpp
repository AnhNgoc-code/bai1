#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//##################################
struct PhongTro {
	char maPhong[20];       // Mã phòng trọ (ví dụ: P101)
	float dienTich;      // Diện Tích phòng
	float giaPhong;       // Gía cho thuê phòng
	char tienNghi[100];     // Tiện nghi đi kèm (Wifi, Điều hòa,...)
	char trangThai[10];     // Trạng thái: "Trong" hoặc "DaThue"
};


struct BSTNodePhong {
	PhongTro Info;
	BSTNodePhong* Left;
	BSTNodePhong* Right;
};

struct BSTreePhong {
	BSTNodePhong* Root;
};
//##################################
struct NguoiThue {
	char maNguoiThue[20];        // Mã người thuê: NT001
	char tenNguoiThue[50];       // Tên người thuê
	char cccd[20];                // CCCD
	char soDienThoai[15];        // SĐT
	char ngayBatDauThue[20];     // Ngày bắt đầu thuê
	char maPhongDangThue[20];    // Mã phòng người đó đang thuê
};

struct SNodeNguoiThue {
	NguoiThue Info;
	SNodeNguoiThue* Next;
};

struct SListNguoiThue
{
	SNodeNguoiThue* Head;
	SNodeNguoiThue* Tail;
};
//##################################
struct HoaDon {
	char soHoaDon[20];       // Số hóa đơn
	char maNguoiThue[20];    // Mã người thuê tương ứng
	char ngayLap[20];        // Ngày lập hóa đơn
	float tongTien;          // Tổng tiền phải thanh toán
};

struct SNodeHoaDon {
	HoaDon Info;
	SNodeHoaDon* Next;
};

struct SListHoaDon
{
	SNodeHoaDon* Head;
	SNodeHoaDon* Tail;
};
//##################################
struct CTHoaDon {
	char soHoaDon[20];       // Số hóa đơn
	char tenDichVu[30];      // Tên dịch vụ (Nước, Internet,...)
	float  donGia;           // Giá dịch vụ
};

struct SNodeCTHoaDon {
	CTHoaDon Info;
	SNodeCTHoaDon* Next;
};

struct SListCTHoaDon
{
	SNodeCTHoaDon* Head;
	SNodeCTHoaDon* Tail;
};
//##################################
void initTree(BSTreePhong& bt) {
	bt.Root = NULL;
}

void initSListNguoiThue(SListNguoiThue& sl1)
{
	sl1.Head = NULL;
	sl1.Tail = NULL;
}

void initSListHoaDon(SListHoaDon& sl2)
{
	sl2.Head = NULL;
	sl2.Tail = NULL;
}

void initSListCTHoaDon(SListCTHoaDon& sl3)
{
	sl3.Head = NULL;
	sl3.Tail = NULL;
}
//##################################
int isEmpty(SListNguoiThue sl1) {
	return sl1.Head == NULL ? 1 : 0;
}

int isEmpty(SListHoaDon sl2) {
	return sl2.Head == NULL ? 1 : 0;
}

int isEmpty(SListCTHoaDon sl3) {
	return sl3.Head == NULL ? 1 : 0;
}
//##################################
BSTNodePhong* createPhong(PhongTro x) {
	BSTNodePhong* p = new BSTNodePhong;
	if (p == NULL)
	{
		printf("Khong the cap phat bo nho!");
		return NULL;
	}
	p->Info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}

SNodeNguoiThue* createSNode1(NguoiThue x)
{
	SNodeNguoiThue* p = new SNodeNguoiThue;
	if (p == NULL)
	{
		printf("Khong the cap phat bo nho!");
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}

SNodeHoaDon* createSNode2(HoaDon x)
{
	SNodeHoaDon* p = new SNodeHoaDon;
	if (p == NULL)
	{
		printf("Khong the cap phat bo nho!");
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}

SNodeCTHoaDon* createSNode3(CTHoaDon x)
{
	SNodeCTHoaDon* p = new SNodeCTHoaDon;
	if (p == NULL)
	{
		printf("Khong the cap phat bo nho!");
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}
//##################################
int insertPhong(BSTNodePhong* &root, BSTNodePhong* p)
{
	if (p == NULL) return 0;
	if (root == NULL) {
		root = p;
		return 1;
	}
	int cmp = strcmp(p->Info.maPhong, root->Info.maPhong);
	if (cmp == 0) {
		printf(">> Loi: Ma phong '%s' da ton tai. Khong them duoc!\n", p->Info.maPhong);
		return 0;
	}
	else if (cmp < 0) {
		return insertPhong(root->Left, p);
	}
	else {
		return insertPhong(root->Right, p);
	}

}

int insertNguoiThue(SListNguoiThue& sl1, SNodeNguoiThue* p)
{
	if (p == NULL)
	{
		return 0;
	}
	if (isEmpty(sl1) == 1)
	{
		sl1.Head = p;
		sl1.Tail = p;
	}
	else
	{
		sl1.Tail->Next = p;
		sl1.Tail = p;
	}
	return 1;
}

int insertHoaDon(SListHoaDon& sl2, SNodeHoaDon* p)
{
	if (p == NULL)
	{
		return 0;
	}
	if (isEmpty(sl2) == 1)
	{
		sl2.Head = p;
		sl2.Tail = p;
	}
	else
	{
		sl2.Tail->Next = p;
		sl2.Tail = p;
	}
	return 1;
}

int insertCTHoaDon(SListCTHoaDon& sl3, SNodeCTHoaDon* p)
{
	if (p == NULL)
	{
		return 0;
	}
	if (isEmpty(sl3) == 1)
	{
		sl3.Head = p;
		sl3.Tail = p;
	}
	else
	{
		sl3.Tail->Next = p;
		sl3.Tail = p;
	}
	return 1;
}
//##################################
void SaveTTPhong(FILE* fo, PhongTro* x)
{
	fprintf(fo, "%s %.1f %.0f %s %s\n", x->maPhong, x->dienTich, x->giaPhong, x->trangThai, x->tienNghi);
}
void SaveALLPhong(BSTNodePhong* root, FILE* fo)
{
	if (root == NULL) return;
	SaveALLPhong(root->Left, fo);
	SaveTTPhong(fo, &root->Info);
	SaveALLPhong(root->Right, fo);
}
int CountBSTNodePhong(BSTNodePhong* root)
{
	if (!root)
	{
		return 0;
	}
	int nl = CountBSTNodePhong(root->Left);
	int nr = CountBSTNodePhong(root->Right);
	return (1 + nl + nr);
}
void docPhongTuFile(BSTreePhong& bt, char tenFile[])
{
	int i = 0;
	PhongTro x;
	initTree(bt);
	int n;
	FILE* fi = fopen(tenFile, "rt");
	if (fi == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	fscanf(fi, "%d\n", &n);
	while (i < n)
	{
		fscanf(fi, "%s %f %f %s %s \n", x.maPhong, &x.dienTich, &x.giaPhong, x.trangThai, x.tienNghi);
		BSTNodePhong* p = createPhong(x);
		insertPhong(bt.Root, p);
		i++;
	}
	fclose(fi);
}
void SavePhongVaoFile(BSTreePhong& bt, char tenFile[])
{
	int i = 0;
	PhongTro x;
	FILE* fo = fopen(tenFile, "wt");
	if (fo == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int n = CountBSTNodePhong(bt.Root);
	fprintf(fo, "%d\n", n);
	SaveALLPhong(bt.Root, fo);
	fclose(fo);
	printf("Da luu thanh cong");
}
//##################################
void SaveTTNguoiThue(FILE* fo, NguoiThue x)
{
	fprintf(fo, "%s %s %s %s %s %s\n", x.maNguoiThue, x.tenNguoiThue, x.cccd, x.soDienThoai, x.ngayBatDauThue, x.maPhongDangThue);
}

int CountSNodeNguoiThue(SListNguoiThue sl1)
{
	int count = 0;
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next)
	{
		count++;
	}
	return count;
}
void docNguoiThueTuFile(SListNguoiThue& sl1, char tenFile[])
{
	int n;
	NguoiThue x;
	initSListNguoiThue(sl1);
	FILE* fi = fopen(tenFile, "rt");
	if (fi == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int i = 0;
	fscanf(fi, "%d\n", &n);
	while (i < n)
	{
		fscanf(fi, "%s %s %s %s %s %s", x.maNguoiThue, x.tenNguoiThue, x.cccd, x.soDienThoai, x.ngayBatDauThue, x.maPhongDangThue);
		SNodeNguoiThue* p = createSNode1(x);
		int kq = insertNguoiThue(sl1, p);
		if (kq == 1) i++;
	}
	fclose(fi);
}

void SaveNguoiThueVaoFile(SListNguoiThue& sl1, char tenFile[])
{
	NguoiThue x;
	FILE* fo = fopen(tenFile, "wt");
	if (fo == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int n = CountSNodeNguoiThue(sl1);
	fprintf(fo, "%d\n", n);
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next)
	{
		SaveTTNguoiThue(fo, p->Info);
	}
	fclose(fo);
}
//##################################
void SaveTTHoaDon(FILE* fo, HoaDon x)
{
	fprintf(fo, "%s %s %s %.0f\n", x.soHoaDon, x.maNguoiThue, x.ngayLap, x.tongTien);
}
int CountSNodeHoaDon(SListHoaDon sl2)
{
	int count = 0;
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next)
	{
		count++;
	}
	return count;
}
void docHoaDonTuFile(SListHoaDon& sl2, char tenFile[])
{
	int n;
	HoaDon x;
	initSListHoaDon(sl2);
	FILE* fi = fopen(tenFile, "rt");
	if (fi == NULL) 
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int i = 0;
	fscanf(fi, " %d\n", &n);
	while (i < n)
	{
		fscanf(fi, "%s %s %s %f\n", x.soHoaDon, x.maNguoiThue, x.ngayLap, &x.tongTien);

		SNodeHoaDon* p = createSNode2(x);
		int kq = insertHoaDon(sl2, p);
		if (kq == 1) i++;
	}
	fclose(fi);
}
void SaveHoaDonVaoFile(SListHoaDon& sl2, char tenFile[])
{
	HoaDon x;
	FILE* fo = fopen(tenFile, "wt");
	if (fo == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int n = CountSNodeHoaDon(sl2);
	fprintf(fo, "%d\n", n);
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next)
	{
		SaveTTHoaDon(fo, p->Info);
	}
	fclose(fo);
}
//##################################
void SaveTTCTHoaDon(FILE* fo, CTHoaDon x)
{
	fprintf(fo, "%s %s %.0f \n", x.soHoaDon, x.tenDichVu, x.donGia);
}
int CountSNodeCTHoaDon(SListCTHoaDon sl3)
{
	int count = 0;
	for (SNodeCTHoaDon* p = sl3.Head; p != NULL; p = p->Next)
	{
		count++;
	}
	return count;
}
void docCTHoaDonTuFile(SListCTHoaDon& sl3, char tenFile[])
{
	int n;
	CTHoaDon x;
	initSListCTHoaDon(sl3);
	FILE* fi = fopen(tenFile, "rt");
	if (fi == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int i = 0;
	fscanf(fi, "%d\n", &n);
	while (i < n)
	{
		fscanf(fi, "%s %s %f ", x.soHoaDon, x.tenDichVu, &x.donGia);

		SNodeCTHoaDon* p = createSNode3(x);
		int kq = insertCTHoaDon(sl3, p);
		if (kq == 1) i++;
	}
	fclose(fi);
}
void SaveCTHoaDonVaoFile(SListCTHoaDon& sl3, char tenFile[])
{
	CTHoaDon x;
	FILE* fo = fopen(tenFile, "wt");
	if (fo == NULL)
	{
		printf("Loi mo file: %s", tenFile);
		return;
	}
	int n = CountSNodeCTHoaDon(sl3);
	fprintf(fo, "%d\n", n);
	for (SNodeCTHoaDon* p = sl3.Head; p != NULL; p = p->Next)
	{
		SaveTTCTHoaDon(fo, p->Info);
	}
	fclose(fo);

}
//##################################
void ShowBSTNodePhong(BSTNodePhong* p)
{
	printf("%-6s %-10.2f %-12.2f %-8s %-6s\n", p->Info.maPhong, p->Info.dienTich, p->Info.giaPhong, p->Info.trangThai, p->Info.tienNghi);
}
void ShowSNodeNguoiThue(SNodeNguoiThue* p)
{
	printf("%-6s %-16s %-16s %-16s %-12s %-6s\n", p->Info.maNguoiThue, p->Info.tenNguoiThue, p->Info.cccd, p->Info.soDienThoai, p->Info.ngayBatDauThue, p->Info.maPhongDangThue);
}
void ShowSNodeHoaDon(SNodeHoaDon* p)
{
	printf("%-10s %-15s %-12s %-8.0f \n", p->Info.soHoaDon, p->Info.maNguoiThue, p->Info.ngayLap, p->Info.tongTien);
}
void ShowSNodeCTHoaDon(SNodeCTHoaDon* p)
{
	printf("%-10s %-15s %-12.0f \n", p->Info.soHoaDon, p->Info.tenDichVu, p->Info.donGia);
}
//##################################
void TieuDePhong()
{
	printf("%-6s %-10s %-12s %-8s %-6s\n", "MaPH", "DienTich", "GiaPhong", "TT", "TienNghi");
}
void TieuDeNguoiThue()
{
	printf("%-6s %-16s %-16s %-16s %-12s %-12s\n", "MaNT", "TenNguoiThue", "CCCD", "SoDienThoai", "NgayBDThue", "MaPhongThue");
}
void TieuDeHoaDon()
{
	printf("\n%-10s %-15s %-12s %-8s\n", "SoHD", "MaNguoiThue", "NgayLap", "TongTien");
}
void TieuDeCTHoaDon()
{
	printf("%-10s %-15s %-12s \n", "SoHD", "TenDichVu", "DonGia");
}
//##################################
void xuatDanhSachPhong(BSTNodePhong* root) {
	if (!root)
	{
		return;
	}
	xuatDanhSachPhong(root->Left);
	ShowBSTNodePhong(root);
	xuatDanhSachPhong(root->Right);
}
void XuatDanhSachNguoiThue(SListNguoiThue sl1)
{
	if (isEmpty(sl1) == 1) return;
	TieuDeNguoiThue();
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next)
	{
		ShowSNodeNguoiThue(p);
	}

}
void XuatDanhSachHoaDon(SListHoaDon sl2)
{
	if (isEmpty(sl2) == 1) return;
	TieuDeHoaDon();
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next)
	{
		ShowSNodeHoaDon(p);
	}

}
void XuatDanhSachCTHoaDon(SListCTHoaDon sl3)
{
	if (isEmpty(sl3) == 1) return;
	TieuDeCTHoaDon();
	for (SNodeCTHoaDon* p = sl3.Head; p != NULL; p = p->Next)
	{
		ShowSNodeCTHoaDon(p);
		printf("\n");
	}

}
//##################################
void NhapTTPhong(PhongTro& x)
{
	getchar();
	printf("Moi ban nhap ma phong: ");
	gets_s(x.maPhong, sizeof(x.maPhong));

	printf("Moi ban nhap dien tich: ");
	scanf_s("%f", &x.dienTich);
	getchar();

	printf("Moi ban nhap gia phong: ");
	scanf_s("%f", &x.giaPhong);
	getchar();

	printf("Moi ban nhap trang thai phong: ");
	gets_s(x.trangThai, sizeof(x.trangThai));

	printf("Moi ban nhap tien nghi: ");
	gets_s(x.tienNghi, sizeof(x.tienNghi));
}
int KiemTraTonTaiMaPhong(BSTNodePhong* root, char maPhong[]) {
	if (root == NULL) return 0;
	int cmp = strcmp(root->Info.maPhong, maPhong);
	if (cmp == 0) return 1;
	else if (cmp > 0) return KiemTraTonTaiMaPhong(root->Left, maPhong);
	else return KiemTraTonTaiMaPhong(root->Right, maPhong);
}

int KiemTraDinhDangMaNguoiThue(char ma[]) {
	if (strlen(ma) != 5) return 0;
	if (ma[0] != 'N' || ma[1] != 'T') return 0;
	for (int i = 2; i < 5; ++i) {
		if (ma[i] < '0' || ma[i] > '9') return 0;
	}
	return 1;
}
void NhapTTNguoiThue(NguoiThue& x, BSTreePhong bt)
{
	getchar();
	do {
		printf("Moi ban nhap Ma nguoi thue (NTxxx): ");
		gets_s(x.maNguoiThue, sizeof(x.maNguoiThue));
		if (!KiemTraDinhDangMaNguoiThue(x.maNguoiThue)) {
			printf(">> Ma nguoi thue khong dung dinh dang! Vui long nhap lai.\n");
		}
	} while (!KiemTraDinhDangMaNguoiThue(x.maNguoiThue));

	printf("Moi ban nhap Ten nguoi thue: ");
	gets_s(x.tenNguoiThue, sizeof(x.tenNguoiThue));

	printf("Moi ban nhap CCCD: ");
	gets_s(x.cccd, sizeof(x.cccd));

	printf("Moi ban nhap So dien thoai: ");
	gets_s(x.soDienThoai, sizeof(x.soDienThoai));

	printf("Moi ban nhap Ngay bat dau thue: ");
	gets_s(x.ngayBatDauThue, sizeof(x.ngayBatDauThue));

	do {
		printf("Moi ban nhap Ma phong dang thue: ");
		gets_s(x.maPhongDangThue, sizeof(x.maPhongDangThue));

		if (!KiemTraTonTaiMaPhong(bt.Root, x.maPhongDangThue)) {
			printf(">> Loi: Ma phong '%s' khong ton tai. Vui long nhap lai!\n", x.maPhongDangThue);
		}
	} while (!KiemTraTonTaiMaPhong(bt.Root, x.maPhongDangThue));
}


void NhapTTHoaDon(HoaDon& x)
{
	getchar();
	printf("Moi ban nhap So hoa don: ");
	gets_s(x.soHoaDon, sizeof(x.soHoaDon));

	do {
		printf("Moi ban nhap Ma nguoi thue (NTxxx): ");
		gets_s(x.maNguoiThue, sizeof(x.maNguoiThue));
		if (!KiemTraDinhDangMaNguoiThue(x.maNguoiThue)) {
			printf(">> Ma nguoi thue khong dung dinh dang! Vui long nhap lai.\n");
		}
	} while (!KiemTraDinhDangMaNguoiThue(x.maNguoiThue));

	printf("Moi ban nhap Ngay Lap: ");
	gets_s(x.ngayLap, sizeof(x.ngayLap));
}

void NhapTTCTHoaDon(CTHoaDon& x)
{
	getchar();
	printf("Nhap so hoa don: ");
	gets_s(x.soHoaDon, sizeof(x.soHoaDon));

	printf("Nhap ten dich vu: ");
	gets_s(x.tenDichVu, sizeof(x.tenDichVu));

	printf("Nhap don gia: ");
	scanf_s("%f", &x.donGia);
	getchar();
}


//##################################
void SwapHoaDon(SNodeHoaDon* a, SNodeHoaDon* b)
{
	HoaDon temp = a->Info;
	a->Info = b->Info;
	b->Info = temp;
}
void XapXepHoaDonTheoTongTien(SListHoaDon sl2)
{
	if (isEmpty(sl2) == 1)
	{
		return;
	}
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next)
	{
		for (SNodeHoaDon* q = p->Next; q != NULL; q = q->Next)
		{
			if (p->Info.tongTien < q->Info.tongTien)
			{
				SwapHoaDon(p, q);
			}
		}
	}
}
//##################################
char* layTenNguoiThueTheoMa(SListNguoiThue sl1, char ma[])
{
	if (isEmpty(sl1) == 1)
	{
		return (char*)"";
	}
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next) {
		if (strcmp(p->Info.maNguoiThue, ma) == 0)
			return p->Info.tenNguoiThue;
	}
	return (char*)"";
}
//##################################
void SapXepHoaDonTheoTenVaMa(SListHoaDon& sl2, SListNguoiThue sl1)
{
	if (isEmpty(sl2) == 1)
	{
		return;
	}
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next) {
		for (SNodeHoaDon* q = p->Next; q != NULL; q = q->Next) {
			char* tenP = layTenNguoiThueTheoMa(sl1, p->Info.maNguoiThue);
			char* tenQ = layTenNguoiThueTheoMa(sl1, q->Info.maNguoiThue);
			int cmpTen = strcmp(tenP, tenQ);
			if (cmpTen > 0 || (cmpTen == 0 && strcmp(p->Info.maNguoiThue, q->Info.maNguoiThue) > 0)) {
				SwapHoaDon(p, q);
			}
		}
	}
}
//##################################
void TimPhongNhieuNguoiNhat(SListNguoiThue sl1)
{
	if (isEmpty(sl1)) {
		printf(">> Danh sach nguoi thue rong.\n");
		return;
	}

	char maPhong[100][20];
	int soNguoi[100];
	int dem = 0;

	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next) {
		int timThay = 0;
		for (int i = 0; i < dem; i++) {
			if (strcmp(maPhong[i], p->Info.maPhongDangThue) == 0) {
				soNguoi[i]++;
				timThay = 1;
				break;
			}
		}
		if (!timThay) {
			strcpy(maPhong[dem], p->Info.maPhongDangThue);
			soNguoi[dem] = 1;
			dem++;
		}
	}

	printf(">> Danh sach so nguoi thue cua tung phong:\n");
	for (int i = 0; i < dem; i++) {
		printf(" - Phong %s: %d nguoi\n", maPhong[i], soNguoi[i]);
	}

	int maxNguoi = 0;
	for (int i = 0; i < dem; i++) {
		if (soNguoi[i] > maxNguoi)
			maxNguoi = soNguoi[i];
	}

	int soPhongDongNhat = 0;
	for (int i = 0; i < dem; i++) {
		if (soNguoi[i] == maxNguoi)
			soPhongDongNhat++;
	}

	if (soPhongDongNhat == 1)
		printf(">> Phong co so nguoi thue cao nhat (%d nguoi): ", maxNguoi);
	else
		printf(">> Cac phong co so nguoi thue cao nhat (%d nguoi): ", maxNguoi);

	for (int i = 0; i < dem; i++) {
		if (soNguoi[i] == maxNguoi) {
			printf("%s ", maPhong[i]);
		}
	}
	printf("\n");

	printf("     %-6s | %-16s | %-16s | %-12s | %-12s\n", "MaNT", "TenNguoiThue", "CCCD", "SDT", "NgayBDThue");
	for (int i = 0; i < dem; i++) {
		if (soNguoi[i] == maxNguoi) {
			for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next) {
				if (strcmp(p->Info.maPhongDangThue, maPhong[i]) == 0) {
					printf("   - %-6s | %-16s | %-16s | %-12s | %-12s\n",
						p->Info.maNguoiThue,
						p->Info.tenNguoiThue,
						p->Info.cccd,
						p->Info.soDienThoai,
						p->Info.ngayBatDauThue);
				}
			}
		}
	}
}

//##################################
int XoaHoaDonTheoSoHD(SListHoaDon& sl2, char a[])
{
	if (isEmpty(sl2) == 1) return 0;

	SNodeHoaDon* p = sl2.Head;
	SNodeHoaDon* q = NULL;

	while ((p != NULL) && (strcmp(p->Info.soHoaDon, a) != 0)) {
		q = p;
		p = p->Next;
	}

	if (p == NULL) {
		return 0;
	}

	if (p == sl2.Head) {
		sl2.Head = p->Next;
		if (sl2.Head == NULL)
			sl2.Tail = NULL;
	}
	else {
		q->Next = p->Next;
		if (p == sl2.Tail)
			sl2.Tail = q;
	}

	delete p;
	return 1;
}
//##################################
void TimCacHoaDonTheoNgayThang(SListHoaDon sl2, char a[])
{
	if (isEmpty(sl2) == 1)
	{
		return;
	}

	int dem = 0;
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next)
	{
		if (strcmp(p->Info.ngayLap, a) == 0)
		{
			ShowSNodeHoaDon(p);
			dem = 1;
		}
	}

	if (dem == 0)
	{
		printf("Khong tim thay hoa don nao co dd/mm/yy : %s \n", a);
	}
}
//##################################
void tinhTongTienChoHoaDon(SListHoaDon& sl2, SListCTHoaDon sl3) {
	if (isEmpty(sl2) == 1 || isEmpty(sl3) == 1)
	{
		return;
	}
	SNodeHoaDon* p = sl2.Head;
	while (p != NULL) {
		p->Info.tongTien = 0;
		SNodeCTHoaDon* q = sl3.Head;
		while (q != NULL) {
			if (strcmp(q->Info.soHoaDon, p->Info.soHoaDon) == 0) {
				p->Info.tongTien += q->Info.donGia;
			}
			q = q->Next;
		}
		p = p->Next;
	}
}
//##################################
int KiemTraTonTaiNguoiThue(SListNguoiThue sl1, char ma[]) {
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next) {
		if (strcmp(p->Info.maNguoiThue, ma) == 0)
			return 1;
	}
	return 0;
}
//##################################
int KiemTraTrungNguoiThue(SListNguoiThue sl1, char maNguoiThue[]) {
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next) {
		if (strcmp(p->Info.maNguoiThue, maNguoiThue) == 0)
			return 1;
	}
	return 0;
}
//##################################
int KiemTraTrungHoaDon(SListHoaDon sl2, char soHoaDon[]) {
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next) {
		if (strcmp(p->Info.soHoaDon, soHoaDon) == 0)
			return 1;
	}
	return 0;
}

//##################################
int ChuyenNgayThanhSo(char* ngaylap)
{
	int ngay, thang, nam;
	sscanf(ngaylap, "%d/%d/%d", &ngay, &thang, &nam);
	return nam * 10000 + thang * 100 + ngay;
}
//##################################
int NamTrongKhoangNgay(char* ngayCanKiem, char* tuNgay, char* denNgay) {
	int d = ChuyenNgayThanhSo(ngayCanKiem);
	int Tu = ChuyenNgayThanhSo(tuNgay);
	int Den = ChuyenNgayThanhSo(denNgay);
	return (d >= Tu && d <= Den);
}
//##################################
float TimGiaPhongTheoMaNguoiThue(BSTNodePhong* root, SListNguoiThue sl1, char* maNguoiThue) {
	char maPhong[20] = "";
	for (SNodeNguoiThue* p = sl1.Head; p != NULL; p = p->Next) {
		if (strcmp(p->Info.maNguoiThue, maNguoiThue) == 0) {
			strcpy(maPhong, p->Info.maPhongDangThue);
			break;
		}
	}
	if (strlen(maPhong) == 0) return 0;
	BSTNodePhong* p = root;
	while (p != NULL) {
		int cmp = strcmp(maPhong, p->Info.maPhong);
		if (cmp == 0) return p->Info.giaPhong;
		else if (cmp < 0) p = p->Left;
		else p = p->Right;
	}
	return 0;
}

//##################################
void ThongKeDoanhThuTheoKhoangNgay(SListHoaDon sl2, BSTreePhong bt, SListNguoiThue sl1, char tuNgay[], char denNgay[]) {
	float TongTienPhong = 0;
	float TongDichVu = 0;
	float tongDoanhThu = 0;
	int dem = 0;
	TieuDeHoaDon();
	for (SNodeHoaDon* p = sl2.Head; p != NULL; p = p->Next) {
		if (NamTrongKhoangNgay(p->Info.ngayLap, tuNgay, denNgay)) {
			float giaPhong = TimGiaPhongTheoMaNguoiThue(bt.Root, sl1, p->Info.maNguoiThue);
			tongDoanhThu += p->Info.tongTien + giaPhong;
			TongTienPhong += giaPhong;
			TongDichVu += p->Info.tongTien;
			ShowSNodeHoaDon(p);
			dem++;
		}
	}
	if (dem == 0) {
		printf(">> Khong co hoa don nao trong khoang %s -> %s.\n", tuNgay, denNgay);
	}
	else {
		printf("\n>> Co %d hoa don trong khoang %s -> %s\n", dem, tuNgay, denNgay);
		printf(">> Tong tien phong:     %.2f\n", TongTienPhong);
		printf(">> Tong tien dich vu:   %.2f\n", TongDichVu);
		printf(">> Tong doanh thu:      %.2f\n", tongDoanhThu);
	}
}

//##################################
void menu() {
	printf("\n");
	printf("====================================================================\n");
	printf("           CHUONG TRINH QUAN LY THUE PHONG TRO (BST + DSLK)        |\n");
	printf("====================================================================\n");
	printf("| STT | CHUC NANG                                                  |\n");
	printf("|=====|============================================================|\n");
	printf("|  1  | Doc du lieu tu file (Nguoi thue, Phong, Hoa don, CT HD)    |\n");
	printf("|  2  | Ghi du lieu vao file sau khi phat sinh                     |\n");
	printf("|  3  | Them Phong moi (neu chua co), luu vao file                 |\n");
	printf("|  4  | Them Hoa don + CTHD + thong tin nguoi thue moi (neu co)    |\n");
	printf("|  5  | Hien thi hoa don giam dan theo Tong tien                   |\n");
	printf("|  6  | Sap xep hoa don theo Ten nguoi thue, neu trung thi theo Ma |\n");
	printf("|  7  | Tim Phong co nhieu nguoi thue nhat                         |\n");
	printf("|  8  | Xoa Hoa don theo So hoa don                                |\n");
	printf("|  9  | Tim Hoa don theo Ngay/Thang/Nam                            |\n");
	printf("| 10  | Thong ke doanh thu theo khoang ngay                        |\n");
	printf("|  0  | Thoat chuong trinh                                         |\n");
	printf("====================================================================\n");
	printf(">> Moi ban chon chuc nang (0 - 10): ");
}

//##################################
void progress()
{
	SListNguoiThue sl1;
	SListHoaDon sl2;
	SListCTHoaDon sl3;
	BSTreePhong bt;

	initSListNguoiThue(sl1);
	initSListHoaDon(sl2);
	initSListCTHoaDon(sl3);
	initTree(bt);

	char fileNguoiThue[] = "NguoiThue.txt";
	char filePhong[] = "Phong.txt";
	char fileHoaDon[] = "HoaDon.txt";
	char fileCTHoaDon[] = "CTHoaDon.txt";

	char a[20];
	int choice;
	do {
		menu();
		scanf_s("%d", &choice);
		switch (choice) {
		case 1:
			docNguoiThueTuFile(sl1, fileNguoiThue);
			docPhongTuFile(bt, filePhong);
			docHoaDonTuFile(sl2, fileHoaDon);
			docCTHoaDonTuFile(sl3, fileCTHoaDon);
			printf(">> Doc du lieu tu file thanh cong!\n");
			break;

		case 2:
			SaveNguoiThueVaoFile(sl1, fileNguoiThue);
			SavePhongVaoFile(bt, filePhong);
			SaveHoaDonVaoFile(sl2, fileHoaDon);
			SaveCTHoaDonVaoFile(sl3, fileCTHoaDon);
			printf(">> Da luu toan bo du lieu vao file thanh cong!\n");
			break;

		case 3: {
			PhongTro pt;
			NhapTTPhong(pt);
			BSTNodePhong* p = createPhong(pt);
			if (insertPhong(bt.Root, p)) {
				SavePhongVaoFile(bt, filePhong);
				printf(">> Da them va luu phong moi vao file Phong.txt\n");
			}
			else {
				printf(">> Khong them duoc phong do trung ma.\n");
			}
			break;
		}

		case 4: {
			HoaDon hd;
			CTHoaDon cthd; 
			char chon;
			printf("MOI NHAP THONG TIN CHO HOA DON MOI: \n");
			NhapTTHoaDon(hd);

			if (KiemTraTrungHoaDon(sl2, hd.soHoaDon)) {
				printf(">> Loi: So hoa don '%s' da ton tai. Khong the them!\n", hd.soHoaDon);
				break;
			}
			if (KiemTraTrungNguoiThue(sl1, hd.maNguoiThue) == 0) {
				printf(">> Khach hang moi! Moi nhap thong tin nguoi thue:\n");
				NguoiThue nt;
				NhapTTNguoiThue(nt, bt);

				if (KiemTraTrungNguoiThue(sl1, nt.maNguoiThue)) {
					printf(">> Loi: Ma nguoi thue '%s' da ton tai. Khong the them!\n", nt.maNguoiThue);
					break;
				}

				SNodeNguoiThue* p = createSNode1(nt);
				insertNguoiThue(sl1, p);
			}
			SNodeHoaDon* p1 = createSNode2(hd);
			insertHoaDon(sl2, p1);
			do
			{
				printf("MOI NHAP THONG TIN CHI TIET HOA DON: \n");
				NhapTTCTHoaDon(cthd);
				SNodeCTHoaDon* p = createSNode3(cthd);
				insertCTHoaDon(sl3, p);
				printf("Ban co muon nhap them thong tin chi tiet hoa don khong (C/K): ");
				scanf(" %c", &chon);
			} while (chon == 'C' || chon == 'c');
			tinhTongTienChoHoaDon(sl2, sl3);
			SaveNguoiThueVaoFile(sl1, fileNguoiThue);
			SaveHoaDonVaoFile(sl2, fileHoaDon);
			SaveCTHoaDonVaoFile(sl3, fileCTHoaDon);
			printf(">> Da them va luu hoa don + chi tiet hoa don va nguoi thue moi vao File\n");
			break;
		}

		case 5: {
			tinhTongTienChoHoaDon(sl2, sl3);
			XapXepHoaDonTheoTongTien(sl2);
			printf(">> Danh sach hoa don sau khi sap xep giam dan theo tong tien:\n");
			XuatDanhSachHoaDon(sl2);
			break;
		}
		case 6: {
			tinhTongTienChoHoaDon(sl2, sl3);
			SapXepHoaDonTheoTenVaMa(sl2, sl1);
			printf(">> Danh sach hoa don sau khi sap xep theo ten nguoi thue (va ma):\n");
			XuatDanhSachHoaDon(sl2);
			break;
		}
		case 7:
			TimPhongNhieuNguoiNhat(sl1);
			break;
		case 8:
		{
			printf("Moi ban nhao so HD can xoa: ");
			scanf(" %s", &a);
			if (XoaHoaDonTheoSoHD(sl2, a) == 1)
			{
				printf(">> Da xoa so HD %s THANH CONG \n", a);
				XuatDanhSachHoaDon(sl2);
			}
			else
			{
				printf(">> XOA KHONG THANH CONG \n");
			}
			break;
		}
		case 9:
		{
			printf("Moi nhap dd/mm/yy de tim cac hoa don ");
			scanf(" %s", &a);
			TimCacHoaDonTheoNgayThang(sl2, a);
			break;
		}
		case 10:
		{
			tinhTongTienChoHoaDon(sl2, sl3);
			char tuNgay[20], denNgay[20];
			getchar();
			printf("Nhap ngay bat dau (dd/mm/yyyy): ");
			gets_s(tuNgay, sizeof(tuNgay));
			printf("Nhap ngay ket thuc (dd/mm/yyyy): ");
			gets_s(denNgay, sizeof(denNgay));

			ThongKeDoanhThuTheoKhoangNgay(sl2, bt, sl1, tuNgay, denNgay);
			break;
		}
		case 0:
			printf("Dang thoat chuong trinh...\n");
			break;
		default:
			printf(">> Lua chon khong hop le. Vui long chon lai.\n");
		}
	} while (choice != 0);
}
int main() {
	progress();
	return 0;
}