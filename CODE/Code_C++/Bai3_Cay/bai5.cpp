#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_ENTRIES_PER_NODE = 30;

struct DictionaryEntry {
    string word;
    string mean;

    DictionaryEntry(string w, string m) : word(w), mean(m) {}

    bool operator<(const DictionaryEntry& other) const {
        return word < other.word;
    }
};

struct DictionaryNode {
    vector<DictionaryEntry> entries;
    vector<DictionaryNode*> children;

    DictionaryNode() {}
};

class DictionaryMTree {
public:
    DictionaryNode* root;

    DictionaryMTree() : root(nullptr) {}

    // a. Xây dựng chương trình dạng menu
    void displayMenu() {
        cout << "\nMenu Tu Dien Anh-Viet:" << endl;
        cout << "1. Tao cay tu file" << endl;
        cout << "2. Duyet tu dien" << endl;
        cout << "3. Tra cuu nghia" << endl;
        cout << "4. Them tu" << endl;
        cout << "5. Xoa tu" << endl;
        cout << "6. Sua nghia" << endl;
        cout << "7. So luong tu" << endl;
        cout << "8. Xoa toan bo tu dien" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
    }

    // b. Tao cay tu 1 file text luu tu dien Anh-Viet
    void createTreeFromFile(const string& filePath) {
        root = new DictionaryNode();
        ifstream file(filePath);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string segment;
                vector<string> parts;
                while (getline(ss, segment, ':')) {
                    parts.push_back(segment);
                }
                if (parts.size() == 2) {
                    insertEntry(root, DictionaryEntry(trim(parts[0]), trim(parts[1])));
                } else {
                    cerr << "Dong khong hop le trong file: " << line << endl;
                }
            }
            file.close();
        } else {
            cerr << "Khong the mo file: " << filePath << endl;
        }
    }

    // Hàm hỗ trợ loại bỏ khoảng trắng đầu và cuối chuỗi
    string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        if (string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // Hàm hỗ trợ chèn một mục từ điển (đơn giản hóa, không đảm bảo cân bằng M-Phân nghiêm ngặt)
    void insertEntry(DictionaryNode* node, const DictionaryEntry& entry) {
        if (!node) {
            root = new DictionaryNode();
            root->entries.push_back(entry);
            sort(root->entries.begin(), root->entries.end());
            return;
        }

        if (node->entries.size() < MAX_ENTRIES_PER_NODE) {
            node->entries.push_back(entry);
            sort(node->entries.begin(), node->entries.end());
        } else {
            // Chia nút (đơn giản hóa) - tạo nút con mới và thêm vào
            if (node->children.empty() || node->children.back()->entries.size() == MAX_ENTRIES_PER_NODE) {
                node->children.push_back(new DictionaryNode());
            }
            insertEntry(node->children.back(), entry);
        }
    }

    // c. Duyệt cây để xem nội dung
    void traverseTree() {
        if (!root) {
            cout << "Tu dien rong." << endl;
            return;
        }
        queue<DictionaryNode*> q;
        q.push(root);
        while (!q.empty()) {
            DictionaryNode* current = q.front();
            q.pop();
            cout << "Nut: [";
            for (size_t i = 0; i < current->entries.size(); ++i) {
                cout << "(" << current->entries[i].word << ": " << current->entries[i].mean << ")";
                if (i < current->entries.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "] ";
            for (DictionaryNode* child : current->children) {
                if (child) {
                    q.push(child);
                }
            }
        }
        cout << endl;
    }

    // d. Tra cuu nghia cua 1 tu bat ky
    string searchWord(const string& word) {
        return searchInNode(root, word);
    }

    string searchInNode(DictionaryNode* node, const string& word) {
        if (!node) {
            return "Khong tim thay tu nay.";
        }
        for (const auto& entry : node->entries) {
            if (entry.word == word) {
                return entry.mean;
            }
        }
        for (DictionaryNode* child : node->children) {
            string result = searchInNode(child, word);
            if (result != "Khong tim thay tu nay.") {
                return result;
            }
        }
        return "Khong tim thay tu nay.";
    }

    // e. Them mot tu bat ky vao cay, duyet lai cay de xem ket qua
    void addWord(const string& word, const string& mean) {
        insertEntry(root, DictionaryEntry(trim(word), trim(mean)));
        cout << "Da them tu: " << word << " - " << mean << endl;
        traverseTree();
    }

    // f. Xoa mot tu bat ky khoi cay, duyet lai cay de xem ket qua
    void deleteWord(const string& word) {
        if (deleteEntry(root, word)) {
            cout << "Da xoa tu: " << word << endl;
        } else {
            cout << "Khong tim thay tu: " << word << " de xoa." << endl;
        }
        traverseTree();
    }

    bool deleteEntry(DictionaryNode* node, const string& word) {
        if (!node) {
            return false;
        }
        for (auto it = node->entries.begin(); it != node->entries.end(); ++it) {
            if (it->word == word) {
                node->entries.erase(it);
                return true;
            }
        }
        for (DictionaryNode* child : node->children) {
            if (deleteEntry(child, word)) {
                return true;
            }
        }
        return false;
    }

    // g. Bo sung hay chinh sua nghia cua 1 tu bat ky
    void editMean(const string& word, const string& newMean) {
        if (editMeanInNode(root, word, newMean)) {
            cout << "Da chinh sua nghia cua tu: " << word << " thanh: " << newMean << endl;
        } else {
            cout << "Khong tim thay tu: " << word << " de chinh sua." << endl;
        }
    }

    bool editMeanInNode(DictionaryNode* node, const string& word, const string& newMean) {
        if (!node) {
            return false;
        }
        for (auto& entry : node->entries) {
            if (entry.word == word) {
                entry.mean = newMean;
                return true;
            }
        }
        for (DictionaryNode* child : node->children) {
            if (editMeanInNode(child, word, newMean)) {
                return true;
            }
        }
        return false;
    }

    // h. Cho biet so luong tu cua tu dien
    int countWords() {
        return countWordsInNode(root);
    }

    int countWordsInNode(DictionaryNode* node) {
        if (!node) {
            return 0;
        }
        int count = node->entries.size();
        for (DictionaryNode* child : node->children) {
            count += countWordsInNode(child);
        }
        return count;
    }

    // i. Xoa toan bo cay
    void clearTree() {
        destroyTree(root);
        root = nullptr;
        cout << "Da xoa toan bo tu dien." << endl;
    }

    ~DictionaryMTree() {
        destroyTree(root);
    }

private:
    void destroyTree(DictionaryNode* node) {
        if (node) {
            for (DictionaryNode* child : node->children) {
                destroyTree(child);
            }
            delete node;
        }
    }
};

int main() {
    DictionaryMTree dictionary;
    int choice;
    string word, mean;
    string filePath = "dictionary.txt"; // Thay doi duong dan neu can

    do {
        dictionary.displayMenu();
        cin >> choice;
        cin.ignore(); // Đọc bỏ ký tự newline

        switch (choice) {
            case 1:
                cout << "Nhap duong dan file tu dien: ";
                getline(cin, filePath);
                dictionary.createTreeFromFile(filePath);
                break;
            case 2:
                cout << "Noi dung tu dien:" << endl;
                dictionary.traverseTree();
                break;
            case 3:
                cout << "Nhap tu can tra cuu: ";
                getline(cin, word);
                cout << "Nghia cua '" << word << "': " << dictionary.searchWord(word) << endl;
                break;
            case 4:
                cout << "Nhap tu muon them: ";
                getline(cin, word);
                cout << "Nhap nghia cua tu '" << word << "': ";
                getline(cin, mean);
                dictionary.addWord(word, mean);
                break;
            case 5:
                cout << "Nhap tu muon xoa: ";
                getline(cin, word);
                dictionary.deleteWord(word);
                break;
            case 6:
                cout << "Nhap tu muon sua nghia: ";
                getline(cin, word);
                cout << "Nhap nghia moi cho tu '" << word << "': ";
                getline(cin, mean);
                dictionary.editMean(word, mean);
                break;
            case 7:
                cout << "So luong tu trong tu dien: " << dictionary.countWords() << endl;
                break;
            case 8:
                dictionary.clearTree();
                break;
            case 0:
                cout << "Thoat chuong trinh tu dien." << endl;
                break;
            default:
                cout << "Chuc nang khong hop le. Vui long chon lai." << endl;
        }
    } while (choice != 0);

    return 0;
}