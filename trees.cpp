#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <algorithm>
#include "tree-node.h"

using namespace std;

int randomInt() // generate random int between 1 - 100 inclusive
{
    int randNum = (rand() % 100) + 1;
    return randNum;
}

int partition(vector<int> &vals, int start, int end) // helper function for quickSort()
{

    int pivot = vals[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; j++)
    {
        if (vals[j] < pivot)
        {
            i++;
            int temp = vals[i];
            vals[i] = vals[j];
            vals[j] = temp;
        }
    }
    i++;
    int temp = vals[i];
    vals[i] = vals[end];
    vals[end] = temp;

    return i;
}

void quickSort(vector<int> &vals, int start, int end) // will be used to sort values taken from a random, unsorted tree
{
    if (end <= start)
        return;

    int pivot = partition(vals, start, end);
    quickSort(vals, start, pivot - 1);
    quickSort(vals, pivot + 1, end);
}

void showMenu()
{
    cout << endl
         << "  [1]: Display tree" << endl
         << "  [2]: Print tree contents in Pre-Order sequence" << endl
         << "  [3]: Print tree contents in In-Order sequence" << endl
         << "  [4]: Print tree contents in Post-Order sequence" << endl
         << "  [5]: Find the size of the tree" << endl
         << "  [6]: Sort the tree" << endl
         << "  [7]: Insert new node" << endl
         << "  [8]: Remove a node" << endl
         << "  [9]: Search the tree for a value" << endl
         << "  [0]: Exit"
         << endl
         << endl;
}

int menuSelection()
{
    cout << "Make a selection: ";
    int selection;
    cin >> selection;

    while (selection < 0 || selection > 9)
    {
        cout << "Make a valid selection: ";
        cin >> selection;
    }

    return selection;
}

