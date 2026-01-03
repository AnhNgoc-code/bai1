#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const string FileName = "BookList.txt";

struct Book
{
    string id;
    string name;
    string author;
    string category;
    string publisher;
    int year;
    int quantity;
};

struct BookNode
{
    Book info;
    BookNode *next;
    BookNode(struct Book data)
    {
        info = data;
        next = NULL;
    };
};

struct BookList
{
    BookNode *head;
    BookNode *tail;
    BookList()
    {
        head = tail = NULL;
    };
};

bool isEmpty(BookList blist)
{
    if(blist.head == NULL||blist.tail==NULL)
    {
        return true;
    }
    return false;
}

void showBookInfo(Book data)
{
    cout << "ID: " << data.id << endl;
    cout << "Name: " << data.name << endl;
    cout << "Author: " << data.author << endl;
    cout << "Category: " << data.category << endl;
    cout << "Released Year: " << data.year << endl;
    cout << "Quantity: " << data.quantity << endl;
    cout << "Publisher" << data.publisher << endl;
    cout << "========================" << endl;
}

void showAll(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display" << endl;
        return;
    }
    else
    {
        printf("\n%-5s |%-10s | %-20s | %-20s | %-15s | %-10s | %-15s | %-5s\n","Numb.order","ID", "Book's Name", "Author", "Publisher", "Released Year", "Category", "Quantity");
        cout<< "-----------------------------------------------------------------------------------------\n";
        BookNode *temp = blist->head;
        int numb=1;
        while (temp != NULL)
        {
            printf("\n%-5d | %-10s | %-20s | %-20s | %-15s | %-10d | %-10s | %-5d\n",
       numb,
       temp->info.id.c_str(),
       temp->info.name.c_str(),
       temp->info.author.c_str(),
       temp->info.publisher.c_str(),
       temp->info.year,
       temp->info.category.c_str(),
       temp->info.quantity);
            temp = temp->next;
            numb+=1;
        }
    }
}

bool isUniqueID(BookList blist, Book data)
{
    if (blist.head == NULL)
    {
        return true;
    }
    BookNode *temp = blist.head;
    while (temp != NULL)
    {
        if (data.id == temp->info.id)
        {
            return false;
        };
        temp = temp->next;
    }
    return true;
}

Book inputBookInfo(BookList blist)
{
    Book data;
    cout << "Thong tin sach moi\n=====" << endl;
    cout << "ID: ";
    do
    {
        cin>>data.id;
        if (!isUniqueID(blist, data))
        {
            cout << "Exsisted ID\nTry Another ID\nID: ";
        };
    } while (isUniqueID(blist, data) == false);
    cin.ignore();
    cout << "Book's Name: ";
    getline(cin, data.name);
    cout << "Author: ";
    getline(cin, data.author);
    cout << "Category: ";
    getline(cin, data.category);
    cout << "Publisher: ";
    getline(cin,data.publisher);
    cout << "Released Year: ";
    cin >> data.year;
    cout << "Quantity: ";
    cin >> data.quantity;
    cin.ignore();
    return data;
}

bool cmprBook(Book tempA, Book tempB)
{
    string catA = tempA.category;
    string catB = tempB.category;
    string idA = tempA.id;
    string idB= tempB.id;
    transform(idA.begin(), idA.end(), idA.begin(), ::tolower);
    transform(idB.begin(), idB.end(), idB.begin(), ::tolower);
    transform(catA.begin(), catA.end(), catA.begin(), ::tolower);
    transform(catB.begin(), catB.end(), catB.begin(), ::tolower);
    return (catA < catB) || (catA == catB && idA < idB);
}

void sortBook(BookList *blist)
{
    if(isEmpty(*blist)||blist->head->next==nullptr)
    {
        return;
    }
    vector<Book> books;
    for (BookNode *temp = blist->head; temp != NULL; temp = temp->next)
        books.push_back(temp->info);

    sort(books.begin(), books.end(), cmprBook);

    BookNode *temp = blist->head;
    for (auto &book : books)
    {
        temp->info = book;
        temp = temp->next;
    }
}

