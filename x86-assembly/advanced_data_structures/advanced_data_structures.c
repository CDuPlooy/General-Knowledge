#include <stdlib.h>
#include <stdio.h>

typedef struct sn{
int a;
int dummyValue;
int b;
}sum_numbers;

int main(){
	sum_numbers sn;
	sn.a = 0;
	sn.b = 10;

	printf("%i\n",sn.a + sn.b);
	return 0;
}
