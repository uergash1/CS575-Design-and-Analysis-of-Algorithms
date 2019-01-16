/*----- treetester.cpp -----------------------------------------------------
                Program for testing BST.
 ------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

#include "BST.h"

int main()
{
   // Testing Constructor and empty()
   BST intBST;            // test the class constructor

   cout << "\n\n /-------------------------- Binary Search Tree Test Part ------------------------------/\n\n";

   cout << "Constructing empty BST\n";
   cout << "BST " << (intBST.empty() ? "is" : "is not") << " empty\n";

   // Testing insert
   cout << "\nNow insert a bunch of integers into the BST."
           "\nTry items not in the BST and some that are in it:\n";
   int number;
   for (;;)
   {
      cout << "Item to insert (-999 to stop): ";
      cin >> number;
      if (number == -999) break;
	  intBST.insertBinNode(number);
   }

   cout << "BST " << (intBST.empty() ? "is" : "is not") << " empty\n";

   cout << "Preorder print: ";
   intBST.preOrder(intBST.getMyBinRoot());
   cout << endl;

   cout << "Inorder print: ";
   intBST.inOrder(intBST.getMyBinRoot());
   cout << endl;

   cout << "Number of nodes: " << intBST.nodeCount(intBST.getMyBinRoot());
   cout << endl;

   cout << "Insert node data that you want to delete: ";
   int data;
   cin >> data;
   intBST.removeBinNode(data);


   cout << "\n\n /-------------------------- AVL Tree Test Part ------------------------------/\n\n";

   int count;
   int avlData;
   BST avl;

   cout << "Insert quantity of numbers: ";
   cin >> count;

   cout << "Insert numbers into AVL tree" << endl;

   for (int i = 0; i < count; i++)
   {
	   cin >> avlData;
	   avl.insertAVLNode(avlData);
   }

   cout << endl << endl << "******** AVL tree *********" << endl;

   avl.inOrder(avl.getMyAvlRoot());

   int deleteAvl;
   cout << "\n\nInsert data to delete: ";
   cin >> deleteAvl;

   avl.removeAvlNode(deleteAvl);
   avl.inOrder(avl.getMyAvlRoot());

   system("pause");

}
