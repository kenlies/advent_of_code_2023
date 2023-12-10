// PART 2
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string nums[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

char determine_val(string line, int first_pos, int mode)
{
	if (!mode)
	{
		int smallest = 9999999;
		int num;
		std::size_t pos;
		for (int i = 0; i < 9; i++)
		{
			pos = line.find(nums[i]);
			if (pos != std::string::npos && pos < smallest)
			{
				smallest = pos;
				num = i;
			}
		}
		if (first_pos < smallest)
			return line[first_pos];
		else
			return num + 1 + 48;
	}
	else
	{
		int highest = 0;
		int num;
		std::size_t pos;
		for (int i = 0; i < 9; i++)
		{
			pos = line.rfind(nums[i]);
			if (pos != std::string::npos && pos > highest)
			{
				highest = pos;
				num = i;
			}
		}
		if (first_pos >= highest)
			return line[first_pos];
		return num + 1 + 48;
	}
}

int main ()
{
	int sum = 0;
	char d[3];
	d[2] = '\0';
	string line;
	ifstream file("input.txt");
	while(getline(file, line))
	{
		int first_pos = 0, second_pos = line.size();
		while (!isdigit(line[first_pos]))
			first_pos++;
		d[0] = determine_val(line, first_pos, 0);
		while (!isdigit(line[second_pos]))
			second_pos--;
		d[1] = determine_val(line, second_pos, 1);
		sum += atoi(d);
	}
	printf("%d", sum);
	return 0;
}