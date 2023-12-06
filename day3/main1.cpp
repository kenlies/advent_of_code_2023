// PART 1
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int has_adjacent(std::vector<std::string>& lines, int row, int col)
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0) continue;
			int newRow = row + i;
			int newCol = col + j;
			if (newRow >= 0 && newRow < lines.size() &&
				newCol >= 0 && newCol < lines[newRow].size() &&
				!isdigit(lines[newRow][newCol]) && lines[newRow][newCol] != '.')
				return 1;
		}
	}
	return 0;
}

int main ()
{
	int sum = 0;
	string num;
	string line;
	std::vector<std::string> lines;
	ifstream file("input.txt");
	while(getline(file, line))
		lines.push_back(line);
	for (int row = 0; row < lines.size(); ++row)
	{
		for (int col = 0; col < lines[row].size(); ++col)
		{
			int has_adj = 0;
			while (col < lines[row].size() && isdigit(lines[row][col]))
			{
				num.push_back(lines[row][col]);
				if (has_adjacent(lines, row, col))
					has_adj = 1;
				col++;
			}
			if (has_adj)
			{
				sum += std::stoi(num);
				has_adj = 0;
			}
			num.clear();
		}
	}
	printf("%d\n", sum);
	return 0;
}