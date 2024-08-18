#include <iostream>
#include <stack>
#define MAX 10
using namespace std;


class GraphMatrix {
private:
    int grp[MAX][MAX];
    int visited[MAX];
    stack<int> stk; // 스택을 사용한 DFS에서 사용

public:
    GraphMatrix(int vertex);
    void AddEdge(int v, int e);
    void DFS(int vertex);
    void DFS_STACK(int start);
    void PrintAll();
    void ResetVisited(); // visited 배열 초기화
};

GraphMatrix::GraphMatrix(int vertex) {
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            grp[i][j] = 0;
        }
        visited[i] = 0;
    }
}

void GraphMatrix::AddEdge(int v, int e) {
    grp[v][e] = 1;
    grp[e][v] = 1;
}

void GraphMatrix::DFS(int vertex) {
    visited[vertex] = 1; // 방문은 1로 표현
    cout << vertex << " ";

    for (int i = 0; i < MAX; i++) {
        if (grp[vertex][i] == 1 && visited[i] == 0) { // 방문되었다고 표시가 안됨
            DFS(i);
        }
    }
}

void GraphMatrix::DFS_STACK(int start) {
    stk.push(start); // 값을 stack에 넣고 방문을 1로 표시
    visited[start] = 1;

    while (!stk.empty()) {
        int Cur = stk.top();
        cout << Cur << " ";
        stk.pop(); // 스택에서 꺼낸 후 팝

        // 인접 노드 확인 
        for (int i = 0; i < MAX; i++) {  
            if (grp[Cur][i] == 1 && visited[i] == 0) { // 현재 방문되었다고 나오지 않는경우
                stk.push(i); 
                visited[i] = 1;
            }
        }
    }
}

void GraphMatrix::PrintAll() {
    for (int v = 0; v < MAX; v++) {
        for (int e = 0; e < MAX; e++) {
            cout << grp[v][e] << " ";
        }
        cout << endl;
    }
}

void GraphMatrix::ResetVisited() {
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
}

int main()
{
    GraphMatrix g(MAX);

    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 3);
    g.AddEdge(1, 4);
    g.AddEdge(2, 5);
    g.AddEdge(2, 6);
    g.AddEdge(3, 7);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);

    cout << "인접 행렬" << endl;
    g.PrintAll();

    cout << "\nDFS (재귀 호출) 탐색 순서: ";
    g.ResetVisited();  // DFS 실행 전 visited 초기화
    g.DFS(0);  // 정점 0에서 DFS 시작

    cout << "\nDFS_STACK (스택 사용) 탐색 순서: ";
    g.ResetVisited();  // DFS_STACK 실행 전 visited 초기화
    g.DFS_STACK(0);  // 정점 0에서 DFS 시작

    cout << endl;
    return 0;
}
