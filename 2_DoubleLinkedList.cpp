#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

class DLL {
private:
    Node* Head; // 더미 헤드 노드
    Node* Tail; // 더미 테일 노드

public:
    DLL();
    ~DLL();
    void PrintAll();
    void AddFirst(int data);
    void AddLast(int data);
    Node* Search(int data);
    void DeleteNode(int data);
    bool IsEmpty(); // 리스트가 비어 있는지 확인
    bool IsFull();  // 리스트가 가득 찼는지 확인 
};

// 생성자
DLL::DLL() {
    Head = new Node(); 
    Tail = new Node(); 
    Head->next = Tail; // 더미 헤드 노드는 Tail을 가리킴.
    Tail->prev = Head; // 더미 테일 노드는 Head를 가리킴.
}

// 소멸자
DLL::~DLL() {
    Node* CurNode = Head->next;
    while (CurNode != Tail) {
        Node* NextNode = CurNode->next;
        delete CurNode;
        CurNode = NextNode;
    }
    delete Head; // 더미 헤드 노드 삭제
    delete Tail; // 더미 테일 노드 삭제
}

// 리스트가 비어 있는지 확인
bool DLL::IsEmpty() {
    if (Head->next == Tail) { // 헤드 노드가 테일을 가리키면 비어있음.
        return true;
    }
    return false;
}

// 리스트가 가득 찼는지 확인 
bool DLL::IsFull() {
    return false;
}

// 리스트의 모든 요소 출력
void DLL::PrintAll() {
    if (IsEmpty()) {
        cout << "리스트가 비어 있습니다." << endl;
        return;
    }

    Node* CurNode = Head->next; // 헤드의 다음 노드 부터 찾기.
    while (CurNode != Tail) {
        cout << "값: " << CurNode->data << endl;
        CurNode = CurNode->next;
    }
    cout << endl;
}

// 리스트의 처음에 노드 추가
void DLL::AddFirst(int data) {
    if (IsFull()) {
        return;
    }
    Node* NewNode = new Node();
    NewNode->data = data;

    NewNode->next = Head->next; // 새 노드의 다음은 헤드가 가리키고 있는 다음 노드.
    NewNode->prev = Head; // 새 노드의 이전은 헤드 노드.
    Head->next->prev = NewNode; // 헤드 노드의 다음 노드가 가리키고 있는 이전은 새로운 노드로 연결.
    Head->next = NewNode; // 헤드 노드의 다음은 새로운 노드.
}

// 리스트의 끝에 노드 추가
void DLL::AddLast(int data) {
    if (IsFull()) {
        return;
    }
    Node* NewNode = new Node();
    NewNode->data = data;

    NewNode->next = Tail; // 새 노드의 다음은 테일 노드.
    NewNode->prev = Tail->prev; // 새 노드의 이전을 테일노드의 이전으로 가리킴.
    Tail->prev->next = NewNode;  // 테일 노드의 이전의 다음은 새로운 노드.
    Tail->prev = NewNode; // 테일 노드의 이전은 새로운 노드,
}

// 노드 검색
Node* DLL::Search(int data) {
    if (IsEmpty()) {
        cout << "리스트가 비어 있습니다. 검색할 수 없습니다." << endl;
        return nullptr;
    }

    Node* CurNode = Head->next; // 검색할 노드는 헤드 노드의 다음부터.
    while (CurNode != Tail) {
        if (CurNode->data == data) {
            cout << "찾은 값: " << CurNode->data << endl;
            return CurNode;
        }
        CurNode = CurNode->next; // 검색할 노드를 그 다음으로 변경.
    }
    cout << "찾는 값이 없습니다." << endl;
    cout << endl;
    return nullptr;
}

// 노드 삭제
void DLL::DeleteNode(int data) {
    if (IsEmpty()) {
        cout << "리스트가 비어 있습니다. 삭제할 수 없습니다." << endl;
        return;
    }

    Node* DelNode = Head->next; // 지울 노드는 헤드 노드의 다음 부터 찾기.
    while (DelNode != Tail && DelNode->data != data) {
        DelNode = DelNode->next;
    }

    if (DelNode == Tail) {
        cout << "지울 값이 없습니다." << endl;
        cout << endl;
        return;
    }
    // 지울 노드가 사라지기 전 연결 시켜주기
    DelNode->prev->next = DelNode->next; 
    DelNode->next->prev = DelNode->prev;
    delete DelNode;
}

int main() {
    DLL list;

    cout << "IsEmpty: " << list.IsEmpty() << endl; // 리스트가 비어있는지 확인

    list.AddFirst(30);
    list.AddFirst(20);
    list.AddFirst(10);
    list.AddLast(40);  // 리스트의 끝에 40 추가
    list.AddLast(50);
    list.AddLast(60);
    list.PrintAll();

    cout << "IsEmpty: " << list.IsEmpty() << endl; // false 출력
    cout << "IsFull: " << list.IsFull() << endl;   // false 출력

    list.Search(100); // 검색 결과가 없음

    list.DeleteNode(20); // 값이 20인 노드 삭제
    list.PrintAll();  
    list.DeleteNode(40); // 값이 40인 노드 삭제
    list.PrintAll();
    list.DeleteNode(100); // 값이 100인 노드 삭제 (존재하지 않는 값)
    list.PrintAll();

    return 0;
}
