#include <iostream>
#include <vector>
#include <queue>
#define MAX 10
using namespace std;

class GraphList {
private:
    vector<int> adj[MAX]; // 각 정점의 인접 리스트를 저장할 벡터 배열
    int visited[MAX]; // 정점의 방문 여부를 추적하는 배열
    queue<int> que; // BFS에서 사용할 큐

public:
    GraphList(int vertex);
    void AddEdge(int v, int e);
    void BFS(int start);
    void PrintAll();
};

GraphList::GraphList(int vertex) {
    for (int i = 0; i < vertex; i++) {
        visited[i] = 0; // 방문 배열을 초기화
    }
}

void GraphList::AddEdge(int v, int e) {
    adj[v].push_back(e); // 정점 v에 인접한 정점 e를 추가
    adj[e].push_back(v); // 양방향 그래프이므로 e에도 v를 추가
}

void GraphList::BFS(int start) {

    que.push(start);
    visited[start] = 1;

    while (!que.empty()) {
        int Front = que.front();
        cout << Front << " "; // 현재 방문한 정점 출력
        que.pop(); // 큐에서 제거

        for (int i : adj[Front]) { // 인접한 정점들을 검사
            if (!visited[i]) {
                visited[i] = 1;
                que.push(i); // 방문하지 않은 정점을 큐에 추가
            }
        }
    }
    cout << endl;
}

void GraphList::PrintAll() {
    for (int v = 0; v < MAX; v++) {
        if (!adj[v].empty()) {
            cout << v << ": "; // 정점 v의 인접 리스트 출력
            for (int e : adj[v]) {
                cout << e << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    GraphList g(MAX);

    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 3);
    g.AddEdge(1, 4);
    g.AddEdge(2, 5);
    g.AddEdge(2, 6);
    g.AddEdge(3, 7);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);

    cout << "인접 리스트" << endl;
    g.PrintAll();

    cout << "\nBFS 탐색 순서: ";
    g.BFS(0);  // 정점 0에서 BFS 시작

    return 0;
}
