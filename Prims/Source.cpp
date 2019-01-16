#include<iostream>
#include<queue>
#include<limits.h>
using namespace std;

// Prototype of a utility function to swap two integers
//void swap(Node *x, Node *y);

class Node
{
public:
	int key;
	int position;

	Node() {}

	Node(int k, int p)
	{
		key = k;
		position = p;
	}
};

// A class for Min Heap
class PriorityQueue
{
	Node* harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:
	// Constructor
	PriorityQueue(int capacity);

	// to heapify a subtree with root at given index
	void MinHeapify(int);

	int parent(int i) { return (i - 1) / 2; }

	// to get index of left child of node at index i
	int left(int i) { return (2 * i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2 * i + 2); }

	// to extract the root which is the minimum element
	int extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap
	int getMin() { return harr[0].position; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k, int pos);

	// Checks whether Priority Queue is empty
	bool isNonEmpty();
};

// Constructor: Builds a heap from a given array a[] of given size
PriorityQueue::PriorityQueue(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new Node[cap];
}

// Inserts a new key 'k'
void PriorityQueue::insertKey(int k, int pos)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	Node nd(k, pos);

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = nd;

	// Fix the min heap property if it is violated
	while (i != 0 && harr[parent(i)].key > harr[i].key)
	{
		/*Node temp = *x;
		*x = *y;
		*y = temp;*/

		swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void PriorityQueue::decreaseKey(int pos, int new_val)
{
	// Here, I am doing linear search. 
	// The reason is that in driver function I dont know index in heap of the value.
	// I know only position (index) of value in adjacency matrix
	int i;
	for (int j = 0; j < heap_size; j++)
	{
		if (harr[j].position == pos)
		{
			harr[j].key = new_val;
			i = j;
			break;
		}
	}
	
	while (i != 0 && harr[parent(i)].key > harr[i].key)
	{
		swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
int PriorityQueue::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0].position;
	}

	// Store the minimum value, and remove it from heap
	int root = harr[0].position;
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void PriorityQueue::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void PriorityQueue::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l].key < harr[i].key)
		smallest = l;
	if (r < heap_size && harr[r].key < harr[smallest].key)
		smallest = r;
	if (smallest != i)
	{
		swap(harr[i], harr[smallest]);
		MinHeapify(smallest);
	}
}

bool PriorityQueue::isNonEmpty()
{
	if (heap_size == 0)
		return false;
	else
		return true;
}

// A utility function to swap two elements
void swap(Node *x, Node *y)
{
	Node temp = *x;
	*x = *y;
	*y = temp;
}

int* Prim(int** adj, int V)
{
	int* parent = new int[V];
	parent[0] = INT_MAX;
	char* color = new char[V];
	int * key = new int[V];
	PriorityQueue pq(V);
	for (int i = 0; i < V; i++)
	{
		color[i] = 'w';
		if (i == 0)
		{
			key[0] = 0;
			pq.insertKey(0, i);
			continue;
		}
		key[i] = INT_MAX;
		pq.insertKey(INT_MAX, i);
	}

	while (pq.isNonEmpty())
	{
		int minVertex = pq.extractMin();
		for (int i = 0; i < V; i++)
		{
			if (adj[minVertex][i] != INT_MAX && color[i] == 'w' && adj[minVertex][i] < key[i])
			{
				key[i] = adj[minVertex][i];
				pq.decreaseKey(i, key[i]);
				parent[i] = minVertex;
			}
		}
		color[minVertex] = 'b';
	}
	return parent;
}

//Function to show full path for each vertex
void showPath(int* parent, int V)
{
	cout << "\nPath:" << endl;

	for (int i = V - 1; i > 0; i--)
	{
		int j = i;
		cout << i << " -> ";
		while (parent[j] != INT_MAX)
		{
			cout << parent[j] << " -> ";
			j = parent[j];
		}
		cout << "NIL";
		cout << endl;
	}

	cout << endl;
}

int main()
{
	int V;
	cout << "Insert number of vertices: ";
	cin >> V;

	int** adjMat = new int*[V]; //adjacency matrix
	for (int i = 0; i < V; i++)
		adjMat[i] = new int[V];

	cout << "Insert 0 for infinity";

	for (int i = 0; i < V; i++)
	{
		cout << "\nInsert adjacent weights for " << i + 1 << " vertex" << endl;

		for (int j = 0; j < V; j++)
		{
			int temp;
			cout << j + 1 << ". ";
			cin >> temp;
			temp == 0 ? adjMat[i][j] = INT_MAX : adjMat[i][j] = temp;
		}
	}

	int* parent = Prim(adjMat, V);
	showPath(parent, V);

	cout << endl;
	//system("pause");
	return 0;
}