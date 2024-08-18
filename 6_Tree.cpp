#include <iostream>
// Bineary Search Tree 이진 탐색 트리
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class Tree {
private:
    Node* root;
    int count;
public:
    Tree();
    ~Tree();
    Node* MakeNode(int data);
    Node* AddNode(int data);
    Node* SearchNode(int data);
    Node* SearchNode2(Node* Curnode, int data); // 재귀 호출 구현
    Node* DeleteNode(Node* node,int data);
    void InorderTraverse(Node* node); // 중위 순회
    void PreorderTraverse(Node* node); // 전위 순회
    void PostorderTraverse(Node* node); // 후위 순회
    void DestroyTree(Node* node);
    Node* GetRoot() { return root; }
};

Tree::Tree() : root(nullptr), count(0) {};

// 트리 소멸자 (메모리 해제)
Tree::~Tree() {
    DestroyTree(root);
}

// 트리 소멸을 위한 재귀 함수
void Tree::DestroyTree(Node* node) {
    if (node != nullptr) { // 후위 순회를 생각하며 트리 소멸
        DestroyTree(node->left); // 왼쪽 
        DestroyTree(node->right); // 오른쪽
        delete node; // 부모
    }
}

Node* Tree::MakeNode(int data) {
    Node* NewNode = new Node();
    NewNode->data = data;
    NewNode->left = nullptr;
    NewNode->right = nullptr;
    return NewNode;
}
Node* Tree::AddNode(int data) {
    Node* NewNode = MakeNode(data);
    Node* CurNode = root; // 삽입위치를 찾을 노드
    Node* Parent = nullptr; // 부모 노드
    count++;

    // root가 null일 경우
    if (root == nullptr) { 
        root = NewNode;
        return NewNode;
    }
    // root가 null이 아닐경우
    while (CurNode != nullptr) {
        Parent = CurNode;  // Parent도 Cur의 위치와 동일
        if (data > CurNode->data) { // 삽입 데이터가 현재 가리키고 있는 데이터 값보다 클 경우
            CurNode = CurNode->right; // 삽입 위치를 오른쪽으로 이동
        }
        else {
            CurNode = CurNode->left; // 삽입 위치를 왼쪽으로 이동
        }
    }
    // 삽입
    if (data > Parent->data) {  // 삽입 데이터가 Parent가 가리키는 데이터 보다 클 경우
        Parent->right = NewNode; // parent오른쪽에 삽입
    }
    else if (data < Parent->data) { // 작을경우
        Parent->left = NewNode; // parent왼쪽에 삽입
    }
    else { // 삽입 데이터가 중복될 경우 nullptr를 반환 count 감소
        cout << " 중복된 데이터 값입니다" << endl;
        count--;
        return nullptr;
    }
    return NewNode;
}

Node* Tree::SearchNode(int data) {
    Node* CurNode = root;
    while (CurNode != nullptr) {
        if (CurNode->data == data) {
            cout << "검색 값: " << CurNode->data << endl;
            return CurNode;
        }
        else if (CurNode->data > data) { // 지울 값이 작기 떄문에 왼쪽으로 탐색
            CurNode = CurNode->left;
        }
        else {                          // (CurNode->data < data)
            CurNode = CurNode->right; // 지울 값이 크기 떄문에 오른쪽으로 탐색
        }
    }
    cout << "검색 값이 없습니다." << endl;
    return nullptr; // 못찾은 경우 null 반환
}   

Node* Tree::SearchNode2(Node* CurNode, int data) {
    if (CurNode == nullptr) {
        cout << "검색 값이 없습니다." << endl;
        return nullptr;
    }

    if (CurNode->data == data) {
        cout << "검색 값: " << CurNode->data << endl;
        return CurNode;
    }

    if (CurNode->data > data) {
        return SearchNode2(CurNode->left, data); // 왼쪽으로 탐색
    }
    else {
        return SearchNode2(CurNode->right, data); // 오른쪽으로 탐색
    }
}

