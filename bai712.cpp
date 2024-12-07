#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char val) : value(val), left(NULL), right(NULL) {}
};

class ExpressionTree {
private:
    Node* root;

    void infix(Node* node, string& result) {
        if (node == NULL) return;
        result += "(";
        infix(node->left, result);
        result += node->value;
        infix(node->right, result);
        result += ")";
    }

    void postfix(Node* node, string& result) {
        if (node == NULL) return;
        postfix(node->left, result);
        postfix(node->right, result);
        result += node->value;
    }

    void prefix(Node* node, string& result) {
        if (node == NULL) return;
        result += node->value;
        prefix(node->left, result);
        prefix(node->right, result);
    }

public:
    ExpressionTree() : root(NULL) {}

    void buildFromPostfix(const string& postfix) {
        stack<Node*> st;

        for (size_t i = 0; i < postfix.length(); ++i) {
            char ch = postfix[i];
            Node* newNode = new Node(ch);

            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                newNode->right = st.top(); st.pop();
                newNode->left = st.top(); st.pop();
            }
            st.push(newNode);
        }

        root = st.top();
    }

    string infix() {
        string result;
        infix(root, result);
        return result;
    }

    string postfix() {
        string result;
        postfix(root, result);
        return result;
    }

    string prefix() {
        string result;
        prefix(root, result);
        return result;
    }
};

int main() {
    string expression = "ab+cd*e+*";
    ExpressionTree tree;
    tree.buildFromPostfix(expression);

    cout << "Trung to (Infix): " << tree.infix() << endl;
    cout << "Hau to (Postfix): " << tree.postfix() << endl;
    cout << "Tien to (Prefix): " << tree.prefix() << endl;

    return 0;
}

