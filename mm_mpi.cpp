#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;


// nfs https://debian-handbook.info/browse/es-ES/stable/sect.nfs-file-server.html
//mpic++ -o mpi mm_mpi.cpp COMO COMPILAR CON MPI EJEMPLO
//https://www.youtube.com/watch?v=x8t5nStMpGE video mpi 
//https://lsi.ugr.es/jmantas/ppr/tutoriales/tutorial_mpi.php?tuto=comienzo_mpi COMO COMPILAR MPI

int **m1;
int **m2;
int **r;

void imprimir_matrices(int TAM){
    cout<<endl;
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

  //http://www.cplusplus.com/forum/beginner/38349/
  ifstream archivo,archivo2;
  ofstream archivo3;//nos servira de prueba para saber si las multi estan bien hechas

  archivo.open("data//m1_1000.csv",ios::in);// matriz 1
  archivo2.open("data//m2_1000.csv",ios::in);//matriz 2
  archivo3.open("result.csv",ios::out);// resultado prueba 

  if (archivo.fail()){
        cout<< "No se encuentra el archivo";
        exit(1);
    }
  if (archivo2.fail()){
      cout<< "No se encuentra el archivo";
      exit(1);
  }
  if (archivo3.fail()){
      cout<< "Problema con el archivo3";
      exit(1);
  }
  

  //Paso de csv a matriz operable 
  for (int i=0; i<TAM; i++){
      for (int j=0; j<TAM; j++){
          archivo >> *(*(m1+i)+j);
          archivo2 >> *(*(m2+i)+j);
      }
  }

  int rank, size;
  int i,j,k;
  MPI_Status status;
  double end,start;
  double mytime,   /*variables used for gathering timing statistics*/
           maxtime;
  

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Barrier(MPI_COMM_WORLD);
  
  //PARCEEE EL i VA A FUNCIONAR IDENTIFICADOR DE WorkerNode Y AL MISMO TIEMPO DE FILA EN LA QUE VA A TRABAJAR, REVISE LA IMAGEN DEL TABLERO EN EL REPOSITORIO PARA ENTENDER MEJOR 
  if(rank == 0){ // ESTE ES EL NODO MASTER
    start = MPI_Wtime();
    //cout<<"estoy en master"<<endl;
    for (i=1; i<TAM; i++){
      MPI_Send(&i,1,MPI_INT,i,0,MPI_COMM_WORLD);//envio info a WN sobre i 
    }
    MPI_Barrier(MPI_COMM_WORLD);

    for (j=0; j<TAM; j++){
      for(k=0; k<TAM; k++){
        *(*(r+0)+j) += *(*(m1+0)+k)  * *(*(m2+j)+k);//transpuesta
      }
      //archivo3 << *(*(r+0)+j);
      //archivo3 <<' ';
    }
   // archivo3 << endl;
  
  end = MPI_Wtime();
  //cout<<TAM<<","<<end-start<<endl;
  }else{// ESTOS SON LOS WORKERs
    
    //cout<<"estoy en el worker "<<rank<<endl;
    MPI_Recv(&i,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);//recibimos la posicion de la fila que el WN trabajara

     for (j=0; j<TAM; j++){
      for(k=0; k<TAM; k++){
        *(*(r+i)+j) += *(*(m1+i)+k)  * *(*(m2+j)+k);//transpuesta
      }
      //archivo3 <<*(*(r+i)+j);
      //archivo3 <<' ';
      
    }
    //archivo3 <<endl;
    MPI_Barrier(MPI_COMM_WORLD);
  }

  
  MPI_Reduce(&end, &maxtime, 1, MPI_DOUBLE,MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Finalize();
  //double global = MPI_WTIME_IS_GLOBAL;
  if(rank == 0){
    //cout<<TAM<<","<<end-start<<endl;
    //cout<<TAM<<","<<maxtime<<endl;
    
    cout<<TAM<<","<<maxtime<<endl;
    //cout<<"global "<< global;
  }
  

  archivo.close();
  archivo2.close();
  archivo3.close();
  //imprimir_matrices(TAM);

  //imprimir_secuencial(TAM);

  /* 
  for(int i=0; i<TAM; i++){
  for(int j=0; j<TAM; j++){
      *(*(r+i)+j) = 0;
      for(int k=0; k<TAM; k++){
            *(*(r+i)+j) += *(*(m1+i)+k)  * *(*(m2+j)+k);//transpuesta 
            
      }
      archivo3 << *(*(r+i)+j);
      archivo3 <<' ';
    }
    archivo3 <<'\n';
  }
  
  */

}