void saveBooktoFile(Book data)
{
    ofstream outfile(FileName, ios::app);
    if (!outfile.is_open())
    {
        cerr << "Something went Wrong";
        return;
    }
    outfile << data.id << "|"
            << data.name << "|"
            << data.author << "|"
            << data.publisher << "|"
            << data.category << "|"
            << data.year << "|"
            << data.quantity << endl;
    outfile.close();
    cout << "Save to BookList.txt Succesfully";
}

void saveAllBooktoFile(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Save";
        return;
    }
    ofstream outfile(FileName);
    if (!outfile.is_open())
    {
        cerr << "Something went Wrong";
        return;
    }
    BookNode *tempNode = blist->head;
    while (tempNode != NULL)
    {
        outfile << tempNode->info.id << "|"
                << tempNode->info.name << "|"
                << tempNode->info.author << "|"
                << tempNode->info.category << "|"
                << tempNode->info.year << "|"
                << tempNode->info.quantity << endl;
        tempNode = tempNode->next;
    }
    outfile.close();
    cout << "Save to BookList.txt Succesfully";
}

void clearList(BookList *blist)
{
    BookNode *temp = blist->head;
    while (temp != NULL)
    {
        BookNode *next = temp->next;
        delete temp;
        temp = next;
    }
    blist->head = blist->tail = NULL;
}

int addBook(BookList *blist)

{
    BookNode *temp = new BookNode(inputBookInfo(*blist));
    if (isEmpty(*blist))
    {
        blist->head = blist->tail = temp;
        saveBooktoFile(temp->info);
        return 1;
    }
    else
    {
        blist->tail->next = temp;
        blist->tail = temp;
    }
    
    sortBook(blist);
    saveAllBooktoFile(blist);
    return 1;
}

void readFile(BookList *blist)
{
    ifstream infile(FileName);
    if (!infile.is_open())
    {
        cerr << "Something went Wrong";
        return;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string temp;
        Book data;
        getline(ss, data.id, '|');
        getline(ss, data.name, '|');
        getline(ss, data.author, '|');
        getline(ss, data.publisher, '|');
        getline(ss, data.category, '|');
        getline(ss, temp, '|');
        data.year = stoi(temp);
        getline(ss, temp, '|');
        data.quantity = stoi(temp);
        showBookInfo(data);
        if (isUniqueID(*blist, data))
        {
            BookNode *newBook = new BookNode(data);
            if (isEmpty(*blist))
            {
                blist->head = blist->tail = newBook;
            }
            else
            {
                blist->tail->next = newBook;
                blist->tail = newBook;
            }
        }
    }
}

bool cmprLetter(char tempA, char tempB)
{
    return tolower(tempA) == tolower(tempB);
}

BookNode *searchbyID(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input ID to Search: ";
    string searchId;
    BookNode *tempNode = blist->head;
    cin >> searchId;
    BookNode *target = NULL;
    int bestMatch = 0;
    while (tempNode != NULL)
    {
        if (searchId == tempNode->info.id)
        {
            cout << "Matching Result\n==========\n";
            showBookInfo(tempNode->info);
            return tempNode;
        }
        int match = 0;
        int len = min(tempNode->info.id.size(), searchId.size());
        int step = 0;
        while (step < len)
        {

            if (tempNode->info.id[step] == searchId[step])
            {
                match += 1;
            }
            step++;
        }
        if (match > bestMatch)
        {
            bestMatch = match;
            target = tempNode;
        }
        tempNode = tempNode->next;
    }
    if (bestMatch == 0 && target == NULL)
    {
        cout << "No ID Matched";
        return NULL;
    }
    cout << "Best Result\n==========\n";
    showBookInfo(target->info);
    return target;
}

