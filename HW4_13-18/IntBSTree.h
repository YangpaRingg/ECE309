#ifndef ECE309_EXAMPLES_SPR23_INTBSTREE_H
#define ECE309_EXAMPLES_SPR23_INTBSTREE_H

#include <list>

class IntBSTree {
private:
    // class for each node of the tree
    class BTNode {
    public:
        int data;
        BTNode* left;
        BTNode* right;
        BTNode(int d, BTNode* l=nullptr, BTNode* r=nullptr)
                : data(d), left(l), right (r) {}
    };

    BTNode* root { nullptr };

    bool removeNode(BTNode* cur, BTNode* parent);
    void deleteSubTree(BTNode*);
    void pushInOrder(BTNode* p, std::list<int> outList) const; // recursive helper function

public:
    IntBSTree() = default;
    ~IntBSTree();

    bool search(int key);
    void insert(int key);
    bool remove(int key);

    std::list<int> getOrderedList() const;

};



#endif //ECE309_EXAMPLES_SPR23_INTBSTREE_H
