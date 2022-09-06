#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
void sort(long int **buffer, int x, int y);
int solve(long int **buffer, int x, int y);
int main(int argc, char const *argv[])
{
	FILE *in, *out;
	char infilename[]="orchestras.in";
	char outfilename[]="orchestras.out";
	int musicians, instruments;
	long int **reward;
	long int totalMusicians;
	in=fopen(infilename, "r");
	if (!in) {
		printf("Error opening %s!", infilename);
		exit(0);
	}
	out=fopen(outfilename, "w");
	if (!out) {
		printf("Error opening %s!", outfilename);
		exit(0);
	}
	if (!fscanf(in, "%d %d\n", &musicians, &instruments)) {
		printf("Encountered an error while reading the contents of the %s file!", infilename);
		exit(0);
	}
	reward=(long int **)malloc(sizeof(long int *)*instruments);
	for (int i=0;i<instruments;i++) {
		reward[i]=(long int *)malloc(sizeof(long int)*musicians);
		for (int y=0;y<musicians;y++) {
			if (!fscanf(in, "%ld ", &reward[i][y])) {
				printf("Encountered an error while reading the contents of the %s file!", infilename);
				exit(0);
			}
		}
	}
	fprintf(out, "%d\n", solve(reward, instruments, musicians));
	for (int i=0;i<instruments;i++) {
		free(reward[i]);
	}
	free(reward);
	fclose(in);
	fclose(out);
	return 0;
}
void sort(long int **buffer, int x, int y)
{
	long int temp;
	bool changed=TRUE;
	while(changed) {
		changed=FALSE;
		for (int i=0;i<x;i++) {
			for (int g=1;g<y;g++) {
				if (buffer[i][g-1]>buffer[i][g]) {
					temp=buffer[i][g-1];
					buffer[i][g-1]=buffer[i][g];
					buffer[i][g]=temp;
					changed=TRUE;
				}
			}
		}
		
	}
	changed=TRUE;
	while(changed) {
		changed=FALSE;
		for (int i=0;i<y;i++) {
			for (int g=1;g<x;g++) {
				if (buffer[g-1][i]<buffer[g][i]) {
					temp=buffer[g-1][i];
					buffer[g-1][i]=buffer[g][i];
					buffer[g][i]=temp;
					changed=TRUE;
				}
			}
		}
	}
}
int solve(long int **buffer, int x, int y)
{
	int diff=0;
	sort(buffer, x, y);
	for (int i=0;i<y;i++) {
		if ((abs(buffer[0][i]-buffer[x-1][i])>diff) || (diff==0)) {
			diff=abs(buffer[0][i]-buffer[x-1][i]);
		}
	}
	return diff;
}
