#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {

  int validarFila[9][10] = {0};
  int validarCol[9][10] = {0};
  int validarSubMatrix[9][10] = {0};

  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      int currentNum = n->sudo[i][k];

      if (currentNum == 0)
        continue;

      if (validarFila[i][currentNum] == 1)
        return 0;
      validarFila[i][currentNum] = 1;

      if (validarCol[k][currentNum] == 1)
        return 0;
      validarCol[k][currentNum] = 1;

      int subMatrix = 3 * (i / 3) + (k / 3);

      if (validarSubMatrix[subMatrix][currentNum] == 1)
        return 0;

      validarSubMatrix[subMatrix][currentNum] = 1;
    }
  }

  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();

  for(int i = 0 ; i < 9 ; i++){
    for(int k = 0 ; k < 9 ; k++){
      if(n->sudo[i][k] == 0){
        for (int num = 1 ; num <= 9 ; num++){
          Node* newNode = copy(n);
          newNode->sudo[i][k] = num;
        
          if(is_valid(newNode)) pushBack(list, newNode);
          else free(newNode);
        }
        break;
      }
    }
  }
  return list;
}

int is_final(Node *n) {
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      if (n->sudo[i][k] == 0)
        return 0;
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont) { 
  
  Stack* S = createStack();
  push(S, initial);

  while(!is_empty(S)){
    Node* currentNode = (Node*)pop(S);
    (*cont)++;

    if(is_final(currentNode)) return currentNode;

    List* adjNodes = get_adj_nodes(currentNode);
    Node* aux = first(adjNodes);
    while (aux) {
      push(S, aux);
      aux = next(adjNodes);
    }
    clean(adjNodes);
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