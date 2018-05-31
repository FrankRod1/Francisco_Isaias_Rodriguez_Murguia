#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct{
	char nombre[15];
	float calificacion;
} Profesor;

float averageArray(Profesor arrF[], int n3);
void readArray(Profesor array[], int n);
void mergeArrays(Profesor arr1[] , int n1, Profesor arr2[], int n2, Profesor arrF[], int n3);
void sortArray(Profesor arrF[], int n3);
void printArray(Profesor arrF[], int n3);


void main(){
	setbuf(stdout, NULL);
	fflush( stdin );
	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados
	int n1, n2; //Longitud de los arreglos
	int n3=40;
	
	scanf("%d", &n1);
	readArray(arr1, n1);
	
	scanf("%d", &n2);
	readArray(arr2, n2);

	mergeArrays(arr1, n1, arr2, n2, arrF, n3);  //Fusionar los dos arreglos en un tercer arreglo

	sortArray(arrF, n3);  
	
	printArray(arr1, n1);   //Imprimir el resultado final
	
	return 0;
}

void readArray(Profesor array[], int n){
	for(int i=0; i<n;i++){
		fflush( stdin );
		printf("Profesor %d: ", i+1);
		scanf("%c", &array[i].nombre);
		fflush( stdin );
		printf("Calificacion %d: ", i+1);
		scanf("%f", &array[i].calificacion);
	}
}

void mergeArrays(Profesor arr1[] , int n1, Profesor arr2[], int n2, Profesor arrF[], int n3){
	int i=0;
	int j=0;
	int k=0;
	while (i < n1 && j < n2) {
		if (arr1[i].calificacion <= arr2[j].calificacion) {
			arrF[k].calificacion= arr1[i].calificacion;
			strcpy(arrF[k].nombre, arr1[i].nombre);
			i++;
			k++;
		} 
		else{
			arrF[k].calificacion = arr2[j].calificacion;
			strcpy(arrF[k].nombre, arr1[j].nombre);
			k++;
			j++;
		}
	}
}

void sortArray(Profesor arrF[], int n3){
	Profesor temp;
	temp.nombre;
	temp.calificacion=0.0;
	for (int i=0;i<n3;i++){
		for (int j=0;j<n3;j++){
			if(arrF[j].calificacion < arrF[i].calificacion){
				temp.calificacion=arrF[j].calificacion;
				strcpy(temp.nombre, arrF[j].nombre);
				arrF[j].calificacion=arrF[i].calificacion;
				strcpy(arrF[j].nombre, arrF[i].nombre);
				arrF[i].calificacion=temp.calificacion;
				strcpy(arrF[i].nombre, temp.nombre);
			}
		}
	}
}

void printArray(Profesor arrF[], int n3){
	for(int i=0; i<n3;i++){
		printf("%c %f\n", arrF[i].nombre, arrF[i].calificacion);
	}
}
