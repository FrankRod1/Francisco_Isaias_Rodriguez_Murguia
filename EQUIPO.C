/*
 * Graph.c
 *
 *  Created on: 05/07/2018
 *      Author: Lanix
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


typedef enum {false, true} boolean;
typedef void *Type;
typedef struct strList *List;


List list_create();

int list_size(List l);

void list_add(List l, Type data);

Type list_get(List l, int p);

void list_set(List l, Type data, int p);

Type list_remove(List l, int p);

void list_destroy(List l);

typedef void (*Print)(Type);





typedef struct strGraphNode * Vertex;
typedef struct strGraph *Graph;
boolean isEmpty(List);

typedef int ( *CMP ) (Type, Type); //Puntero a función "Comparadora"

unsigned long graph_outDegree(Graph g, Type source);

Graph graph_create ( CMP );
void graph_destroy( Graph );
boolean graph_print(Graph g, Print p);

struct strGraphNode{
	int id;
	Type data;
	List followingList;
};

struct strGraph{
	Vertex *arrVertex;
	unsigned long numVertex;
	unsigned long numArris;
	CMP cmpFunction;
};


typedef struct {
		int id;
		char nombre[50];
		char fchNacimiento[40];
		char etapa[200];
	} strPerson;

Graph graph_create (CMP comparator){
	Graph graph = (Graph) malloc(sizeof(struct strGraph));
	if(graph == NULL)
		return NULL;
	graph->arrVertex = NULL;
	graph->numVertex = 0;
	graph->numArris = 0;
	graph->cmpFunction = comparator;
	return graph;
}

void graph_destroy(Graph g){
	int i;
	for(i=0; i<g->numVertex; i++)
		list_destroy(g->arrVertex[i]->followingList);
	free(g->arrVertex);
	free(g);
}

unsigned long graph_vertexCount(Graph g){
	if(g == NULL)
		return 0;
	return g->numVertex;
}

unsigned long graph_edgeCount(Graph g){
	if(g == NULL)
		return 0;
	return g->numArris;
}

boolean graph_hasEdge(Graph g, Type source, Type sink){
    for(int i=0; i<g->numVertex; i++){
        if(g->cmpFunction(source, g->arrVertex[i]->data)){
            Vertex aux=g->arrVertex[i];
            for(i=0; i<g->numVertex; i++){
                if(g->cmpFunction(sink, g->arrVertex[i]->data)){
                    Vertex auxSink=g->arrVertex[i];
                    for(int i=0; i<graph_outDegree(g, aux->data); i++){
                        if(list_get(aux->followingList, i)==auxSink){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

boolean graph_addEdge(Graph g, Type source, Type sink){
	int i;
	for(i=0; i<g->numVertex; i++){
		if(g->cmpFunction(source, g->arrVertex[i]->data)){
			Vertex aux=g->arrVertex[i];
			for(i=0; i<g->numVertex; i++){
				if(g->cmpFunction(sink, g->arrVertex[i]->data)){
					Vertex auxSink=g->arrVertex[i];
					if(graph_hasEdge(g, aux->data, auxSink)==false)
						return false;
					else{
						list_add(aux->followingList, auxSink);
						g->numArris++;
						return true;
					}
				}
			}
		}
	}
	return false;
}


unsigned long graph_outDegree(Graph g, Type source){
	int i;
	for(i=0; i<g->numVertex; i++){
		if(g->cmpFunction(source, g->arrVertex[i]->data)){
			return list_size(g->arrVertex[i]->followingList);
		}
	}
	return 0;
}

boolean graph_addVertex(Graph g, Type data){
	if(g->arrVertex == NULL){
		g->arrVertex = (Vertex*) malloc(sizeof(Vertex) * 1);
		if(g->arrVertex == NULL)
			return false;
		g->arrVertex[0] = (Vertex) malloc(sizeof(struct strGraphNode));
		if(g->arrVertex[0] == NULL)
			return false;
		g->arrVertex[0]->id = g->numVertex+1;
		g->arrVertex[0]->data = data;
		g->arrVertex[0]->followingList = list_create();
		g->numVertex++;
		return true;
	}

	int i;
	for(i=0; i<g->numVertex; i++){
		if(g->cmpFunction(data , g->arrVertex[i]->data))
			return false;
	}
	Vertex *temp = (Vertex*) realloc(g->arrVertex, (g->numVertex + 1) * sizeof(Vertex));
	if (temp == NULL)
		return false;
	g->arrVertex = temp;
	g->arrVertex[i] = (Vertex) malloc(sizeof(struct strGraphNode));
	if(g->arrVertex[i] == NULL)
		return false;
	g->arrVertex[i]->id = g->numVertex+1;
	g->arrVertex[i]->data = data;
	g->arrVertex[i]->followingList = list_create();
	g->numVertex++;
	return true;
}

boolean graph_print(Graph g, Print p){
  int i;
  if(g==NULL){
    return false;
  }
  else{
    for(i=0;i<g->numVertex;i++){
    printf("Vertice %d\n",g->arrVertex[i]->id);
    p(g->arrVertex[i]->data);
    while(isEmpty(g->arrVertex[i]->followingList)==false){
        if(isEmpty(g->arrVertex[i]->followingList)==true){
            printf("No tiene enlaces.\n");
        }
        else{
            printf("Esta enlazado con: \n");
            for(int j=0;j<list_size(g->arrVertex[i]->followingList);j++){
                Vertex eje=(Vertex)list_get(g->arrVertex[i]->followingList,j);
                printf("%d\n", eje->id);
        }
        }


    }
  }
  }
  return true;
}


struct strNode{
	Type Data;
	struct strNode *next;
	struct strNode *prior;
};

typedef struct strNode Node;

struct strList{
	Node *first;
	Node *last;
	unsigned int size;
};

List list_create(){
	List l;
	l=(List)malloc(sizeof(struct strList));
	l->size=0;
	l->last=NULL;
	l->first=NULL;
	return l;
}

int list_size(List l){
	if(l!=NULL)
		return l->size;
	else
		return -1;
}

Node * createNode(Type data){
	Node *new;
	new=(Node *)malloc(sizeof(Node));
	new->Data=(void *)malloc(sizeof(*data));
	memcpy(new->Data, data, sizeof(*data));
	new->next=NULL;
	new->prior=NULL;
	return new;
}

void list_add(List l, Type data){
	//Agrega un elemento al final de la lista
	//e incrementa el size
	if(l!=NULL){
		Node *new;
		new=createNode(data);
		if(l->size==0)
		{
			l->first=new;
			l->last=new;
		}
		else{
			l->last->next=new;
			new->prior=l->last;
			l->last=new;
		}
		l->size++;
	}
}

Type list_get(List l, int p){
	Type value=NULL;
	Node *current=NULL;
	int i=0;
	int s=l->size;
	if(l!=NULL){
		if ((p>=0) && (p<s)){
			current=l->first;
			while(i<p){
				current=current->next;
				i++;
			}
			value=current->Data;
		}
	}
	return value;
}

void list_set(List l, Type data, int p){
	Node *current=NULL;
	int i=0;
	int s=l->size;
	if(l!=NULL){
		if ((p>=0) && (p<s)){
			current=l->first;
			while(i<p){
				current=current->next;
				i++;
			}
			current->Data=data;
		}
	}
}

Type list_remove(List l, int p){
	Node *current=NULL;
	Type tmp;
	int i=0;
	int s=l->size;
	if(l!=NULL){
		//Buscar el nodo a remover
		if ((p>=0) && (p<s)){
			current=l->first;
			while(i<p){
				current=current->next;
				i++;
			}
		}
		if((p==0)&&(s==1)){
			tmp=current->Data;
			l->first=NULL;
			l->last=NULL;
			l->size=0;
			free(current);
			return tmp;
		}else{
			if(p==0) //Se va a eliminar el nodo inicial
			{
				tmp=current->Data;
				l->first=current->next;
				l->first->prior=NULL;
				l->size--;
				free(current);
				return tmp;
			}
			else{
				if(p==(s-1))//Se va a eliminar el nodo final
				{
					tmp=current->Data;
					l->last=current->prior;
					l->last->next=NULL;
					l->size--;
					free(current);
					return tmp;
				}
				else
				{//El elemento a remover esta en medio
					tmp=current->Data;
					current->prior->next=current->next;
					current->next->prior=current->prior;
					free(current);
					return tmp;
				}
			}
		}

	}
	return NULL;
}

void list_destroy(List l){
	while(list_size(l)>0)
		list_remove(l, 0);
	free(l);
}





int cmpInteger (void* v1, void* v2){
	int num1 = *(int *)v1;
	int num2 = *(int *)v2;

	if(num1 == num2)
		return 1;
	else
		return 0;
}

void printInt(void* v1){
	strPerson num1 = *(strPerson *)v1;
	puts(num1.nombre);
	puts(num1.fchNacimiento);
	puts(num1.etapa);
}

#define NUMCHARS 200


int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	Graph grafo1;
	grafo1 = graph_create( cmpInteger );
	if(grafo1 != NULL)
		printf("Grafo creado correctamente\n");

	FILE *archivoVertexPerson;
	archivoVertexPerson = fopen("vertex_person.csv", "rt"); //Abrir para leer
	if (archivoVertexPerson != NULL)
		printf("Vertex_Person se abrió para lectura\n");



	strPerson arrPerson_Movies[250];

	char linea[NUMCHARS];

	int i, j;
	int countStruct = 0;
	puts("Separando Lineas de Person");
	while (!feof(archivoVertexPerson)) {
		fgets(linea, NUMCHARS, archivoVertexPerson);
		//puts(linea);

		arrPerson_Movies[countStruct].id = 1;

		i = 0;
		j = 0;

		while (linea[j] != ',') {
			arrPerson_Movies[countStruct].nombre[i] = linea[j];
			j++;
			i++;
		}
		arrPerson_Movies[countStruct].nombre[i] = '\0';
		j++;

		i = 0;
		while (linea[j] != ',') {
			arrPerson_Movies[countStruct].fchNacimiento[i] = linea[j];
			j++; i++;
		}
		arrPerson_Movies[countStruct].fchNacimiento[i] = '\0';
		j++;

		i = 0;
		while (linea[j] != '\0') {
			arrPerson_Movies[countStruct].etapa[i] = linea[j];
			j++; i++;
		}
		arrPerson_Movies[countStruct].etapa[i] = '\0';


		countStruct++;
	}//Cierre del While
	int w1,w2;
		for (w1 = 0; w1 < countStruct; w1++) {
			graph_addVertex(grafo1, &arrPerson_Movies[w1]);
			w2 = w1+1;
			graph_print(grafo1, printInt);
	//		printf("%d\n",arrPerson_Movies[i].id );
	//		printf("name:%s\n", arrPerson_Movies[i].nombre);
	//		printf("fch:%s\n", arrPerson_Movies[i].fchNacimiento);
	//		printf("etapa: ->");
	//		puts(arrPerson_Movies[i].etapa);
		}
	puts("Cadenas Independientes");
	fclose(archivoVertexPerson);


	FILE *archivoVertexMovies;
	archivoVertexMovies = fopen("vertex_movies.csv", "rt");	//Abrir para leer
	if(archivoVertexMovies != NULL)
		printf("Vertex_Movies se abrió para lectura\n");

	puts("Separando Lineas de Movies");
	while (!feof(archivoVertexMovies )) {
		fgets(linea, NUMCHARS, archivoVertexMovies );
		//puts(linea);
		arrPerson_Movies[countStruct].id = 2;

		i = 0;
		j = 0;
		while (linea[j] != ',') {
			arrPerson_Movies[countStruct].nombre[i] = linea[j];
			j++;
			i++;
		}
		arrPerson_Movies[countStruct].nombre[i] = '\0';
		j++;

		i = 0;
		while (linea[j] != ',') {
			arrPerson_Movies[countStruct].fchNacimiento[i] = linea[j];
			j++; i++;
		}
		arrPerson_Movies[countStruct].fchNacimiento[i] = '\0';
		j++;

		i = 0;
		while (linea[j] != '\0') {
			arrPerson_Movies[countStruct].etapa[i] = linea[j];
			j++; i++;
		}
		arrPerson_Movies[countStruct].etapa[i] = '\0';

		countStruct++;
	}//Cierre del While

		for (w2; w2 < countStruct; w2++) {
			graph_addVertex(grafo1, &arrPerson_Movies[w2]);
			graph_print(grafo1, printInt );
	//		printf("%d\n",arrPerson_Movies[i].id );
	//		printf("titulo:%s\n", arrPerson_Movies[i].nombre);
	//		printf("estreno:%s\n", arrPerson_Movies[i].fchNacimiento);
	//		printf("tagline: ->");
	//		puts(arrPerson_Movies[i].etapa);
		}
	puts("Cadenas Independientes");
	fclose(archivoVertexMovies);





	FILE *archivoEdges;
	archivoEdges = fopen("edges_PersonMovies.csv", "rt");	//Abrir para leer
	if(archivoEdges != NULL)
		printf("EDGES_PersonMovies se abrió para lectura\n");

	typedef struct {
		char namePerson[40];
		char titleMovie[200];
	} strEdges;

	strEdges arrEdges[250];

	puts("Separando Lineas de EDGES");
	countStruct = 0;
	while (!feof(archivoEdges )) {
		fgets(linea, NUMCHARS, archivoEdges );
		//puts(linea);

		i = 0;
		j = 0;
		while (linea[j] != ',') {
			arrEdges[countStruct].namePerson[i] = linea[j];
			j++; i++;
		}
		arrEdges[countStruct].namePerson[i] = '\0';
		j++;


		i = 0;
		while (linea[j] != '\0') {
			arrEdges[countStruct].titleMovie[i] = linea[j];
			j++; i++;
		}
		arrEdges[countStruct].titleMovie[i] = '\0';

		countStruct++;
	}//Cierre del While

	//	for (i = 1; i < countStruct-1; i++) {
	//		printf("nombrePersona:%s\n", arrEdges[i].namePerson);
	//		printf("tituloPelicula:%s\n", arrEdges[i].titleMovie);
	//	}
	puts("Cadenas Independientes");
	fclose(archivoEdges);




	Type valor[10];
	for(i=0; i<10; i++){
		j = 10 + i;
		valor[i] = &j;
		graph_addVertex(grafo1, valor[i]);
		graph_print(grafo1, printInt );
	}

	printf("El valor de j: %d", j);

	return 0;
}//Termina MAIN


boolean isEmpty(List who){
	if (who->size==0)
		return true;
	else
		return false;
}




