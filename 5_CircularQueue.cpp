#include <iostream>
#include <cstring>
#define SIZE 10
using namespace std;

class C_QUEUE {
private:
    int arr[SIZE];
    int front;
    int rear;

public:
    C_QUEUE();
    ~C_QUEUE();
    bool IsFull();
    bool IsEmpty();
    void PrintAll();
    void Enqueue(int data);
    int Dequeue();
};

C_QUEUE::C_QUEUE() : front(0), rear(0) {
    memset(arr, 0, sizeof(arr));
}

C_QUEUE::~C_QUEUE() {}

bool C_QUEUE::IsFull() {
    if ((rear + 1) % SIZE == front) { // rear의 다음위치가 front를 가리킬 경우 , (rear가 배열의 마지막을 가리킬 경우)
        return true;
    }
    return false;
    
}

bool C_QUEUE::IsEmpty() {
    if (front == rear) { // front와 rear가 같은 위치를 가리키는 경우.
        return true;
    }
    return false;
}

void C_QUEUE::PrintAll() {
    if (IsEmpty()) {
        cout << "큐가 비어 있습니다." << endl;
        return;
    }
    int i = front; // 먼저 들어간 원소의 위치
    while (i != rear) { // 마지막에 삽입한 원소의 위치까지
        cout << "값: " << arr[i] << endl;
        i = (i + 1) % SIZE;
    }
}

void C_QUEUE::Enqueue(int data) {
    if (IsFull()) {
        cout << "큐가 가득 찼습니다." << endl;
        return;
    }
    arr[rear] = data; // rear는 최근에 삽입한 위치가 된다.
    rear = (rear + 1) % SIZE; // rear 업데이트
}

int C_QUEUE::Dequeue() {
    if (IsEmpty()) {
        cout << "큐가 비어 있습니다." << endl;
        return -1;
    }
    int Del = arr[front]; // front는 마지막에 삽입한 위치를 가리키고 있다.
    front = (front + 1) % SIZE; // front 업데이트
    return Del;
}

int main() {
    C_QUEUE queue;

    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);

    cout << "큐의 모든 요소:" << endl;
    queue.PrintAll(); // 10, 20, 30 출력

    cout << "Dequeue: " << queue.Dequeue() << endl; // 10 출력
    cout << "Dequeue: " << queue.Dequeue() << endl; // 20 출력

    cout << "큐의 모든 요소:" << endl;
    queue.PrintAll(); // 30 출력

    return 0;
}
