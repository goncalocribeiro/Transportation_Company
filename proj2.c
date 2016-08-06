/*
Instituto Superior Tecnico - LEIC
ASA - Projeto 2
Goncalo Ribeiro - 82303
Andre Mendonca - 82304
Grupo: AL009
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

typedef struct node {
	int disc;
	int totalDisc;
} Node;
typedef Node* NodeL;

typedef struct arco {
	int prev;
	int target;
	int cost;
} Arco;
typedef Arco* ArcoL;

NodeL newNode(){
	NodeL new = (NodeL) malloc(sizeof(Node));
	new->disc = INT_MAX;
	new->totalDisc=0;

	return new;
}

ArcoL addEdge(int u, int v, int w, NodeL nodes[]){
	ArcoL new = (ArcoL) malloc(sizeof(Arco));
	new->prev = u;
	new->target = v;
	new->cost = w;

	return new;
}

void BellmanFord(NodeL nodes[], ArcoL arcos[], int fID, int n_localidades, int n_ligacoes){
	int boolean=TRUE, i=1;
	NodeL firstNode;
	NodeL secondNode;
	ArcoL vAdjacente;

	/*Define tempos de descoberta em infinito*/
	while(i<=n_localidades){
		firstNode = nodes[i];
		firstNode->disc = INT_MAX;
		i++;
	}

	/*Define tempo de descoberta do vertice inicial a zero*/
	firstNode = nodes[fID];
	firstNode->disc=0;

	/*Processo de relaxamento*/
	while(boolean==TRUE){
		boolean = FALSE;
		for (i=1; i<=n_ligacoes; i++){
			vAdjacente = arcos[i];
			firstNode = nodes[vAdjacente->prev];
			secondNode = nodes[vAdjacente->target];
			if(secondNode->disc > firstNode->disc + vAdjacente->cost && firstNode->disc!=INT_MAX){
				secondNode->disc = firstNode->disc + vAdjacente->cost;
				boolean = TRUE;
            }
		}
	}
}

void freeM(ArcoL arcos[], NodeL nodes[], int n_localidades, int n_ligacoes){
	int i=1;

	while(i<=n_ligacoes){
        free(arcos[i]);
        i++;
    }

    i=1;
    while(i<=n_localidades){
      free(nodes[i]);
      i++;
    }
}

int main(){
	int fID, n_localidades, n_filiais, n_ligacoes, u, v, w, ponto_encontro=1, boolean=TRUE;
	NodeL node;
	int i=1, j=1, k=1, x=1, x1=1, y=2, z=1;

    /*Le a primeira linha do input (Localidades, Filiais, Ligacoes)*/
    scanf("%d %d %d", &n_localidades, &n_filiais, &n_ligacoes);

	ArcoL arcos[n_ligacoes+1];
	NodeL nodes[n_localidades+1];
	int filiaisID[n_filiais+1];

	/*Inicializa a lista dos nodes*/
	for(i=1; i<=n_localidades; i++){
	    nodes[i] = newNode();
	}

	/*Guarda filiais*/
	for(j=1; j<=n_filiais; j++){
	    scanf("%d", &fID);
		filiaisID[j] = fID;
	}

	/*Guarda localidades*/
	for (k=1; k<=n_ligacoes; k++){
		scanf("%d %d %d", &u, &v, &w);
		arcos[k] = addEdge(u, v, w, nodes);
	}

    /*Inicia processo*/
    while(x<=n_filiais){
    	fID=filiaisID[x];
		BellmanFord(nodes, arcos, fID, n_localidades, n_ligacoes);
		for(x1=1; x1<=n_localidades; x1++){
			node = nodes[x1];
			if(node->totalDisc != INT_MAX && node->disc != INT_MAX){
			    node->totalDisc += node->disc;
			} else {
                node->totalDisc = INT_MAX;
			}
		}
		x++;
    }

	if(nodes[1]->totalDisc != INT_MAX){
	    boolean=FALSE;
	}

	while(y<=n_localidades){
		if((nodes[y])->totalDisc < (nodes[ponto_encontro])->totalDisc){
		    ponto_encontro=y;
		}

		if((nodes[y])->totalDisc!=INT_MAX){
		    boolean=FALSE;
		}
		y++;
	}

	if(boolean==FALSE){
		printf("%d %d\n", ponto_encontro, (nodes[ponto_encontro])->totalDisc);
		for(z=1; z<=n_filiais; z++){
			BellmanFord(nodes, arcos, filiaisID[z], n_localidades, n_ligacoes);
			w = (nodes[ponto_encontro])->disc;
			printf("%d ", w);
		}
		printf("\n");
	} else {
		printf("N\n");
	}

    /*Liberta a memoria que ja nao e necessaria*/
	freeM(arcos, nodes, n_localidades, n_ligacoes);
	return 0;
}
