#include<stdio.h>

struct Alumno{
	int expediente;
	char nombre;
	int carrera;
	int edad;
};

int main(){
	int op, i, con=0;
	int *des=&con;
	static struct Alumno alumnos[20];
	while(op!=6){
		printf("			Menu			\na.Registrar nuevo alumno[1]\nb.Imprimir datos[2]\nc.Eliminar alumno[3]\nd.Buscar alumno\n	-Por expediente[4]\n	-Por edad[5]\ne.Salir[6]\n");
		scanf("%d", &op);
		while ((getchar()) != '\n');
	
		if(op==1){
			printf("\n*****************\n");
			printf("Expediente del alumno\n");
			scanf("%d", &alumnos[*des].expediente);
			while ((getchar()) != '\n');
			printf("Nombre del alumno\n");
			scanf("%c", &alumnos[*des].nombre);
			while ((getchar()) !='\n');
			printf("Carrera del alumno\n");
			scanf("%d", &alumnos[*des].carrera);
			while ((getchar()) !='\n');
			printf("Edad del alumno\n");
			scanf("%d", &alumnos[*des].edad);
			while ((getchar()) !='\n');
			printf("\n*****************\n");
			if(con!=20){
				*des++;
				con++;
			}
		}
		else if(op==2){
			for (i=0; i<con; i++){
				printf("\n*****************\n");
				printf("Expediente del alumno: %d\n", alumnos[i].expediente);
				printf("Nombre del alumno: %c\n", alumnos[i].nombre);
				printf("Carrera del alumno: %d\n", alumnos[i].carrera);
				printf("Edad del alumno: %d\n", alumnos[i].edad);
				printf("\n*****************\n");
			}
			
		}
		else if(op==3){
			int num, num1;
			printf("Numero del alumno a eliminar: ");
			scanf("%d", &num);
			num1=num-1;
			int *pnum=&num1;
			alumnos[*pnum].expediente=NULL;
			alumnos[*pnum].nombre=NULL;
			alumnos[*pnum].carrera=NULL;
			alumnos[*pnum].edad=NULL;
		}
		else if(op==4){
			int exp;
			printf("Numero de expediente: ");
			scanf("%d", &exp);
			int *pexp=&exp;
			for(i=0; i<20; i++){
				if(*pexp==alumnos[i].expediente){
				printf("\n*****************\n");
				printf("Expediente del alumno: %d\n", alumnos[i].expediente);
				printf("Nombre del alumno: %c\n", alumnos[i].nombre);
				printf("Carrera del alumno: %d\n", alumnos[i].carrera);
				printf("Edad del alumno: %d\n", alumnos[i].edad);
				printf("\n*****************\n");
				}
			}
		}
		else if(op==5){
			int edad;
			printf("Edad del alumno: \n");
			scanf("%d", &edad);
			int *pedad=&edad;
			for(i=0; i<20; i++){
				if(*pedad==alumnos[i].edad){
				printf("\n*****************\n");
				printf("Expediente del alumno: %d\n", alumnos[i].expediente);
				printf("Nombre del alumno: %c\n", alumnos[i].nombre);
				printf("Carrera del alumno: %d\n", alumnos[i].carrera);
				printf("Edad del alumno: %d\n", alumnos[i].edad);
				printf("\n*****************\n");
				}
			}
		}
	};
	
	
	return 0;
}
