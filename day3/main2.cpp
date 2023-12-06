// PART 2
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int get_num_forward(string line, int pos)
{
	int res = 0;
	string num;
	if (isdigit(line[pos]))
	{
		while (pos < line.size() && line[pos] != '.')
		{
			num.push_back(line[pos]);
			pos++;
		}
		res = std::stol(num);
		num.clear();
		return res;
	}
	return 0;
}

int get_num_backward(string line, int pos)
{
	int res = 0;
	string num;
	if (isdigit(line[pos]))
	{
		while (pos >= 0 && line[pos] != '.')
		{
			num.push_back(line[pos]);
			pos--;
		}
		reverse(num.begin(), num.end());
		res = std::stol(num);
		num.clear();
		return res;
	}
	return 0;
}

int get_big_num(string line, int pos)
{
	int res = 0;
	string num;
	while (pos > 0 && isdigit(line[pos]))
		pos--;
	if (!isdigit(line[pos]))
		pos++;
	while (pos < line.size() && line[pos] != '.')
	{
		num.push_back(line[pos]);
		pos++;
	}
	res = std::stol(num);
	num.clear();
	return res;
}

void get_num_over_below(string line, int pos, int *adj_nums, int *adj_num_count)
{
    if (isdigit(line[pos - 1]) && isdigit(line[pos]) && isdigit(line[pos + 1]))
    {
        adj_nums[(*adj_num_count)++] = get_big_num(line, pos - 1);
		return ;
    }
    if (!isdigit(line[pos - 1]) && isdigit(line[pos]) && !isdigit(line[pos + 1]))
    {
        adj_nums[(*adj_num_count)++] = line[pos] - '0'; // Convert char to int
		return ;
    }
    if (isdigit(line[pos - 1]) && isdigit(line[pos]))
    {
        adj_nums[(*adj_num_count)++] = get_num_backward(line, pos);
		return ;
    }
    if (isdigit(line[pos]) && isdigit(line[pos + 1]))
    {
        adj_nums[(*adj_num_count)++] = get_num_forward(line, pos);
		return ;
    }
    if (!isdigit(line[pos]) && isdigit(line[pos - 1]))
    {
        adj_nums[(*adj_num_count)++] = get_num_backward(line, pos - 1);
    }
    if (!isdigit(line[pos]) && isdigit(line[pos + 1]))
        adj_nums[(*adj_num_count)++] = get_num_forward(line, pos + 1);
}


int has_two_adjacent_nums(std::vector<std::string>& lines, int row, int col)
{
	int adj_num_cout = 0;
	int adj_nums[6];
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0) continue;
			int newRow = row + i;
			int newCol = col + j;
			if (i == 0 && j == -1 && newRow >= 0 && newRow < lines.size() &&
				newCol >= 0 && newCol < lines[newRow].size())
			{
				adj_nums[adj_num_cout] = get_num_backward(lines[newRow], newCol);
				if (adj_nums[adj_num_cout])
					adj_num_cout++;
			}
			else if(i == 0 && j == 1 && newRow >= 0 && newRow < lines.size() &&
				newCol >= 0 && newCol < lines[newRow].size())
			{
				adj_nums[adj_num_cout] = get_num_forward(lines[newRow], newCol);
				if (adj_nums[adj_num_cout])
					adj_num_cout++;
			}
			else if (i == -1 && j == 0 && newRow >= 0 && newRow < lines.size() &&
				newCol >= 0 && newCol < lines[newRow].size())
				get_num_over_below(lines[newRow], newCol, adj_nums, &adj_num_cout);
			else if (i == 1 && j == 0 && newRow >= 0 && newRow < lines.size() &&
				newCol >= 0 && newCol < lines[newRow].size())
				get_num_over_below(lines[newRow], newCol, adj_nums, &adj_num_cout);
		}
	}
	if (adj_num_cout == 2)
		return adj_nums[0] * adj_nums[1];
	return 0;
}

int main ()
{
	int sum = 0;
	string line;
	std::vector<std::string> lines;
	ifstream file("input.txt");
	while(getline(file, line))
		lines.push_back(line);
	for (int row = 0; row < lines.size(); ++row)
	{
		for (int col = 0; col < lines[row].size(); ++col)
		{
			if (lines[row][col] == '*')
				sum += has_two_adjacent_nums(lines, row, col);
		}
	}
	printf("%d\n", sum);
	return 0;
}