//PART 2
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

void add_column(vector<vector<char>> &universe, const vector<char> &empty_space, int position)
{
	for (int i = 0; i < universe.size(); i++)
		universe[i].insert(universe[i].begin() + position, empty_space[i]);
}

int	expand_universe(vector<vector<char>> &universe, fstream &file, vector<int> &v_positions, vector<int> &h_positions)
{
	string line;
	int galaxies = 0;
	int line_num = 0;

	while (getline(file, line))
	{
		vector<char> row;
		if (line.find('#') == string::npos)
			h_positions.push_back(line_num);
		for (auto ch : line)
			row.push_back(ch);
		universe.push_back(row);
		for (auto ch : line)
			if (ch == '#')
				galaxies++;
		line_num++;
	}
	int rows_count = universe.size();
	vector<char> empty_space(rows_count, '.');
	for (int col = 0; col < universe[0].size(); col++)
	{
		bool found_galax = false;
		for (int row = 0; row < rows_count; row++)
		{
			if (universe[row][col] == '#')
			{
				found_galax = true;
				break ;
			}
		}
		if (found_galax == false)
			v_positions.push_back(col);
	}
	return galaxies;
}

void	get_galaxy_cordinates(map<int, vector<int>> &galaxies, vector<vector<char>> universe)
{
	int num = 1;

	for (int i = 0; i < universe.size(); i++)
	{
		for (int j = 0; j < universe[0].size(); j++)
		{
			if (universe[i][j] == '#')
			{
				galaxies[num] = {i, j};
				num++;
			}
		}
	}
}

unsigned long long  calc_paths(map<int, vector<int>> galaxies, vector<int> &v_positions, vector<int> &h_positions)
{
	unsigned long long sum = 0;

	while (!galaxies.empty())
	{
		auto it = galaxies.begin();
		for (auto elem : galaxies)
		{
			int horizontal_cof = 0;
			int vertical_cof = 0;
			if (it->second.front() < elem.second.front())
			{
				for (int i = it->second.front(); i < elem.second.front(); i++)
					for (auto e : h_positions)
						if (i == e)
							horizontal_cof++;
			}
			if (it->second.back() < elem.second.back())
			{
				for (int i = it->second.back(); i < elem.second.back(); i++)
					for (auto e : v_positions)
						if (i == e)
							vertical_cof++;
			}
			else if (it->second.back() > elem.second.back())
			{
				for (int i = elem.second.back(); i < it->second.back(); i++)
					for (auto e : v_positions)
						if (i == e)
							vertical_cof++;
			}
			sum += llabs(it->second.front() - elem.second.front()) + abs(it->second.back() - elem.second.back()) -
					horizontal_cof - vertical_cof + (vertical_cof * 1000000) + (horizontal_cof * 1000000);
		}
		galaxies.erase(it);
	}
	return sum;
}

int main ()
{
	fstream file;
	file.open("input.txt");
	vector<int> v_positions;
	vector<int> h_positions;
	vector<vector<char>> universe;
	map<int, vector<int>> galaxies;
	int galaxy_count = expand_universe(universe, file, v_positions, h_positions);
	get_galaxy_cordinates(galaxies, universe);
	unsigned long long sum = calc_paths(galaxies, v_positions, h_positions);

	cout << "galaxies: " << galaxy_count << endl;
	cout << "final: " << sum << endl;
	return 0;
}