BookNode *searchbyName(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input Book's Name to Search: ";
    cin.ignore();
    string searchName;
    BookNode *tempNode = blist->head;
    getline(cin, searchName);
    BookNode *target = NULL;
    BookList *tempList = new BookList();
    int bestMatch = 0;
    while (tempNode != NULL)
    {
        string nameLower = tempNode->info.name;
        string searchLower = searchName;
        transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (nameLower.find(searchLower) != string::npos)
        {
            BookNode *newNode = new BookNode(tempNode->info);
            if (isEmpty(*tempList))
                tempList->head = tempList->tail = newNode;
            else
            {
                tempList->tail->next = newNode;
                tempList->tail = newNode;
            }
        }
        tempNode = tempNode->next;
    }
    if (isEmpty(*tempList))
    {
        tempNode = blist->head;
        while (tempNode != NULL)
        {
            int match = 0;
            int len = min(tempNode->info.name.size(), searchName.size());
            int step = 0;
            while (step < len)
            {
                if (cmprLetter(tempNode->info.name[step], searchName[step]))
                {
                    match += 1;
                }
                step++;
            }
            if (match > bestMatch)
            {
                bestMatch = match;
                target = tempNode;
            }
            tempNode = tempNode->next;
        }
    }
    tempNode = blist->head;
    if (target != NULL)
    {
        while (tempNode != NULL)
        {
            if (tempNode->info.name == target->info.name)
            {
                BookNode *newNode = new BookNode(tempNode->info);
                if (isEmpty(*tempList))
                    tempList->head = tempList->tail = newNode;
                else
                {
                    tempList->tail->next = newNode;
                    tempList->tail = newNode;
                }
            }
            tempNode = tempNode->next;
        }
    }
    if (isEmpty(*tempList))
    {
        cout << "No Book's Name Matched" << endl;
        delete tempList;
        return NULL;
    }
    showAll(tempList);
    target = searchbyID(tempList);
    clearList(tempList);
    delete tempList;
    return target;
}

BookNode *searchbyAuthor(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input Author to Search: ";
    cin.ignore();
    string searchAuthor;
    BookNode *tempNode = blist->head;
    getline(cin, searchAuthor);
    BookNode *target = NULL;
    BookList *tempList = new BookList();
    int bestMatch = 0;
    while (tempNode != NULL)
    {
        string authorLower = tempNode->info.author;
        string searchLower = searchAuthor;
        transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (authorLower.find(searchLower) != string::npos)
        {
            BookNode *newNode = new BookNode(tempNode->info);
            if (isEmpty(*tempList))
                tempList->head = tempList->tail = newNode;
            else
            {
                tempList->tail->next = newNode;
                tempList->tail = newNode;
            }
        }
        tempNode = tempNode->next;
    }
    if (isEmpty(*tempList))
    {
        tempNode = blist->head;
        while (tempNode != NULL)
        {
            int match = 0;
            int len = min(tempNode->info.author.size(), searchAuthor.size());
            int step = 0;
            while (step < len)
            {
                if (cmprLetter(tempNode->info.author[step], searchAuthor[step]))
                {
                    match += 1;
                }
                step++;
            }
            if (match > bestMatch)
            {
                bestMatch = match;
                target = tempNode;
            }
            tempNode = tempNode->next;
        }
    }
    tempNode = blist->head;
    if (target != NULL)
    {
        while (tempNode != NULL)
        {
            if (tempNode->info.author == target->info.author)
            {
                BookNode *newNode = new BookNode(tempNode->info);
                if (isEmpty(*tempList))
                    tempList->head = tempList->tail = newNode;
                else
                {
                    tempList->tail->next = newNode;
                    tempList->tail = newNode;
                }
            }
            tempNode = tempNode->next;
        }
    }
    if (isEmpty(*tempList))
    {
        cout << "No Author Matched" << endl;
        delete tempList;
        return NULL;
    }
    showAll(tempList);
    target = searchbyID(tempList);
    clearList(tempList);
    delete tempList;
    return target;
}

