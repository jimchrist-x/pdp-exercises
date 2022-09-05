/* USER: jimchrist
LANG: C
TASK: smalltank */
#include <stdio.h>
#include <stdlib.h>

struct trip {
	long int citystart, cityend;
	long int liters;
};
struct passed {
	long int liters;
	long int tocity;
};
typedef struct trip TRIP;
typedef struct passed PASSED;
long int solve(TRIP *trips, long int cities, long int roads); // Solves the exercise
int main(int argc, char *argv[]) {
	// Variables
	FILE *in, *out;
	char filein[]="smalltank.in";
	char fileout[]="smalltank.out";
	long int cities, roads;
	TRIP *trips;
	
	// Opening Files
	in=fopen(filein, "r");
	if (!in) {
		printf("Error opening %s", filein);
		exit(0);
	}
	out=fopen(fileout, "w");
	if (!out) {
		printf("Error opening %s", filein);
		exit(0);
	}
	// Input
	
	if (!fscanf(in, "%ld %ld\n", &cities, &roads)) {
		printf("Encountered an error while reading the contents of the %s file!", filein);
		exit(0);
	}
	trips=(TRIP *)malloc(sizeof(TRIP)*roads);
	if (!trips) {
		printf("Error allocating memory!");
		exit(0);
	}
	for (long int i=0;i<roads;i++) {
		if (!fscanf(in, "%ld %ld %ld\n",&trips[i].citystart, &trips[i].cityend, &trips[i].liters)) {
			printf("Encountered an error while reading the contents of the %s file!", filein);
			exit(0);
		}
	}
	printf("%ld Cities | %ld Roads\n", cities, roads);
	// Output
	fprintf(out, "%ld\n", solve(trips, cities, roads));
	
	// Exiting
	free(trips);
	fclose(in);
	fclose(out);
	return 0;
}
long int solve(TRIP *trips, long int cities, long int roads) {
	long int min=0, opt=0;
	PASSED **visited=(PASSED **)malloc(sizeof(PASSED *)*cities);
	if (!visited) {
		printf("Error allocating memory!");
		exit(0);
	}
	long int *num=(long int *)malloc(sizeof(long int)*cities);
	if (!num) {
		printf("Error allocating memory!");
		exit(0);
	}
	long int elem=0;
	
	// Initializing roads from city num
	for (long int i;i<cities;i++) {
		num[i]=0;
	}
	// Calculating total routes from a city
	for (long int city=0;city<cities;city++) {
		for (long int road=0;road<roads;road++) {
			if (city==trips[road].citystart) {
				num[city]++;
			}
			else if (city==trips[road].cityend) {
				num[city]++;
			}
			else
				continue;
		}
		visited[city]=(PASSED *)malloc(sizeof(PASSED)*num[city]);
		if (!visited[city]) {
			printf("Error allocating memory!");
			exit(0);
		}	
	}
	
	
	// Storing every route from a city
	for (long int city=0;city<cities;city++) {
		for (long int road=0;road<roads;road++) {
			if (city==trips[road].citystart) {
				visited[city][elem].tocity=trips[road].cityend;
				visited[city][elem].liters=trips[road].liters;
				elem++;
			}
			else if (city==trips[road].cityend) {
				visited[city][elem].tocity=trips[road].citystart;
				visited[city][elem].liters=trips[road].liters;
				elem++;
			}
			else
				continue;
		}
		elem=0;
	}
	
	// Calculating the minimum fuel required
	for (long int city=0;city<cities;city++) {
		for (long int elem=0;elem<num[city];elem++) {
			if ((visited[city][elem].liters<opt) || (opt==0)) {
				opt=visited[city][elem].liters;
			}
		}
		if (opt>min) {
			printf("Found new minimum: %ld\n",opt);
			min=opt;
		}
		opt=0;
	}
	
	for (long int city=0;city<cities;city++) {
		free(visited[city]);
	}
	free(num);
	free(visited);
	return min;
}
