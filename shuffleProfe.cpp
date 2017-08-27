#include <iostream>
// vector.h is needed to use vectors.
#include <vector>
// algorithms.h is needed for using the random_shuffle function.
#include <algorithm>
// time.h is needed for using the time() function.
#include "time.h"

using namespace std;

int main()
{
	// Initializes the data here.
	string tmp[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "-"};
	// Loads the data into a vector.
	vector<string> data(tmp, tmp + 16);
	// Sets the seed for the random number generator.
	// If you remove the line for the seed you will always see the same sequence of random
	// numbers
	srand(time(0));
	// Shuffles the contents of the vector.
	random_shuffle(data.begin(), data.end());
	// This prints the contents of the vector.
	// It should print the elements in a random order.
	for (int i = 0; i < data.size(); i++)
	{
		cout << data.at(i) << " ";
	}
	cout << endl;
}