BookNode *searchbyCategory(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input Category to Search: ";
    cin.ignore();
    string searchCategory;
    BookNode *tempNode = blist->head;
    getline(cin, searchCategory);
    BookNode *target = NULL;
    BookList *tempList = new BookList();
    int bestMatch = 0;
    while (tempNode != NULL)
    {
        string CategoryLower = tempNode->info.category;
        string searchLower = searchCategory;
        transform(CategoryLower.begin(), CategoryLower.end(), CategoryLower.begin(), ::tolower);
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (CategoryLower.find(searchLower) != string::npos)
        {
            BookNode *newNode = new BookNode(tempNode->info);
            if (isEmpty(*tempList))
                tempList->head = tempList->tail = newNode;
            else
            {
                tempList->tail->next = newNode;
                tempList->tail = newNode;
            }
        }
        tempNode = tempNode->next;
    }
    if (isEmpty(*tempList))
    {
        tempNode = blist->head;
        while (tempNode != NULL)
        {
            int match = 0;
            int len = min(tempNode->info.category.size(), searchCategory.size());
            int step = 0;
            while (step < len)
            {
                if (cmprLetter(tempNode->info.category[step], searchCategory[step]))
                {
                    match += 1;
                }
                step++;
            }
            if (match > bestMatch)
            {
                bestMatch = match;
                target = tempNode;
            }
            tempNode = tempNode->next;
        }
    }
    tempNode = blist->head;
    if (target != NULL)
    {
        while (tempNode != NULL)
        {
            if (tempNode->info.category == target->info.category)
            {
                BookNode *newNode = new BookNode(tempNode->info);
                if (isEmpty(*tempList))
                    tempList->head = tempList->tail = newNode;
                else
                {
                    tempList->tail->next = newNode;
                    tempList->tail = newNode;
                }
            }
            tempNode = tempNode->next;
        }
    }
    if (isEmpty(*tempList))
    {
        cout << "No Category Matched" << endl;
        delete tempList;
        return NULL;
    }
    showAll(tempList);
    target = searchbyID(tempList);
    clearList(tempList);
    delete tempList;
    return target;
}

BookNode *searchbyPublisher(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input Publisher to Search: ";
    cin.ignore();
    string searchPublisher;
    BookNode *tempNode = blist->head;
    getline(cin, searchPublisher);
    BookNode *target = NULL;
    BookList *tempList = new BookList();
    int bestMatch = 0;
    while (tempNode != NULL)
    {
        string publisherLower = tempNode->info.publisher;
        string searchLower = searchPublisher;
        transform(publisherLower.begin(), publisherLower.end(), publisherLower.begin(), ::tolower);
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (publisherLower.find(searchLower) != string::npos)
        {
            BookNode *newNode = new BookNode(tempNode->info);
            if (isEmpty(*tempList))
                tempList->head = tempList->tail = newNode;
            else
            {
                tempList->tail->next = newNode;
                tempList->tail = newNode;
            }
        }
        tempNode = tempNode->next;
    }
    if (isEmpty(*tempList))
    {
        tempNode = blist->head;
        while (tempNode != NULL)
        {
            int match = 0;
            int len = min(tempNode->info.publisher.size(), searchPublisher.size());
            int step = 0;
            while (step < len)
            {
                if (cmprLetter(tempNode->info.publisher[step], searchPublisher[step]))
                {
                    match += 1;
                }
                step++;
            }
            if (match > bestMatch)
            {
                bestMatch = match;
                target = tempNode;
            }
            tempNode = tempNode->next;
        }
    }
    tempNode = blist->head;
    if (target != NULL)
    {
        while (tempNode != NULL)
        {
            if (tempNode->info.publisher == target->info.publisher)
            {
                BookNode *newNode = new BookNode(tempNode->info);
                if (isEmpty(*tempList))
                    tempList->head = tempList->tail = newNode;
                else
                {
                    tempList->tail->next = newNode;
                    tempList->tail = newNode;
                }
            }
            tempNode = tempNode->next;
        }
    }
    if (isEmpty(*tempList))
    {
        cout << "No publisher Matched" << endl;
        delete tempList;
        return NULL;
    }
    showAll(tempList);
    target = searchbyID(tempList);
    clearList(tempList);
    delete tempList;
    return target;
}

BookNode *searchbyYear(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input Released Year: ";
    int tempYear;
    cin >> tempYear;
    BookNode *tempNode = blist->head;
    BookList *tempList = new BookList();
    BookNode *target;
    while (tempNode != NULL)
    {
        if (tempNode->info.year == tempYear)
        {
            BookNode *newNode = new BookNode(tempNode->info);
            if (isEmpty(*tempList))
            {
                tempList->head = tempList->tail = newNode;
            }
            else
            {
                tempList->tail->next = newNode;
                tempList->tail = newNode;
            }
        }
        tempNode = tempNode->next;
    }
    if (isEmpty(*tempList))
    {
        cout << "No Data Matched";
        return NULL;
    }
    showAll(tempList);
    target = searchbyID(tempList);
    clearList(tempList);
    delete tempList;
    return target;
}

