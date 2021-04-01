#include <iostream> //Header que define los objetos de flujo de entrada y salida
#include <fstream> //Header que define los obejetos de flujo de entrada y salida desde y hacia archivos
#include <string> //Header recomendado para el uso de tipos de datos string
#include <vector> //Header que define la clase necesaria para el uso de vectores
#include <iomanip> //Librer�a necesaria para el uso de las funciones setw y setprecision (Explicadas m�s adelante)
#include <stdlib.h> //Librer�a necesario para el uso de la funci�n system("cls") usada para borrar el contenido mostrado en pantalla

using namespace std; //Utiliza el namespace llamado std el cual permite escribir operadores, como cout y cin, sin el prefijo necesaria std::

#define NOTA_MIN 0.0f //Define una directiva de preprocesador para la calificaci�n m�nima aceptada
#define NOTA_MAX 5.0f //Define una directiva de preprocesador para la calificaci�n m�xima aceptada

#define CRED_MIN 0 //Define una directiva de preprocesador para la cantidad m�nima de cr�ditos posibles
#define CRED_MAX 20 //Define una directiva de procesador para la cantidad m�xima de cr�ditos posibles (Esto puede variar y se usa 20 porque es una cantidad de cr�ditos grande)

struct datos{/////estructura para pedir los datos de usuario
	string nombre;
	int semestre;
	string carrera;
}persona,*puntero_datos=&persona;

bool existencia(const string&); //Funci�n que verifica la existencia de un archivo (Ver la funci�n main para mayor informaci�n)
void resultado(short sumCreditos, float sumPonderacion); //Funci�n para la impresi�n del resultado en pantalla
void opciones(); //Funci�n que imprime en pantalla las opciones disponibles que el usuario puede escoger
void mostrarPromedioGuardado(); //Funci�n a utilizar si el usuario elige esta opci�n. Ver la funci�n main para m�s informaci�n
void cambiarCalificaciones(); //Funci�n a utilizar si el usuario elige esta opci�n. Ver la funci�n main para m�s informaci�n
void nuevaSesion(); //Funci�n a utilizar si el usuario elige esta opci�n. Ver la funci�n main para m�s informaci�n
void pedirDatos();//funcion que pide datos del usuario con referencia a la estructura
void mostrarDatos();
void pedir_datos_op3();

int main() { //Funci�n principal

	//Verificacion de la existencia de archivos los cuales se crean luego de un primer uso
	//y evitan que el usuario tengo que ingresar toda la informaci�n cada vez que usa el programa
	bool ver_existencia; //Llama a la funci�n ver_existencia() que devuelve un booleana, es decir, true o false
	ver_existencia = existencia("Nombres.txt"); //Asigna el valor devuelto por la funci�n Ver_existencia a la variable Ver_existencia que es de tipo bool
                                                //Pasando el par�metro "Nombres.txt" que es el nombre del archivo cuya existencia va a comprobar
	//Opciones mostradas al usuario de acuerdo a la respuesta obtenida en el paso anterior

	if (ver_existencia) { //Si la variable ver_existencia es 'true' se ejecutar� el c�digo dentro del if
		short eleccion = 0; //Creaci�n de la variable elecci�n de tipo short que ser� utilizada para almacenar la elecci�n del usuario
		do { // do-while sirve para que el usuario ingrese una de las opciones mostradas 1, 2, 3 y se seguir� ejecuntando mientras se ingrese otro valor
			opciones(); //Llama a la funci�n opciones(). Ver dicha funci�n para m�s informaci�n
			cin >> eleccion; //El usuario ingresa su elecci�n
			system("cls"); //Borra todo lo mostrado en pantalla para evitar que se llene en cada iteraci�n si la elecci�n no es correcta y para un uso posterior
		} while (eleccion < 1 || eleccion > 3); //Condici�n: Repetir el c�digo mientras la variable elecci�n sea menor que uno o mayor que no

        switch (eleccion){ //Se usa la opci�n ingresada y se llama a una funci�n espec�fica de acuerdo a dicha elecci�n
            case 1: mostrarPromedioGuardado(); //Si el usuario escogi� la opci�n 1, se llama a la funci�n hom�nima
                break; //Sale de switch y evita que se ejecuten las dem�s opciones
            case 2: cambiarCalificaciones(); //Si el usuario escogi� la opci�n 1, se llama a la funci�n hom�nima
                break; //Sale de switch y evita que se ejecuten las dem�s opciones
            case 3: nuevaSesion(); //Si el usuario escogi� la opci�n 1, se llama a la funci�n hom�nima
                break; //Sale de switch y evita que se ejecuten las dem�s opciones
    }
	} else { //Si el programa no se us� antes, no existir�n archivos por lo que la variable Ver_existencia ser� 'false'
		nuevaSesion(); //En dicho caso, se llama a la funci�n nuevaSesion(). Ver dicha funci�n para m�s informaci�n
	}

	cin.get(); //Evita que el programa, en modo Release, se cierre autom�ticamente. Es preferible usarlo en lugar de system(�pause�)
	return 0; //Retorna cero si el programa se ejecut� correctamente
}

