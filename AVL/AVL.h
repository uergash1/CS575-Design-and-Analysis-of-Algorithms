#include <iostream>
using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

class BST
{
private:
	/***** Node class *****/
	class BinNode
	{
	public:
		int data;
		BinNode * left;
		BinNode * right;

		// BinNode constructors
		// Default -- data part is default int value; both links are null.
		BinNode()
			: left(0), right(0)
		{}

		// Explicit Value -- data part contains item; both links are null.
		BinNode(int item)
			: data(item), left(0), right(0)
		{}

	};// end of class BinNode declaration

private:
	class AVLNode
	{
	public:
		int data;
		AVLNode* parent;
		AVLNode* left;
		AVLNode* right;
		int height;

		AVLNode()
			: left(0), right(0), height(0)
		{}

		AVLNode(int item)
			: data(item), left(0), right(0), height(0)
		{}

		void updateHeight(); //
	};

	/***** Data Members *****/
	BinNode* myBinRoot;
	AVLNode* myAvlRoot;

public:
	/***** Function Members *****/
	BST();

	void insert(int item);
	void rebalance(AVLNode* node);
	int getDifference(AVLNode* node);
	void inOrder(AVLNode* root);
	void removeAvlNode(int data);
	AVLNode* getMyAvlRoot() { return myAvlRoot; };
	
	AVLNode* rotateLeft(AVLNode* node)
	{
		AVLNode* temp = node->right;
		node->right = temp->left;

		if (node->parent != NULL)
		{
			temp->parent = node->parent;

			if (node->parent->left == node)
				node->parent->left = temp;
			else
				node->parent->right = temp;
		}
		else
		{
			temp->parent = NULL;
		}

		if (temp->left != NULL) temp->left->parent = node;
		
		temp->left = node;

		node->parent = temp;

		//update the Nodes new height
		node->updateHeight();

		return temp;
	}

	//Rotate a Node branch to the right, in order to balance things
	AVLNode* rotateRight(AVLNode* node)
	{
		AVLNode* temp = node->left;
		node->left = temp->right;
		
		if (node->parent != NULL)
		{
			temp->parent = node->parent;

			if (node->parent->left == node)
				node->parent->left = temp;
			else
				node->parent->right = temp;
		}
		else
		{
			temp->parent = NULL;
		}

		if (temp->right != NULL) temp->right->parent = node;

		temp->right = node;

		node->parent = temp;
		


		//update the Nodes new height
		node->updateHeight();

		return temp;
	}

	//Rotate a Node branch to the right then the left, in order to balance things
	AVLNode* rotateRightLeft(AVLNode* node)
	{
		AVLNode* temp = node->right;
		node->right = rotateRight(temp);
		return rotateLeft(node);
	}

	//Rotate a Node branch to the left then the right, in order to balance things
	AVLNode* rotateLeftRight(AVLNode* node)
	{
		AVLNode* temp = node->left;
		node->left = rotateLeft(temp);
		return rotateRight(node);
	}

}; // end of class declaration

#endif
