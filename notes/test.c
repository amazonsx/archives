#include <stdio.h>

int main(){
	int a = 8;
	int b = 10;
	int *p = &a;
	int *q = &a;
	printf("pointers to one variant comparition p == q: %i\n", (p == q));
	q = &b;
	printf("pointers to different variants comparition p == q: %i\n", (p == q));
	printf("p:%i\n", *p);
	printf("q:%i\n", *q);
	b = 8;
	printf("pointers to different variants with same value comparition p == q: %i\n", (p == q));
	printf("p:%i\n", *p);
	printf("q:%i\n", *q);
	p = NULL;
	printf("pointers to NULL and non-NULL  comparition p == q(p=NULL): %i\n", (p == q));
	printf("pointers to NULL and non-NULL  comparition q == p(p=NULL): %i\n", (q == p));
	q = NULL;
	printf("pointers to NULL comparition p == q(p=NULL): %i\n", (p == q));
	printf("pointers to NULL comparition p == p(p=NULL): %i\n", (p == p));



	int c,d= 20;
	printf("c & d: %i, %i\n", c, d);

	a = 4;
	b = 3;
	double division = (double)a/b;
	printf("show a/b has a decimals or note: %f\n", division);

	return 0;
}