//Funci�n encargada de comprobar la existencia de un archivo en la carpeta en la que se aloja el ejecutable
bool existencia(const string& Nombres) {
    //El par�metro es la referencia a un objeto de tipo string cuyo contenido no ser� cambiado

	ifstream ifile(Nombres.c_str()); //La clase ifstream no sabe c�mo tomar un string como el nombre del archivo por lo que agregamos .c_str
                                    //que presenta dicho string como un arreglo de caracteres
	return (bool)ifile; //Retorna el resultado. 'true' si encontr� un archivo con el nombre indicado o 'false' si no encontr� dicho archivo
} //Fin de la funci�n existencia()

//Funci�n que imprime en pantalla las opciones disponibles si el programa ya fue usado anteriormente y se guardaron datos en archivos
void opciones(){
	cout << "\t\t Promedio Semestral\n\n"; //Imprime el nombre del programa
	cout << "Se hallaron archivos con informacion." << endl; //Imprime el mensaje y da un salto de l�nea
	cout << "Escoja la opcion que desee:" << endl; //Imprime el mensaje y da un salto de l�nea
	cout << "1 -> Usar toda la informacion anterior e imprimir el resultado." << endl; //Opci�n 1 y salto de l�nea
	cout << "2 -> Usar los nombres y creditos guardados pero cambiar las calificaciones." << endl; //Opci�n 2 y salto de l�nea
	cout << "3 -> Borrar todo y empezar de nuevo." << endl; //Opci�n 3 y salto de l�nea
} //Fin de la funci�n opciones()

