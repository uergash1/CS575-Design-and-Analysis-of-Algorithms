#include <iostream>
#include <algorithm> 
using namespace std;

// Function for finding minimum number of exchanges 
int* MinCoinExchange(int V, int coin[], int n)
{
	// Array to store number exchanges for each coin
	int* count = new int[n];
	for (int i = 0; i < n; i++)
		count[i] = 0;

	// Because we make greedy choice, we start with the highest possible value of coin from the array
	int i = n - 1;

	// We continue exchanging while amount of money is 0 
	while (V > 0)
	{
		// If amount of money is more than ith coin, then we take ith coin and subtract from amount of money.
		// Otherwise, we consider (i-1)th coin. 
		if (V >= coin[i])
		{
			count[i]++;
			V -= coin[i];
		}
		else
		{
			i--;
		}
	}

	return count;
}

// Driver function to lunch Minimum Coin Exchange function
int main()
{
	char userAnswer = 'y';

	while (userAnswer == 'y')
	{
		int V; // amount of money that should be exchanged
		int n = 4; // number of coins
		int* coin = new int[] { 1, 5, 10, 25 }; // array to store value of coins

		cout << "Insert amount of money that should be exchanged: ";
		cin >> V;

		// array with number of exchanges for each coin
		int* count = MinCoinExchange(V, coin, n);

		cout << "In order to exchange " << V << " amount of money for coins with denominations";
		for (int i = 0; i < n; i++)
		{
			cout << ", " << coin[i];
		}

		cout << ", you need: " << endl;

		for (int i = n - 1; i >= 0; i--)
		{
			if (count[i] != 0)
			{
				cout << count[i] << " coin(s) with denomination " << coin[i] << endl;
			}
		}

		cout << endl << "Do you want to continue (y/n)? ";
		cin >> userAnswer;
	}

	return 0;
}