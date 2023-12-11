//PART 1
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

int	expand_universe(vector<vector<char>> &universe, fstream &file)
{
	string line;
	int galaxies = 0;
	vector<int> positions;

	while (getline(file, line))
	{
		vector<char> row;
		if (line.find('#') == string::npos)
		{
			vector<char> copy;
			for (auto ch : line)
				copy.push_back(ch);
			universe.push_back(copy);
		}
		for (auto ch : line)
			row.push_back(ch);
		universe.push_back(row);
		for (auto ch : line)
			if (ch == '#')
				galaxies++;
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
			positions.push_back(col);
	}
	for (int i = 0; i < positions.size(); i++)
		add_column(universe, empty_space, positions[i] + i);
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

int calc_paths(map<int, vector<int>> galaxies)
{
	int sum = 0;
	int counter = 1;

	while (!galaxies.empty())
	{
		auto it = galaxies.begin();
		for (auto elem : galaxies)
			sum += abs(it->second.front() - elem.second.front()) + abs(it->second.back() - elem.second.back());
		galaxies.erase(it);
	}
	return sum;
}

int main ()
{
	fstream file;
	file.open("input.txt");
	vector<vector<char>> universe;
	map<int, vector<int>> galaxies;
	int galaxy_count = expand_universe(universe, file);
	get_galaxy_cordinates(galaxies, universe);
	int sum = calc_paths(galaxies);

	cout << "galaxies: " << galaxy_count << endl;
	cout << "final: " << sum << endl;
	return 0;
}