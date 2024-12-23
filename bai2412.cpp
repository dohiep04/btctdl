#include <iostream>
using namespace std;

struct Node {
    int khoa;
    Node* trai;
    Node* phai;
    int chieu_cao;
};

int layChieuCao(Node* node) {
    if (node == NULL)
        return 0;
    return node->chieu_cao;
}

Node* taoNode(int khoa) {
    Node* node = new Node();
    node->khoa = khoa;
    node->trai = NULL;
    node->phai = NULL;
    node->chieu_cao = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* xoayPhai(Node* y) {
    Node* x = y->trai;
    Node* T2 = x->phai;

    x->phai = y;
    y->trai = T2;

    y->chieu_cao = max(layChieuCao(y->trai), layChieuCao(y->phai)) + 1;
    x->chieu_cao = max(layChieuCao(x->trai), layChieuCao(x->phai)) + 1;

    return x;
}

Node* xoayTrai(Node* x) {
    Node* y = x->phai;
    Node* T2 = y->trai;

    y->trai = x;
    x->phai = T2;

    x->chieu_cao = max(layChieuCao(x->trai), layChieuCao(x->phai)) + 1;
    y->chieu_cao = max(layChieuCao(y->trai), layChieuCao(y->phai)) + 1;

    return y;
}

int layHeSoCanBang(Node* node) {
    if (node == NULL)
        return 0;
    return layChieuCao(node->trai) - layChieuCao(node->phai);
}

Node* themNode(Node* node, int khoa) {
    if (node == NULL)
        return taoNode(khoa);

    if (khoa < node->khoa)
        node->trai = themNode(node->trai, khoa);
    else if (khoa > node->khoa)
        node->phai = themNode(node->phai, khoa);
    else
        return node;

    node->chieu_cao = 1 + max(layChieuCao(node->trai), layChieuCao(node->phai));

    int can_bang = layHeSoCanBang(node);

    if (can_bang > 1 && khoa < node->trai->khoa)
        return xoayPhai(node);

    if (can_bang < -1 && khoa > node->phai->khoa)
        return xoayTrai(node);

    if (can_bang > 1 && khoa > node->trai->khoa) {
        node->trai = xoayTrai(node->trai);
        return xoayPhai(node);
    }

    if (can_bang < -1 && khoa < node->phai->khoa) {
        node->phai = xoayPhai(node->phai);
        return xoayTrai(node);
    }

    return node;
}

void duyetTrungVi(Node* root) {
    if (root != NULL) {
        duyetTrungVi(root->trai);
        cout << root->khoa << " ";
        duyetTrungVi(root->phai);
    }
}

int main() {
    Node* root = NULL;

    int day_so[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(day_so) / sizeof(day_so[0]);

    for (int i = 0; i < n; i++) {
        root = themNode(root, day_so[i]);
    }

    cout << "Duyet cay theo thu tu trung vi: ";
    duyetTrungVi(root);
    cout << endl;

    return 0;
}

