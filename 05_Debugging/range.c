#include <stdio.h>

int str_to_num(char *str)
{
	int i = 0;
	int flag = 0;
	if (str[0] == '-')
	{
		i = 1;
		flag = 1;
	}
	int res = 0;
	while(str[i] != 0)
	{
		res *= 10;
		res += str[i] - '0';
		++i;
	}
	if (flag == 1)
	{
		return (-1) * res;
	}
	return res;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Count of argument should be more or equal to 2.\n");
		return -1;
	}
	int start = 0;
	int finish = 0;
	int step = 1;
	if (argc == 2)
	{
		finish = str_to_num(argv[1]);
	}
	else if (argc == 3)
	{
		start = str_to_num(argv[1]);
		finish = str_to_num(argv[2]);
	}
	else if (argc == 4)
	{
		start = str_to_num(argv[1]);
		finish = str_to_num(argv[2]);
		step = str_to_num(argv[3]);
	}

	int elem = start;
	for (int i = 0; elem < finish;++i)
	{
		elem += step;
	}
	return 0;
}
