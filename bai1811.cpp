#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <set>
using namespace std;

struct Node {
    string word;
    Node* next;
};

void append(Node*& head, const string& word) {
    Node* newNode = new Node{word, NULL};
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void displayList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->word << " ";
        temp = temp->next;
    }
    cout << endl;
}

string findMostFrequent(Node* head) {
    map<string, int> freq;
    Node* temp = head;
    while (temp) {
        freq[temp->word]++;
        temp = temp->next;
    }
    string mostFrequent;
    int maxCount = 0;

    for (map<string, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        if (it->second > maxCount) {
            maxCount = it->second;
            mostFrequent = it->first;
        }
    }
    return mostFrequent;
}

void removeReduplications(Node*& head) {
    set<string> uniqueWords;
    Node* temp = head;
    Node* prev = NULL;
    while (temp) {
        if (uniqueWords.count(temp->word)) {
            Node* toDelete = temp;
            if (prev) prev->next = temp->next;
            else head = temp->next;
            temp = temp->next;
            delete toDelete;
        } else {
            uniqueWords.insert(temp->word);
            prev = temp;
            temp = temp->next;
        }
    }
}

int countWords(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

int main() {
    Node* head = NULL;
    string sentence;
    cout << "Nhap mot cau: ";
    getline(cin, sentence);
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        append(head, word);
    }
    cout << "Danh sach cac tu: ";
    displayList(head);
    string mostFrequent = findMostFrequent(head);
    cout << "Tu xuat hien nhieu nhat: " << mostFrequent << endl;
    removeReduplications(head);
    cout << "Danh sach sau khi loai bo tu lay: ";
    displayList(head);
    int wordCount = countWords(head);
    cout << "So tu vung xuat hien: " << wordCount << endl;
    return 0;
}

