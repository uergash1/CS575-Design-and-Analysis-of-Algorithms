#include <iostream>
//#include <iomanip>

using namespace std;

#include "BST.h"

//--- Definition of constructor
BST::BST()
: myBinRoot(0), myAvlRoot(0)
{}

bool BST::empty() const
{
	return myBinRoot == 0;
}

/***** Function Members for BinNode class *****/

bool BST::search(const int & item) const
{
	BinNode * locptr = myBinRoot;
	bool found = false;
	while (!found && locptr != 0)
	{
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	return found;
}

void BST::insertBinNode(const int & item)
{
	BinNode * locptr = myBinRoot;   // search pointer
	BinNode * parent = 0;        // pointer to parent of current node
	bool found = false;     // indicates if item already in BST
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	if (!found)
	{                                 // construct node containing item
		locptr = new BinNode(item);
		if (parent == 0)               // empty tree
			myBinRoot = locptr;
		else if (item < parent->data)  // insert to left of parent
			parent->left = locptr;
		else                           // insert to right of parent
			parent->right = locptr;
	}
	else
		cout << "Item already in the tree\n";
}

void BST::preOrder(BinNode* root)
{
	if (root == 0) return;
	cout << root->data << " ";
	preOrder(root->left);
	preOrder(root->right);
}

void BST::inOrder(BinNode* root)
{
	if (root == 0) return;
	inOrder(root->left);
	cout << root->data << " ";
	inOrder(root->right);
}

int BST::nodeCount(BinNode* root)
{
	if (root == NULL) { //This node doesn't exist. Therefore there are no nodes in this 'subtree'
		return 0;
	}
	else { //Add the size of the left and right trees, then add 1 (which is the current node)
		return nodeCount(root->left) + nodeCount(root->right) + 1;
	}
}

void BST::removeBinNode(int data)
{
	BinNode* parent = myBinRoot;
	BinNode* node = myBinRoot;
	// Finds the node with given data
	bool found = false;
	while (!found && node != NULL)
	{
		if (data < node->data)       // descend left
		{
			parent = node;
			node = node->left;
		}
		else if (node->data < data)  // descend right
		{
			parent = node;
			node = node->right;
		}
		else                           // item found
			found = true;
	}

	if (found)
	{
		// The node has no children
		if (node->left == NULL && node->right == NULL)
		{
			parent->right == node ? parent->right = NULL : parent->left = NULL;
			delete node;
		}
		// The node has only one right child
		else if (node->left == NULL)
		{
			parent->right == node ? parent->right = node->right : parent->left = node->right;
			delete node;
		}
		// The node has only one left child
		else if (node->right == NULL)
		{
			parent->right == node ? parent->right = node->left : parent->left = node->left;
			delete node;
		}
		// The node has two children
		else if (node->left != NULL && node->right != NULL)
		{
			// Finds a node with minimum data - leftmost node on the right side of the given node
			BinNode* minRightNode = node->right;
			BinNode* parentMinRightNode = node;
			while (minRightNode->left != NULL)
			{
				parentMinRightNode = minRightNode;
				minRightNode = minRightNode->left;
			}

			// Logic for deleting the node
			if (parent == node) // case when node for deleting is root node
			{
				if (parentMinRightNode == node)
				{
					minRightNode->left = node->left;
					myBinRoot = minRightNode;
					node = NULL;
				}
				else
				{
					minRightNode->right == NULL ? parentMinRightNode->left = NULL : parentMinRightNode->left = minRightNode->right;
					minRightNode->left = node->left;
					minRightNode->right = node->right;
					myBinRoot = minRightNode;
					node = NULL;
				}
			}
			else if (parentMinRightNode != node)
			{
				parent->right == node ? parent->right = minRightNode : parent->left = minRightNode;
				minRightNode->right == NULL ? parentMinRightNode->left = NULL : parentMinRightNode->left = minRightNode->right;
				minRightNode->right = node->right;
				minRightNode->left = node->left;
			}
			else
			{
				parent->right == node ? parent->right = minRightNode : parent->left = minRightNode;
				minRightNode->left = node->left;
			}
			delete node;

		}
		cout << "Inorder print: ";
		this->inOrder(myBinRoot);
	}
	else
		cout << "Node is not found!";
}


/***** Function Members for AVLNode class *****/
void BST::AVLNode::updateHeight()
{
	int lHeight = 0;
	int rHeight = 0;

	if (left != NULL)
		lHeight = left->height;

	if (right != NULL)
		rHeight = right->height;

	int max = (lHeight > rHeight) ? lHeight : rHeight;
	this->height = max + 1;

	if (this->parent != NULL)
		this->parent->updateHeight();
}

void BST::insertAVLNode(int item)
{
	AVLNode * locptr = myAvlRoot;      // search pointer
	AVLNode * parent = 0;              // pointer to parent of current node
	bool found = false;                // indicates if item already in BST
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}

	if (!found)
	{                                 // construct node containing item
		locptr = new AVLNode(item);
		if (parent == 0)               // empty tree
		{
			myAvlRoot = locptr;
			locptr->updateHeight();
		}
		else if (item < parent->data)  // insert to left of parent
		{
			parent->left = locptr;
			locptr->parent = parent;
			locptr->updateHeight();
			rebalance(locptr);
		}
		else                           // insert to right of parent
		{
			parent->right = locptr;
			locptr->parent = parent;
			locptr->updateHeight();
			rebalance(locptr);
		}
	}
	else
		cout << "Item already in the tree\n";

}