BookNode *searchbyQuantity(BookList *blist)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Display";
        return NULL;
    }
    cout << "Input Released quantity: ";
    int tempQuantity;
    cin >> tempQuantity;
    BookNode *tempNode = blist->head;
    BookList *tempList = new BookList();
    BookNode *target;
    while (tempNode != NULL)
    {
        if (tempNode->info.quantity == tempQuantity)
        {
            BookNode *newNode = new BookNode(tempNode->info);
            if (isEmpty(*tempList))
            {
                tempList->head = tempList->tail = newNode;
            }
            else
            {
                tempList->tail->next = newNode;
                tempList->tail = newNode;
            }
        }
        tempNode = tempNode->next;
    }
    if (isEmpty(*tempList))
    {
        cout << "No Data Matched";
        return NULL;
    }
    showAll(tempList);
    target = searchbyID(tempList);
    clearList(tempList);
    delete tempList;
    return target;
}

void deleteNode(BookList *blist, BookNode *target)
{
    if (isEmpty(*blist))
    {
        cout << "No Data To Delete";
        return;
    }
    BookNode *tempNode = blist->head, *preNode = NULL;
    while (tempNode != NULL)
    {
        if (tempNode == target)
        {
            break;
        }
        preNode = tempNode;
        tempNode = tempNode->next;
    }
    if (preNode == NULL)
    {
        blist->head = tempNode->next;
    }
    else
    {
        preNode->next = tempNode->next;
    }
    delete tempNode;
    cout << "Delete Successfully";
    saveAllBooktoFile(blist);
}

int countAll(BookList *blist)
{
    BookNode *temp = blist->head;
    int counted = 0;
    while (temp!=NULL)
    {
        counted+=1;
        temp=temp->next;
    }
    return counted;
}

void insertHead(BookList *blist, BookNode *tempNode) 
{
    tempNode = new BookNode(inputBookInfo(*blist));
    if (isEmpty(*blist))
    {
        blist->head = blist->tail = tempNode;
    }
    else 
    {
        tempNode->next = blist->head;
        blist->head = tempNode;
    }
    saveAllBooktoFile(blist);
}

void insertTail(BookList *blist, BookNode *tempNode)
{
    tempNode = new BookNode(inputBookInfo(*blist));
    if (isEmpty(*blist))
    {
        blist->head = blist->tail = tempNode;
    }
    else
    {
        blist->tail->next=tempNode;
        blist->tail=tempNode;
    }
    saveBooktoFile(tempNode->info);
}

void insertPos(BookList *blist, BookNode *tempNode)
{
    int maxPos=countAll(blist), pos;
    do
    {
       cout<< "Input Position To Insert (0 to " <<maxPos<< "): ";
       cin>> pos;
    } while (pos>maxPos||pos<0);
    if (pos == 0 || blist->head == NULL) {
        insertHead(blist, tempNode);
        return;
    }
    int i = 0;
    BookNode *temp = blist->head;
    while (temp != NULL && i < pos - 1) 
    {
        temp = temp->next;
        i++;
    }
    if (temp == NULL || temp->next == NULL) {
        insertTail(blist, tempNode);
    }
    else {
        inputBookInfo(*blist);
        tempNode->next = temp->next;
        temp->next = tempNode;
    }
    saveAllBooktoFile(blist);
}

void deleteHead(BookList *blist) 
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Delete";
        return;
    }
    BookNode *temp = blist->head;
    blist->head = blist->head->next;
    delete temp;
    if (blist->head == NULL)
    {
        blist->tail = NULL;
    }
    saveAllBooktoFile(blist);
}

void deleteTail(BookList *blist) 
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Delete";
        return;
    }
    if (blist->head == blist->tail) {
        deleteHead(blist);
        return;
    }
    BookNode *temp = blist->head;
    while (temp->next != blist->tail) 
    {
        temp = temp->next;
    }
    delete blist->tail;
    temp->next = NULL;
    blist->tail = temp;
    saveAllBooktoFile(blist);
}

