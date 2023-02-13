#include <iostream>
#include <vector>
#include "tree-node.h"

using namespace std;

Tree::Tree()
{
    root = NULL;
}

int Tree::rollLR()
{
    int randNum = (rand() % 100) + 1;
    return randNum;
}

void Tree::generateRandomTree(int val, int num)
{
    treeNode *newNode = new treeNode;
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;
        return;
    }

    treeNode *p = root;

    int leftOrRight = num;

    while (p)
    {
        if (leftOrRight % 2 == 0)
        {
            if (p->left == NULL)
            {
                p->left = newNode;
                break;
            }
            p = p->left;
            leftOrRight = rollLR();
        }
        else
        {
            if (leftOrRight % 2 == 1)
            {
                if (p->right == NULL)
                {
                    p->right = newNode;
                    break;
                }
                p = p->right;
                leftOrRight = rollLR();
            }
        }
    }
}

void Tree::graphTree(int num)
{
    graphTreePvt(root, num);
}

void Tree::graphTreePvt(treeNode *root, int space)
{
    if (root == NULL)
    {
        return;
    }

    space += 10;
    graphTreePvt(root->right, space);
    cout << endl;
    for (int i = 10; i < space; i++)
    {
        cout << " ";
    }
    cout << root->data << endl;
    graphTreePvt(root->left, space);
}

void Tree::printPreOrder()
{
    printPreOrderPvt(root);
}

void Tree::printPreOrderPvt(treeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->data << " ";
    printPreOrderPvt(root->left);
    printPreOrderPvt(root->right);
}

void Tree::printInOrder()
{
    printInOrderPvt(root);
}

void Tree::printInOrderPvt(treeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printInOrderPvt(root->left);
    cout << root->data << " ";
    printInOrderPvt(root->right);
}

void Tree::printPostOrder()
{
    printPostOrderPvt(root);
}

void Tree::printPostOrderPvt(treeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printPostOrderPvt(root->left);
    printPostOrderPvt(root->right);
    cout << root->data << " ";
}

int Tree::treeSize()
{
    return treeSizePvt(root);
}

int Tree::treeSizePvt(treeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + treeSizePvt(root->left) + treeSizePvt(root->right);
    }
};

void Tree::traverseInOrder(vector<int> &vals)
{
    traverseInOrderPvt(root, vals);
}

void Tree::traverseInOrderPvt(treeNode *root, vector<int> &vals)
{
    if (root == NULL)
    {
        return;
    }
    traverseInOrderPvt(root->left, vals);
    vals.push_back(root->data);
    traverseInOrderPvt(root->right, vals);
}

Tree::treeNode *Tree::listToBST(treeNode *root, vector<int> vals, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int midpoint = start + (end - start) / 2;
    treeNode *node = new treeNode;
    node->data = vals[midpoint];
    node->left = listToBST(node, vals, start, midpoint - 1);
    node->right = listToBST(node, vals, midpoint + 1, end);

    return node;
}

void Tree::buildBST(treeNode *&root, vector<int> vals, int start, int end)
{
    root = listToBST(root, vals, start, end);
}

void Tree::sortBST(vector<int> vals, int start, int end)
{
    buildBST(root, vals, start, end);
}

Tree::treeNode *Tree::minValPvt(treeNode *root)
{
    treeNode *p = root;
    while (p && p->left != NULL)
    {
        p = p->left;
    }
    return p;
}

void Tree::insert(int val)
{
    insertPvt(root, val);
}

Tree::treeNode *Tree::insertPvt(treeNode *root, int val)
{
    if (root == NULL)
    {
        treeNode *newNode = new treeNode;
        newNode->data = val;
        newNode->left = NULL;
        newNode->right = NULL;
        root = newNode;
        return root;
    }

    treeNode *p = root;
    while (p)
    {
        if (p->data == val)
        {
            return root;
        }
        else if (p->data < val)
        {
            if (p->right != NULL)
            {
                p = p->right;
            }
            else
            {
                treeNode *newNode = new treeNode;
                newNode->data = val;
                newNode->left = NULL;
                newNode->right = NULL;
                p->right = newNode;
                break;
            }
        }
        else
        {
            if (p->left != NULL)
            {
                p = p->left;
            }
            else
            {
                treeNode *newNode = new treeNode;
                newNode->data = val;
                newNode->left = NULL;
                newNode->right = NULL;
                p->left = newNode;
                break;
            }
        }
    }
    return root;
}

void Tree::remove(int val)
{
    removePvt(root, val);
}

Tree::treeNode *Tree::removePvt(treeNode *root, int val)
{
    if (root == NULL)
    {
        return root;
    }
    if (val < root->data)
    {
        root->left = removePvt(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = removePvt(root->right, val);
    }
    else
    {
        if (root->left == NULL)
        {
            treeNode *p = root->right;
            delete root;
            return p;
        }
        else if (root->right == NULL)
        {
            treeNode *p = root->left;
            delete root;
            return p;
        }
        treeNode *p = minValPvt(root->right);
        root->data = p->data;
        root->right = removePvt(root->right, p->data);
    }
    return root;
}

bool Tree::search(int val)
{
    return searchPvt(root, val);
}

bool Tree::searchPvt(treeNode *root, int val)
{
    int depth = 0;
    treeNode *p = new treeNode;
    p = root;

    while (p)
    {
        if (p->data == val)
        {
            cout << val << " was found at depth: " << depth << endl;
            return true;
        }
        else if (p->data > val)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
        depth++;
    }

    cout << val << " was not found." << endl;
    return false;
}

bool Tree::contains(int val)
{
    return containsPvt(root, val);
}

bool Tree::containsPvt(treeNode *root, int val)
{
    treeNode *p = new treeNode;
    p = root;

    while (p)
    {
        if (p->data == val)
        {
            return true;
        }
        else if (p->data > val)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return false;
}