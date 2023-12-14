//PART 1
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void read_to_dish(vector<vector<char>> &dish, fstream &file, int &line_count)
{
	string line;

	while (getline(file, line))
	{
		vector<char> row;
		for (auto elem : line)
			row.push_back(elem);
		dish.push_back(row);
		line_count++;
	}
}

int calc(vector<vector<char>> &dish, int line_count)
{
	int res = 0;

	for (int i = 0; i < dish[0].size(); i++)
	{
		int base = line_count;
		for (int k = 0; k < line_count; k++)
		{
			if (dish[k][i] == '#')
				base = line_count - k - 1;
			else if (dish[k][i] == 'O')
				res += base--;
		}
	}
	return res;
}

int main ()
{
	fstream file;
	file.open("input.txt");
	int sum = 0;
	int line_count = 0;
	vector<vector<char>> dish;
	
	read_to_dish(dish, file, line_count);
	sum = calc(dish, line_count);

	cout << "final: " << sum << endl;

	return 0;
}