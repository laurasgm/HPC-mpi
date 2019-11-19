#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "timer.hh"

using namespace std;

int **m1;
int **m2;
int **r;

void imprimir_matrices(int TAM){

    for (int i=0; i<TAM; i++){

        for (int j=0; j<TAM; j++){
            cout<<m1[i][j]<<"\t";
        }
        cout<<endl;
    }

    
    cout<<endl;
    for (int i=0; i<TAM; i++){

        for (int j=0; j<TAM; j++){
            cout<<m2[i][j]<<"\t";
        }
        cout<<endl;
    }

}

void imprimir_secuencial(int TAM){
    cout << endl
         << "Multiplicacion secuencial" << endl;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            cout << *(*(r+i)+j)  << " ";
        cout << endl;
    }
}

int main (int argc, char **argv)
{
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

  
  ifstream archivo,archivo2;
  string prueba;

  archivo.open("data//m1_100.csv",ios::in);
  archivo2.open("data//m2_100.csv",ios::in);

  if (archivo.fail()){
        cout<< "No se encuentra el archivo";
        exit(1);
    }
  if (archivo2.fail()){
      cout<< "No se encuentra el archivo";
      exit(1);
  }



  for (int i=0; i<TAM; i++){
      for (int j=0; j<TAM; j++){
          archivo >> *(*(m1+i)+j);
          archivo2 >> *(*(m2+i)+j);
      }
  }

/*
  while(!archivo.eof()){
     for(int i=0; i<TAM; i++){
      for(int j=0; j<TAM; j++){
          *(*(r+i)+j) = 0;
          for(int k=0; k<TAM; k++){
                *(*(r+i)+j) += *(*(m1+i)+k)  * *(*(m2+k)+j) ;
          }
      }
  }
  }
*/
  imprimir_matrices(TAM);

  //imprimir_secuencial(TAM);



  /*
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &p_id );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  //este tiempo se toma con la libreria timer.hh
  ScopedTimer p;

  //multiplicacion 
    for(int i=0; i<TAM; i++){
      for(int j=0; j<TAM; j++){
          *(*(r+i)+j) = 0;
          for(int k=0; k<TAM; k++){
                *(*(r+i)+j) += *(*(m1+i)+k)  * *(*(m2+k)+j) ;
          }
      }
    }


    cout<<TAM<<","<<p.elapsed()/1e+6<<endl;
     MPI_Finalize();*/
    //imprimir_matrices(TAM);
    //imprimir_secuencial(TAM);
}