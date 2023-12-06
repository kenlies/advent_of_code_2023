//PART 1
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int get_winning(vector<int> winning_nums, string line)
{
	int winning_val = 0;
	for (int i = 0; i < winning_nums.size(); i++)
	{
		stringstream ss(line);
		string temp;
		while (!ss.eof())
		{
			ss >> temp;
			if (winning_nums[i] == stoi(temp))
			{
				if (winning_val == 0)
					winning_val++;
				else
				{
					winning_val *= 2;
				}
			}
			temp.clear();
		}
	}
	return winning_val;
}

int main() {
    string line;
    char stp = '|';

	int sum = 0;
    fstream file;
    file.open("input.txt");
    while (getline(file, line)) {
        string newLine = line.substr(10);
        stringstream ss(newLine);
        string temp;
        vector<int> winning_nums;
        char curr;

        while (ss.get(curr)) {
            if (curr == stp) {
                break;
            }
            if (isdigit(curr)) {
                ss.unget();  // Put the digit back into the stream
                ss >> temp;
                winning_nums.push_back(stoi(temp));
                temp.clear();
            }
        }
		sum += get_winning(winning_nums, line.substr(42));
    }
	cout << sum << endl;
    return 0;
}
