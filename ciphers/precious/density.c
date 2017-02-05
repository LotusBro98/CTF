#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct Letter
{
	char c;
	int n;
};

//- - - - GLOBAL - - - -
char codetable[256];
//- - - - GLOBAL - - - -

int countChars(FILE * file, int* all)
{
	int i;
	char c;

	for (i = 0; i < 256; i++)
	{
		all[i] = 0;
	}

	i = 0;
	while (fscanf(file, "%c", &c) == 1)
	{
		all[c]++;
		i++;
	}
	return i;
}

int cmp_q(const void* p1, const void* p2)
{
	return ((struct Letter*)p2)->n - ((struct Letter*)p1)->n;
}

void sortTable(struct Letter * sorted, int * all) {
	int i;
	for (i = 0; i < 256; i++)
	{
		sorted[i].n = all[i];
		sorted[i].c = i;
	}
	qsort(sorted, 256, sizeof(struct Letter), cmp_q);
}

int maxQuantity(struct Letter * sorted) 
{
	int i;
	int max = sorted[0].n;
	for (i = 1; i < 256; i++) 
	{
		if (sorted[i].n > max) max = sorted[i].n;
	}
	return max;
}

void printRow(float length)
{
	int i;
	for (i = 0; i < (int)(length * 100); i++)
		printf("*");
	printf("\n");
}

void printSorted(int n, struct Letter * sorted)
{
	int i;
	float percent;
	float length;

	for (i = 0; i < 256; i++)
	{
		if (sorted[i].n > 0) {
			percent = (float)sorted[i].n / (float)(n);
			length = (float)sorted[i].n / (float)(maxQuantity(sorted));
			printf("%1c  %7.1f%% %7d  ", sorted[i].c, percent*128, sorted[i].n);
			printRow(length);
		}
	}

}

int getSorted(char* filename, struct Letter * sorted)
{
	FILE * file;
	int i;
	int all[256];
	
	file = fopen(filename, "rt");

	i = countChars(file, all);
	sortTable(sorted, all);

	fclose(file);

	return i;
}

void makeCodeTable(struct Letter * bad, struct Letter * good) {
	int i;
	for (i = 0; i < 256; i++) {
		codetable[i] = '?';
	}

	for (i = 0; i < 20; i++) {
		if (good[i].n > 0) {
			codetable[bad[i].c] = good[i].c;
		}
	}

	codetable['\n'] = '\n';
	codetable[' '] = ' ';
}

void decode(char * fnameIn, char * fnameOut)
{
	FILE * in;
	FILE * out;
	char c;

	in = fopen(fnameIn, "rt");
	out = fopen(fnameOut, "wt");

	while (fscanf(in, "%c", &c) == 1)
	{
		fprintf(out, "%c", codetable[c]);
	}

	fclose(in);
	fclose(out);
}

void printCodeTable()
{
	int i;
	for (i = 0; i < 256; i++)
	{
		printf("%c %c\n", i, codetable[i]);
	}
}

int main(int argc, char * argv[])
{
	struct Letter good[256];
	int nGood;
	struct Letter bad[256];
	int nBad;

	if (argc == 4)
	{
		nBad = getSorted(argv[1], bad);
		nGood = getSorted(argv[2], good);

		printSorted(nBad, bad);
		printf("\n\n------------------\n\n");
		printSorted(nGood, good);

		makeCodeTable(bad, good);
		//printCodeTable();

		decode(argv[1], argv[3]);
		return 0;
	} else {
		printf("Wrong Format\n");
		return 1;
	}
}
