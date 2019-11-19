#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

int **m1;
int **m2;
int **r;



int main(int argc, char **argv){

    // argc es 3 = argv[0]nombre del programa,argv[1]TAM
    int TAM;
    TAM = strtol(argv[1], NULL, 10);


  //reservar memoria para la matriz dinamica
  m1 = new int*[TAM];//reservando memoria para las filas
  for (int i=0;i<TAM;i++){
    m1[i]= new int[TAM];//reservando memoria para las columnas
  }

  //reservar memoria para la matriz dinamica
  m2 = new int*[TAM];//reservando memoria para las filas
  for (int i=0;i<TAM;i++){
    m2[i]= new int[TAM];//reservando memoria para las columnas
  }

  //reservar memoria para la matriz dinamica
  r = new int*[TAM];//reservando memoria para las filas
  for (int i=0;i<TAM;i++){
    r[i]= new int[TAM];//reservando memoria para las columnas
  }

    //llenado
  for (int i=0; i<TAM; i++){

      for (int j=0; j<TAM; j++){
          *(*(m1+i)+j) =rand() % 10 + 1;
          *(*(m2+i)+j) =rand() % 10 + 1;
      }
  }
    //http://www.cplusplus.com/doc/tutorial/files/
    //https://www.youtube.com/watch?v=GaqgqQL3wnQ
    ofstream archivo,archivo2;


    //recordar cambiar el nombre del archivo depende de las matrices que vayamos a guardar
    archivo.open("data//m1_100.csv",ios::out);
    archivo2.open("data//m2_100.csv",ios::out);
    if (archivo.fail()){
        cout<< "No se pudo abrir el archivo";
        exit(1);
    }
    if (archivo2.fail()){
        cout<< "No se pudo abrir el archivo";
        exit(1);
    }
  
     for (int i=0; i<TAM; i++){
      for (int j=0; j<TAM; j++){
          archivo<< *(*(m1+i)+j);
          archivo<<',';
          archivo2 << *(*(m2+i)+j);
          archivo2<<',';
      }
      archivo<<'\n';
      archivo2<<'\n';
     }

    archivo.close();
    archivo2.close();
   
}