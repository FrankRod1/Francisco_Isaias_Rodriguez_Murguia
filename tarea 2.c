#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#define MAX 50000000000

typedef struct {
	long long int sup;
	long long int inf;
	double	res;
}lims;

double p=0;

DWORD WINAPI calcularPi(void *);

int main(void)
{
	setbuf(stdout, NULL);
	fflush(stdout); 
	int time;
	int i;
	int num;
	long long int l;

	HANDLE array[16]; 
	lims lim[16];      

	printf("Cuantos hilos necesitas?\n");
	scanf("%d", &num);
	l = MAX/num;

	clock_t init = clock();

	for(i=0;i<num;i++){
		lim[i].inf=l*i+1;
		lim[i].sup=l*(i+1);
		lim[i].res=0;
		array[i]=CreateThread(NULL,0,calcularPi,(void *)&lim[i],0,NULL);
	}

	for(i=0;i<num;i++){
			WaitForSingleObject(array[i],INFINITE);
		}


	for(i=0;i<num;i++){
			p=p+lim[i].res;
			}

	clock_t end = clock();
	printf("Pi : %0.10lf\n",p);
	time = ((end-init)/CLOCKS_PER_SEC)*1000;
	printf("El tiempo de calculo fueron %d ms", time);
	
	return 0;
}

DWORD WINAPI  calcularPi(void * param){
	lims *pLim= (lims*)param;
	long long int i;

	for (i=pLim->inf; i<pLim->sup; i++){
		pLim->res+=((i-1) &1 ? -1.0 : 1.0 )/(2*i-1);
	}
	pLim->res=(pLim->res)*4;
	return 0;
}
