#include <iostream>
#include <algorithm> 
using namespace std;

// Function to test the code by showing the table
void ShowKnapsackTable(int** table, int n, int kw)
{
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < kw + 1; j++)
		{
			cout << table[i][j] << " ";
		}

		cout << "\n";
	}
}

// Function that returns maximum possible value of items that can fit knapsack
int Knapsack01(int** table, int kw, int* iw, int* iv, int n)
{
	for (int j = 0; j <= kw; j++)
	{
		for (int i = 0; i <= n; i++)
		{
			// Initializing the table - step 2 in dynamic programming
			if (j == 0 || i == 0)
			{
				table[i][j] = 0;
				continue;
			}

			// Filling the table - step 3 in dynamic programming
			// If weight of the i-th item is less or equal to Knapsack capacity j, then
			// this item can be included in the optimal solution - in this case value of (i,j) cell 
			// is max of iv[i - 1] + table[i - 1][j - iw[i - 1]], table[i - 1][j]
			// If weight of the i-th item is more than Knapsack capacity j, then
			// value of (i,j) cell is table[i - 1][j]
			if (j >= iw[i - 1])
			{
				table[i][j] = max(iv[i - 1] + table[i - 1][j - iw[i - 1]], table[i - 1][j]);
			}
			else
			{
				table[i][j] = table[i - 1][j];
			}
		}
	}

	// Output solution - step 4 in dynamic programming (maximum value of the items that knapsack can handle)
	return table[n][kw];
}

// Function for finding which items were taken into the knapsack
int* Backtracking(int** table, int n, int kw, int* iw)
{
	int count = 0;
	int i = n;
	int j = kw;
	int* takenItems = new int[n];

	// Maximum number of taken items can be n
	for (int k = 0; k < n; k++)
		takenItems[k] = -1;

	while (i > 0 && j > 0)
	{
		// If value of i,jth cell is the same with the value of i-1,jth cell, then
		// pointer goes up.
		// If those two values are not the same, then
		// it means that i-1th item was put into the knapsack, and 
		// pointer goes to i-1,j-iw[i-1] cell.
		if (table[i][j] == table[i - 1][j])
		{
			i = i - 1;
		}
		else
		{
			takenItems[count++] = i - 1;
			j = j - iw[i - 1];
			i = i - 1;
		}
	}

	return takenItems;
}

// Driver function to lunch knapsack program
int main()
{
	char userAnswer = 'y';

	while (userAnswer == 'y')
	{
		int n;
		int kw;

		// Number of items
		cout << "Insert number of item(s): ";
		cin >> n;

		// Weights of items
		cout << "Insert weight(s) of all " << n << " item(s)" << endl;
		int* iw = new int[n];
		for (int i = 0; i < n; i++)
			cin >> iw[i];

		// Values of items
		cout << "Insert respective values of all " << n << " element(s)" << endl;
		int* iv = new int[n];
		for (int i = 0; i < n; i++)
			cin >> iv[i];

		// Weight of knapsack
		cout << "Insert weight of knapsack: ";
		cin >> kw;

		// Table defenition - step 1 in dynamic programming
		int **table = new int*[n + 1];
		for (int i = 0; i <= n; i++)
			table[i] = new int[kw + 1];

		cout << "Maximum value that can be taken: " << Knapsack01(table, kw, iw, iv, n) << endl << endl;

		ShowKnapsackTable(table, n, kw);

		int* takenItems = Backtracking(table, n, kw, iw);

		cout << endl << "Items that were put into the knapsack: " << endl;

		int count = 0;
		for (int i = n - 1; i >= 0; i--)
		{
			if (takenItems[i] != -1)
				cout << ++count << ". Item with weight = " << iw[takenItems[i]] << " and value = " << iv[takenItems[i]] << endl;
		}

		cout << endl << "Do you want to continue (y/n)? ";
		cin >> userAnswer;
	}

	return 0;
}