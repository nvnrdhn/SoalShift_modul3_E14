#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_t t[100];
unsigned long long num[100], hasil[100], n;


int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

void *fact( void *ptr )
{
	unsigned long long ans=1;
	unsigned long long *f = (unsigned long long*)ptr;
	pthread_t id = pthread_self();
	for (int i=2;i<=*f;i++)
		ans*=i;
	for (int i=0;i<n;i++) {
		if (pthread_equal(id, t[i])) {
			hasil[i] = ans;
		}
	}
}

int main(int argc, char **argv)
{
	n = argc-1;
    for (int i = 1;i<argc;i++) 
    	sscanf(argv[i], "%llu", &num[i-1]);
    qsort(num, n, sizeof(unsigned long long), cmpfunc);
    for (int i=0;i<n;i++) 
    	pthread_create(&t[i], NULL, fact, (void*)&num[i]);
    for (int i=0;i<n;i++) 
    	pthread_join(t[i], NULL);
    for (int i=0;i<n;i++)
    	printf("%llu! = %llu\n", num[i], hasil[i]);
}