//Funci�n a utilizar si la opci�n elegida es la 1
void mostrarPromedioGuardado(){

    //Esta opci�n se habilitar� cuando el usuario ya haya usado el programa anteriormente por lo que existir�n archivos conteniendo la informaci�n que
    //el usuario ingres� y la imprimir� en pantalla, tanto el nombre de las materias, sus respectivos cr�ditos y calificaciones y el promedio semestral
    //calculado con dicha informaci�n.

    mostrarDatos();//se llama esta funcion para mostrar los datos ingresados en la funcion de pedir_datos

	cout << "\t\tPromedio Semestral" << endl; //Imprime el nombre del programa
	cout << endl << endl; //Realiza dos saltos de l�nea

	//Declarar vectores para cada variable. Es m�s eficiente obtener la informaci�n de los archivos y guardarlos en los vectores que guardarlos en un arreglo din�mico
	vector <string> vNombres; //Vector para guardar datos de tipo string, es decir, los nombres provenientes del archivo Nombres.txt
	vector <short> vCreditos; //Vector para guardar datos de tipo short, es decir, los cr�ditos provenientes del archivo Creditos.txt
	vector <float> vNotas; //Vector para guardar datos de tipo float, es decir, las notas provenientes del archivo Notas.txt

	//Obtener nombres
	string nombre; //Se crea la variable nombre de tipo string que servir� para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fNombres("Nombres.txt"); //Apertura en modo lectura del archivo llamado Nombres.txt
	if (fNombres.is_open()){ //Comprueba que el archivo est� abierto y mientras lo est� ejecuta el siguiente c�digo
		while (getline(fNombres, nombre, '\n')){ //Mientras hayan nombres en el archivo, separados por un salto de l�nea, los leer� y escribir� en el vector
			vNombres.push_back(nombre); //Esta funci�n guarda el elemento le�do en el archivo al final del vector en cada iteraci�n
		}
	} //Fin del condicional if
	fNombres.close(); //Cierra el archivo utilizado

	//Obtener creditos
	short cre = 0; //Se crea la variable cre de tipo short que servir� para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fCreditos("Creditos.txt"); //Apertura en modo lectura del archivo llamado Creditos.txt
	if (fCreditos.is_open()){ //Comprueba que el archivo est� abierto y mientras lo est� ejecuta el siguiente c�digo
		while (fCreditos >> cre){ //Mientras hayan n�meros en el archivo, separados por un salto de l�nea, los leer� y escribir� en el vector
			vCreditos.push_back(cre); //Esta funci�n guarda el elemento le�do en el archivo al final del vector en cada iteraci�n
		}
	} //Fin del condicional if
	fCreditos.close(); //Cierra el archivo utilizado

	//Obtener calificaciones
	float cal = 0; //Se crea la variable cal de tipo float que servir� para guardar las calificaciones de cada materia, provenientes del archivo
	ifstream fNotas("Notas.txt"); //Apertura en modo lectura del archivo llamado Notas.txt
	if (fNotas.is_open()){ //Comprueba que el archivo est� abierto y mientras lo est� ejecuta el siguiente c�digo
		while (fNotas >> cal){ //Mientras hayan n�meros en el archivo, separados por un salto de l�nea, los leer� y escribir� en el vector
			vNotas.push_back(cal); //Esta funci�n guarda el elemento le�do en el archivo al final del vector en cada iteraci�n
		}
	} //Fin del condicional if
	fNotas.close(); //Cierra el archivo utilizado

	float sumPonderacion = 0; //Creaci�n e inicializaci�n de la variable sumPonderacion que servir� para guardar la suma del producto de las notas y los cr�ditos
	short sumCreditos = 0; //Creaci�n e inicializaci�n de la variable sumCreditos que servir� para guardar la suma de todos los cr�ditos
	short cantidad = vNotas.size(); //Permite obtener la cantidad de elementos alojados en el vector Notas el cual coincide con la cantidad de materias

	cout << "\t\t     Creditos\t      Notas" << endl; //Se imprime en pantalla las palabras Creditos y Notas con un formato que permite tener un orden
	for (short i = 0; i < cantidad; i++){ //Este ciclo imprime en pantalla el nombre de la materia, sus cr�ditos y la calificaci�n obtenida
        //Se crea la variable i tipo short, se inicializa con el valor de cero y en cada iteraci�n aumentar� en uno para as� recorrer todas las posiciones
        //del vector, desde el inicio hasta la posici�n final (la posici�n final o valor final de i est� definido por la cantidad de elementos encontrados
        //en el vector vNotas el cual concide, como ya se indic� cuando se cre� la variable cantidad, con la cantidad de materias)
		cout << vNombres[i]; //Imprime el elemento ubicado en la posici�n i del vector
		cout << "\t\t" << vCreditos[i]; //Imprime el elemento ubicado en la posici�n i del vector con un formato que permite tener un orden en la pantalla
		cout << "\t\t" << vNotas[i] << endl; //Imprime el elemento ubicado en la posici�n i del vector con un formato que permite tener un orden en la pantalla

		sumCreditos += vCreditos[i]; //En cada iteraci�n se suman los cr�ditos y el valor se guarda en la variable sumCreditos
		sumPonderacion += vNotas[i] * vCreditos[i]; //En cada iteraci�n se suma el producto de los cr�ditos y las notas correspondientes a una materia en espec�fico
	} //Finaliza el ciclo for
	cout << endl << endl; //Realiza dos saltos de l�nea
	resultado(sumCreditos, sumPonderacion); //Llama a la funci�n resultado, haciendo un paso por valor de dos par�matros. Ver la funci�n resultado() para m�s informaci�n
} //Fin de la funci�n mostrarPromedioGuardado()
//Funci�n a utilizar si la opci�n elegida es la 2
void cambiarCalificaciones(){

    //Esta opci�n se habilitar� cuando el usuario ya haya usado el programa anteriormente por lo que existir�n archivos conteniendo la informaci�n que
    //el usuario ingres� e imprimir� en pantalla el nombre de las materias y sus respectivos cr�ditos permitiendo modificar tan s�lo las calificaciones
    //y procediendo a calcular el promedio semestral con la nueva informaci�n

    mostrarDatos();//se llama esta funcion para mostrar los datos ingresados en la funcion de pedir_datos

	cout << "\t\tPromedio semestral"; //Imprime el nombre del programa
	cout << endl << endl; //Realiza dos saltos de l�nea

	//Declarar vectores para almacenar la informaci�n proveniente de los archivos
	vector <string> vNombres; //Vector para guardar datos de tipo string, es decir, los nombres provenientes del archivo Nombres.txt
	vector <short> vCreditos; //Vector para guardar datos de tipo short, es decir, los cr�ditos provenientes del archivo Creditos.txt

    //Obtener nombres
	string nombre; //Se crea la variable nombre de tipo string que servir� para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fNombres("Nombres.txt"); //Apertura en modo lectura del archivo llamado Nombres.txt
	if (fNombres.is_open()){ //Comprueba que el archivo est� abierto y mientras lo est� ejecuta el siguiente c�digo
		while (getline(fNombres, nombre, '\n')){ //Mientras hayan nombres en el archivo, separados por un salto de l�nea, los leer� y escribir� en el vector
			vNombres.push_back(nombre); //Esta funci�n guarda el elemento le�do en el archivo al final del vector en cada iteraci�n
		}
	} //Fin del condicional if
	fNombres.close(); //Cierra el archivo utilizado

	//Hallar la cantidad de elementos en el vector Nombre para saber con cuantas materias se va a trabajar y usarlo al crear el arreglo dinamico
	short cantidad = vNombres.size();

	//Creacion de punteros y arreglos dinamicos
    float *pNotas = NULL; //Crea un puntero para datos de tipo float y se apunta a NULL
    pNotas = new float[cantidad]; //Se crea un arreglo din�mico de tama�o igual a 'cantidad' y se apunta el puntero pNotas a la primera posici�n de este arreglo

	//Obtener creditos
	short cre = 0; //Se crea la variable cre de tipo string que servir� para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fCreditos("Creditos.txt"); //Apertura en modo lectura del archivo llamado Creditos.txt
	if (fCreditos.is_open()){ //Comprueba que el archivo est� abierto y mientras lo est� ejecuta el siguiente c�digo
		while (fCreditos >> cre){ //Mientras hayan n�meros en el archivo, separados por un salto de l�nea, los leer� y escribir� en el vector
			vCreditos.push_back(cre); //Esta funci�n guarda el elemento le�do en el archivo al final del vector en cada iteraci�n
		}
	} //Fin del condicional if
	fCreditos.close(); //Cierra el archivo utilizado

    //Creacion y apertura de archivo para los notas en modo escritura el cual sobreescribe al archivo existente del mismo nombre
	ofstream fNotas("Notas.txt");

	//Declara variables para almacenar la suma ponderada, la suma de cr�ditos y la calificaci�n de una materia inicializ�ndolas con el valor cero
	float sumPonderacion = 0;
	short sumCreditos = 0;
	float cal = 0;

	cout << "\t\tNota:" << endl; //Imprime en pantalla el mensaje mencioando y da un salto de l�nea
	for (short i = 0; i < cantidad; i++) {

		// Loop para obtener las calificaciones
		do{ // Mientras la calificaci�n ingresada por el usuario sea menor que NOTA_MIN o mayor que NOTA_MAX, se seguir� ejecutando este c�digo
			cout << vNombres[i] << ": \t\t"; //Imprime en pantalla el nombre almacenado en la posici�n 'i' del vector vNombres[] con un formato espec�fico
			cin >> cal; //Se lee el valor ingresado por el usuario
			*(pNotas+i) = cal; //El contenido de la variable cal se guarda en el arreglo din�mico usando la aritm�tica de punteros
			fNotas << pNotas[i] << endl; //Guarda las calificaciones en un archivo seguido de un salto de l�nea
		} while (cal < NOTA_MIN || cal > NOTA_MAX); //Condici�n: Repetir el c�digo mientras la variable cal sea menor que NOTA_MIN o mayor que NOTA_MAX

		// sumar las notas*creditos y los creditos
		sumCreditos += vCreditos[i]; //En cada iteraci�n se suman los cr�ditos almacenados en el vector con el nuevo elemento y se guarda en la variable sumCreditos
		sumPonderacion += pNotas[i] * vCreditos[i]; //En cada iteraci�n se suma el producto de los cr�ditos (almacenados en un vector) y las notas
                                                    //(almacenadas en un arreglo din�mico) correspondientes a una materia en espec�fico y el valor se guarda
                                                    //en la variable sumPonderacion
	}

	//Imprimir el resultado
	resultado(sumCreditos, sumPonderacion); //Llama a la funci�n resultado, haciendo un paso por valor de dos par�matros. Ver la funci�n resultado() para m�s informaci�n
}
//Funci�n a utilizar si la opci�n elegida es la 3
void nuevaSesion(){

    //Esta opci�n se habilitar� por defecto cuando el usuario no ha usado el programa anteriormente y tambi�n cuando el usuario elija la opci�n 3
    //cuando el programa encuentre informaci�n la cual se crea despu�s de un primer uso por lo que existir�n archivos conteniendo la informaci�n que
    //el usuario ingres� en un uso anterior.
    //Su funci�n es la de obtener del usuario la cantidad de materias que est� viendo en el semestre actual y el nombre, cr�dito y calificaciones de las mismas
    //Para devolver el promedio semestral.


	//Declara variables para el numero de materias, la suma ponderada y la suma de cr�ditos
	short num_Mat = 0;
	float sumPonderacion = 0;
	short sumCreditos = 0;

	cout << "\t\tPromedio semestral"; //Imprime el nombre del programa
	cout << endl << endl; //Realiza dos saltos de l�nea

	pedir_datos_op3();

	//Solicitar el numero de materias
	cout << "Ingrese el numero de materias\n";
	cin >> num_Mat; //Se lee el valor ingresado por el usuario y se almacenada en la variable num_Mat que servir� para crear el arreglo din�mico
	cout << endl; //Realiza un salto de l�nea
	cin.ignore();    // Elimina el stroke del Enter. Evita que la primera materia sea cero (vacio)

    //Crear archivos para las tres variables
	ofstream fNombres;
	ofstream fCreditos;
	ofstream fNotas;

	//Abrir los archivos y nombrarlos
	fNombres.open("Nombres.txt"); //Abre el archivo y lo nombra Nombres.txt
	fCreditos.open("Creditos.txt"); //Abre el archivo y lo nombra Creditos.txt
	fNotas.open("Notas.txt"); //Abre el archivo y lo nombra Notas.txt

	//Declaraci�n de punteros
	float *pCreditos, *pNotas;
	string *pNombres;

	//Creaci�n de arreglos din�micos
	pNombres = new string[num_Mat];
	pCreditos = new float[num_Mat];
	pNotas = new float[num_Mat];

	cout << "Nota: No ingrese nombres largos, por favor." << endl << endl;
	//Se solicita no ingresar nombres largos para que el formato que se le da a continuaci�n no se vea afectado
	//Lo anterior se puede evitar si se usa la funci�n setw() y esto puede ser implementado m�s adelante

	//Loop para obtener los nombres de todas las materias
	for (short i = 0; i < num_Mat; i++){ //Ciclo for usado para solicitar al usuario los nombres de las materias y almacenarlas en un arreglo din�mico
		string nombre;    //Declarar una variable tipo string
		cout << "Ingresa el nombre de la materia " << i + 1 << endl; //Se solicita al usuario los nombres de las materias
		getline(cin, nombre); //Obtiene los nombres de las materias, los cuales pueden contener espacios
		//vNombres.push_back(nombre);    //Guarda cada materia al final del vector en cada loop
		*(pNombres+i) = nombre; //Aritm�tica de punteros usada para llenar el arreglo din�mica empezando en la posici�n cero
		fNombres << *(pNombres+i) << endl; //Guarda los nombres en un archivo seguido de un salto de l�nea
		cout << endl; //Realiza un salto de l�nea
	} //Finaliza el ciclo for

	//Loops para imprimir el nombre de las materias una a una y obtener las calificaciones y los cr�ditos de cada materia
	for (short i = 0; i < num_Mat; i++){
		cout << pNombres[i] << ": \t" << endl;  //Imprime los nombres de las materias
		float cal = 0; //Declara la variable cal de tipo float que servir� para almacenar la calificaci�n ingresada por el usuario

		// Loop para obtener las calificaciones
		do{ // Mientras la calificaci�n ingresada por el usuario sea menor que NOTA_MIN o mayor que NOTA_MAX, se seguir� ejecutando este c�digo
			cout << "Nota:\t\t"; //Imprime en pantalla el mensaje mencionado
			cin >> cal; //Se lee el valor ingresado por el usuario y se almacenada en la variable cal
		} while (cal < NOTA_MIN || cal > NOTA_MAX);
		*(pNotas+i) = cal; //El contenido de la variable cal se guarda en el arreglo din�mico usando la aritm�tica de punteros
		fNotas << pNotas[i] << endl; //Guarda las calificaciones en un archivo seguido de un salto de l�nea

		short cre = 0; //Declara la variable cre de tipo short que servir� para almacenar el cr�dito ingresado por el usuario

		// Loop para obtener los creditos
		do{ // Mientras el valor del cr�dito ingresado por el usuario sea menor que CRED_MIN o mayor que CRED_MAX, se seguir� ejecutando este c�digo
			cout << "Credito:\t"; //Imprime en pantalla el mensaje mencionado
			cin >> cre; //Se lee el valor ingresado por el usuario y se almacenada en la variable cre
		} while (cre < CRED_MIN || cre > CRED_MAX); //Condici�n de la funci�n do-while
		pCreditos[i] = cre; //El contenido de la variable cre se guarda en el arreglo din�mico usando otra forma de almacenamiento, estaba: *(pCreditos+i) = cre
		fCreditos << pCreditos[i] << endl; //Guarda los cr�ditos en un archivo seguido de un salto de l�nea
		cout << endl;

		// sumar las notas*creditos y los creditos
		sumCreditos += pCreditos[i]; //En cada iteraci�n se suman los cr�ditos usando un puntero y el valor se guarda en la variable sumCreditos
		sumPonderacion += pNotas[i] * pCreditos[i]; //En cada iteraci�n se suma el producto de los cr�ditos y las notas correspondientes a una materia
                                                    //en espec�fico y el valor se guarda en la variable sumPonderacion
	} //Finaliza el ciclo for

	//Cerrar los archivos creados
	fNombres.close(); //Cierra el archivo de los nombres
	fCreditos.close(); //Cierra el archivo de los cr�ditos
	fNotas.close(); ////Cierra el archivo de las calificaciones

	//Imprimir el resultado
	resultado(sumCreditos, sumPonderacion); //Llama a la funci�n resultado, haciendo un paso por valor de dos par�matros. Ver la funci�n resultado() para m�s informaci�n
}
//Funci�n que imprime en pantalla el resultado
void resultado(short sumCreditos, float sumPonderacion){
    //Recibe como par�metros un short y un float los cu�les se pasan por valor y no por puntero ni referencia ya que no queremos cambiar sus valores, s�lo utilizarlos
	float resultado = sumPonderacion / sumCreditos; //Se declara la variable resultado de tipo float y se inicializa con la divisi�n de los dos par�metros que recibe esta funci�n
	cout << "Tu promedio semestral es: " << setprecision(3) << resultado << endl; //Imprime en pantalla el resultado obtenido correspondiente al promedio semestral
                                                                                //Se usa la funci�n setprecision() para mostrar tan s�lo 2 decimales
	cin.get();
}

