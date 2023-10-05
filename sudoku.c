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

  // Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.
int is_valid(Node* n){ 
  int arrAux_fila[9][10] = {0};
  int arrAux_col[9][10] = {0};
  
  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      int num = n->sudo[i][k];

      if(arrAux_fila[i][num] || arrAux_col[k][num]) {
        return 0;
      }
      
      arrAux_fila[i][num] = 1;
      arrAux_col[k][num] = 1;
      
          /*
          // condicion 2: que el numero no este en la misma columna
          for (size_t columna = 0; columna < 9; columna++) {
            if (columna != k && n->sudo[i][columna] == valor) {
              return 0;
            }
          }
          // condicion 3: que el numero no este en el mismo cuadrado (3x3)
          size_t fila_inicial = (i / 3) * 3;
          size_t col_inicial = (k / 3) * 3;
          for(size_t fila = fila_inicial; fila < fila_inicial + 3; fila++) {
            for(size_t columna = col_inicial; columna < col_inicial + 3; columna++) {
              if((fila != i || columna != k) && n->sudo[fila][columna] == valor) {
                return 0;
              }
            }
          }
        }*/
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n){
  List* list = createList();

  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      // si esta vacio, crear una posible jugada (nodo adyacente).
      if(n->sudo[i][k] == 0) {
        for (int num = 1; num <= 9; num++) {
          Node * copiaNodo = copy(n);
          copiaNodo->sudo[i][k] = num;
          pushBack(list, copiaNodo);
        }
        return list;
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