void BST::rebalance(AVLNode* node)
{
	bool flag = false;
	int hDifference = getDifference(node);
	if (hDifference > 1)
	{
		if (getDifference(node->left) > 0) {
			flag = true;
			node = rotateRight(node);
		}
		else {
			flag = true;
			node = rotateLeftRight(node);
		}
	}
	else if (hDifference < -1)
	{
		if (getDifference(node->right) < 0) {
			flag = true;
			node = rotateLeft(node);
		}
		else {
			flag = true;
			node = rotateRightLeft(node);
		}
	}

	if (node->parent != NULL)
		rebalance(node->parent);

	if (flag == true && node->parent == NULL)
	{
		myAvlRoot = node;
		flag = false;
	}

}

int BST::getDifference(AVLNode* node)
{
	int lHeight = 0;
	int rHeight = 0;
	if (node->left != NULL)
		lHeight = node->left->height;
	if (node->right != NULL)
		rHeight = node->right->height;
	return lHeight - rHeight;
}

void BST::removeAvlNode(int data)
{
	AVLNode* parent = myAvlRoot;
	AVLNode* node = myAvlRoot;
	// Finds the node with given data
	bool found = false;
	while (!found && node != NULL)
	{
		if (data < node->data)       // descend left
		{
			parent = node;
			node = node->left;
		}
		else if (node->data < data)  // descend right
		{
			parent = node;
			node = node->right;
		}
		else                           // item found
			found = true;
	}

	if (found)
	{
		// The node has no children
		if (node->left == NULL && node->right == NULL)
		{
			parent->right == node ? parent->right = NULL : parent->left = NULL;
			parent->updateHeight();
			rebalance(parent);
			node = NULL;
			delete node;
		}
		// The node has only one right child
		else if (node->left == NULL)
		{
			parent->right == node ? parent->right = node->right : parent->left = node->right;
			node->right->parent = parent;
			node = NULL;
			delete node;
			parent->right->updateHeight();
			rebalance(parent->right);

		}
		// The node has only one left child
		else if (node->right == NULL)
		{
			parent->right == node ? parent->right = node->left : parent->left = node->left;
			node->left->parent = parent;
			node = NULL;
			delete node;
			parent->left->updateHeight();
			rebalance(parent->left);
		}
		// The node has two children
		else if (node->left != NULL && node->right != NULL)
		{
			// Finds a node with minimum data - leftmost node on the right side of the given node
			AVLNode* minRightNode = node->right;
			AVLNode* parentMinRightNode = node;
			while (minRightNode->left != NULL)
			{
				parentMinRightNode = minRightNode;
				minRightNode = minRightNode->left;
			}

			// Logic for deleting the node
			if (parent == node) // case when node for deleting is root node
			{
				if (parentMinRightNode == node)
				{
					minRightNode->left = node->left;
					node->left->parent = minRightNode;
					minRightNode->parent = NULL;
					myAvlRoot = minRightNode;
					node = NULL;
					delete node;
					minRightNode->updateHeight();
					rebalance(minRightNode);
				}
				else
				{
					if (minRightNode->right == NULL)
					{
						parentMinRightNode->left = NULL;
					}
					else
					{
						parentMinRightNode->left = minRightNode->right;
						minRightNode->right->parent = parentMinRightNode;
					}

					minRightNode->parent = NULL;
					node->left->parent = minRightNode;
					node->right->parent = minRightNode;

					minRightNode->left = node->left;
					minRightNode->right = node->right;
					myAvlRoot = minRightNode;
					node = NULL;
					delete node;
					parentMinRightNode->updateHeight();
					rebalance(parentMinRightNode);
				}
			}
			else if (parentMinRightNode != node)
			{
				parent->right == node ? parent->right = minRightNode : parent->left = minRightNode;
				minRightNode->parent = parent;

				parentMinRightNode->parent = minRightNode;

				if (node->left != NULL)
					node->left->parent = minRightNode;

				if (minRightNode->right == NULL)
				{
					parentMinRightNode->left = NULL;
				}
				else
				{
					parentMinRightNode->left = minRightNode->right;
					minRightNode->right->parent = parentMinRightNode;
				}

				minRightNode->right = node->right;
				minRightNode->left = node->left;
				node = NULL;
				delete node;
				parentMinRightNode->updateHeight();
				rebalance(parentMinRightNode);
			}
			else
			{
				parent->right == node ? parent->right = minRightNode : parent->left = minRightNode;
				minRightNode->parent = parent;

				if (node->left != NULL)
				{
					minRightNode->left = node->left;
					node->left->parent = minRightNode;
				}
				node = NULL;
				delete node;
				minRightNode->updateHeight();
				rebalance(minRightNode);
			}


		}
		/*cout << "Inorder print: ";
		this->inOrder(myAvlRoot);*/
	}
	else
		cout << "Node is not found!";
}

void BST::inOrder(AVLNode* root)
{
	if (root == 0) return;
	inOrder(root->left);
	cout << "Data: " << root->data << "; Height: " << root->height << endl;
	inOrder(root->right);
}