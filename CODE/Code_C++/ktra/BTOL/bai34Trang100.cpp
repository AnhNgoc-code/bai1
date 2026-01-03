#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <sstream> // Thêm để dùng stringstream

using namespace std;

const int MAX_VALUES_PER_NODE = 30;

struct Node {
    vector<int> values;
    vector<Node*> children;

    Node() {}
};

class MTree {
public:
    Node* root;

    MTree() : root(nullptr) {}

    void displayMenu() {
        cout << "\nMenu chuong trinh:" << endl;
        cout << "1. Tao cay tu mang" << endl;
        cout << "2. Duyet cay" << endl;
        cout << "3. Them phan so" << endl;
        cout << "4. Tim kiem phan so" << endl;
        cout << "5. Xuat nut chua gia tri lon nhat" << endl;
        cout << "6. Xuat nut chua nhieu gia tri nhat" << endl;
        cout << "7. Dem nut chua toan so nguyen to" << endl;
        cout << "8. Tinh tong gia tri cac nut" << endl;
        cout << "9. Liet ke phan so co tu so nho hon mau so (gia dinh la so nguyen)" << endl;
        cout << "10. Dem so phan so co tu so la so chan (gia dinh la so nguyen)" << endl;
        cout << "11. Liet ke phan so co tu so va mau so dong thoi la so hoan thien (gia dinh la so nguyen)" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
    }

    void createTree(const vector<int>& arr) {
        root = new Node();
        for (int val : arr) {
            insertValue(root, val);
        }
    }

    void insertValue(Node* node, int value) {
        if (node->values.size() < MAX_VALUES_PER_NODE) {
            node->values.push_back(value);
            sort(node->values.begin(), node->values.end());
        } else {
            if (node->children.empty() || node->children.back()->values.size() == MAX_VALUES_PER_NODE) {
                node->children.push_back(new Node());
            }
            insertValue(node->children.back(), value);
        }
    }

    void traverseTree() {
        if (!root) {
            cout << "Cay rong." << endl;
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << "Nut: [";
            for (size_t i = 0; i < current->values.size(); ++i) {
                cout << current->values[i] << (i == current->values.size() - 1 ? "" : ", ");
            }
            cout << "]" << endl;
            for (Node* child : current->children) {
                q.push(child);
            }
        }
    }

    void addValue(int value) {
        if (!root) root = new Node();
        insertValue(root, value);
    }

    bool search(int value) {
        return searchNode(root, value);
    }

    bool searchNode(Node* node, int value) {
        if (!node) return false;
        if (binary_search(node->values.begin(), node->values.end(), value)) return true;
        for (Node* child : node->children)
            if (searchNode(child, value)) return true;
        return false;
    }

    void findNodesWithMaxValue() {
        if (!root) return;
        int maxValue = findMaxValue(root);
        cout << "Cac nut chua gia tri lon nhat (" << maxValue << "):" << endl;
        printNodesWithValue(root, maxValue);
        cout << endl;
    }

    int findMaxValue(Node* node) {
        if (!node) return -1e9;
        int maxVal = *max_element(node->values.begin(), node->values.end());
        for (Node* child : node->children)
            maxVal = max(maxVal, findMaxValue(child));
        return maxVal;
    }

    void printNodesWithValue(Node* node, int value) {
        if (!node) return;
        if (find(node->values.begin(), node->values.end(), value) != node->values.end()) {
            cout << "[";
            for (size_t i = 0; i < node->values.size(); ++i) {
                cout << node->values[i] << (i == node->values.size() - 1 ? "" : ", ");
            }
            cout << "]" << endl;
        }
        for (Node* child : node->children)
            printNodesWithValue(child, value);
    }

    void findNodesWithMostValues() {
        if (!root) return;
        int maxCount = findMaxValuesCount(root);
        cout << "Cac nut chua nhieu gia tri nhat (" << maxCount << " gia tri):" << endl;
        printNodesWithCount(root, maxCount);
        cout << endl;
    }

    int findMaxValuesCount(Node* node) {
        if (!node) return 0;
        int maxCount = node->values.size();
        for (Node* child : node->children)
            maxCount = max(maxCount, findMaxValuesCount(child));
        return maxCount;
    }

