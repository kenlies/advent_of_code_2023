//PART 1
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

bool is_everything_zero(vector<long long> curr)
{
    for (auto elem : curr)
    {
        if (elem != 0)
            return false;
    }
    return true;
}

long long calc_history_value(string line)
{
	vector<vector<long long> > diffs;
	vector<long long> first;
	stringstream ss(line);
	string temp;
	while (ss >> temp)
		first.push_back(stol(temp));
	diffs.push_back(first);
	while (42)
	{
		vector<long long> curr;
		vector<long long> cmp = diffs.back();
		for (int i = 0; i < cmp.size() - 1; i++)
		{
			long long tmp = llabs(cmp[i] - cmp[i + 1]);
			if (cmp[i] > cmp[i + 1])
				tmp = tmp * -1;
			curr.push_back(tmp);
		}
		if (is_everything_zero(curr))
			break ;
		diffs.push_back(curr);
	}
	vector<long long> ans;
	ans.push_back(diffs.back().back());
	diffs.pop_back();
	while (!diffs.empty())
	{
		ans.push_back(ans.back() + diffs.back().back());
		diffs.pop_back();
	}
	return ans.back();
}

int main ()
{
	fstream file;
	string line;
	long long sum = 0;

	file.open("input.txt");
	while (getline(file, line))
	{
		sum += calc_history_value(line);
	}
	cout << sum << endl;
	return 0;
}