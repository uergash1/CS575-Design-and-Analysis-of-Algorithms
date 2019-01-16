#include <iostream>
#include <math.h>
#include <algorithm>
#include <limits.h>
using namespace std;

//Function to display the table
void displayTable(int** table, int V)
{
	cout << "#" << "\t";
	for (int i = 0; i < V - 1; i++)
		cout << "D(" << i + 2 << ")\t";
	cout << endl;

	for (int i = 0; i < V; i++)
	{
		cout << i + 1 << ".\t";
		for (int j = 0; j < V - 1; j++)
		{
			table[i][j] == INT_MAX ? cout << INFINITY << "\t" : cout << table[i][j] << "\t";
		}
		cout << endl;
	}
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

int** dijkstraMst(int** adjMat, int V)
{
	int minLastRowIndex; //variable to store index of minimum value of last row
	int minVal = INT_MAX; 
	int minIndex;
	int** table = new int*[V]; //DP table
	bool* takenVertex = new bool[V]; //array to keep track which vertex is taken 
	int* parent = new int[V]; //array to keep track of parent of each vertex

	for (int i = 0; i < V; i++)
	{
		takenVertex[i] = false;
		table[i] = new int[V - 1];
	}

	takenVertex[0] = true; //by default first vertex is taken
	parent[0] = INT_MAX; //there is no parent of first vertex

	for (int i = 0; i < V; i++)
	{
		for (int j = 1; j < V; j++)
		{
			if (i == 0) //initialization - step 2 in DP
			{
				table[i][j - 1] = adjMat[i][j];
				parent[j] = i;

				if (minVal > adjMat[i][j])
				{
					minVal = adjMat[i][j];
					minIndex = j;
				}
			}
			else if (i == V - 1) //last row of table is repeated
			{
				table[i][j - 1] = table[i - 1][j - 1];
			}
			else
			{
				if (takenVertex[j] == true) //if current vertex is already taken, then upper value is just copied
				{
					table[i][j - 1] = table[i - 1][j - 1];
				}
				else
				{
					adjMat[minLastRowIndex + 1][j] == INT_MAX ? table[i][j - 1] = table[i - 1][j - 1] : table[i][j - 1] = min(table[i - 1][j - 1], table[i - 1][minLastRowIndex] + adjMat[minLastRowIndex + 1][j]);

					//if value of the current cell is changed, then we assign a new parent
					if (table[i][j - 1] == table[i - 1][minLastRowIndex] + adjMat[minLastRowIndex + 1][j])
						parent[j] = minLastRowIndex + 1;

					//keeping track of min value of current row
					if (minVal > table[i][j - 1])
					{
						minVal = table[i][j - 1];
						minIndex = j;
					}
				}
			}
		}
		minLastRowIndex = minIndex - 1;
		takenVertex[minIndex] = true;
		minVal = INT_MAX;
	}
	showPath(parent, V);
	return table;
}

int main()
{
	int V; //number of vertices
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

	int** table = dijkstraMst(adjMat, V);
	displayTable(table, V);

	cout << "\n\n";

	system("pause");
	return 0;
}

