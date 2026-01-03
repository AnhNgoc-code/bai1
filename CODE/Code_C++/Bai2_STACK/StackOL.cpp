#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef union {
    int iValue;
    char cValue;
    void *pValue;
} ItemType;

struct StackNode {
    ItemType Info;
    StackNode *Next;
};

struct Stack {
    StackNode *Top;
};

void initStack(Stack &st) {
    st.Top = NULL;
}

int isEmpty(Stack st) {
    return (st.Top == NULL);
}

StackNode* createStackNode(ItemType x) {
    StackNode *p = new StackNode;
    if (p == NULL) {
        printf("Không đủ bộ nhớ!\n");
        return NULL;
    }
    p->Info = x;
    p->Next = NULL;
    return p;
}

void push(Stack &st, StackNode *p) {
    if (p == NULL) return;
    p->Next = st.Top;
    st.Top = p;
}

int pop(Stack &st, ItemType &x) {
    if (isEmpty(st)) return 0;
    StackNode *p = st.Top;
    x = p->Info;
    st.Top = st.Top->Next;
    delete p;
    return 1;
}

int getTop(Stack st, ItemType &x) {
    if (isEmpty(st)) return 0;
    x = st.Top->Info;
    return 1;
}

// ==================== Các hàm cho bài tập ====================

// Bài 2: Chuyển đổi thập phân sang hệ cơ số bất kỳ
void decimalToAnyBase(int n, int base) {
    if (n < 0 || base < 2 || base > 16) {
        printf("Đầu vào không hợp lệ!\n");
        return;
    }

    Stack st;
    initStack(st);
    ItemType item;

    while (n > 0) {
        int remainder = n % base;
        item.iValue = remainder;
        push(st, createStackNode(item));
        n /= base;
    }

    printf("Kết quả: ");
    while (!isEmpty(st)) {
        pop(st, item);
        if (item.iValue < 10)
            printf("%d", item.iValue);
        else
            printf("%c", 'A' + (item.iValue - 10));
    }
    printf("\n");
}

// Bài 3: Tính giai thừa không đệ quy
long long factorialNonRecursive(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;

    Stack st;
    initStack(st);
    ItemType item;

    for (int i = 1; i <= n; i++) {
        item.iValue = i;
        push(st, createStackNode(item));
    }

    long long result = 1;
    while (!isEmpty(st)) {
        pop(st, item);
        result *= item.iValue;
    }

    return result;
}

// Bài 4: Đảo ngược chuỗi
void reverseString(char *str) {
    Stack st;
    initStack(st);
    ItemType item;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        item.cValue = str[i];
        push(st, createStackNode(item));
    }

    for (int i = 0; i < len; i++) {
        pop(st, item);
        str[i] = item.cValue;
    }
}

// Bài 5: Kiểm tra chuỗi ngoặc hợp lệ
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') || 
           (open == '{' && close == '}') || 
           (open == '[' && close == ']');
}

int isBalancedParentheses(const char *exp) {
    Stack st;
    initStack(st);
    ItemType item;

    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            item.cValue = exp[i];
            push(st, createStackNode(item));
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(st)) return 0;
            
            getTop(st, item);
            if (!isMatchingPair(item.cValue, exp[i])) return 0;
            
            pop(st, item);
        }
    }

    return isEmpty(st);
}

// Bài 6 và 7: Chuyển trung tố sang hậu tố và tính toán
// (Cần thêm các hàm phụ trợ)

// Bài 8: QuickSort không đệ quy
typedef struct {
    int low;
    int high;
} QSRange;