void pedirDatos(){


	/////se pasan los datos de la estructura por medio de punteros hacia la funcion, la cual en esta misma funcion se abre un archivo txt en donde se guardan los datos insertados por teclado////
	cout<<"Nombre del usuario: ";
	getline(cin,puntero_datos-> nombre);////gaurda el nombre dentro del objeto persona de la estructura datos//
	cin.ignore();//para que tome el valor de la linea del usuario
	cout<<"Semestre: ";/////////////////////////////////////////////////////////////////////////
	cin>>puntero_datos->semestre;////gaurda el numero del semestre dentro del objeto persona de la estructura datos/
	cin.ignore();//para que tome el valor de la linea del semestre//
	cout<<"Carrera: ";/////////////////////////////////////////////////////////////////////////
	getline(cin,puntero_datos->carrera);////gaurda  la carrera  dentro del objeto persona de la estructura datos/

    ofstream Datos;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Datos.open("Datos.txt",ios::out);///abre el archivo txt////////////////////////////////////////////////
	Datos<<"Nombre:"<<endl;////////////////creacion del archivo txt para el llenado de la informacion de los datos de usuario /////
	Datos<<	puntero_datos->nombre<<"  "<<endl;/////////////////////////////////////////////////////////////////////////////////////////
    Datos<<"Carrera:"<<endl;/////////////////////////////////////////////////////////////////////////////////////////////////////
	Datos<<	puntero_datos->carrera<<"  "<<endl;/////////////////////////////////////////////////////////////////////////////////////////
    Datos<<"Semestre:"<<endl;//////////////////////////////////////////////////////////////////////////////////////////////////
	Datos<<	puntero_datos->semestre<<"  "<<endl;/////////////////////////////////////////////////////////////////////////////////////////
	Datos.close();////////////////////////////////////////////////////////////////////////////////////////////////////////////
	system("cls");
}