Node* Tree::DeleteNode(Node* root, int data) {
    if (root == nullptr) {
        return root;
    }

    if (root->data > data) {
        root->left = DeleteNode(root->left, data);
    }
    else if(root->data < data) {
        root->right = DeleteNode(root->right, data);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) { //  리프 노드의 경우
            delete root;
            root = nullptr;
            count--;
        }
        else if (root->left == nullptr) { // 오른쪽 자식만 존재
            Node* Temp = root->right;
            delete root;
            root = Temp; // 끊긴 root 이어주기
            count--;
        }
        else if (root->right == nullptr) { // 왼쪽 자식만 존재
            Node* Temp = root->left;
            delete root;
            root = Temp;
            count--;
        }
        else { // 2개의 자식이 존재할 경우 
               //1번: 오른쪽 서브트리 가장 작은 값 or 2번: 왼쪽 서브트리 가장 큰 값
            Node* Temp = root->right; // 1번 선택
            while (Temp && Temp->left != nullptr) {
                Temp = Temp->left;
            }
            root->data = Temp->data; // root를 1번 에서 찾은 값으로 변경(대체)
            root->right = DeleteNode(root->right, Temp->data); // 1번 값을 삭제 
            count--;
        }
    }
    return root;
}


void Tree::InorderTraverse(Node* node) {
    if (node != nullptr) {
        InorderTraverse(node->left);
        cout << node->data << " ";
        InorderTraverse(node->right);
    }
}
void Tree::PreorderTraverse(Node* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        PreorderTraverse(node->left);
        PreorderTraverse(node->right);
    }
}
void Tree::PostorderTraverse(Node* node) {
    if (node != nullptr) {
        PostorderTraverse(node->left);
        PostorderTraverse(node->right);
        cout << node->data << " ";
    }
}

int main()
{
    Tree tree;

    // 노드 추가
    tree.AddNode(50);
    tree.AddNode(30);
    tree.AddNode(20);
    tree.AddNode(40);
    tree.AddNode(70);
    tree.AddNode(60);
    tree.AddNode(80);

    cout << "트리에 노드를 추가한 후:" << endl;

    cout << "중위 순회: ";
    Node* rootNode = tree.GetRoot();
    if (rootNode) {
        tree.InorderTraverse(rootNode); // 루트 노드부터 중위 순회
    }
    else {
        cout << "루트 노드를 찾을 수 없습니다.";
    }
    cout << endl;

    cout << "전위 순회: ";
    if (rootNode) {
        tree.PreorderTraverse(rootNode); // 루트 노드부터 전위 순회
    }
    else {
        cout << "루트 노드를 찾을 수 없습니다.";
    }
    cout << endl;

    cout << "후위 순회: ";
    if (rootNode) {
        tree.PostorderTraverse(rootNode); // 루트 노드부터 후위 순회
    }
    else {
        cout << "루트 노드를 찾을 수 없습니다.";
    }
    cout << endl;

    // 노드 삭제
    rootNode = tree.DeleteNode(tree.GetRoot(), 20);
    cout << "\n노드 20 삭제 후 중위 순회: ";
    if (rootNode) {
        tree.InorderTraverse(rootNode);
    }
    else {
        cout << "루트 노드를 찾을 수 없습니다.";
    }
    cout << endl;

    rootNode = tree.DeleteNode(tree.GetRoot(), 30);
    cout << "\n노드 30 삭제 후 중위 순회: ";
    if (rootNode) {
        tree.InorderTraverse(rootNode);
    }
    else {
        cout << "루트 노드를 찾을 수 없습니다.";
    }
    cout << endl;

    rootNode = tree.DeleteNode(tree.GetRoot(), 50);
    cout << "\n노드 50 삭제 후 중위 순회: ";
    if (rootNode) {
        tree.InorderTraverse(rootNode);
    }
    else {
        cout << "루트 노드를 찾을 수 없습니다.";
    }
    cout << endl;

    return 0;
}