    void printNodesWithCount(Node* node, int count) {
        if (!node) return;
        if (node->values.size() == count) {
            cout << "[";
            for (size_t i = 0; i < node->values.size(); ++i) {
                cout << node->values[i] << (i == node->values.size() - 1 ? "" : ", ");
            }
            cout << "]" << endl;
        }
        for (Node* child : node->children)
            printNodesWithCount(child, count);
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) return false;
        return true;
    }

    bool areAllPrime(const vector<int>& values) {
        if (values.empty()) return false;
        for (int val : values)
            if (!isPrime(val)) return false;
        return true;
    }

    int countNodesWithAllPrimes() {
        return countPrimeNodes(root);
    }

    int countPrimeNodes(Node* node) {
        if (!node) return 0;
        int count = areAllPrime(node->values) ? 1 : 0;
        for (Node* child : node->children)
            count += countPrimeNodes(child);
        return count;
    }

    long long sumOfAllNodes() {
        return sumNodes(root);
    }

    long long sumNodes(Node* node) {
        if (!node) return 0;
        long long sum = 0;
        for (int val : node->values)
            sum += val;
        for (Node* child : node->children)
            sum += sumNodes(child);
        return sum;
    }

    void listFractionsWithNumeratorSmallerThanDenominator() {
        cout << "Cac phan so co tu so nho hon mau so (mau = 2):" << endl;
        printFractionsWithNumeratorSmallerThanDenominator(root);
        cout << endl;
    }

    void printFractionsWithNumeratorSmallerThanDenominator(Node* node) {
        if (!node) return;
        for (int val : node->values)
            if (val < 2) cout << val << "/2 ";
        for (Node* child : node->children)
            printFractionsWithNumeratorSmallerThanDenominator(child);
    }

    int countFractionsWithEvenNumerator() {
        return countEvenNumerators(root);
    }

    int countEvenNumerators(Node* node) {
        if (!node) return 0;
        int count = 0;
        for (int val : node->values)
            if (val % 2 == 0) count++;
        for (Node* child : node->children)
            count += countEvenNumerators(child);
        return count;
    }

    bool isPerfectNumber(int n) {
        if (n <= 1) return false;
        int sum = 1;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                sum += i;
                if (i * i != n) sum += n / i;
            }
        }
        return sum == n;
    }

    void listFractionsWithPerfectNumeratorAndDenominator() {
        cout << "Cac phan so co tu va mau la so hoan thien (mau = 6):" << endl;
        printPerfectFractions(root);
        cout << endl;
    }

    void printPerfectFractions(Node* node) {
        if (!node) return;
        for (int val : node->values)
            if (isPerfectNumber(val) && isPerfectNumber(6))
                cout << val << "/6 ";
        for (Node* child : node->children)
            printPerfectFractions(child);
    }

    ~MTree() {
        destroyTree(root);
    }

private:
    void destroyTree(Node* node) {
        if (!node) return;
        for (Node* child : node->children)
            destroyTree(child);
        delete node;
    }
};

int main() {
    MTree mTree;
    int choice;
    vector<int> initialArray = {10, 5, 20, 3, 15, 25, 1, 8, 30, 12, 18, 22, 7, 11, 28, 4, 16, 21, 9, 27, 2, 14, 19, 6, 23, 29, 26, 13, 17, 24, 31, 32, 33};
    mTree.createTree(initialArray);

    do {
        mTree.displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Nhap cac phan so (so nguyen): ";
                string input;
                getline(cin, input);
                stringstream ss(input);
                vector<int> newArray;
                int num;
                while (ss >> num) newArray.push_back(num);
                mTree.createTree(newArray);
                break;
            }
            case 2:
                mTree.traverseTree(); break;
            case 3: {
                int val;
                cout << "Nhap gia tri: ";
                cin >> val;
                mTree.addValue(val); break;
            }
            case 4: {
                int val;
                cout << "Nhap gia tri can tim: ";
                cin >> val;
                cout << (mTree.search(val) ? "Tim thay.\n" : "Khong tim thay.\n");
                break;
            }
            case 5: mTree.findNodesWithMaxValue(); break;
            case 6: mTree.findNodesWithMostValues(); break;
            case 7: cout << "So nut toan so nguyen to: " << mTree.countNodesWithAllPrimes() << endl; break;
            case 8: cout << "Tong gia tri: " << mTree.sumOfAllNodes() << endl; break;
            case 9: mTree.listFractionsWithNumeratorSmallerThanDenominator(); break;
            case 10: cout << "So phan so tu chan: " << mTree.countFractionsWithEvenNumerator() << endl; break;
            case 11: mTree.listFractionsWithPerfectNumeratorAndDenominator(); break;
            case 0: cout << "Thoat chuong trinh.\n"; break;
            default: cout << "Chon sai, vui long thu lai.\n"; break;
        }
    } while (choice != 0);

    return 0;
}
