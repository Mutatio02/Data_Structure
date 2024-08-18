#include <iostream>
using namespace std;
// 링크드 리스트 기반
struct Node {
    int data;
    Node* next;
};

class QUEUE {
private:
    Node* Rear;  // Enqueue  부분
    Node* Front;  // Enqueue 부분
public:
    QUEUE();
    ~QUEUE();
    bool IsEmpty();
    void PrintAll();
    void Enqueue(int data);
    int Dequeue();
    Node* Search(int data);
    
};
QUEUE::QUEUE() : Front(nullptr), Rear(nullptr) {}
QUEUE::~QUEUE() {
    while (!IsEmpty()) {
        Dequeue();
    }
}
bool QUEUE::IsEmpty() {
    if (Front == nullptr) { // Front가 아무것도 가리키지 않는다면 비어 있는 큐.
        return true;
    }
    return false;
}

void QUEUE::PrintAll() {
    Node* CurNode = Front; //출력할 노드는 Front에서 부터.
    if (IsEmpty()) {
        cout << "큐가 비어 있습니다." << endl;
        return;
    }
    while (CurNode != nullptr) {
        cout << "값: " << CurNode->data << endl;
        CurNode = CurNode->next;
    }
}

void QUEUE::Enqueue(int data) {
    Node* NewNode = new Node();
    NewNode->data = data;
    if (IsEmpty()) { // 비어 있는 경우 Front와  Rear 둘다 새로운 노드을 가리킴.
        Front = NewNode;
        Rear = NewNode;
    } else {
        Rear->next = NewNode; // 큐의 맨 뒤에 새로운 노드가 오게 함.
        Rear = NewNode; // Rear는 새로운 노드를 가리킴.
    }
}
int QUEUE::Dequeue() {
    Node* DelNode = Front; // Dequeue의 위치는 Front.
    if (IsEmpty()) {
        cout << "큐가 비어 있습니다." << endl;
        return -1;
    } else {
        int value = DelNode->data;
        Front = Front->next; // Front는 그 다음 노드를 가리키게 변경.
        if (Front == nullptr) {
            Rear = nullptr;
        }
        delete DelNode;
        return value;
    }
}

Node* QUEUE::Search(int data) {
    Node* CurNode = Front; // 검색의 시작은 Front에서 부터.
    while (CurNode != nullptr) {
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

int main()
{
    QUEUE queue;

    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);

    cout << "큐의 모든 요소" << endl;
    queue.PrintAll(); // 10, 20, 30 출력

    cout << "Dequeue: " << queue.Dequeue() << endl; // 10 출력
    cout << "Dequeue: " << queue.Dequeue() << endl; // 20 출력

    cout << "큐의 모든 요소" << endl;
    queue.PrintAll(); // 30 출력

    return 0;
}

