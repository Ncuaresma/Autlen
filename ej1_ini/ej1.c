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
  int estado=0;
  int efin;
  int nfilas;
  int ncols;
  char* simbolos = NULL;
  int i, j;

  fscanf(file, "%d", &efin);
  fscanf(file, "%d", &nfilas);
  fscanf(file, "%d", &ncols);
  simbolos = (char*)malloc(ncols*sizeof(char));

  for(i=0 ; i<ncols; i++){
    fscanf(file, "%s", &simbolos[i]);
  }
  //fgets (simbolos, ncols, file);
  matriz = (int**)malloc(nfilas*sizeof(int*));

  for (i=0;i<nfilas;i++){
    matriz[i] = (int*)malloc(ncols*sizeof(int));
    for (j=0;j<ncols;j++){
      fscanf(file, "%d", &matriz[i][j]);
    }
  }
  i = 0;
  while(letra != '\0'){
    for (j=0; j<ncols; j++){
      if(letra == simbolos[j]){
        printf("%c\n", letra);
        printf("1: %d\n",estado );
        estado = matriz[estado][j];
        printf("2: %d\n",estado );
        break;
      }
    }
    i++;
    letra=palabra[i];
    if(j == ncols){
      printf("Palabra no aceptada ya que hay una letra que no esta en nuestro lenguaje.\n");
      return;
    }
    if(estado == -1){
      printf("Palabra no aceptada, no llega al estado final.\n");
      return;
    }
  }
  if(estado==efin){
    printf("Has alcanzado el estado final!!!! (es el %d gg)\n", estado);
  }
  else{
    printf("Palabra no aceptada, no llega al estado final.\n");
  }
}
