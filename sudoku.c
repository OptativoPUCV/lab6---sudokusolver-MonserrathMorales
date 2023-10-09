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

/* Esta función inicializa tres arreglos auxiliares, uno para filas, otro para columnas y otro para submatrices, para rastrear números ya vistos. Se verifica que no haya números repetidos en la misma fila, en la misma columna, ni en la misma submatriz 3x3.
Si pasa todas las verificaciones sin encontrar números repetidos, retorna 1, indicando que el Sudoku es válido. En caso contrario, retorna 0, indicando que no es válido. */
int is_valid(Node* n){ 
  int arrAux_fila[10] = {0};
  int arrAux_col[10] = {0};
  int arrAux_subM[10] = {0};

  // condicion 1: Ningun numero repetido en la misma fila
  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      int num_fila = n->sudo[i][k];
      
      if(num_fila != 0) {
        if(arrAux_fila[num_fila] > 0) {
          return 0;
        }
        else {
          arrAux_fila[num_fila] = 1;
        }
      }
    }
    for (int j = 1; j <= 9; j++) {
      arrAux_fila[j] = 0; // reestablecer valores en 0 para siguiente fila.
    }
  }
  // condicion 2: Ningun numero repetido en la misma columna
  for(size_t k = 0; k < 9; k++) {
    for(size_t i = 0; i < 9; i++) {
      int num_col = n->sudo[k][i];
      
      if(num_col != 0) {
        if(arrAux_col[num_col] > 0) {
          return 0;
        }
        else {
          arrAux_col[num_col] = 1;
        }
      }
    }
    for (int j = 1; j <= 9; j++) {
      arrAux_col[j] = 0; // reestablecer valores en 0 para siguiente columna.
    }
  }
  // condicion 3: Ningun numero repetido en la submatriz 3x3
  for(int k = 0; k < 9; k++) {
    for(int p = 0; p < 9; p++) {
      int fila = 3 * (k / 3) + (p / 3);
      int col = 3 * (k % 3) + (p % 3);
      int num_subM = n->sudo[fila][col];

      if(num_subM != 0) {
        if(arrAux_subM[num_subM] > 0) {
          return 0;
        }
        else {
          arrAux_subM[num_subM] = 1;
        }
      }
    }
    for (int indice = 1; indice <= 9; indice++) {
        arrAux_subM[indice] = 0; // reestablecer valores en 0 para siguiente submatriz.
    }
  }
  
  return 1;
}

/* Esta función inicializa una lista vacía (List* list) para almacenar los nodos adyacentes. Se recorren todas las celdas vacías en el tablero de Sudoku y para cada celda vacía, crea una copia del nodo actual y prueba números del 1 al 9 como posibles jugadas. Si una jugada es válida (sin números repetidos en filas, columnas o submatrices), agrega la copia del nodo a la lista de nodos adyacentes. Finalmente Retorna la lista de nodos adyacentes, que representa todas las jugadas posibles en las celdas vacías del Sudoku. */
List* get_adj_nodes(Node* n) {
  List* list = createList();

  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      // si esta vacio, crear una posible jugada (nodo adyacente).
      if(n->sudo[i][k] == 0) {
        for (int num = 1; num <= 9; num++) {
          Node * copiaNodo = copy(n);
          copiaNodo->sudo[i][k] = num;
          
          if(is_valid(copiaNodo)) {
            pushBack(list, copiaNodo);
          }
          else {
            free(copiaNodo);
          }
        }
        return list;
      }
    }
  }
  return list;
}

/* Esta función recorre todas las celdas del tablero de Sudoku utilizando dos bucles anidados. Si encuentra al menos una celda vacía (donde n->sudo[i][k] == 0), retorna 0, indicando que el Sudoku no está completo. Si no encuentra ninguna celda vacía después de recorrer todo el tablero, retorna 1, indicando que el Sudoku está completo y cumple con las reglas del juego. */
int is_final(Node* n) {
  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      if(n->sudo[i][k] == 0) {
        return 0;
      }
    }
  }
    return 1;
}

/* Esta función inicializa una pila y la inserta con el nodo inicial. Mientras la pila no esté vacía, se incrementa el contador, se obtiene y elimina el nodo en la cima de la pila, y si es un estado final, lo devuelve y libera la memoria de la pila. Luego, agrega los nodos adyacentes a la pila. Si no encuentra un estado final, devuelve NULL y libera la memoria de la pila. */
Node* DFS(Node* initial, int* cont) {
  Stack * pila = createStack();
  push(pila,initial);
  
  while (!is_empty(pila)) {
    (*cont)++;
    Node * nodo = top(pila);
    pop(pila);
    if (is_final(nodo)) {
      free(pila);
      return nodo;
    }
    
    List * adj_nodos = get_adj_nodes(nodo);
    Node * nodo_adyac = first(adj_nodos);
    while(nodo_adyac != NULL) {
      push(pila, nodo_adyac);
      nodo_adyac = next(adj_nodos);
    }
    free(adj_nodos);
  }
  free(pila);
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
} */