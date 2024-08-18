#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;
    int value;
    Node* next;
};

class HashTable {
private:
    Node** table; // Node* 들을 가리키고 있는 배열이므로 이중 포인터로 선언
    int size; // table의 크기 (버킷의 수)
    int datacnt; // 들어있는 자료의 수
    int HashFunc(const string& key);    
public:
    HashTable(int size);
    ~HashTable();
    void Insert(const string& key, int value);
    void Delete(const string& key);
    bool Search(const string& key, int& value);
    void PrintAll();
};

int HashTable::HashFunc(const string& key) {
    int hash = 0;
    for(char c : key) {
        hash = (hash * 47 + c) % size;
    }
    return hash;
}

HashTable::HashTable(int size): size(size), datacnt(0) {
    table = new Node*[size]; // Node* 포인터 배열 생성

    for (int i = 0; i < size; i++) {
        table[i] = nullptr; // 각각의 버킷들 초기화
    }
}

HashTable::~HashTable()  {
    for (int i = 0; i < size; i++) {
        Node* Cur = table[i]; 
        while (Cur != nullptr) {
            Node* Temp = Cur;
            Cur = Cur->next;
            delete Temp;
        }
    }
    delete[] table; // Node* 포인터 배열 해제
}

void HashTable::Insert(const string& key,int value) {
    int index = HashFunc(key); // 해시 함수를 이용해 해시값을 인덱스로 사용
    Node* NewNode = new Node();
    NewNode->key = key;
    NewNode->value = value;
    NewNode->next = nullptr;
    datacnt++; // 자료의 수가 증가
    if (table[index] == nullptr) { // 비어 있는 경우 새로운 노드 할당
        table[index] = NewNode; 
    }
    else { // 공통된 해시값을 가지면 Chaining을 통해 연결
        Node* CurNode = table[index];
        while (CurNode->next != nullptr) {
            CurNode = CurNode->next;
        }
        CurNode->next = NewNode;
    } 
}

void HashTable::Delete(const string& key) {
    int index = HashFunc(key);
    Node* DelNode = table[index]; // 삭제할 노드
    Node* PreNode = nullptr; // 삭제할 노드의 이전 노드
    while (DelNode != nullptr && DelNode->key != key) {
        PreNode = DelNode;
        DelNode = DelNode->next;
    }

    if (DelNode == nullptr) { // 키를 찾지 못한경우 종료
        return;
    }

    if (PreNode == nullptr) { 
        table[index] = DelNode->next; // 첫번째 노드를 삭제할 경우
    }
    else {
        PreNode->next = DelNode->next; //이전 노드와 지울노드의 다음을 연결
    }
    datacnt--; // 자료의 수가 감소
    delete DelNode;
}

bool HashTable::Search(const string& key, int& value) {
    int index = HashFunc(key);
    Node* CurNode = table[index]; // 처음 인덱스 부터 시작
    while (CurNode != nullptr) {
        if (CurNode->key == key) {
            value = CurNode->value;
            cout << "찾은 값: " << value << endl;
            return true;
        }
        CurNode = CurNode->next; // 아닐경우 다음으로 이동
    }
    return false;
}

void HashTable::PrintAll() {
    for (int i = 0; i < size; i++) {
        cout << "Bucket " << i << ": ";
        Node* CurNode = table[i];
        while (CurNode != nullptr) {
            cout << "(" << CurNode->key << ", " << CurNode->value << ") ";
            CurNode = CurNode->next;
        }
        cout << endl;
    }
}

int main()
{
    HashTable ht(10); // 크기가 10인 해시 테이블 생성

    ht.Insert("apple", 100);
    ht.Insert("banana", 200);
    ht.Insert("cherry", 300);
    ht.Insert("cherry", 400);
    ht.Insert("banana", 500);

    ht.PrintAll();

    int value;
    if (ht.Search("banana", value)) {
        cout << "Found 'banana' with value: " << value << endl;
    }
    else {
        cout << "'banana' not found." << endl;
    }

    ht.Delete("banana");
    ht.PrintAll();

    if (ht.Search("banana", value)) {
        cout << "Found 'banana' with value: " << value << endl;
    }
    else {
        cout << "'banana' not found." << endl;
    }

    return 0;
}

