#include<iostream>
#include<math.h>

int main(){
	int i=0,j=0,k=0,n=0;

    std::cout << "\t\tDESCOMPOSICION LU";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "NOTA: El orden de la matriz debe ser mayor o igual que 2 y entero." << std::endl;
	std::cout << "Ingresa el orden de la matriz: ";
    std::cin >> n;

    //Comprobacion de ingreso de un valor correcto para el orden de la matriz
    if(n<=1){
        std::cout << std::endl;
        std::cout << "No ha ingresado un valor correcto. Cerrando el programa...";
        std::cout << std::endl;
        return 0;
    } else {
        float A[n][n]={0}, L[n][n]={0}, U[n][n]={0};
        std::cout << "La matriz es de " << n << "x" << n <<".";
        std::cout << std::endl << std::endl;

        //Obtencion de los elementos de la matriz A de coeficientes
        std::cout <<"Ingrese los coeficientes de la matriz A: ";
        std::cout << std::endl;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                std::cout << "Ingrese el elemento A["<<i+1<<"]["<<j+1<<"]: ";
                std::cin >> A[i][j];
            }
        }
        std::cout << std::endl;

        //Descomposicion LU

        //Copiar la matriz A en la matriz U para su triangulacion sin afectar la matriz original
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                U[i][j]=A[i][j];
               }
        }

        //Comprobacion de que la copia fue correcta
        /*for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                std::cout << U[i][j] << "    ";
               }
            std::cout << std::endl;
        }*/

        //Llenado de ceros y unos en posiciones conocidas de la matriz L
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i==j){
                    L[i][j]=1;    //Unos en la diagonal de L
                } else if(i>j){
                    L[i][j]=0;     //Ceros encima de la diagonal para la matriz L
                }
            }
        }
        //Llenado del resto de L y eliminacion Gaussiana en la matriz U
        double a;       //Sirve para llenar la matriz L y para la triangulacion de U
        for(j=0;j<n;j++){
            for(i=1;i-1<n;i++){
                a=-(U[i][j])/(U[j][j]);
                std::cout << "a [" << i << "]= " << a;
                for(int k=j; k<n; k++){   //Sirve para que la transformacion elemental afecte a toda la fila actual
                    U[i][k]+=a;
                }
                if(i>j){
                    L[i][j]=a;
                }
                a=0;
            }
        }


        //Mostrar en pantalla la matriz L
        std::cout << std::endl << std::endl;
        std::cout << "Matriz L:";
        std::cout << std::endl;
        std::cout << "    ";
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                std::cout << L[i][j] <<"   ";
            }
            std::cout << "\n    ";
        }

        //Mostrar en pantalla la matriz U
        std::cout << std::endl << std::endl;
        std::cout << "Matriz U:";
        std::cout << std::endl;
        std::cout << "    ";

        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                std::cout << U[i][j] <<"   ";;
            }
            std::cout << "\n    ";
        }
    }
    return 0;
}
