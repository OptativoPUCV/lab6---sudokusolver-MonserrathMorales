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
  int arrAux_fila[10] = {0};
  int arrAux_col[10] = {0};
  int arrAux_subM[10] = {0};

  // condicion 1: Ningun numero repetido en la misma fila
  for(size_t i = 0; i < 9; i++) {
    for(size_t k = 0; k < 9; k++) {
      int num_fila = n->sudo[i][k];
      
      if(num_fila != 0) {
        arrAux_fila[num_fila]++;
        if(arrAux_fila[num_fila] > 1) return 0;
      }
    }
    for (int j = 1; j <= 9; j++) {
      arrAux_fila[j] = 0; // reestablecer valores en 0 para siguiente fila.
    } 
  }
  // condicion 2: Ningun numero repetido en la misma columna
  for(size_t k = 0; k < 9; k++) {
    for(size_t i = 0; i < 9; i++) {
      int num_col = n->sudo[i][k];
      
      if(num_col != 0) {
        arrAux_col[num_col]++;
        if(arrAux_col[num_col] > 1) return 0;
      }
    }
    for (int j = 1; j <= 9; j++) {
      arrAux_col[j] = 0; // reestablecer valores en 0 para siguiente columna.
    }
  }
  // condicion 3: Ningun numero repetido en la submatriz 3x3
  for (int k = 0; k < 9; k++) {
    int fila = 3 * (k / 3);
    int col = 3 * (k % 3);
    
    for(size_t i = fila; i < fila + 3; i++) {
      for(size_t k = col; k < col + 3; k++) {
        int num_subM = n->sudo[i][k];
  
        if(num_subM != 0) {
          arrAux_subM[num_subM]++;
          if(arrAux_subM[num_subM] > 1) return 0;
        }
      }
      for (int j = 1; j <= 9; j++) {
        arrAux_subM[j] = 0; // reestablecer valores en 0 para siguiente submatriz.
      }
    }
  }
  
  return 1;
}

List* get_adj_nodes(Node* n) {
  List* list = createList();

  for (int num = 1; num <= 9; num++) {
    for(size_t i = 0; i < 9; i++) {
      for(size_t k = 0; k < 9; k++) {
        // si esta vacio, crear una posible jugada (nodo adyacente).
        if(n->sudo[i][k] == 0) {
          Node * copiaNodo = copy(n);
          copiaNodo->sudo[i][k] = num;
          if(is_valid(copiaNodo)) {
            pushBack(list, copiaNodo);
          }
          else {
            free(copiaNodo);
          }
          return list;
        }
      }
    }
  }
  
  return list;
}


int is_final(Node* n) {
    return 0;
}


Node* DFS(Node* initial, int* cont) {
  Stack * pila = createStack();
  push(pila,initial);
  Node * solucion = NULL;
  List * visitados = createList();
  
  while (!is_empty(pila)) {
    (* cont)++;
    Node * nodo = first(pila);
    if(nodo == NULL) {
      pop(pila);
      continue;
    }
    
    if (is_valid(nodo)) {
      void * current = front(visitados);
      int visitado = 0;
      while(current != NULL) {
        if(current == nodo) {
          visitado = 1;
          break;
        }
        current = next(visitados);
      }
    
      if(!visitado) {
        push(visitados, nodo);
        List * adj = get_adj_nodes(nodo);
        Node * aux = first(adj);
        int todos_visitados = 1;
  
        while(aux) {
          push(pila,aux);
          aux = next(adj);
        }

        current = front(visitados);
        while(current != NULL) {
          if(current != nodo) {
            todos_visitados = 0;
            break;
          }
          current = next(visitados);
        }
        
        if(todos_visitados) {
          solucion = nodo;
          break;
        }
      }
    }
    pop(pila);
  }
  free(visitados);
  
  return solucion;
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