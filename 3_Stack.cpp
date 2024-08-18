#include <iostream>
using namespace std;
// 링크드 리스트 기반
struct Node {
    int data;
    Node* next;
};

class STACK {
private:
    Node* Top; // 맨 위를 나타내는 탑

public:
    STACK();
    ~STACK();
    bool IsEmpty();
    void PrintAll();
    void Push(int data);
    int Pop(); 
    Node* Search(int data);
    int Peek();
};


STACK::STACK() : Top(nullptr) {}

STACK::~STACK() {
    while (!IsEmpty()) {
        Pop(); 
    }
}

bool STACK::IsEmpty() {
    if (Top == nullptr) {
        return true;
    }
    return false;
}

// 스택의 모든 요소 출력
void STACK::PrintAll() {
    Node* CurNode = Top; // 출력할 노드는 Top부터.
    if (IsEmpty()) {
        cout << "스택이 비어 있습니다" << endl;
        return;
    }
    while (CurNode != nullptr) {
        cout << "값: " << CurNode->data << endl;
        CurNode = CurNode->next;
    }
}

// 스택에 데이터 추가
void STACK::Push(int data) {
    Node* NewNode = new Node();
    NewNode->data = data;
    NewNode->next = Top; // 새 노드의 다음을 현재 Top으로 설정
    Top = NewNode; // Top을 새 노드로 업데이트
}

// 스택에서 데이터 제거
int STACK::Pop() {
    if (IsEmpty()) {
        cout << "스택이 비어 있습니다. 팝할 수 없습니다." << endl;
        return -1; // 오류 값을 반환
    }
    Node* DelNode = Top; // 제거할 노드
    int value = DelNode->data; // 제거할 노드의 데이터
    Top = Top->next; // Top을 다음 노드로 이동
    delete DelNode; // 제거할 노드 메모리 해제
    return value; // 제거한 데이터 반환
}
Node* STACK::Search(int data) {
    Node* CurNode = Top;  // 검색할 노드는 Top에서 부터 찾기
    while (CurNode!= nullptr) {
        if (CurNode->data == data) {
            cout << "검색 값:" << CurNode->data << endl;
            return CurNode;
        }
        CurNode = CurNode->next;
    }
    cout << "검색 값이 없습니다." << endl;
    cout << endl;
    return nullptr;
}

int STACK::Peek() {
    if (IsEmpty()) {
        cout << "스택이 비어 있습니다, Peek 불가." << endl;
        return -1; 
    }
    return Top->data; // Top 노드의 데이터를 반환
}

int main() {
    STACK stack;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    cout << "스택의 모든 요소" << endl;
    stack.PrintAll(); // 30, 20, 10 출력

    cout << "Peek: " << stack.Peek() << endl; // 30 출력, 스택에서 제거하지 않음
    cout << "Pop: " << stack.Pop() << endl; // 30 출력
    cout << "Peek: " << stack.Peek() << endl; // 20 출력

    cout << "스택의 모든 요소" << endl;
    stack.PrintAll(); // 20, 10 출력

    return 0;
}
