// PART 1
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main ()
{
	int sum = 0;
	char d[3];
	d[2] = '\0';
	string line;
	ifstream file("input.txt");
	while(getline(file, line))
	{
		int i = 0, y = line.size();
		while (!isdigit(line[i]))
			i++;
		d[0] = line[i];
		while (!isdigit(line[y]))
			y--;
		d[1] = line[y];
		sum += atoi(d);
	}
	printf("%d", sum);
	return 0;
}