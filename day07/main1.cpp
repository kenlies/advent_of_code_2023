// PART 1
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

struct Cards 
{
    std::unordered_map<char, int> cardMap;

    Cards() {
        cardMap['2'] = 0;
        cardMap['3'] = 1;
        cardMap['4'] = 2;
        cardMap['5'] = 3;
		cardMap['6'] = 4;
		cardMap['7'] = 5;
		cardMap['8'] = 6;
		cardMap['9'] = 7;
		cardMap['T'] = 8;
		cardMap['J'] = 9;
		cardMap['Q'] = 10;
		cardMap['K'] = 11;
		cardMap['A'] = 12;
    }
};

void get_hands_bids(fstream &file, vector<string> &hands, vector<int> &bids, int &rank)
{
	string line;
	string temp;

	while (getline(file, line))
	{
		stringstream ss(line);
		ss >> temp;
		hands.push_back(temp);
		ss >> temp;
		bids.push_back(stoi(temp));
		temp.clear();
		rank++;
	}
}

bool compareHands(const std::string& hand1, const std::string& hand2)
{
	Cards cards;
    // Compare hands based on the mapping in the Cards struct
    for (std::size_t i = 0; i < hand1.size(); ++i) 
	{
        if (cards.cardMap[hand1[i]] < cards.cardMap[hand2[i]])
            return false;
		else if (cards.cardMap[hand1[i]] > cards.cardMap[hand2[i]])
            return true;
    }
    return true;  // hands are equal
}

int operate(vector<string> &transformed, vector<string> &hands, vector<int> &bids, int &rank)
{
	int sum = 0;

	std::sort(transformed.begin(), transformed.end(), compareHands);
	for (int i = 0; i < transformed.size(); i++)
	{
		auto it = std::find(hands.begin(), hands.end(), transformed[i]);
		int bid_index = it - hands.begin();
		sum += rank * bids[bid_index];
		cout << "card: " << transformed[i] << ": " << rank << " * " << bids[bid_index] << endl;
		rank--;
	}
	for (int i = 0; i < transformed.size(); i++)
	{
		auto it = std::find(hands.begin(), hands.end(), transformed[i]);
		int bid_index = it - hands.begin();
		hands.erase(it);
		bids.erase(bids.begin() + bid_index);
	}
	cout << "sum: " << sum << endl;
	return sum;
}

int five_of_a_kind(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----FIVE OF A KIND----" << endl;
	vector<string> fives;
	unsigned long long sum = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < 4; j++)
		{
			if (hands[i][j] != hands[i][j + 1])
			{
				flag = true;
				break ;
			}
		}
		if (!flag)
			fives.push_back(hands[i]);
	}
	return operate(fives, hands, bids, rank);
}

int four_of_a_kind(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----FOUR OF A KIND----" << endl;
	vector<string> fours;
	unsigned long long sum = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int counter = 0;
			for (int k = j + 1; k < 5; k++)
				if (hands[i][j] == hands[i][k])
					counter++;
			if (counter == 3)
				fours.push_back(hands[i]);
		}
	}
	return operate(fours, hands, bids, rank);
}

int full_house(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----FULL HOUSE----" << endl;
	vector<string> houses;
	unsigned long long sum = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		// find three of a kind
		char three_of_kind = '\0';
		for (int j = 0; j < 5; j++)
		{
			int counter = 0;
			for (int k = j + 1; k < 5; k++)
				if (hands[i][j] == hands[i][k])
					counter++;
			if (counter == 2)
				three_of_kind = hands[i][j]; // found three of a kind
		}
		if (three_of_kind)
		{
			for (int j = 0; j < 5; j++)
			{
				bool flag = false;
				for (int k = j + 1; k < 5; k++)
				{
					if (hands[i][j] == hands[i][k] && hands[i][j] != three_of_kind)
					{
						flag = true;
						break ;
					}
				}
				if (flag)
				{
					houses.push_back(hands[i]);
					break ;
				}
			}
		}
	}
	return operate(houses, hands, bids, rank);
}

int three_of_a_kind(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----THREE OF A KIND----" << endl;
	vector<string> threes;
	unsigned long long sum = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int counter = 0;
			for (int k = j + 1; k < 5; k++)
			{
				if (hands[i][j] == hands[i][k])
					counter++;
			}
			if (counter == 2)
			{
				threes.push_back(hands[i]);
				break ;
			}
		}
	}
	return operate(threes, hands, bids, rank);
}

int two_pairs(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----TWO PAIRS----" << endl;
	vector<string> two_pairs;
	unsigned long long sum = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		int counter = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int k = j + 1; k < 5; k++)
			{
				if (hands[i][j] == hands[i][k])
					counter++;
			}
			if (counter == 2)
			{
				two_pairs.push_back(hands[i]);
				break ;
			}
		}
	}
	return operate(two_pairs, hands, bids, rank);
}

int one_pair(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----ONE PAIR----" << endl;
	vector<string> pairs;
	unsigned long long sum = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			bool flag = false;
			for (int k = j + 1; k < 5; k++)
			{
				if (hands[i][j] == hands[i][k])
				{
					flag = true;
					break ;
				}
			}
			if (flag)
			{
				pairs.push_back(hands[i]);
				break ;
			}
		}
	}
	return operate(pairs, hands, bids, rank);
}

int high_card(vector<string> &hands, vector<int> &bids, int &rank)
{
	cout << "----HIGH CARDS----" << endl;
	vector<string> high_cards;
	unsigned long long sum = 0;

	high_cards = hands;
	std::sort(high_cards.begin(), high_cards.end(), compareHands);
	return operate(high_cards, hands, bids, rank);
}

int main()
{
    fstream file;
	string line;
	vector<int> bids;
	vector<string> hands;
	unsigned long long sum = 0;
	int rank = 0;
	file.open("input.txt");
	get_hands_bids(file, hands, bids, rank);

	sum += five_of_a_kind(hands, bids, rank);
	sum += four_of_a_kind(hands, bids, rank);
	sum += full_house(hands, bids, rank);
	sum += three_of_a_kind(hands, bids, rank);
	sum += two_pairs(hands, bids, rank);
	sum += one_pair(hands, bids, rank);
	sum += high_card(hands, bids, rank);

	cout << "final: " << sum << endl;
    return 0;
}