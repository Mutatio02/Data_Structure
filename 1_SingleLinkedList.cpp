#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class SLL {
private:
    Node* Head;

public:
    SLL();
    ~SLL();
    void PrintAll();
    void AddFirst(int data);
    void AddLast(int data);
    Node* Search(int data);
    void DeleteNode(int data);
};

SLL::SLL() {
    Head = new Node(); // 더미 헤드 노드 생성.
    Head->next = nullptr; // 헤드 노드의 다음은 nullptr로 초기화.
}

SLL::~SLL() {
    Node* CurNode = Head; // 현재 노드는 더미 헤드 노드.
    while (CurNode != nullptr) { 
        Node* NextNode = CurNode->next; // 다음 노드는 현재의 next.
        delete CurNode; 
        CurNode = NextNode; // 현재 노드는 다음 노드로 변경.
    }
}

void SLL::PrintAll() {
    Node* CurNode = Head->next; // 출력할 노드는 헤드 노드의 다음부터 시작.
    if (CurNode == nullptr) {
        cout << "리스트가 비어 있습니다." << endl;
        return;
    }
    while (CurNode != nullptr) {
        cout << "값: " << CurNode->data << endl;
        CurNode = CurNode->next; // 다음 노드로 이동.
    }
}
// 맨 처음 위치에 삽입
void SLL::AddFirst(int data) {
    Node* NewNode = new Node();
    NewNode->data = data;
    NewNode->next = Head->next; // 새로운 노드는 기존 헤드노드가 가리키고 있는 곳으로 변경.
    Head->next = NewNode; // 더미 헤드 노드는 새로운 노드를 가리킴.
}
// 맨 마지막 위치에 삽입
void SLL::AddLast(int data) {
    Node* NewNode = new Node();
    NewNode->data = data;
    NewNode->next = nullptr; // 새로운 노드는 마지막 노드이기 때문에 nullptr을 가리킴.

    Node* CurNode = Head; // 마지막 위치를 찾을 노드 설정
    while (CurNode->next != nullptr) {
        CurNode = CurNode->next; 
    }
    CurNode->next = NewNode; // 위치를 찾은 경우 새로운 노드를 가리키게 연결.
}

Node* SLL::Search(int data) {
    Node* CurNode = Head->next; // 검색할 노드는 현재 헤드 노드의 다음.
    while (CurNode != nullptr) {
        if (CurNode->data == data) {
            cout << "검색 값: " << CurNode->data << endl; // 검색 값을 찾은 경우
            return CurNode;
        }
        CurNode = CurNode->next; // 검색할 노드가 아닌경우 그 다음으로 가리킴.
    }
    cout << "검색 값이 없습니다." << endl; // 검색 값을 찾지 못한 경우
    cout << endl;
    return nullptr;
}

void SLL::DeleteNode(int data) {
    Node* PreNode = Head; // 지울 노드의 이전노드를 헤드 노드로 설정.
    Node* DelNode = Head->next; // 지울 노드는 헤드 노드의 다음으로 설정.
    while (DelNode != nullptr && DelNode->data != data) { // 찾는 값이 아닐경우
        PreNode = DelNode; // 이전노드를 지울려 했던 노드로 변경.
        DelNode = DelNode->next; // 지울 노드를 지울 노드의 다음으로 변경.
    }
    if (DelNode == nullptr) {
        cout << "지울 값이 없습니다." << endl;
        cout << endl;
        return;
    }
    PreNode->next = DelNode->next;
    delete DelNode;
}

int main() {
    SLL list;
    list.AddFirst(30);
    list.AddFirst(20);
    list.AddFirst(10);
    list.AddLast(40);  // 리스트의 끝에 40 추가
    list.PrintAll();

    list.Search(50); // 검색 결과가 없음

    list.DeleteNode(20); // 값이 20인 노드 삭제
    list.PrintAll();
    list.DeleteNode(40); // 값이 40인 노드 삭제
    list.PrintAll();
    list.DeleteNode(100); // 값이 100인 노드 삭제 (존재하지 않는 값)
    list.PrintAll();
}
