#include <iostream>
#include <vector>

using namespace std;

class Tree
{
private:
    struct treeNode
    {
        int data;
        treeNode *left;
        treeNode *right;
    };
    treeNode *root;
    void graphTreePvt(treeNode *, int);
    void printPreOrderPvt(treeNode *);
    void printInOrderPvt(treeNode *);
    void printPostOrderPvt(treeNode *);
    int treeSizePvt(treeNode *);
    void traverseInOrderPvt(treeNode *, vector<int> &);
    void buildBST(treeNode *&, vector<int>, int, int);
    treeNode *minValPvt(treeNode *);
    treeNode *insertPvt(treeNode *, int);
    treeNode *removePvt(treeNode *, int);
    bool searchPvt(treeNode *, int);
    bool containsPvt(treeNode *, int);

public:
    Tree();
    void generateRandomTree(int, int);                      // creates a new treeNode, places in random position
    void graphTree(int);                                    // displays a rough shape of the tree to the console
    void printPreOrder();                                   // prints tree vals in pre-order traversal
    void printInOrder();                                    // prints tree vals in in-order traversal
    void printPostOrder();                                  // prints tree vals in post-order traversal
    void traverseInOrder(vector<int> &);                    // traverses tree and copies vals to a vector
    int treeSize();                                         // returns number of nodes in tree
    int rollLR();                                           // used to decide left or right child
    treeNode *listToBST(treeNode *, vector<int>, int, int); // algorithm helper funciion for sortBST
    void sortBST(vector<int>, int, int);                    // use this function in main to sort BST
    void insert(int);                                       // insert new node into correct position (tree must be sorted with sortBST first), duplicates are not inserted
    void remove(int);                                       // remove a node from the tree if it exists
    bool search(int);                                       // finds a value in the tree, if it exists
    bool contains(int);
};