int main()
{
    srand(time(NULL));

    cout << endl
         << "Hello and welcome to my AWESOME Binary Search Tree program!" << endl
         << endl
         << "We're here for one reason so let's get right into it. " << endl
         << "We'll start by generating a random tree, " << endl
         << "but you can decide how large you want the starting tree to be (how many nodes)." << endl
         << "So, how large should we make the starting tree? (For printing output, probably between 20 - 30 is best)" << endl
         << endl
         << "Enter a number (between 1 - 100): ";

    int numNodes = 0;
    cin >> numNodes;
    cout << endl;
    while (numNodes < 1 || numNodes > 100)
    {
        cout
            << "Enter a valid number: ";
        cin >> numNodes;
    }

    Tree tree;
    vector<int> treeContains; // vector used to ensure unique treeNode values (no duplicates)

    for (int i = 0; i < numNodes; i++)
    {
        int randomData = randomInt();                                                         // generate random int
        if (find(treeContains.begin(), treeContains.end(), randomData) != treeContains.end()) // ensure random int has not been used yet
        {
            while (find(treeContains.begin(), treeContains.end(), randomData) != treeContains.end())
            {
                randomData = randomInt(); // if random int has already been used, roll again
            }
        }
        int direction = tree.rollLR();                  // decide left or right path
        tree.generateRandomTree(randomData, direction); // create new treeNode with the random int and direction
        treeContains.push_back(randomData);             // append the random number to the list to check for duplicates in next iteration
    }

    vector<int> inOrderVals;
    tree.traverseInOrder(inOrderVals);
    int start = 0;
    int end = inOrderVals.size() - 1;
    quickSort(inOrderVals, start, end);

    cout << "Ok, great, we've got a tree now and we can do some stuff." << endl
         << "Here is a list of some operations to perform: " << endl;

    showMenu();
    int userNum = menuSelection();

    bool isSorted = false;

    if (numNodes == 1)
    {
        isSorted = true;
    }

    while (userNum != 0)
    {
        switch (userNum)
        {
        case 1:
            cout << endl
                 << "Printing tree:" << endl
                 << endl;
            tree.graphTree(0);
            break;
        case 2:
            cout << endl
                 << "Printing Pre-Order contents: ";
            tree.printPreOrder();
            cout << endl;
            break;
        case 3:
            cout << endl
                 << "Printing In-Order contents: ";
            tree.printInOrder();
            cout << endl;
            break;
        case 4:
            cout << endl
                 << "Printing Post-Order contents: ";
            tree.printPostOrder();
            cout << endl;
            break;
        case 5:
            cout << endl
                 << "The tree currently has " << tree.treeSize() << " nodes." << endl;
            break;
        case 6:
            if (isSorted == false)
            {
                tree.sortBST(inOrderVals, start, end);
                isSorted = true;
                cout << endl
                     << "The tree is now sorted." << endl;
            }
            else
            {
                cout << endl
                     << "The tree is already sorted." << endl;
            }
            break;
        case 7:
            if (isSorted == false)
            {
                char userYorN;
                cout << endl
                     << "The tree must be sorted before inserting new nodes." << endl
                     << endl
                     << "Sort now? ('Y' for 'yes', 'N' for 'no'): ";
                cin >> userYorN;
                while (userYorN != 'Y' && userYorN != 'y' && userYorN != 'N' && userYorN != 'n')
                {
                    cout << "Make a valid selection: ";
                    cin >> userYorN;
                }
                if (userYorN == 'Y' || userYorN == 'y')
                {
                    tree.sortBST(inOrderVals, start, end);
                    isSorted = true;
                    cout << endl
                         << "The tree is now sorted." << endl;
                    int insertNum;
                    cout << endl
                         << "Enter a number to insert (duplicates will be ignored): ";
                    cin >> insertNum;
                    if (tree.contains(insertNum))
                    {
                        cout << endl
                             << insertNum << " is already in the tree." << endl;
                    }
                    else
                    {
                        cout << endl
                             << insertNum << " has been inserted. " << endl;
                        tree.insert(insertNum);
                    }
                }
                else
                    break;
            }
            else
            {
                int insertNum;
                cout << endl
                     << "Enter a number to insert (duplicates will be ignored): ";
                cin >> insertNum;
                if (tree.contains(insertNum))
                {
                    cout << endl
                         << insertNum << " is already in the tree." << endl;
                }
                else
                {
                    cout << endl
                         << insertNum << " has been inserted. " << endl;
                    tree.insert(insertNum);
                }
            }
            break;
        case 8:
            if (isSorted == false)
            {
                char userYorN;
                cout << endl
                     << "The tree must be sorted before removing nodes." << endl
                     << endl
                     << "Sort now? ('Y' for 'yes', 'N' for 'no'): ";
                cin >> userYorN;
                while (userYorN != 'Y' && userYorN != 'y' && userYorN != 'N' && userYorN != 'n')
                {
                    cout << "Make a valid selection: ";
                    cin >> userYorN;
                }
                if (userYorN == 'Y' || userYorN == 'y')
                {
                    tree.sortBST(inOrderVals, start, end);
                    isSorted = true;
                    cout << endl
                         << "The tree is now sorted." << endl;
                    int removeNum;
                    cout << endl
                         << "Enter a number to remove: ";
                    cin >> removeNum;
                    if (tree.contains(removeNum))
                    {
                        tree.remove(removeNum);
                        cout << endl
                             << removeNum << " has been removed from the tree." << endl;
                    }
                    else
                    {
                        cout << endl
                             << removeNum << " is not in the tree. " << endl;
                    }
                }
                else
                    break;
            }
            else
            {
                int removeNum;
                cout << endl
                     << "Enter a number to remove: ";
                cin >> removeNum;
                if (tree.contains(removeNum))
                {
                    tree.remove(removeNum);
                    cout << endl
                         << removeNum << " has been removed from the tree." << endl;
                }
                else
                {
                    cout << endl
                         << removeNum << " is not in the tree. " << endl;
                }
            }
            break;
        case 9:
            int searchNum;
            cout << endl
                 << "Enter a number to see if it is contained within the tree: ";
            cin >> searchNum;
            cout << endl;
            tree.search(searchNum);
            break;
        }
        showMenu();
        userNum = menuSelection();
    }

    cout << endl
         << "Thanks for checking out my AWESOME tree program!" << endl
         << endl;

    // original code
    // cout << "pre order:";
    // tree.printPreOrder();
    // cout << endl;

    // cout << "in order: ";
    // tree.printInOrder();
    // cout << endl;

    // cout << "post order: ";
    // tree.printPostOrder();
    // cout << endl;

    // cout << "tree size is: " << tree.treeSize() << endl;

    // tree.graphTree(0);
    // cout << endl;

    // vector<int> inOrderVals;
    // tree.traverseInOrder(inOrderVals);

    // int start = 0;
    // int end = inOrderVals.size() - 1;

    // quickSort(inOrderVals, start, end);

    // tree.sortBST(inOrderVals, start, end);
    // cout << "new pre order: ";
    // tree.printPreOrder();
    // cout << endl;
    // tree.graphTree(0);
    // cout << endl;

    // tree.insert(50);
    // tree.insert(53);
    // tree.insert(56);
    // tree.insert(59);
    // tree.insert(62);
    // tree.insert(65);
    // tree.insert(68);
    // tree.insert(71);
    // tree.insert(74);
    // tree.insert(77);
    // tree.insert(47);

    // tree.printPreOrder();
    // cout << endl;
    // tree.graphTree(0);
    // cout << endl;

    // tree.remove(68);
    // tree.printPreOrder();
    // cout << endl;
    // tree.graphTree(0);
    // cout << endl;

    // tree.search(77);

    return 0;
}