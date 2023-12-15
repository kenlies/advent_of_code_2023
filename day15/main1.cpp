//PART 1
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int hash_algorithm(string line)
{
	int value = 0;

	for (auto elem : line)
	{
		value += elem;
		value *= 17;
		value %= 256;
	}
	return value;
}

int main()
{
	fstream file;
	string line;
	file.open("input.txt");
	int sum = 0;

	while (getline(file, line, ','))
	{
		sum += hash_algorithm(line);
	}
	
	cout << "final: " << sum << endl;

	return 0;
}