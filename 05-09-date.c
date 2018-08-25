#include <stdio.h>
#include <string.h>

static short daytab[2][13] =
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isleap(int y)
{
	return (y%4 == 0 && y%100 != 0) || y%400 == 0;
}

int day_of_year(int y, int m, int d)
{
	short *dt;

	if (m < 1 || m > 12)
		return -1;

	dt = daytab[isleap(y)] + 1;
	while (--m)
	{
		printf("\t%3d (%2d)\n", d, *dt);
		d += *dt++;
	}
	return d;
}

int month_day(int y, int yearday, int *pm, int *pd)
{
	short *dt;
	int leap;

	if (yearday < 1 || yearday > 366)
		return -1;
	leap = isleap(y);

	dt = daytab[leap];

	while (yearday > *dt)
	{
		printf("\t%3d (%2d)\t%ld\n",
				yearday, *dt, dt - daytab[leap]);
		yearday -= *dt++;
	}
	*pm = dt - daytab[leap];
	*pd = yearday;
	return 1;
}

int main(int argc, char **argv)
{
	int a,b,c, out_m, out_d;

	if (argc != 2)
	{
		printf("Usage: %s (dy|md)\n", argv[0]);
		return 1;
	}
	if (strcmp(argv[1], "dy") == 0)
	{
		printf("y/m/d: ");
		scanf("%d/%d/%d", &a, &b, &c);
		out_d = day_of_year(a, b, c);
		if (out_d < 0)
			printf("Invalid date\n");
		else
			printf("%d day of the year\n", out_d);
	}
	else
	{
		printf("y/ddd: ");
		scanf("%d/%d", &a, &b);
		c = month_day(a, b, &out_m, &out_d);
		if (c < 0)
			printf("Invalid day of year\n");
		else
			printf("%d/%d\n", out_m, out_d);
	}
	return 0;
}
