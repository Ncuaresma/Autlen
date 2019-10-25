#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* next_state(int ntrans, int** matriz, int l, int nestados, char letra){
  int* estadon = (int*)malloc(nestados*sizeof(int));
  int k;
  for(k=0; k<ntrans; k++){
    printf("pos: %d\n", matriz[k][0]);
    printf("letra: %d\n", matriz[k][1]);
    printf("letra: %d\n", letra);
    printf("\n");
    if(l == matriz[k][0] && toascii(letra) == matriz[k][1]){
      printf("je pasaa\n");
      estadon[matriz[k][2]] = 1;
    }
  }
  return estadon;
}

void main(int argc, char **argv){
  if(argc!=3){
    printf("Error en los argumentos: palabra filename\n");
    return;
  }
  FILE* file = fopen(argv[2], "r");
  int** matriz = NULL;
  char* palabra =argv[1];
  char letra=palabra[0];
  int* estadov = NULL;
  int* estadon = NULL;
  int efin;
  int nsimbol;
  int ntrans;
  int nestados;
  char* simbolos = NULL;
  int i, j, k, l, flag;

  fscanf(file, "%d", &efin);
  fscanf(file, "%d", &nsimbol);
  fscanf(file, "%d", &nestados);
  simbolos = (char*)malloc(nsimbol*sizeof(char));
  estadov = (int*)malloc(nestados*sizeof(int));
  estadon = (int*)malloc(nestados*sizeof(int));

  for(i=0 ; i<nsimbol; i++){
    fscanf(file, "%s", &simbolos[i]);
  }
  for(i=0 ; i<nestados; i++){
    estadov[i]=0;
    estadon[i]=0;
  }
  estadov[0]=1;

  fscanf(file, "%d", &ntrans);
  matriz = (int**)malloc(ntrans*sizeof(int*));

  for (i=0;i<ntrans;i++){
    matriz[i] = (int*)malloc(3*sizeof(int));
    for (j=0;j<3;j++){
      fscanf(file, "%d", &matriz[i][j]);
    }
  }

  i = 0;
  while(letra != '\0'){
    flag=0;
    //Comprobar la letra con funcioncita maravillosa
    for(l=0; l<nestados; l++){
      printf("estadov: %d\n", estadov[l]);
      if(estadov[l] == 1){
        /*Buscamos a que estado pasamos y con que transicion*/
        estadon = next_state(ntrans, matriz, l, nestados, letra);
      }
    }
    for (l=0; l<nestados; l++){
      estadov[l]=estadon[l];
      printf("%d %d hola\n", estadon[l], l);
      if(estadon[l] != 0){
        flag = 1;
      }
      estadon[l]=0;
    }
    i++;
    letra=palabra[i];
    if(flag == 0){
      printf("Palabra no aceptada, no llega al estado final.\n");
      return;
    }
  }
  printf("%d\n", estadov[efin]);
  if(estadov[efin]==1){
    printf("Has alcanzado el estado final!!!!\n");
  }
  else{
    printf("Palabra no aceptada.\n");
  }
}
