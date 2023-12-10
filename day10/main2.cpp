//PART 2
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void	find_starting_pos(vector<vector<char>> map, vector<int> &curr_pos)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'S')
			{
				curr_pos[0] = i;
				curr_pos[1] = j;
				return ;
			}
		}
	}
}

bool	move_in(char &curr_square, char new_square, vector<int> &curr_pos, vector<int> &prev_pos, int row_or_col, int increment, vector<vector<char>> &empty_map)
{
	curr_square = new_square;
	prev_pos = curr_pos;
	if (row_or_col == 0)
		curr_pos[0] += increment;
	else
		curr_pos[1] += increment;
	empty_map[curr_pos[0]][curr_pos[1]] = new_square;
	return true;
}

void	readinput_craete_empty_map(vector<vector<char>> &map, fstream &file, vector<vector<char>> &empty_map)
{
	string line;
	string line2;

	while (getline(file, line))
	{	
		vector<char> line_;
		vector<char> line2_;
		for (auto ch : line)
		{
			line_.push_back(ch);
			line2_.push_back('.');
		}
		map.push_back(line_);
		empty_map.push_back(line2_);
	}
}

bool	try_move_south(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square, vector<vector<char>> &empty_map)
{
	if (curr_pos[0] + 1 == prev_pos[0] && curr_pos[1] == prev_pos[1])
		return false;
	if ((curr_square == '|' || curr_square == 'F' || curr_square == '7' || !curr_square) &&
		curr_pos[0] + 1 < map.size() && (map[curr_pos[0] + 1][curr_pos[1]] == '|' || map[curr_pos[0] + 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, '|', curr_pos, prev_pos, 0, 1, empty_map);
	if ((curr_square == '|' || curr_square == 'F' || curr_square == '7' || !curr_square) &&
		curr_pos[0] + 1 < map.size() && (map[curr_pos[0] + 1][curr_pos[1]] == 'L' || map[curr_pos[0] + 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, 'L', curr_pos, prev_pos, 0, 1, empty_map);
	if ((curr_square == '|' || curr_square == 'F' || curr_square == '7' || !curr_square) &&
		curr_pos[0] + 1 < map.size() && (map[curr_pos[0] + 1][curr_pos[1]] == 'J' || map[curr_pos[0] + 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, 'J', curr_pos, prev_pos, 0, 1, empty_map);
	return false;
}

bool	try_move_west(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square, vector<vector<char>> &empty_map)
{
	if (curr_pos[1] - 1 == prev_pos[1] && curr_pos[0] == prev_pos[0])
		return false;
	if ((curr_square == '-' || curr_square == 'J' || curr_square == '7' || !curr_square) &&
		curr_pos[1] - 1 >= 0 && (map[curr_pos[0]][curr_pos[1] - 1] == '-' || map[curr_pos[0]][curr_pos[1] - 1] == 'S'))
		return move_in(curr_square, '-', curr_pos, prev_pos, 1, -1, empty_map);
	if ((curr_square == '-' || curr_square == 'J' || curr_square == '7' || !curr_square) &&
		curr_pos[1] - 1 >= 0 && (map[curr_pos[0]][curr_pos[1] - 1] == 'L' || map[curr_pos[0]][curr_pos[1] - 1] == 'S'))
		return move_in(curr_square, 'L', curr_pos, prev_pos, 1, -1, empty_map);
	if ((curr_square == '-' || curr_square == 'J' || curr_square == '7' || !curr_square) &&
		curr_pos[1] - 1 >= 0 && (map[curr_pos[0]][curr_pos[1] - 1] == 'F' || map[curr_pos[0]][curr_pos[1] - 1] == 'S'))
		return move_in(curr_square, 'F', curr_pos, prev_pos, 1, -1, empty_map);
	return false;
}
bool	try_move_east(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square, vector<vector<char>> &empty_map)
{
	if (curr_pos[1] + 1 == prev_pos[1] && curr_pos[0] == prev_pos[0])
		return false;
	if ((curr_square == 'L' || curr_square == 'F' || curr_square == '-' || !curr_square) &&
		curr_pos[1] + 1 < map[curr_pos[0]].size() && (map[curr_pos[0]][curr_pos[1] + 1] == '-' || map[curr_pos[0]][curr_pos[1] + 1] == 'S'))
		return move_in(curr_square, '-', curr_pos, prev_pos, 1, 1, empty_map);
	if ((curr_square == 'L' || curr_square == 'F' || curr_square == '-' || !curr_square) &&
		curr_pos[1] + 1 < map[curr_pos[0]].size() && (map[curr_pos[0]][curr_pos[1] + 1] == 'J' || map[curr_pos[0]][curr_pos[1] + 1] == 'S'))
		return move_in(curr_square, 'J', curr_pos, prev_pos, 1, 1, empty_map);
	if ((curr_square == 'L' || curr_square == 'F' || curr_square == '-' || !curr_square) &&
		curr_pos[1] + 1 < map[curr_pos[0]].size() && (map[curr_pos[0]][curr_pos[1] + 1] == '7' || map[curr_pos[0]][curr_pos[1] + 1] == 'S'))
		return move_in(curr_square, '7', curr_pos, prev_pos, 1, 1, empty_map);
	return false;
}

bool	try_move_north(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square, vector<vector<char>> &empty_map)
{
	if (curr_pos[0] - 1 == prev_pos[0] && curr_pos[1] == prev_pos[1])
		return false;
	if ((curr_square == '|' || curr_square == 'L' || curr_square == 'J' || !curr_square) &&
		curr_pos[0] - 1 >= 0 && (map[curr_pos[0] - 1][curr_pos[1]] == '|' || map[curr_pos[0] - 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, '|', curr_pos, prev_pos, 0, -1, empty_map);
	if ((curr_square == '|' || curr_square == 'L' || curr_square == 'J' || !curr_square) &&
		curr_pos[0] - 1 >= 0 && (map[curr_pos[0] - 1][curr_pos[1]] == '7' || map[curr_pos[0] - 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, '7', curr_pos, prev_pos, 0, -1, empty_map);
	if ((curr_square == '|' || curr_square == 'L' || curr_square == 'J' || !curr_square) &&
		curr_pos[0] - 1 >= 0 && (map[curr_pos[0] - 1][curr_pos[1]] == 'F' || map[curr_pos[0] - 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, 'F', curr_pos, prev_pos, 0, -1, empty_map);
	return false;
}

void	build_map(vector<vector<char>> &map, vector<vector<char>> &empty_map, vector<int> curr_pos)
{
	vector<int>	starting_pos(2);
	vector<int>	prev_pos(2);
	char curr_square = '\0';
	starting_pos = curr_pos;
	prev_pos = curr_pos;
	int steps = 0;
	do 
	{
		if (try_move_north(map, curr_pos, prev_pos, curr_square, empty_map));
		else if (try_move_south(map, curr_pos, prev_pos, curr_square, empty_map));
		else if (try_move_west(map, curr_pos, prev_pos, curr_square, empty_map));
		else if (try_move_east(map, curr_pos, prev_pos, curr_square, empty_map));
		steps++;
	} while (curr_pos != starting_pos);
	empty_map[starting_pos[0]][starting_pos[1]] = 'L'; // SET THIS MANUALLY
	map = empty_map;
	cout << steps << endl;
}

int countWalls(const vector<vector<char>> &map, int row, int col, int row_size) {
    int count = 0;
	bool up = false;
	bool down = false;
    for (int i = col + 1; i < row_size; i++)
	{
		if (map[row][i] == '|')
		{
			up = false;
			down = false;
			count++;
		}
		else if (map[row][i] == 'L')
		{
			up = true;
			down = false;
		}
		else if (map[row][i] == '7' && up)
		{
			up = false;
			count++;
		}
		else if (map[row][i] == 'F')
		{
			down = true;
			up = false;
		}
		else if (map[row][i] == 'J' && down)
		{
			down = false;
			count++;
		}
	}
    return count;
}

int main ()
{
	fstream file;
	file.open("input.txt");
	vector<vector<char>> map;
	vector<vector<char>> empty_map;
	vector<int> curr_pos(2);
	readinput_craete_empty_map(map, file, empty_map);
	find_starting_pos(map, curr_pos);
	build_map(map, empty_map, curr_pos);
	int dots_inside = 0;
	cout << endl;
	int row_size = map[0].size();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < row_size; j++)
		{
			if (map[i][j] == '.')
			{
				int surroundingEastWalls = countWalls(map, i, j, row_size);
				if (surroundingEastWalls % 2 == 1)
				{
					map[i][j] = '#';
					dots_inside++;
				}
			}
		}
	}
	for (auto vec : map)
	{
		for (auto elem : vec)
			cout << elem;
		cout << endl;
	}
	cout << "final: " << dots_inside << endl;

	return 0;
}
