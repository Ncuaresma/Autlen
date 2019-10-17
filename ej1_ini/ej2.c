#include <stdio.h>
#include <stdlib.h>

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
      if(estadov[l] == 1){
        for(k=0; k<ntrans; k++){
          if(l == matriz[k][0] && letra == matriz[k][1]){
            estadon[matriz[k][2]] = 1;
          }
        }
      }
    }
    for (l=0; l<nestados; l++){
      estadov[l]=estadon[l];
      printf("%d hola", estadon[l]);
      if(estadon[l] =! 0){
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
  if(estadov[efin]==1){
    printf("Has alcanzado el estado final!!!!\n");
  }
  else{
    printf("Palabra no aceptada.\n");
  }
}
