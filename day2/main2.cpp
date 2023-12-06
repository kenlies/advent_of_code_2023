// PART 2
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main ()
{
	int powersum = 0;
	string line;
	ifstream file("input.txt");
	while(getline(file, line))
	{
		int size = line.size();
		int possible = 1;
		int i = 0;
		int l_red = 0;
		int l_green = 0;
		int l_blue = 0;
		for(; line[i] != ':'; i++);
		i = i + 2;
		for (; i < size; i++)
		{
			while (line[i] != ';' && i < size)
			{
				int red = 12;
				int green = 13;
				int blue = 14;
				if (isdigit(line[i]))
				{
					int num;
					if (!isdigit(line[i + 1]))
						num = atoi(&line[i]);
					else
					{
						char p[3];
						p[0] = line[i];
						p[1] = line[i + 1];
						p[2] = '\0';
						num = atoi(p);
					}
					for (; line[i] != 'b' && line[i] != 'g' && line[i] != 'r'; i++);
					switch(line[i])
					{
						case 114: // red
							red -= num;
							if (num >= l_red)
								l_red = num;
							break ;
						case 103: // green
							green -= num;
							if (num >= l_green)
								l_green = num;
							break ;
						case 98:  // blue
							blue -= num;
							if (num >= l_blue)
								l_blue = num;
							break ;
					}
				}
				i++;
			}
		}
		int power = l_red * l_green * l_blue;
		powersum += power;
	}
	printf("%d", powersum);
	return 0;
}