void mostrarDatos(){
	///el archivo txt se abre en modo lectura para visualizar los datos introducidos anteriormente para luego mostrarlos por medio del llamado de esta funcion//
    string texto;////////se declara una variable de tipo string para que no vaya a generar inconvenientes cuando se llamen los datos del txt//
	ifstream datos;////////////se utiliza para la lectura de texto del archivo txt//
	datos.open("Datos.txt",ios::in);//se abre en modo lectura//
	if(datos.fail()){//////////////comprobacion que exista ya un archivo con los datos del estudiante//
		cout<<" No se pudo abrir el archivo";/////////////
		exit(1);////////////////se declara para salir del bucle en caso de que haya un archivo//
	}
	///se declara este bucle para leer todo lo que hay en el archivo txt//
	while(!datos.eof()){////////////////mientras no sea el final del archivo realice los pasos siguientes:
		getline(datos,texto);////copie lo que hay dentro del archivo a la variable texto.
		cout<<setw(2)<<texto<<setw(0)<<" ";/////seguido muestre esa variable texto en pantalla
	}
	datos.close();/////se cierra el archivo de texto.

	cout << endl << endl;
}
void pedir_datos_op3(){///en esta funcion se abre y se modifica el archivo txtpara la opcion 3 especificamente
	ofstream Datos;
	Datos.open("Datos.txt",ios::out);

    cout<<"Nombre del usuario: ";
	getline(cin,puntero_datos-> nombre);////gaurda el nombre dentro del objeto persona de la estructura datos//
	Datos<<"Nombre:"<<endl;////////////////creacion del archivo txt para el llenado de la informacion de los datos de usuario /////
	Datos<<	puntero_datos->nombre<<"    "<<endl;

	cout<<"Carrera: ";/////////////////////////////////////////////////////////////////////////
	getline(cin,puntero_datos->carrera);
	Datos<<"Carrera:"<<endl;/////////////////////////////////////////////////////////////////////////////////////////////////////
	Datos<<	puntero_datos->carrera<<"    "<<endl;

	cout<<"Semestre: ";/////////////////////////////////////////////////////////////////////////
	cin>>puntero_datos->semestre;
	Datos<<"Semestre:"<<endl;//////////////////////////////////////////////////////////////////////////////////////////////////
	Datos<<	puntero_datos->semestre<<"    "<<endl;
	Datos.close();
}