void quickSortNonRecursive(int arr[], int n) {
    Stack st;
    initStack(st);
    ItemType item;
    
    QSRange initial = {0, n-1};
    item.pValue = malloc(sizeof(QSRange));
    *(QSRange*)item.pValue = initial;
    push(st, createStackNode(item));

    while (!isEmpty(st)) {
        pop(st, item);
        QSRange current = *(QSRange*)item.pValue;
        free(item.pValue);

        if (current.low < current.high) {
            int pivot = arr[current.high];
            int i = current.low - 1;

            for (int j = current.low; j < current.high; j++) {
                if (arr[j] < pivot) {
                    i++;
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
            int temp = arr[i+1];
            arr[i+1] = arr[current.high];
            arr[current.high] = temp;
            int pi = i + 1;

            // Push các range mới
            QSRange left = {current.low, pi-1};
            item.pValue = malloc(sizeof(QSRange));
            *(QSRange*)item.pValue = left;
            push(st, createStackNode(item));

            QSRange right = {pi+1, current.high};
            item.pValue = malloc(sizeof(QSRange));
            *(QSRange*)item.pValue = right;
            push(st, createStackNode(item));
        }
    }
}

// Bài 9: Tính giá trị biểu thức hậu tố
int evaluatePostfix(const char *exp) {
    Stack st;
    initStack(st);
    ItemType item;

    for (int i = 0; exp[i]; i++) {
        if (isdigit(exp[i])) {
            item.iValue = exp[i] - '0';
            push(st, createStackNode(item));
        } else {
            int val1, val2;
            pop(st, item); val2 = item.iValue;
            pop(st, item); val1 = item.iValue;
            
            switch (exp[i]) {
                case '+': item.iValue = val1 + val2; break;
                case '-': item.iValue = val1 - val2; break;
                case '*': item.iValue = val1 * val2; break;
                case '/': item.iValue = val1 / val2; break;
                case '^': item.iValue = (int)pow(val1, val2); break;
            }
            push(st, createStackNode(item));
        }
    }
    
    pop(st, item);
    return item.iValue;
}

// Bài 10: Kiểm tra dấu ngoặc thừa
int hasRedundantParentheses(const char *exp) {
    Stack st;
    initStack(st);
    ItemType item;

    for (int i = 0; exp[i]; i++) {
        if (exp[i] == ')') {
            item.cValue = exp[i];
            getTop(st, item);
            
            if (item.cValue == '(') return 1;
            
            while (!isEmpty(st) && item.cValue != '(') 
                pop(st, item);
                
            pop(st, item); // Remove '('
        } else {
            item.cValue = exp[i];
            push(st, createStackNode(item));
        }
    }
    return 0;
}

// Bài 11: Undo/Redo
typedef struct {
    char type[20];
    char data[100];
} Action;

void demoUndoRedo() {
    Stack undoStack, redoStack;
    initStack(undoStack);
    initStack(redoStack);
    ItemType item;

    // Giả lập các hành động
    Action act1 = {"type", "Hello"};
    Action act2 = {"delete", "o"};
    
    item.pValue = malloc(sizeof(Action));
    *(Action*)item.pValue = act1;
    push(undoStack, createStackNode(item));

    item.pValue = malloc(sizeof(Action));
    *(Action*)item.pValue = act2;
    push(undoStack, createStackNode(item));

    // Undo hành động cuối
    pop(undoStack, item);
    Action lastAction = *(Action*)item.pValue;
    printf("Undo: %s %s\n", lastAction.type, lastAction.data);
    
    // Đẩy vào redo stack
    push(redoStack, createStackNode(item));
}

int main() {
    // Test các hàm
    decimalToAnyBase(255, 16); // FF
    printf("5! = %lld\n", factorialNonRecursive(5));
    
    char str[] = "Hello";
    reverseString(str);
    printf("Reversed: %s\n", str);
    
    printf("Balanced? %d\n", isBalancedParentheses("({[]})"));
    
    int arr[] = {5, 2, 8, 1, 6};
    quickSortNonRecursive(arr, 5);
    printf("Sorted array: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    
    printf("\nPostfix eval: %d\n", evaluatePostfix("23+5*"));
    printf("Has redundant? %d\n", hasRedundantParentheses("((a+b))"));
    
    demoUndoRedo();
    
    return 0;
}