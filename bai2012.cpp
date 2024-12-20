#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreeNode {
public:
    string title;
    int pages;
    string nodeType;
    vector<TreeNode*> children;

    TreeNode(string t, int p, string type) : title(t), pages(p), nodeType(type) {}

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    ~TreeNode() {
        for (size_t i = 0; i < children.size(); ++i) {
            delete children[i];
        }
    }
};

class Book {
private:
    vector<TreeNode*> chapters;

    int calculatePages(TreeNode* node) {
        int totalPages = node->pages;
        for (size_t i = 0; i < node->children.size(); ++i) {
            totalPages += calculatePages(node->children[i]);
        }
        return totalPages;
    }

    bool findAndRemove(TreeNode* parent, string title) {
        for (size_t i = 0; i < parent->children.size(); ++i) {
            if (parent->children[i]->title == title) {
                delete parent->children[i];
                parent->children.erase(parent->children.begin() + i);
                return true;
            }
            if (findAndRemove(parent->children[i], title)) {
                return true;
            }
        }
        return false;
    }

public:
    void addChapter(TreeNode* chapter) {
        chapters.push_back(chapter);
    }

    int countChapters() {
        return chapters.size();
    }

    TreeNode* findLongestChapter() {
        TreeNode* longestChapter = NULL ;
        int maxPages = 0;

        for (size_t i = 0; i < chapters.size(); ++i) {
            int totalPages = calculatePages(chapters[i]);
            if (totalPages > maxPages) {
                maxPages = totalPages;
                longestChapter = chapters[i];
            }
        }
        return longestChapter;
    }

    bool findAndRemove(string title) {
        for (size_t i = 0; i < chapters.size(); ++i) {
            if (chapters[i]->title == title) {
                delete chapters[i];
                chapters.erase(chapters.begin() + i);
                return true;
            }
            if (findAndRemove(chapters[i], title)) {
                return true;
            }
        }
        return false;
    }

    void printBook() {
        for (size_t i = 0; i < chapters.size(); ++i) {
            printNode(chapters[i], 0);
        }
    }

    void printNode(TreeNode* node, int level) {
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }
        cout << node->nodeType << ": " << node->title << " (" << node->pages << " pages)" << endl;

        for (size_t i = 0; i < node->children.size(); ++i) {
            printNode(node->children[i], level + 1);
        }
    }

    ~Book() {
        for (size_t i = 0; i < chapters.size(); ++i) {
            delete chapters[i];
        }
    }
};

int main() {
    Book book;

    TreeNode* chapter1 = new TreeNode("Chapter 1: Introduction", 10, "chapter");
    chapter1->addChild(new TreeNode("Section 1.1: Basics", 5, "section"));
    chapter1->addChild(new TreeNode("Section 1.2: Advanced", 8, "section"));

    TreeNode* chapter2 = new TreeNode("Chapter 2: Methods", 15, "chapter");
    chapter2->addChild(new TreeNode("Section 2.1: Overview", 7, "section"));
    chapter2->addChild(new TreeNode("Section 2.2: Implementation", 10, "section"));

    book.addChapter(chapter1);
    book.addChapter(chapter2);

    cout << "Total chapters: " << book.countChapters() << endl;

    TreeNode* longestChapter = book.findLongestChapter();
    if (longestChapter) {
        cout << "Longest chapter: " << longestChapter->title << endl;
    }

    cout << "\nBook structure:" << endl;
    book.printBook();

    cout << "\nRemoving 'Section 1.2: Advanced'..." << endl;
    book.findAndRemove("Section 1.2: Advanced");

    cout << "\nUpdated book structure:" << endl;
    book.printBook();

    return 0;
}

