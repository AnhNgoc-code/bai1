#include <iostream>
#include <fstream>
using namespace std;

const int M = 4; // Số nhánh tối đa trong 1 nút

struct MNode {
    int key[M - 1];        // Mỗi nút chứa tối đa M-1 giá trị
    MNode* child[M];       // Con trỏ đến các cây con
    int size;              // Số lượng giá trị hiện tại trong nút

    MNode() {
        size = 0;
        for (int i = 0; i < M; i++) child[i] = nullptr;
    }
};

// ========================== a. In menu ==========================
void menu() {
    cout << "\n===== CHUONG TRINH QUAN LY SO NGUYEN BANG CAY M-PHAN =====";
    cout << "\n1. Tao cay tu mang (nhap tay)";
    cout << "\n2. Tao cay tu file";
    cout << "\n3. Them mot so vao cay";
    cout << "\n4. Xoa mot gia tri bat ky";
    cout << "\n5. Tim kiem gia tri";
    cout << "\n6. Xuat nut chua it gia tri nhat";
    cout << "\n7. Xuat nut chua nhieu gia tri nhat";
    cout << "\n8. Dem so nut toan gia tri la so nguyen to";
    cout << "\n9. Tinh tong gia tri cac nut";
    cout << "\n0. Thoat\n";
}

// ========================== d. Chèn ==========================
void insertNode(MNode*& root, int x) {
    if (!root) {
        root = new MNode();
        root->key[0] = x;
        root->size = 1;
        return;
    }

    int i = 0;
    while (i < root->size && x > root->key[i]) i++;
    if (i < root->size && x == root->key[i]) return;

    if (root->size < M - 1) {
        for (int j = root->size; j > i; j--)
            root->key[j] = root->key[j - 1];
        root->key[i] = x;
        root->size++;
    } else {
        insertNode(root->child[i], x);
    }
}

// ========================== b. Tạo cây từ mảng ==========================
void taoCayTuMang(MNode*& root) {
    int arr[50] = {
        15, 2, 6, 9, 33, 24, 50, 18, 7, 8,
        10, 20, 1, 4, 3, 30, 45, 19, 23, 11,
        5, 27, 31, 12, 14, 16, 17, 21, 22, 25,
        26, 28, 29, 32, 34, 35, 36, 37, 38, 39,
        40, 41, 42, 43, 44, 46, 47, 48, 49, 13
    };

    for (int i = 0; i < 50; i++) {
        insertNode(root, arr[i]);
    }

    cout << "Da tao cay tu mang co san.\n";
}

// ========================== c. Tạo cây từ file ==========================
void taoCayTuFile(MNode*& root, const string& filename) {
    ifstream file(filename);
    int x;
    while (file >> x) {
        insertNode(root, x);
    }
    file.close();
    cout << "Da tao cay tu file.\n";
}

// ========================== e. Xóa ==========================
void deleteNode(MNode*& root, int x) {
    if (!root) return;

    int i = 0;
    while (i < root->size && x > root->key[i]) i++;

    if (i < root->size && root->key[i] == x) {
        if (root->child[i + 1]) {
            MNode* temp = root->child[i + 1];
            while (temp->child[0]) temp = temp->child[0];
            root->key[i] = temp->key[0];
            deleteNode(root->child[i + 1], temp->key[0]);
        } else {
            for (int j = i; j < root->size - 1; j++)
                root->key[j] = root->key[j + 1];
            root->size--;
        }
    } else {
        deleteNode(root->child[i], x);
    }

    if (root->size == 0) {
        bool hasChild = false;
        for (int j = 0; j < M; j++)
            if (root->child[j]) {
                hasChild = true;
                break;
            }

        if (!hasChild) {
            delete root;
            root = nullptr;
        }
    }
}

// ========================== f. Tìm kiếm ==========================
bool timKiem(MNode* root, int x) {
    if (!root) return false;
    for (int i = 0; i < root->size; i++) {
        if (root->key[i] == x)
            return true;
        if (x < root->key[i])
            return timKiem(root->child[i], x);
    }
    return timKiem(root->child[root->size], x);
}

// ========================== g. In nút chứa ít giá trị nhất ==========================
void xuatNutItNhat(MNode* root, int& minVal) {
    if (!root) return;
    if (root->size < minVal) minVal = root->size;
    for (int i = 0; i <= root->size; i++) {
        xuatNutItNhat(root->child[i], minVal);
    }
}

void inNutItNhat(MNode* root, int minVal) {
    if (!root) return;
    if (root->size == minVal) {
        cout << "[ ";
        for (int i = 0; i < root->size; i++)
            cout << root->key[i] << " ";
        cout << "]\n";
    }
    for (int i = 0; i <= root->size; i++) {
        inNutItNhat(root->child[i], minVal);
    }
}

// ========================== i. Đếm nút toàn số nguyên tố ==========================
bool laNguyenTo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int demNutNguyenTo(MNode* root) {
    if (!root) return 0;
    bool allPrime = true;
    for (int i = 0; i < root->size; i++)
        if (!laNguyenTo(root->key[i])) {
            allPrime = false;
            break;
        }

    int dem = allPrime ? 1 : 0;
    for (int i = 0; i <= root->size; i++)
        dem += demNutNguyenTo(root->child[i]);

    return dem;
}

// ========================== j. Tính tổng giá trị ==========================
int tongGiaTri(MNode* root) {
    if (!root) return 0;
    int tong = 0;
    for (int i = 0; i < root->size; i++)
        tong += root->key[i];
    for (int i = 0; i <= root->size; i++)
        tong += tongGiaTri(root->child[i]);
    return tong;
}

// ========================== Main ==========================
int main() {
    MNode* root = nullptr;
    int chon;

    do {
        menu();
        cout << "\nNhap lua chon: ";
        cin >> chon;

        switch (chon) {
        case 1:
            taoCayTuMang(root);
            break;
        case 2: {
            string filename;
            cout << "Nhap ten file: ";
            cin >> filename;
            taoCayTuFile(root, filename);
            break;
        }
        case 3: {
            int x;
            cout << "Nhap gia tri muon them: ";
            cin >> x;
            insertNode(root, x);
            break;
        }
        case 4: {
            int x;
            cout << "Nhap gia tri muon xoa: ";
            cin >> x;
            deleteNode(root, x);
            break;
        }
        case 5: {
            int x;
            cout << "Nhap gia tri can tim: ";
            cin >> x;
            if (timKiem(root, x))
                cout << "Tim thay.\n";
            else
                cout << "Khong tim thay.\n";
            break;
        }
        case 6: {
            int minVal = M;
            xuatNutItNhat(root, minVal);
            cout << "Cac nut chua it gia tri nhat (" << minVal << "):\n";
            inNutItNhat(root, minVal);
            break;
        }
        case 8:
            cout << "So nut toan so nguyen to: " << demNutNguyenTo(root) << endl;
            break;
        case 9:
            cout << "Tong cac gia tri trong cay: " << tongGiaTri(root) << endl;
            break;
        case 0:
            cout << "Ket thuc chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }

    } while (chon != 0);

    return 0;
}
