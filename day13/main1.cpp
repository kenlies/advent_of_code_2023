//PART 1
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void	read_to_note(vector<vector<char>> &note, fstream &file)
{
	string line;

	while (getline(file, line) && !line.empty())
	{
		vector<char> row;
		for (auto elem : line)
			row.push_back(elem);
		note.push_back(row);
	}
}

int find_vertical_reflections(vector<vector<char>> note)
{
	int res = 0;
	bool r_mode = false;
	int save;

	vector<vector<char>> reflection;

	for (int j = 0; j < note[0].size(); j++)
	{
		bool flag = false;
		vector<char> col;
		for (int k = 0; k < note.size() && !r_mode; k++)
		{
			col.push_back(note[k][j]);
			if (note[k][j] != note[k][j + 1])
				flag = true;
		}
		for (int k = 0; k < note.size() && r_mode; k++)
			col.push_back(note[k][j]);
		if (r_mode && col == reflection.back())
		{
			reflection.pop_back();
			if (j + 1 == note[0].size() || reflection.empty())
				return res;
		}
		else if (r_mode)
		{
			j = save;
			reflection.clear();
			r_mode = false;
			continue ;
		}
		if (!r_mode)
			reflection.push_back(col);
		if (!flag && !r_mode)
		{
			save = j;
			reflection.pop_back();
			res = j + 1;
			if (reflection.empty() && (j == 0))
				return res;
			if (j + 2 == note[0].size())
				return res;
			r_mode = true;
			j++;
		}
	}
	return 0;
}

int find_horizontal_reflections(vector<vector<char>> note)
{
	int res = 0;
	int save;
	vector<vector<char>> reflection;
	bool flag = false;

	for (int i = 0; i < note.size(); i++)
	{
		if (!flag)
			reflection.push_back(note[i]);
		if (i + 1 < note.size() && note[i] == note[i + 1] && !flag)
		{
			res = ((i + 1) * 100);
			reflection.pop_back();
			save = i;
			if (reflection.empty() && i == 0)
				return res;
			if (i + 2 == note.size())
				return res;
			i++;
			flag = true;
		}
		else if (reflection.back() == note[i] && flag)
		{
			reflection.pop_back();
			if (reflection.empty())
				return res;
		}
		else if (flag)
		{
			res = 0;
			i = save;
			flag = false;
			reflection.clear();
		}
	}
	if (flag)
		return res;
	return 0;
}

int main ()
{
	fstream file;
	file.open("input.txt");
	vector<vector<char>> note;
	int sum = 0;
	while (!file.eof())
	{
		read_to_note(note, file);
		sum += find_vertical_reflections(note);
		sum += find_horizontal_reflections(note);
		note.clear();
	}
	cout << "final: " << sum << endl;

	return 0;	
}