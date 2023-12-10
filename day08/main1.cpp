//PART 1
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map> 
#include <string>
using namespace std;

int main ()
{
	fstream file;
	string line;
	vector <char> instructions;
	unordered_map <string, string> map;
	file.open("input.txt");

	// fill instructions vector
	getline(file, line);
	for (int i = 0; i < line.size(); i++) 
		instructions.push_back(line[i]);
	getline(file, line); // skip new line;
	// fill map
	while (getline(file, line))
		map[line.substr(0, 3)] = line.substr(6, 15);
	int steps = 0;
	int inst_size = instructions.size();
	string curr = "AAA";
	string goal = "ZZZ";
	for (int i = 0; curr != goal; i++)
	{
		if (i == inst_size)
			i = 0;
		if (curr == goal)
			break ;
		if (instructions[i] == 'R')
			curr = map[curr].substr(6, 3);
		else
			curr = map[curr].substr(1, 3);
		steps++;
	}
	cout << "final: " << steps << endl;
	return 0;
}