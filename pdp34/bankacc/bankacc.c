/* USER: jimchrist
LANG: C
TASK: bankacc */

#include <stdio.h>
#include <stdlib.h>
int main() {
	const long MAXN=500000;
	long Acc[MAXN];
	FILE *in,*out;
	long N;
	char mode;
	long A, X;
	in=fopen("bankacc.in","r");
	out=fopen("bankacc.out","w");
	
	
	if (!in || !out) {
		printf("Error opening files!");
		exit(EXIT_FAILURE);
	}
	fscanf(in,"%ld",&N);
	for (int i=0; i<N; i++) {
		fscanf(in,"\n %c %ld", &mode, &A);
		switch(mode) {
			case 'q':
				fprintf(out,"%ld\n",Acc[A]);
				break;
			case 'd':
				fscanf(in,"%ld",&X);
				Acc[A] += X;
				fprintf(out,"s\n");
				break;
			case 'w':
				fscanf(in,"%ld", &X);
				if (Acc[A] < X) {
					fprintf(out,"f\n");
				}
				else {
					Acc[A] -= X;
					fprintf(out,"s\n");
				}
				break;
		}
	}
	fclose(in);
	fclose(out);
	return 0;
	
}


