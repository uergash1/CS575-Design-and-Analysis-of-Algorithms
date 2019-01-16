#include <iostream>
#include <algorithm> 
using namespace std;

// Function to test the code by showing the table
void ShowDDTable(int** table, int n, int V)
{
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < V + 1; j++)
		{
			cout << table[i][j] << "\t";
		}

		cout << "\n";
	}
}

// Function that fills and calculates minimum number of coin exchanges 
int DifferentDenominations(int** table, int* coin, int V, int n)
{
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < V + 1; j++)
		{
			// Initialize - step 2 in dynamic programming
			if (i == 0 || j == 0)
			{
				table[i][j] = 0;
				continue;
			}

			if (i == 1)
			{
				table[i][j] = j;
				continue;
			}

			// If jth amount of money is equal or more than (i-1)th coin, we calculate (i,j) cell according bellow given formula
			// Otherwise, we copy value from above cell
			if (j >= coin[i - 1])
			{
				table[i][j] = min(table[i - 1][j], 1 + table[i][j - coin[i - 1]]);
			}
			else
			{
				table[i][j] = table[i - 1][j];
			}
		}
	}

	return table[n][V];
}

// Function that finds which coins should be taken according the table which was filled by DifferentDenominations function
int* Backtracking(int** table, int* coin, int n, int V)
{
	int i = n;
	int j = V;
	int* countCoins = new int[n];

	// Number of coins for each 
	for (int k = 0; k < n; k++)
		countCoins[k] = 0;

	while (j > 0)
	{
		// If value of i,jth cell is the same with the value of (i-1,j)th cell, then
		// pointer goes up.
		// If those two values are not the same, then
		// it means that (i-1)th coin was chosen to exchange, and 
		// pointer goes to (i,j-coin[i-1]) cell.
		if (table[i][j] == table[i - 1][j])
		{
			i = i - 1;
		}
		else
		{
			countCoins[i - 1]++;
			j = j - coin[i - 1];
		}
	}

	return countCoins;
}

//Driver function to lunch Different Denomination Coins
int main()
{
	char userAnswer = 'y';

	while (userAnswer == 'y')
	{
		int n; // Number of coins
		int V; // Amount of money that should be returned

		// Number of items
		cout << "Insert number of coin(s): ";
		cin >> n;

		cout << "First value of coin must be 1" << endl;

		// Values of coins
		cout << "Insert values coin(s):" << endl;
		int* coin = new int[n];
		for (int i = 0; i < n;)
		{
			int temp;
			cin >> temp;
			if (i == 0 && temp != 1)
			{
				cout << "Your fist value of coin is not 1, thus please repeat your first insert." << endl;
				continue;
			}
			coin[i] = temp;
			i++;
		}


		// Amount of money that should be exchanged
		cout << "Insert amount of money that should be exchanged: ";
		cin >> V;

		// Table defenition - step 1 in dynamic programming
		int **table = new int*[n + 1];
		for (int i = 0; i < n + 1; i++)
			table[i] = new int[V + 1];

		cout << "Minimum number exchanges: " << DifferentDenominations(table, coin, V, n) << endl << endl;

		ShowDDTable(table, n, V);

		int* countCoins = Backtracking(table, coin, n, V);

		cout << endl << "Coin(s) that should be used to exchange " << V << " cents:" << endl;

		int count = 0;
		for (int i = 0; i < n; i++)
		{
			if (countCoins[i] != 0)
				cout << ++count << ". Coin with denomination = " << coin[i] << " and number of coins = " << countCoins[i] << endl;
		}

		cout << endl << "Do you want to continue (y/n)? ";
		cin >> userAnswer;
	}

	return 0;
}