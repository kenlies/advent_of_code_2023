//PART 1
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<int> get_input(string line)
{
	stringstream ss(line);
	vector<int> res;
	string temp;

	while (ss >> temp)
	{	
		if (isdigit(temp[0]))
			res.push_back(stoi(temp));	
	}
	return res;
}

int get_ways_to_win(int time, int dist)
{
	int ways_to_win = 0;
	int time_clone = time;

	for (int curr_time = 0; curr_time < time_clone; curr_time++, time--)
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
	vector <int> time;
	vector <int> dist;
	file.open("input.txt");
	getline(file, line);
	time = get_input(line);
	getline(file, line);
	dist = get_input(line);

	int sum = 1;
	for (int i = 0; i < time.size(); i++)
	{
		sum *= get_ways_to_win(time[i], dist[i]);
	}
	cout << sum << endl;

    return 0;
}