// PART 2
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

bool compareVectors(const vector<unsigned long long>& v1, const vector<unsigned long long>& v2)
{
    return v1[0] < v2[0];
}

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
	vector<unsigned long long> ins = read_line(line);
	vector<vector<unsigned long long>> seeds(ins.size() / 2, vector<unsigned long long>(2, 0));
	for (int i = 0; i < ins.size(); i += 2)
	{
        seeds[i / 2][0] = ins[i];
        seeds[i / 2][1] = ins[i] + ins[i + 1];
	}
	getline(file, line); // skip the newline
	getline(file, line); // skip the text
	for (int x = 0; x < 7; x++)
	{
		vector<vector<unsigned long long>> blocks = read_blocks(file);
		vector<vector<unsigned long long>> new_seeds;
		while (seeds.size() > 0)
		{
			vector<unsigned long long> last = seeds.back();
			seeds.pop_back();
			bool flag = false;
			for (int j = 0; j < blocks.size(); j++)
			{
				unsigned long long a = blocks[j][0];
				unsigned long long b = blocks[j][1];
				unsigned long long c = blocks[j][2];
				unsigned long long os = max(last[0], b);
				unsigned long long oe = min(last[1], b + c);
				if (os < oe)
				{
					vector<unsigned long long> l;
					l.push_back(os - b + a);
					l.push_back(oe - b + a);
					new_seeds.push_back(l);
					if (os > last[0])
					{
						vector<unsigned long long> m;
						m.push_back(last[0]);
						m.push_back(os);
						seeds.push_back(m);
					}
					if (last[1] > oe)
					{
						vector<unsigned long long> n;
						n.push_back(oe);
						n.push_back(last[1]);
						seeds.push_back(n);
					}
					flag = true;
					break ;
				}
			}
			if (!flag)
				new_seeds.push_back(last);
		}
		seeds = new_seeds;
	}
	auto ml = min_element(seeds.begin(), seeds.end(), compareVectors);
	unsigned long long val1 = *ml->begin();
	unsigned long long val2 = *(ml->begin() + 1);
	cout << min(val1, val2) << endl;
	return 0;
}