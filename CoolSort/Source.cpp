#include <iostream>
using namespace std;

void CoolSort(int* arr, int arrSize, int* h, int hSize)
{
	// Go through step size array
	for (int k = 0; k < hSize; k++)
	{
		int step = h[k];
		for (int l = 0; l < arrSize; l++)
		{
			for (int i = l + step; i < arrSize; i = i + step)
			{
				int key = arr[i];
				int j = i - step;
				while (j >= 0 && arr[j] > key)
				{
					arr[j + step] = arr[j];
					j = j - step;
				}
				arr[j + step] = key;
			}			
		}	
	}
}

// Function to print an array 
void PrintArray(int* arr, int arrSize)
{
	cout << "Sorted array:" << endl;
	for (int i = 0; i < arrSize; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver function to test above function
int main()
{
	int arrSize, hSize; // size of array
	char answer; // user answer to the question whether he/she wants to continue the session
	do
	{
		cout << "Insert size of the array: ";
		cin >> arrSize;
		int *arr = new int[arrSize]; // creating array 
		cout << "Insert " << arrSize << " values of the array that should be sorted" << endl;

		// filling the array
		for (int i = 0; i < arrSize; i++)
			cin >> arr[i];

		cout << "Insert size for step size array: ";
		cin >> hSize;
		int *h = new int[hSize];
		cout << "Insert " << hSize << " values of the step size array" << endl;

		// filling the array
		for (int i = 0; i < hSize; i++)
			cin >> h[i];

		CoolSort(arr, arrSize, h, hSize);
		PrintArray(arr, arrSize);

		cout << "Do you want to continue (y/n)? ";
		cin >> answer;
	} while (answer == 'y'); // loop terminates when answer is n
	return 0;
}