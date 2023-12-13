//PART 1
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <time.h>
using namespace std;

vector<int> build_contiguous(string line)
{
	vector<int> values;
	istringstream ss(line);

	int num;
	while (ss >> num)
	{
		values.push_back(num);
		if (ss.peek() == ',')
			ss.ignore();
	}
	return values;
}

bool is_valid_line(string line, vector<int> contiguous)
{
	int c = 0;
	int size = line.size();

	for (int i = 0; i < size; i++)
	{
		if (line[i] == '#')
		{
			if (contiguous.empty())
				return false;
			c++;
			if (c == *contiguous.begin() && (i + 1 == size || line[i + 1] == '.'))
			{
				contiguous.erase(contiguous.begin());
				c = 0;
			}
		}
		else if (line[i] == '.' && c)
			return false;
	}
	if (contiguous.empty())
		return true;
	return false;
}

vector<char> build_trfrm(string line, vector<int> contiguous)
{
	vector<char> res;
	int total_cont = 0;
	int total_hash = 0;
	int total_qst = 0;
	int add_hash = 0;

	for (auto elem : contiguous)
		total_cont += elem;
	for (auto elem : line)
		if (elem == '#')
			total_hash++;
		else if (elem == '?')
			total_qst++;
	add_hash = total_cont - total_hash; 
	while(total_qst)
	{
		if (add_hash)
		{
			res.push_back('#');
			add_hash--;
		}
		else
			res.push_back('.');
		total_qst--;
	}
	return res;
}

string combine(string line, vector<char> trfrm)
{
	int size = line.size();

	for (int i = 0; i < size; i++)
	{
		if (line[i] == '?')
		{
			line[i] = *trfrm.begin();
			trfrm.erase(trfrm.begin());
		}
	}
	return line;
}

void permutation(vector<char>&trfrm, int i, int &arrangements, string line, vector<int> contiguous)
{
	int size = trfrm.size();

    if (i == size)
    {
        string cmb = combine(line, trfrm);
		if (is_valid_line(cmb, contiguous))
			arrangements++;
        return ;
    }
    unordered_set<char> s;
    for (int j = i; j < size; j++)
    {
        if (s.find(trfrm[j]) != s.end())
            continue ;
        s.insert(trfrm[j]);
        swap(trfrm[i], trfrm[j]);
        permutation(trfrm, i + 1, arrangements, line, contiguous);
        swap(trfrm[i], trfrm[j]);
    }
}

int calc(string line, vector<int> contiguous)
{
	int arrangements = 0;
	vector<char> trfrm = build_trfrm(line, contiguous);
	permutation(trfrm, 0, arrangements, line, contiguous);
	if (arrangements == 0)
		return 1;
	return arrangements;
}

int main ()
{
	fstream file;
	vector<int> contiguous;
	string line;
	file.open("input.txt");
	int sum = 0;
	clock_t tStart = clock();

	while (getline(file, line))
	{
		stringstream ss(line);
		string temp;
		ss >> line;
		ss >> temp;
		contiguous = build_contiguous(temp);
		sum += calc(line, contiguous);
	}
	printf("time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	cout << "final: " << sum << endl;

	return 0;
}