#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

    return 1;
}

/* > - Utilice la función Node* copy(Node* n) para copiar nodos. */
List* get_adj_nodes(Node* n){
  List* list=createList();/*
  int numero = 1;
  bool existe = false;

  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      // si esta vacio, crear una posible jugada (nodo adyacente). Se debe copiar el nodo n.
      if(n->sudo[i][k] == ' ') {
        // Node * posibleJugada = (Node *) malloc(sizeof(Node));
        Node * posibleJugada = copy(n);

        // rellenar la casilla con un valor del 1 al 9, solo si cumple con las reglas del sudoku (que no se repita el numero en la fila, columna o cuadrado [3][3])

        // condicion 1: que el numero no este en la misma fila
        while(k < 9) {
          if(posibleJugada->sudo[i][k] == numero) {
            
          }
          k++;
        }

        // condicion 2: que el numero no este en la misma columna
        posibleJugada->sudo[i][k] = numero;


        
        // condicion 3: que el numero no este en el mismo cuadrado (3x3)
        

        
        posibleJugada->sudo[i][k] = numero;

        pushBack(list, posibleJugada);
      }
    }
  }




  */
  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila,initial);
  
  while (size(pila) != 0){
     Node * nodo = pop(pila);
    
     List * adj = get_adj_nodes(nodo);
     Node * aux = first(adj);
    
     while(aux){
        push(pila,aux);
        aux=next(adj);
     }
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/