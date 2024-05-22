#include <iostream>
#include <queue>
#include <initializer_list>

using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    void addNode(Node* child) {
        if (child->data < data) {
            if (!left) {
                addLeftChild(child);
            }
            else {
                left->addNode(child);
            }
        }
        else {
            if (!right) {
                addRightChild(child);
            }
            else {
                right->addNode(child);
            }
        }
    }
    void addLeftChild(Node* child) {
        left = child;
        left->parent = this;
    }
    void addRightChild(Node* child) {
        right = child;
        right->parent = this;
    }
};

class BSTree {
    Node* root;
    int size;
public:
    BSTree(const initializer_list<int>& list) : size(list.size()) {
        if (size < 1)
            return;
        // create root Node 
        root = createNode(*list.begin());
        Node* curNode = root;
        for (auto item = list.begin() + 1; item < list.end(); item++) {
            // call addNode for each item
            root->addNode(createNode(*item));
        }
    }

    Node* getRoot() {
        return root;
    }

    bool searchNode(int key) {
        return searchNodePrivate(root, key);
    }

    friend void printLikeTree(Node* root);

private:
    Node* createNode(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    bool searchNodePrivate(Node* node, int key) {
        while (node) {
            if (node->data == key) return true;
            if (key < node->data) node = node->left;
            else node = node->right;
        }
        return false;
    }
};

void printLikeTree(Node* root) {
    cout << endl;
    Node* curNode = root;
    int level = 0;
    queue<Node*> q;
    q.push(curNode);

    while (!q.empty()) {
        if (!curNode) {
            break;
        }
        int num = 10;
        while (num - level > 0) {
            cout << "  ";
            num -= (level + 1) * 1.2;
        }
        cout << curNode->data << " ";
        level++;
        if (curNode->left)
            q.push(curNode->left);
        if (curNode->right)
            q.push(curNode->right);
        if (level == 1 || level == 3 || level == 7) {
            cout << endl << endl;
        }
        q.pop();
        curNode = q.front();
    }
}

int main() {
    BSTree tree{ 5, 3, 4, 2, 10, 9, 11 };
    printLikeTree(tree.getRoot());
    int key = 4;
    if (tree.searchNode(key)) {
        cout << "Node with a key " << key << " is found." << endl;
    }
    else {
        cout << "Node with a key " << key << " isn't found." << endl;
    }

    return 0;
}