void deletePos(BookList *blist) 
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Delete";
        return;
    }
    int maxPos=countAll(blist), pos;
    do
    {
       cout<< "Input Position To Insert (0 to " <<maxPos<< "): ";
       cin>> pos;
    } while (pos>maxPos||pos<0);
    if (pos == 0 || blist->head == NULL || blist->head->next == NULL) 
    {
        deleteHead(blist);
        return;
    }
    int i = 0;
    BookNode *preNode = NULL;
    BookNode *target = blist->head;
    while (target != NULL && i < pos) {
        preNode = target;
        target = target->next;
        i++;
    }
    if (target == NULL) return;
    preNode->next = target->next;
    if (target == blist->tail) blist->tail = preNode;
    delete target;
    saveAllBooktoFile(blist);
}

void stcAuthor(BookList *blist)
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Statistc";
        return;
    }
    BookNode *tempNode = searchbyAuthor(blist);
    string tempAuth=tempNode->info.author;
    map<string, int> book;
    tempNode=blist->head;
    while(tempNode!=0)
    {
        if(tempNode->info.author==tempAuth)
        {
            book[tempNode->info.publisher] += 1;
        }
        tempNode=tempNode->next;
    }
    if(book.empty())
    {
        cout<<"Not Found Book Of " << tempAuth ;
        return;
    }
    printf("\n%-40s | %-30d\n","Publisher", "Quantity");
    cout<< "---------------\n";
    for(auto &entry : book)
    {
        printf("\n%-40s | %-30s\n",entry.first, entry.second);
    }
}

void stcCategory(BookList *blist)
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Statistc";
        return;
    }
    map<string, int> book;
    BookNode *temp=blist->head;
    while(temp!=NULL)
    {
        book[temp->info.category]+=1;
        temp=temp->next;
    }
    if(book.empty())
    {
        cout<<"Not Found" ;
        return;
    }
    printf("\n%-40s | %-30s\n","Category", "Quantity");
    cout<< "---------------\n";
    for(auto& entry : book)
    {
        printf("\n%-40s | %-30d\n",entry.first, entry.second);
    }
}

void stcPub(BookList *blist)
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Statistc";
        return;
    }
    BookNode *tempNode = searchbyPublisher(blist);
    string tempPub=tempNode->info.publisher;
    map<int, int> book;
    tempNode=blist->head;
    while(tempNode!=0)
    {
        if(tempNode->info.publisher==tempPub)
        {
            book[tempNode->info.year] += 1;
        }
        tempNode=tempNode->next;
    }
    if(book.empty())
    {
        cout<<"Not Found Book Of " << tempPub ;
        return;
    }
    printf("\n%-40s | %-30s\n","Year", "Quantity");
    cout<< "---------------\n";
    for(auto &entry : book)
    {
        printf("\n%-40d | %-30d",entry.first, entry.second);
    }
}

void leastPub(BookList *blist)
{
    if (isEmpty(*blist)) 
    {
        cout<<"No Data To Statistc";
        return;
    }
    map<string, int> book;
    BookNode *tempNode=blist->head;
    while(tempNode!=NULL)
    {
        book[tempNode->info.publisher]+=1;
        tempNode=tempNode->next;
    }
    int min = 999;
    string minPub;
    for(auto& entry : book)
    {
        if(entry.second<=min)
        {
            min=entry.second;
            minPub=entry.first;
        }
    }
    printf("\n%-50s | %-30s\n","Publisher Has Least Book", "Quantity");
    cout<< "---------------\n";
    printf("\n%-50s | %-30d\n",minPub,min);
}

void editMenu()
{
    cout << "\n===== Choose Your Option =====\n";
    cout << "1. Edit ID\n";
    cout << "2. Edit Name\n";
    cout << "3. Edit Author\n";
    cout << "4. Edit Publisher\n";
    cout << "5. Edit Category\n";
    cout << "6. Edit Released Year\n";
    cout << "7. Edit Quantity\n";
    cout << "8. Delete Book\n";
    cout << "0. Exit\n";
    cout << "Enter Your Choice: ";
}

