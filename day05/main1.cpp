// PART 1
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

vector<unsigned long long> read_line(string line)
{
    stringstream ss(line);
    string temp;
    vector<unsigned long long> ret;
    while (!ss.eof())
    {
        ss >> temp;
        if (isdigit(temp[0]))
            ret.push_back(stoull(temp));
        temp.clear();
    }
    return ret;
}

vector<vector<unsigned long long>>read_blocks(fstream &file)
{
	string line;
	vector<vector<unsigned long long>> blocks;
	
	while(getline(file, line))
	{
		if (!isdigit(line[0]))
		{
			getline(file, line); // skip the newline
			break ;
		}
		blocks.push_back(read_line(line));
	}
	return blocks;
}

int main()
{
    fstream file;
	string line;

	file.open("input.txt");
	getline(file, line);
	vector<unsigned long long> seeds = read_line(line);
	getline(file, line); // skip the newline
	getline(file, line); // skip the text

	for (int x = 0; x < 7; x++)
	{
		vector<vector<unsigned long long>> blocks = read_blocks(file);
		vector<unsigned long long> new_seeds;

		for (int i = 0; i < seeds.size(); i++)
		{
			bool flag = false;
			for (int j = 0; j < blocks.size(); j++)
			{
				unsigned long long a = blocks[j][0];
				unsigned long long b = blocks[j][1];
				unsigned long long c = blocks[j][2];
				if (b <= seeds[i] && seeds[i] < b + c)
				{
					new_seeds.push_back(seeds[i] - b + a);
					flag = true;
					break ;
				}
			}
			if (!flag)
				new_seeds.push_back(seeds[i]);
		}
		seeds = new_seeds;
	}
	cout << *std::min_element(seeds.begin(), seeds.end()) << endl;
    return 0;
}