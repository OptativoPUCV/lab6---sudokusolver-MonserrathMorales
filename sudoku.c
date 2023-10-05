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

  // rellenar la casilla con un valor del 1 al 9, solo si cumple con las reglas del sudoku (que no se repita el numero en la fila, columna o cuadrado [3][3])
int is_valid(Node* n){ 
      for(size_t i = 0; i < 9; i++) {
        for(size_t k = 0; k < 9; k++) {
          int valor = n->sudo[i][k];

          // condicion 1: No se repitan números en las filas
          size_t fila = i;
          while(fila < 9) {
            fila++;
            if(n->sudo[fila][k] == valor) {
              return 0;
            }
          }

          // condicion 2: que el numero no este en la misma columna
          size_t columna = k;
          while(columna < 9) {
            columna++;
            if(n->sudo[i][columna] == valor) {
              return 0;
            }
          }
          // condicion 3: que el numero no este en el mismo cuadrado (3x3)
          if((i==0&&k==0) || (i==0&&k==3) || (i==0&&k==6) || (i==3&&k==0) || (i==3&&k==3) || (i==3&&k==6) || (i==6&&k==0) || (i==6&&k==3) || (i==6&&k==6))
          for(fila = i; fila < i + 3; fila++) {
            for(columna = k; columna < k + 3; columna++) {
              if(n->sudo[fila][columna] == valor) {
                return 0;
              }
            }
          }
        }
      }
        
    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();

  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      // si esta vacio, crear una posible jugada (nodo adyacente). Se debe copiar el nodo n.
      if(n->sudo[i][k] == ' ') {
        int num = 1;
        while(num <= 9) {
          Node* posibleJugada = copy(n);
          posibleJugada->sudo[i][k] = num;

          if (is_valid(posibleJugada)) {
            pushBack(list, posibleJugada);
          } else {     
            free(posibleJugada);
          }
        }
        // for (int num = 1; num <= 9; num++) {
      }
    }
  }
  return list;
}


int is_final(Node* n){
    return 0;
}


Node* DFS(Node* initial, int* cont){ /*
  Stack * pila = createStack();
  push(pila,initial);
  
  while (!is_empty(pila)){
    Node * nodo = first(pila);
    if (nodo == NULL) {
      continue;
    }
    
    List * adj = get_adj_nodes(nodo);
    Node * aux = first(adj);
    
    while(aux){
        push(pila,aux);
        aux=next(adj);
    }
  } */
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