Problem Statement
=================

In this problem you will implement a sorting algorithm, which has not been covered in class. We will call this sorting algorithm CoolSort(). We will take advantage of insertion sort for designing this sorting algorithm. The description of the sorting algorithm is as follows. 

We will first choose a decreasing sequence of numbers that ends at 1. For example, let us consider the sequence of step sizes H = 5, 3, 1. You can choose any decreasing sequence. Note that the first element of the sequence is less than the number of elements in the array. For each H, sort sub-arrays that start at arbitrary element and include every Hth element using insertion sort. For example, consider the following array

    a = [ 62 83 18 53 07 17 95 86 47 69 25 28].

An example run of CoolSort with gaps 5, 3 and 1 is shown below.

    a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12

Input 62 83 18 53 07 17 95 86 47 69 25 28

	H = 5 17 28 18 47 07 25 83 86 53 69 62 95
	H = 3 17 07 18 47 28 25 69 62 53 83 86 95
	H = 1 07 17 18 25 28 47 53 62 69 83 86 95

The first pass, 5-sorting, performs insertion sort on separate subarrays (a1, a6, a11), (a2, a7, a12), (a3, a8), (a4, a9), (a5, a10). For instance, it changes the subarray (a1, a6, a11) from (62, 17, 25) to (17, 25, 62). The next pass, 3-sorting, performs insertion sort on the subarrays (a1, a4, a7, a10), (a2, a5, a8, a11), (a3, a6, a9, a12). The last pass, 1-sorting, is an ordinary insertion sort of the entire array (a1,..., a12).

As the example illustrates, the subarrays that CoolSort operates on are initially short; later they are longer but almost ordered.

Though unintuitive, it can be shown that the above algorithm has a runtime of O(N3/2) in comparison to selection sort which has a runtime of O(N2). That is why this algorithm is cool!

Sample Test Case 1
------------------

	Input = [2, 5, 6, 4, 10, 9, 8, 1, 10, 5] and H = [5, 3,1]
	Output = [1, 2, 4, 5, 5, 6, 8, 9, 10, 10]

Sample Test Case 2
------------------

	Input = [2, 5, 9, 4, 10, 7, 8, 1, 11, 5] and H = [5, 2,1]
	Output = [1, 2, 4, 5, 5, 7, 8, 9, 10, 11]