//PART 2
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> getInput()
{
    string s;
    vector<string> input;
    while(getline(cin, s))
        input.push_back(s);
    return input;
}

int score(const vector<string>& input,  vector<int>& dp, int c_num)
{
    stringstream ss (input[c_num]);
    string temp;
    vector<int> winning_num;

    int i = 0;
    bool winning_card = false;
    bool is_my_nums = false;
	int n_win = 0;
    while(ss >> temp)
    {
        i++;
        if(i <= 2) continue;
        if(temp == "|") is_my_nums = true;
        else if(is_my_nums)
        {
            int my_num = stoi(temp);
            if(find(winning_num.begin(), winning_num.end(), my_num) != winning_num.end())
            {
                winning_card = true;
                n_win++;
            }
        }
        else
            winning_num.push_back(stoi(temp));
    }
    if(winning_card)
    {
        if(dp[c_num] == -1)
        {
            int sum = 0;
            for(int j = 1; j <= n_win; j++)
                sum += score(input, dp, c_num + j);
            sum += 1;
            dp[c_num] = sum;
        }
    }
    else
        dp[c_num] = 1;
    return dp[c_num];
}

int main()
{
    freopen("input.txt", "r", stdin);
    vector<string> input = getInput();
    vector<int> dp(input.size());
    fill(dp.begin(), dp.end(), -1);
    long long sum = 0;
    for(int i = 0; i < input.size(); i++)
        sum += score(input, dp,  i);
	cout << sum << endl;
}