//PART 2
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map> 
#include <string>
#include <numeric>
using namespace std;

unsigned long long gcd(long long int a, long long int b) 
{ 
	if (b == 0) 
		return a; 
	return gcd(b, a % b); 
}

int main ()
{
	fstream file;
	string line;
	vector <char> instructions;
	vector <string> ghosts;
	vector<int> cycles;
	unordered_map <string, string> map;
	file.open("input.txt");

	// fill instructions vector
	getline(file, line);
	for (int i = 0; i < line.size(); i++) 
		instructions.push_back(line[i]);
	getline(file, line); // skip new line;
	// fill map
	while (getline(file, line))
	{
		if (line[2] == 'A')
			ghosts.push_back(line.substr(0, 3));
		map[line.substr(0, 3)] = line.substr(6, 15);
	}
	int inst_size = instructions.size();
	for (auto &elem : ghosts)
	{
		int step_count = 0;
		for (int i = 0; elem[2] != 'Z'; i++)
		{
			step_count++;
			if (i == inst_size)
				i = 0;
			if (instructions[i] == 'R')
				elem = map[elem].substr(6, 3);
			else
				elem = map[elem].substr(1, 3);
		}
		cycles.push_back(step_count);
	}
	unsigned long long lcm = 1;
	for (auto &elem : cycles)
		lcm = elem / gcd(elem, lcm) * lcm;

	cout << "final: " << lcm << endl;

	return 0;
}