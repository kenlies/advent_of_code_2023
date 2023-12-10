#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void	readinput(vector<vector<char>> &map, fstream &file)
{
	string line;

	while (getline(file, line))
	{
		vector<char> line_;
		for (auto ch : line)
			line_.push_back(ch);
		map.push_back(line_);
	}
}

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

bool	move_in(char &curr_square, char new_square, vector<int> &curr_pos, vector<int> &prev_pos, int row_or_col, int increment)
{
	curr_square = new_square;
	prev_pos = curr_pos;
	if (row_or_col == 0)
		curr_pos[0] += increment;
	else
		curr_pos[1] += increment;
	return true;
}

bool	try_move_south(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square)
{
	if (curr_pos[0] + 1 == prev_pos[0] && curr_pos[1] == prev_pos[1])
		return false;
	if ((curr_square == '|' || curr_square == 'F' || curr_square == '7' || !curr_square) &&
		curr_pos[0] + 1 < map.size() && (map[curr_pos[0] + 1][curr_pos[1]] == '|' || map[curr_pos[0] + 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, '|', curr_pos, prev_pos, 0, 1);
	if ((curr_square == '|' || curr_square == 'F' || curr_square == '7' || !curr_square) &&
		curr_pos[0] + 1 < map.size() && (map[curr_pos[0] + 1][curr_pos[1]] == 'L' || map[curr_pos[0] + 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, 'L', curr_pos, prev_pos, 0, 1);
	if ((curr_square == '|' || curr_square == 'F' || curr_square == '7' || !curr_square) &&
		curr_pos[0] + 1 < map.size() && (map[curr_pos[0] + 1][curr_pos[1]] == 'J' || map[curr_pos[0] + 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, 'J', curr_pos, prev_pos, 0, 1);
	return false;
}

bool	try_move_west(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square)
{
	if (curr_pos[1] - 1 == prev_pos[1] && curr_pos[0] == prev_pos[0])
		return false;
	if ((curr_square == '-' || curr_square == 'J' || curr_square == '7' || !curr_square) &&
		curr_pos[1] - 1 >= 0 && (map[curr_pos[0]][curr_pos[1] - 1] == '-' || map[curr_pos[0]][curr_pos[1] - 1] == 'S'))
		return move_in(curr_square, '-', curr_pos, prev_pos, 1, -1);
	if ((curr_square == '-' || curr_square == 'J' || curr_square == '7' || !curr_square) &&
		curr_pos[1] - 1 >= 0 && (map[curr_pos[0]][curr_pos[1] - 1] == 'L' || map[curr_pos[0]][curr_pos[1] - 1] == 'S'))
		return move_in(curr_square, 'L', curr_pos, prev_pos, 1, -1);
	if ((curr_square == '-' || curr_square == 'J' || curr_square == '7' || !curr_square) &&
		curr_pos[1] - 1 >= 0 && (map[curr_pos[0]][curr_pos[1] - 1] == 'F' || map[curr_pos[0]][curr_pos[1] - 1] == 'S'))
		return move_in(curr_square, 'F', curr_pos, prev_pos, 1, -1);
	return false;
}
bool	try_move_east(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square)
{
	if (curr_pos[1] + 1 == prev_pos[1] && curr_pos[0] == prev_pos[0])
		return false;
	if ((curr_square == 'L' || curr_square == 'F' || curr_square == '-' || !curr_square) &&
		curr_pos[1] + 1 < map[curr_pos[0]].size() && (map[curr_pos[0]][curr_pos[1] + 1] == '-' || map[curr_pos[0]][curr_pos[1] + 1] == 'S'))
		return move_in(curr_square, '-', curr_pos, prev_pos, 1, 1);
	if ((curr_square == 'L' || curr_square == 'F' || curr_square == '-' || !curr_square) &&
		curr_pos[1] + 1 < map[curr_pos[0]].size() && (map[curr_pos[0]][curr_pos[1] + 1] == 'J' || map[curr_pos[0]][curr_pos[1] + 1] == 'S'))
		return move_in(curr_square, 'J', curr_pos, prev_pos, 1, 1);
	if ((curr_square == 'L' || curr_square == 'F' || curr_square == '-' || !curr_square) &&
		curr_pos[1] + 1 < map[curr_pos[0]].size() && (map[curr_pos[0]][curr_pos[1] + 1] == '7' || map[curr_pos[0]][curr_pos[1] + 1] == 'S'))
		return move_in(curr_square, '7', curr_pos, prev_pos, 1, 1);
	return false;
}

bool	try_move_north(vector<vector<char>> map, vector<int> &curr_pos, vector<int> &prev_pos, char &curr_square)
{
	if (curr_pos[0] - 1 == prev_pos[0] && curr_pos[1] == prev_pos[1])
		return false;
	if ((curr_square == '|' || curr_square == 'L' || curr_square == 'J' || !curr_square) &&
		curr_pos[0] - 1 >= 0 && (map[curr_pos[0] - 1][curr_pos[1]] == '|' || map[curr_pos[0] - 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, '|', curr_pos, prev_pos, 0, -1);
	if ((curr_square == '|' || curr_square == 'L' || curr_square == 'J' || !curr_square) &&
		curr_pos[0] - 1 >= 0 && (map[curr_pos[0] - 1][curr_pos[1]] == '7' || map[curr_pos[0] - 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, '7', curr_pos, prev_pos, 0, -1);
	if ((curr_square == '|' || curr_square == 'L' || curr_square == 'J' || !curr_square) &&
		curr_pos[0] - 1 >= 0 && (map[curr_pos[0] - 1][curr_pos[1]] == 'F' || map[curr_pos[0] - 1][curr_pos[1]] == 'S'))
		return move_in(curr_square, 'F', curr_pos, prev_pos, 0, -1);
	return false;
}

int main ()
{
	fstream file;
	file.open("input.txt");
	int steps = 0;
	vector<vector<char>> map;
	vector<int> curr_pos(2);
	vector<int>	starting_pos(2);
	vector<int>	prev_pos(2);
	char curr_square = '\0';
	readinput(map, file);
	find_starting_pos(map, curr_pos);
	starting_pos = curr_pos;
	prev_pos = curr_pos;
	do 
	{
		if (try_move_north(map, curr_pos, prev_pos, curr_square));
		else if (try_move_south(map, curr_pos, prev_pos, curr_square));
		else if (try_move_west(map, curr_pos, prev_pos, curr_square));
		else if (try_move_east(map, curr_pos, prev_pos, curr_square));
		steps++;
	} while (curr_pos != starting_pos);
	cout << "final: " << steps / 2 << endl;

	return 0;
}