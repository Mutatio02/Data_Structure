#include <iostream>
using namespace std;

class Heap {
private:
    int* heap;
    int size; // 크기
    int count; // 자료의 개수

    void ReHeapUp(int small);
    void ReHeapDown(int parent);
public:
    Heap(int size);
    ~Heap();
    bool IsEmpty() const;
    bool IsFull() const;
    bool Insert(int data);
    bool Delete();
    void PrintAll() const;
    void Search(int data) const;
};

Heap::Heap(int size) : size(size), count(0) {
    heap = new int[size]; // 0부터 시작, 1부터 시작할경우 size+1
}

Heap::~Heap() {
    delete[] heap;
}

bool Heap::IsEmpty() const {
    return (count == 0); // 자료가 없는 경우
}

bool Heap::IsFull() const {
    return (size == count); // 자료의 개수 = 전체 크기
}

bool Heap::Insert(int data) {
    if (IsFull()) {
        return false;
    }

    heap[count] = data;
    ++count; // 먼저 수가 증가

    ReHeapUp(count - 1); // 마지막 위치에 삽입된 인덱스, 1부터 지각할 경우 ReHeapUp(count)
    return true;
}

void Heap::ReHeapUp(int small) {
    int parent = (small - 1) / 2;

    if (small <= 0) {
        return;
    }

    if (heap[small] >= heap[parent]) { // 자식이 부모보다 크기 때문에 올릴 필요 없음
        return;
    }

    swap(heap[small], heap[parent]); // 나머지 경우 자식과 부모를 바꿈

    ReHeapUp(parent); // 재귀호출로 계속 진행
}

bool Heap::Delete() {
    if (IsEmpty()) {
        return false;
    }

    // 루트 노드를 삭제
    heap[0] = heap[count - 1]; // 루트 노드를 마지막노드로 설정
    --count;

    ReHeapDown(0); // 루트에서 시작하여 재조정
    return true;
}

void Heap::ReHeapDown(int parent) {
    int left = 2 * parent + 1; // 왼쪽 자식 인덱스
    int right = 2 * parent + 2; // 오른쪽 자식 인덱스
    int child = parent; // 초기 child는 부모로 설정

    // 왼쪽 자식이 범위 내에 있는지 확인
    if (left < count) {
        // 왼쪽 자식이 부모보다 작다면 child는 왼쪽 자식
        if (heap[left] < heap[child]) {
            child = left;
        }

        // 오른쪽 자식이 범위 내에 있고 오른쪽 자식이 현재 child보다 작다면 child는 오른쪽 자식
        if (right < count && heap[right] < heap[child]) {
            child = right;
        }

        // child가 부모보다 작으면 swap하고 재귀 호출, 초기에 child를 parent로 설정해놨기 떄문
        if (child != parent) {
            swap(heap[parent], heap[child]);
            ReHeapDown(child); // child로 재귀 호출
        }
    }
}

void Heap::PrintAll() const {
    for (int i = 0; i < count; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

void Heap::Search(int data) const {
    for (int i = 0; i < count; i++) {
        if (heap[i] == data) {
            cout << "찾은 위치: " << i << endl;
            return;
        }
    }
    cout << "데이터가 없습니다." << endl;
}

int main() {
    Heap heap(10);

    // 데이터 삽입
    heap.Insert(12);
    heap.Insert(87);
    heap.Insert(111);
    heap.Insert(34);
    heap.Insert(16);
    heap.Insert(75);

    cout << "힙 상태: ";
    heap.PrintAll();  // 현재 힙 상태 출력

    heap.Delete();

    cout << "삭제 후 힙 상태: ";
    heap.PrintAll();  // 삭제 후 힙 상태 출력

    // 데이터 검색
    heap.Search(34);  // 존재하는 데이터 검색
    heap.Search(99);  // 존재하지 않는 데이터 검색

    return 0;
}
