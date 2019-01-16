#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

int lcs(int** table, char* xWord, char* yWord, int x, int y)
{

	for (int j = 0; j <= y; j++)
	{
		for (int i = 0; i <= x; i++)
		{
			if (i == 0 || j == 0)
			{
				table[i][j] = 0;
				continue;
			}

			if (xWord[i - 1] == yWord[j - 1])
				table[i][j] = table[i - 1][j - 1] + 1;
			else
				table[i][j] = max(table[i - 1][j], table[i][j - 1]);
		}
	}

	return table[x][y];
}

char* Backtracking(int** table, char* xWord, char* yWord, int x, int y, int lcsCount)
{
	int i = x;
	int j = y;
	lcsCount--;
	char* lcs = new char[lcsCount];
	//lcs[lcsCount] = '\0';

	// Maximum number of taken items can be n
	/*for (int k = 0; k < x; k++)
		lcs[k] = -1;*/

	while (i > 0 && j > 0)
	{
		// If value of i,jth cell is the same with the value of i-1,jth cell, then
		// pointer goes up.
		// If those two values are not the same, then
		// it means that i-1th item was put into the knapsack, and 
		// pointer goes to i-1,j-iw[i-1] cell.
		if (xWord[i - 1] == yWord[j - 1])
		{
			lcs[lcsCount--] = xWord[i - 1];
			i = i - 1;
			j = j - 1;
		}
		else if (table[i - 1][j] < table[i][j - 1])
			j--;
		else
			i--;
	}

	return lcs;
}

int main()
{
	int x;
	int y;

	cout << "Insert length of first word: ";
	cin >> x;

	cout << "Insert the first word: " << endl;
	char* xWord = new char[x];
	for (int i = 0; i < x; i++)
		cin >> xWord[i];

	cout << "Insert length of second word: ";
	cin >> y;

	cout << "Insert the second word: " << endl;
	char* yWord = new char[y];
	for (int i = 0; i < y; i++)
		cin >> yWord[i];


	int **table = new int*[x + 1];
	for (int i = 0; i <= x; i++)
		table[i] = new int[y + 1];

	int lcsCount = lcs(table, xWord, yWord, x, y);
	cout << "Length of LCS: " << lcsCount << endl;

	char* lcs = Backtracking(table, xWord, yWord, x, y, lcsCount);

	cout << "Longest common subsequence: ";

	for (int i = 0; i < lcsCount; i++)
		cout << lcs[i] << " ";
	
	cout << endl;
	system("pause");
	return 0;
}