void editBook(BookList *blist,BookNode *temp)
{
    int choice;
    do
    {
        editMenu();
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                cout<< "Present ID: " << temp->info.id << "\nEnter New ID: ";
                do
                {
                    getline(cin, temp->info.id);
                    if (!isUniqueID(*blist, temp->info))
                    {
                        cout << "Exsisted ID\nTry Another ID: ";
                    };
                } while (isUniqueID(*blist, temp->info) == false);
                cout<< "Edit ID Successfully";
                break;
            }
            case 2:
            {
                cout<< "Present Name: " << temp->info.name << "\nEnter New Name: ";
                getline(cin, temp->info.name);
                cout<< "Edit Name Successfully";
                break;
            }
            case 3:
            {
                cout<< "Present Author: " << temp->info.author << "\nEnter New Author: ";
                getline(cin, temp->info.author);
                cout<< "Edit Author Successfully";
                break;
            }
            case 4:
            {
                cout<< "Present Publisher: " << temp->info.publisher << "\nEnter New Publisher: ";
                getline(cin, temp->info.publisher);
                cout<< "Edit Publisher Successfully";
                break;
            }
            case 5:
            {
                cout<< "Present Category: " << temp->info.category << "\nEnter New Category: ";
                getline(cin, temp->info.category);
                cout<< "Edit Category Successfully";
                break;
            }
            case 6:
            {
                cout<< "Present Released Year: " << temp->info.year << "\nEnter New Released Year: ";
                cin>>temp->info.year;
                cin.ignore();
                cout<< "Edit Released Year Successfully";
                break;
            }
            case 7:
            {
                cout<< "Present Quantity: " << temp->info.quantity << "\nEnter New Quantity: ";
                cin>> temp->info.quantity;
                cin.ignore();
                cout<< "Edit Quantity Successfully";
                break;
            }
            case 8:
            {
                deleteNode(blist, temp);
                break;
            }
            default:
            {
                cout<<"Invalid Selection";
            }
        }
    } while (choice!=0);
    

}

void displayMenu()
{
    cout << "\n===== Library Management System =====\n";
    cout << "1. Add New Book (sort list after add)\n";
    cout << "2. Display All Books\n";
    cout << "3. Search Book by ID\n";
    cout << "4. Search Book by Name\n";
    cout << "5. Search Book by Author\n";
    cout << "6. Search Book by Publisher\n";
    cout << "7. Search Book by Category\n";
    cout << "8. Search Book by Year\n";
    cout << "9. Search Book by Quantity\n";
    cout << "10. Delete First Book\n";
    cout << "11. Delete Last Book\n";
    cout << "12. Delete Book At Choosed Position\n";
    cout << "13. Add Book At First\n";
    cout << "14. Add Book At Last\n";
    cout << "15. Add Book At Choosed Position\n";
    cout << "16. Statistc Book Of Author For Each Publisher\n";
    cout << "17. Statistc Book Of Each Category\n";
    cout << "18. Statistc Book Of Publisher Each Year\n";
    cout << "19. Publisher Has Least Book\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    BookList *library= new BookList;
    int choice;
    do
    {
        displayMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                int quantity;
                cout<< "Input Quantity Of Book You Want To Add: ";
                cin>> quantity;
                int i=0;
                while(i<quantity)
                {
                    addBook(library);
                    i+=1;
                }
                break;
            }
            case 2:
            {
                showAll(library);
                break;
            }
            case 3:
            {
                BookNode *target = searchbyID(library);
                editBook(library, target);
                break;
            }
            case 4:
            {
                BookNode *target = searchbyName(library);
                editBook(library, target);
                break;
            }
            case 5:
            {
                BookNode *target = searchbyAuthor(library);
                editBook(library, target);
                break;
            }
            case 6:
            {
                BookNode *target = searchbyPublisher(library);
                editBook(library, target);
                break;
            }
            case 7:
            {
                BookNode *target = searchbyCategory(library);
                editBook(library, target);
                break;
            }
            case 8:
            {
                BookNode *target = searchbyYear(library);
                editBook(library, target);
                break;
            }
            case 9:
            {
                BookNode *target = searchbyQuantity(library);
                editBook(library, target);
                break;
            }
            case 10:
            {
                deleteHead(library);
                break;
            }
            case 11:
            {
                deleteTail(library);
                break;
            }
            case 12:
            {
                deletePos(library);
                break;
            }
            case 13:
            {

                break;
            }
            case 14:
            {

                break;
            }
            case 15:
            {

                break;
            }
            case 16:
            {

                break;
            }
            case 17:
            {

                break;
            }
            case 18:
            {

                break;
            }
            default:
            {

            }
        }

    } while (choice != 0);

    return 0;
}