//PART 2
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

unsigned long long get_input(string line)
{
	stringstream ss(line);
	string res;
	string temp;

	while (ss >> temp)
	{	
		if (isdigit(temp[0]))
			res += temp;
	}
	return stoull(res);
}

int get_ways_to_win(unsigned long long time, unsigned long long dist)
{
	unsigned long long ways_to_win = 0;
	unsigned long long time_clone = time;

	for (unsigned long long curr_time = 0; curr_time < time_clone; curr_time++, time--)
	{
		if ((time * curr_time) > dist)
			ways_to_win++;
	}
	return ways_to_win;
}

int main()
{
    fstream file;
	string line;
	unsigned long long time;
	unsigned long long dist;
	file.open("input.txt");
	getline(file, line);
	time = get_input(line);
	getline(file, line);
	dist = get_input(line);

	cout << get_ways_to_win(time, dist) << endl;

    return 0;
}