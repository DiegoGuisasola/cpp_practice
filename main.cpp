#include <iostream> //Header que define los objetos de flujo de entrada y salida
#include <fstream> //Header que define los obejetos de flujo de entrada y salida desde y hacia archivos
#include <string> //Header recomendado para el uso de tipos de datos string
#include <vector> //Header que define la clase necesaria para el uso de vectores
#include <iomanip> //Librería necesaria para el uso de las funciones setw y setprecision (Explicadas más adelante)
#include <stdlib.h> //Librería necesario para el uso de la función system("cls") usada para borrar el contenido mostrado en pantalla

using namespace std; //Utiliza el namespace llamado std el cual permite escribir operadores, como cout y cin, sin el prefijo necesaria std::

#define NOTA_MIN 0.0f //Define una directiva de preprocesador para la calificación mínima aceptada
#define NOTA_MAX 5.0f //Define una directiva de preprocesador para la calificación máxima aceptada

#define CRED_MIN 0 //Define una directiva de preprocesador para la cantidad mínima de créditos posibles
#define CRED_MAX 20 //Define una directiva de procesador para la cantidad máxima de créditos posibles (Esto puede variar y se usa 20 porque es una cantidad de créditos grande)

struct datos{/////estructura para pedir los datos de usuario
	string nombre;
	int semestre;
	string carrera;
}persona,*puntero_datos=&persona;

bool existencia(const string&); //Función que verifica la existencia de un archivo (Ver la función main para mayor información)
void resultado(short sumCreditos, float sumPonderacion); //Función para la impresión del resultado en pantalla
void opciones(); //Función que imprime en pantalla las opciones disponibles que el usuario puede escoger
void mostrarPromedioGuardado(); //Función a utilizar si el usuario elige esta opción. Ver la función main para más información
void cambiarCalificaciones(); //Función a utilizar si el usuario elige esta opción. Ver la función main para más información
void nuevaSesion(); //Función a utilizar si el usuario elige esta opción. Ver la función main para más información
void pedirDatos();//funcion que pide datos del usuario con referencia a la estructura
void mostrarDatos();
void pedir_datos_op3();

int main() { //Función principal

	//Verificacion de la existencia de archivos los cuales se crean luego de un primer uso
	//y evitan que el usuario tengo que ingresar toda la información cada vez que usa el programa
	bool ver_existencia; //Llama a la función ver_existencia() que devuelve un booleana, es decir, true o false
	ver_existencia = existencia("Nombres.txt"); //Asigna el valor devuelto por la función Ver_existencia a la variable Ver_existencia que es de tipo bool
                                                //Pasando el parámetro "Nombres.txt" que es el nombre del archivo cuya existencia va a comprobar
	//Opciones mostradas al usuario de acuerdo a la respuesta obtenida en el paso anterior

	if (ver_existencia) { //Si la variable ver_existencia es 'true' se ejecutará el código dentro del if
		short eleccion = 0; //Creación de la variable elección de tipo short que será utilizada para almacenar la elección del usuario
		do { // do-while sirve para que el usuario ingrese una de las opciones mostradas 1, 2, 3 y se seguirá ejecuntando mientras se ingrese otro valor
			opciones(); //Llama a la función opciones(). Ver dicha función para más información
			cin >> eleccion; //El usuario ingresa su elección
			system("cls"); //Borra todo lo mostrado en pantalla para evitar que se llene en cada iteración si la elección no es correcta y para un uso posterior
		} while (eleccion < 1 || eleccion > 3); //Condición: Repetir el código mientras la variable elección sea menor que uno o mayor que no

        switch (eleccion){ //Se usa la opción ingresada y se llama a una función específica de acuerdo a dicha elección
            case 1: mostrarPromedioGuardado(); //Si el usuario escogió la opción 1, se llama a la función homónima
                break; //Sale de switch y evita que se ejecuten las demás opciones
            case 2: cambiarCalificaciones(); //Si el usuario escogió la opción 1, se llama a la función homónima
                break; //Sale de switch y evita que se ejecuten las demás opciones
            case 3: nuevaSesion(); //Si el usuario escogió la opción 1, se llama a la función homónima
                break; //Sale de switch y evita que se ejecuten las demás opciones
    }
	} else { //Si el programa no se usó antes, no existirán archivos por lo que la variable Ver_existencia será 'false'
		nuevaSesion(); //En dicho caso, se llama a la función nuevaSesion(). Ver dicha función para más información
	}

	cin.get(); //Evita que el programa, en modo Release, se cierre automáticamente. Es preferible usarlo en lugar de system(¨pause¨)
	return 0; //Retorna cero si el programa se ejecutó correctamente
}

//Función encargada de comprobar la existencia de un archivo en la carpeta en la que se aloja el ejecutable
bool existencia(const string& Nombres) {
    //El parámetro es la referencia a un objeto de tipo string cuyo contenido no será cambiado

	ifstream ifile(Nombres.c_str()); //La clase ifstream no sabe cómo tomar un string como el nombre del archivo por lo que agregamos .c_str
                                    //que presenta dicho string como un arreglo de caracteres
	return (bool)ifile; //Retorna el resultado. 'true' si encontró un archivo con el nombre indicado o 'false' si no encontró dicho archivo
} //Fin de la función existencia()

//Función que imprime en pantalla las opciones disponibles si el programa ya fue usado anteriormente y se guardaron datos en archivos
void opciones(){
	cout << "\t\t Promedio Semestral\n\n"; //Imprime el nombre del programa
	cout << "Se hallaron archivos con informacion." << endl; //Imprime el mensaje y da un salto de línea
	cout << "Escoja la opcion que desee:" << endl; //Imprime el mensaje y da un salto de línea
	cout << "1 -> Usar toda la informacion anterior e imprimir el resultado." << endl; //Opción 1 y salto de línea
	cout << "2 -> Usar los nombres y creditos guardados pero cambiar las calificaciones." << endl; //Opción 2 y salto de línea
	cout << "3 -> Borrar todo y empezar de nuevo." << endl; //Opción 3 y salto de línea
} //Fin de la función opciones()

//Función a utilizar si la opción elegida es la 1
void mostrarPromedioGuardado(){

    //Esta opción se habilitará cuando el usuario ya haya usado el programa anteriormente por lo que existirán archivos conteniendo la información que
    //el usuario ingresó y la imprimirá en pantalla, tanto el nombre de las materias, sus respectivos créditos y calificaciones y el promedio semestral
    //calculado con dicha información.

    mostrarDatos();//se llama esta funcion para mostrar los datos ingresados en la funcion de pedir_datos

	cout << "\t\tPromedio Semestral" << endl; //Imprime el nombre del programa
	cout << endl << endl; //Realiza dos saltos de línea

	//Declarar vectores para cada variable. Es más eficiente obtener la información de los archivos y guardarlos en los vectores que guardarlos en un arreglo dinámico
	vector <string> vNombres; //Vector para guardar datos de tipo string, es decir, los nombres provenientes del archivo Nombres.txt
	vector <short> vCreditos; //Vector para guardar datos de tipo short, es decir, los créditos provenientes del archivo Creditos.txt
	vector <float> vNotas; //Vector para guardar datos de tipo float, es decir, las notas provenientes del archivo Notas.txt

	//Obtener nombres
	string nombre; //Se crea la variable nombre de tipo string que servirá para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fNombres("Nombres.txt"); //Apertura en modo lectura del archivo llamado Nombres.txt
	if (fNombres.is_open()){ //Comprueba que el archivo esté abierto y mientras lo esté ejecuta el siguiente código
		while (getline(fNombres, nombre, '\n')){ //Mientras hayan nombres en el archivo, separados por un salto de línea, los leerá y escribirá en el vector
			vNombres.push_back(nombre); //Esta función guarda el elemento leído en el archivo al final del vector en cada iteración
		}
	} //Fin del condicional if
	fNombres.close(); //Cierra el archivo utilizado

	//Obtener creditos
	short cre = 0; //Se crea la variable cre de tipo short que servirá para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fCreditos("Creditos.txt"); //Apertura en modo lectura del archivo llamado Creditos.txt
	if (fCreditos.is_open()){ //Comprueba que el archivo esté abierto y mientras lo esté ejecuta el siguiente código
		while (fCreditos >> cre){ //Mientras hayan números en el archivo, separados por un salto de línea, los leerá y escribirá en el vector
			vCreditos.push_back(cre); //Esta función guarda el elemento leído en el archivo al final del vector en cada iteración
		}
	} //Fin del condicional if
	fCreditos.close(); //Cierra el archivo utilizado

	//Obtener calificaciones
	float cal = 0; //Se crea la variable cal de tipo float que servirá para guardar las calificaciones de cada materia, provenientes del archivo
	ifstream fNotas("Notas.txt"); //Apertura en modo lectura del archivo llamado Notas.txt
	if (fNotas.is_open()){ //Comprueba que el archivo esté abierto y mientras lo esté ejecuta el siguiente código
		while (fNotas >> cal){ //Mientras hayan números en el archivo, separados por un salto de línea, los leerá y escribirá en el vector
			vNotas.push_back(cal); //Esta función guarda el elemento leído en el archivo al final del vector en cada iteración
		}
	} //Fin del condicional if
	fNotas.close(); //Cierra el archivo utilizado

	float sumPonderacion = 0; //Creación e inicialización de la variable sumPonderacion que servirá para guardar la suma del producto de las notas y los créditos
	short sumCreditos = 0; //Creación e inicialización de la variable sumCreditos que servirá para guardar la suma de todos los créditos
	short cantidad = vNotas.size(); //Permite obtener la cantidad de elementos alojados en el vector Notas el cual coincide con la cantidad de materias

	cout << "\t\t     Creditos\t      Notas" << endl; //Se imprime en pantalla las palabras Creditos y Notas con un formato que permite tener un orden
	for (short i = 0; i < cantidad; i++){ //Este ciclo imprime en pantalla el nombre de la materia, sus créditos y la calificación obtenida
        //Se crea la variable i tipo short, se inicializa con el valor de cero y en cada iteración aumentará en uno para así recorrer todas las posiciones
        //del vector, desde el inicio hasta la posición final (la posición final o valor final de i está definido por la cantidad de elementos encontrados
        //en el vector vNotas el cual concide, como ya se indicó cuando se creó la variable cantidad, con la cantidad de materias)
		cout << vNombres[i]; //Imprime el elemento ubicado en la posición i del vector
		cout << "\t\t" << vCreditos[i]; //Imprime el elemento ubicado en la posición i del vector con un formato que permite tener un orden en la pantalla
		cout << "\t\t" << vNotas[i] << endl; //Imprime el elemento ubicado en la posición i del vector con un formato que permite tener un orden en la pantalla

		sumCreditos += vCreditos[i]; //En cada iteración se suman los créditos y el valor se guarda en la variable sumCreditos
		sumPonderacion += vNotas[i] * vCreditos[i]; //En cada iteración se suma el producto de los créditos y las notas correspondientes a una materia en específico
	} //Finaliza el ciclo for
	cout << endl << endl; //Realiza dos saltos de línea
	resultado(sumCreditos, sumPonderacion); //Llama a la función resultado, haciendo un paso por valor de dos parámatros. Ver la función resultado() para más información
} //Fin de la función mostrarPromedioGuardado()
//Función a utilizar si la opción elegida es la 2
void cambiarCalificaciones(){

    //Esta opción se habilitará cuando el usuario ya haya usado el programa anteriormente por lo que existirán archivos conteniendo la información que
    //el usuario ingresó e imprimirá en pantalla el nombre de las materias y sus respectivos créditos permitiendo modificar tan sólo las calificaciones
    //y procediendo a calcular el promedio semestral con la nueva información

    mostrarDatos();//se llama esta funcion para mostrar los datos ingresados en la funcion de pedir_datos

	cout << "\t\tPromedio semestral"; //Imprime el nombre del programa
	cout << endl << endl; //Realiza dos saltos de línea

	//Declarar vectores para almacenar la información proveniente de los archivos
	vector <string> vNombres; //Vector para guardar datos de tipo string, es decir, los nombres provenientes del archivo Nombres.txt
	vector <short> vCreditos; //Vector para guardar datos de tipo short, es decir, los créditos provenientes del archivo Creditos.txt

    //Obtener nombres
	string nombre; //Se crea la variable nombre de tipo string que servirá para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fNombres("Nombres.txt"); //Apertura en modo lectura del archivo llamado Nombres.txt
	if (fNombres.is_open()){ //Comprueba que el archivo esté abierto y mientras lo esté ejecuta el siguiente código
		while (getline(fNombres, nombre, '\n')){ //Mientras hayan nombres en el archivo, separados por un salto de línea, los leerá y escribirá en el vector
			vNombres.push_back(nombre); //Esta función guarda el elemento leído en el archivo al final del vector en cada iteración
		}
	} //Fin del condicional if
	fNombres.close(); //Cierra el archivo utilizado

	//Hallar la cantidad de elementos en el vector Nombre para saber con cuantas materias se va a trabajar y usarlo al crear el arreglo dinamico
	short cantidad = vNombres.size();

	//Creacion de punteros y arreglos dinamicos
    float *pNotas = NULL; //Crea un puntero para datos de tipo float y se apunta a NULL
    pNotas = new float[cantidad]; //Se crea un arreglo dinámico de tamaño igual a 'cantidad' y se apunta el puntero pNotas a la primera posición de este arreglo

	//Obtener creditos
	short cre = 0; //Se crea la variable cre de tipo string que servirá para guardar los nombres de las materias, uno a uno, provenientes del archivo
	ifstream fCreditos("Creditos.txt"); //Apertura en modo lectura del archivo llamado Creditos.txt
	if (fCreditos.is_open()){ //Comprueba que el archivo esté abierto y mientras lo esté ejecuta el siguiente código
		while (fCreditos >> cre){ //Mientras hayan números en el archivo, separados por un salto de línea, los leerá y escribirá en el vector
			vCreditos.push_back(cre); //Esta función guarda el elemento leído en el archivo al final del vector en cada iteración
		}
	} //Fin del condicional if
	fCreditos.close(); //Cierra el archivo utilizado

    //Creacion y apertura de archivo para los notas en modo escritura el cual sobreescribe al archivo existente del mismo nombre
	ofstream fNotas("Notas.txt");

	//Declara variables para almacenar la suma ponderada, la suma de créditos y la calificación de una materia inicializándolas con el valor cero
	float sumPonderacion = 0;
	short sumCreditos = 0;
	float cal = 0;

	cout << "\t\tNota:" << endl; //Imprime en pantalla el mensaje mencioando y da un salto de línea
	for (short i = 0; i < cantidad; i++) {

		// Loop para obtener las calificaciones
		do{ // Mientras la calificación ingresada por el usuario sea menor que NOTA_MIN o mayor que NOTA_MAX, se seguirá ejecutando este código
			cout << vNombres[i] << ": \t\t"; //Imprime en pantalla el nombre almacenado en la posición 'i' del vector vNombres[] con un formato específico
			cin >> cal; //Se lee el valor ingresado por el usuario
			*(pNotas+i) = cal; //El contenido de la variable cal se guarda en el arreglo dinámico usando la aritmética de punteros
			fNotas << pNotas[i] << endl; //Guarda las calificaciones en un archivo seguido de un salto de línea
		} while (cal < NOTA_MIN || cal > NOTA_MAX); //Condición: Repetir el código mientras la variable cal sea menor que NOTA_MIN o mayor que NOTA_MAX

		// sumar las notas*creditos y los creditos
		sumCreditos += vCreditos[i]; //En cada iteración se suman los créditos almacenados en el vector con el nuevo elemento y se guarda en la variable sumCreditos
		sumPonderacion += pNotas[i] * vCreditos[i]; //En cada iteración se suma el producto de los créditos (almacenados en un vector) y las notas
                                                    //(almacenadas en un arreglo dinámico) correspondientes a una materia en específico y el valor se guarda
                                                    //en la variable sumPonderacion
	}

	//Imprimir el resultado
	resultado(sumCreditos, sumPonderacion); //Llama a la función resultado, haciendo un paso por valor de dos parámatros. Ver la función resultado() para más información
}
//Función a utilizar si la opción elegida es la 3
void nuevaSesion(){

    //Esta opción se habilitará por defecto cuando el usuario no ha usado el programa anteriormente y también cuando el usuario elija la opción 3
    //cuando el programa encuentre información la cual se crea después de un primer uso por lo que existirán archivos conteniendo la información que
    //el usuario ingresó en un uso anterior.
    //Su función es la de obtener del usuario la cantidad de materias que está viendo en el semestre actual y el nombre, crédito y calificaciones de las mismas
    //Para devolver el promedio semestral.


	//Declara variables para el numero de materias, la suma ponderada y la suma de créditos
	short num_Mat = 0;
	float sumPonderacion = 0;
	short sumCreditos = 0;

	cout << "\t\tPromedio semestral"; //Imprime el nombre del programa
	cout << endl << endl; //Realiza dos saltos de línea

	pedir_datos_op3();

	//Solicitar el numero de materias
	cout << "Ingrese el numero de materias\n";
	cin >> num_Mat; //Se lee el valor ingresado por el usuario y se almacenada en la variable num_Mat que servirá para crear el arreglo dinámico
	cout << endl; //Realiza un salto de línea
	cin.ignore();    // Elimina el stroke del Enter. Evita que la primera materia sea cero (vacio)

    //Crear archivos para las tres variables
	ofstream fNombres;
	ofstream fCreditos;
	ofstream fNotas;

	//Abrir los archivos y nombrarlos
	fNombres.open("Nombres.txt"); //Abre el archivo y lo nombra Nombres.txt
	fCreditos.open("Creditos.txt"); //Abre el archivo y lo nombra Creditos.txt
	fNotas.open("Notas.txt"); //Abre el archivo y lo nombra Notas.txt

	//Declaración de punteros
	float *pCreditos, *pNotas;
	string *pNombres;

	//Creación de arreglos dinámicos
	pNombres = new string[num_Mat];
	pCreditos = new float[num_Mat];
	pNotas = new float[num_Mat];

	cout << "Nota: No ingrese nombres largos, por favor." << endl << endl;
	//Se solicita no ingresar nombres largos para que el formato que se le da a continuación no se vea afectado
	//Lo anterior se puede evitar si se usa la función setw() y esto puede ser implementado más adelante

	//Loop para obtener los nombres de todas las materias
	for (short i = 0; i < num_Mat; i++){ //Ciclo for usado para solicitar al usuario los nombres de las materias y almacenarlas en un arreglo dinámico
		string nombre;    //Declarar una variable tipo string
		cout << "Ingresa el nombre de la materia " << i + 1 << endl; //Se solicita al usuario los nombres de las materias
		getline(cin, nombre); //Obtiene los nombres de las materias, los cuales pueden contener espacios
		//vNombres.push_back(nombre);    //Guarda cada materia al final del vector en cada loop
		*(pNombres+i) = nombre; //Aritmética de punteros usada para llenar el arreglo dinámica empezando en la posición cero
		fNombres << *(pNombres+i) << endl; //Guarda los nombres en un archivo seguido de un salto de línea
		cout << endl; //Realiza un salto de línea
	} //Finaliza el ciclo for

	//Loops para imprimir el nombre de las materias una a una y obtener las calificaciones y los créditos de cada materia
	for (short i = 0; i < num_Mat; i++){
		cout << pNombres[i] << ": \t" << endl;  //Imprime los nombres de las materias
		float cal = 0; //Declara la variable cal de tipo float que servirá para almacenar la calificación ingresada por el usuario

		// Loop para obtener las calificaciones
		do{ // Mientras la calificación ingresada por el usuario sea menor que NOTA_MIN o mayor que NOTA_MAX, se seguirá ejecutando este código
			cout << "Nota:\t\t"; //Imprime en pantalla el mensaje mencionado
			cin >> cal; //Se lee el valor ingresado por el usuario y se almacenada en la variable cal
		} while (cal < NOTA_MIN || cal > NOTA_MAX);
		*(pNotas+i) = cal; //El contenido de la variable cal se guarda en el arreglo dinámico usando la aritmética de punteros
		fNotas << pNotas[i] << endl; //Guarda las calificaciones en un archivo seguido de un salto de línea

		short cre = 0; //Declara la variable cre de tipo short que servirá para almacenar el crédito ingresado por el usuario

		// Loop para obtener los creditos
		do{ // Mientras el valor del crédito ingresado por el usuario sea menor que CRED_MIN o mayor que CRED_MAX, se seguirá ejecutando este código
			cout << "Credito:\t"; //Imprime en pantalla el mensaje mencionado
			cin >> cre; //Se lee el valor ingresado por el usuario y se almacenada en la variable cre
		} while (cre < CRED_MIN || cre > CRED_MAX); //Condición de la función do-while
		pCreditos[i] = cre; //El contenido de la variable cre se guarda en el arreglo dinámico usando otra forma de almacenamiento, estaba: *(pCreditos+i) = cre
		fCreditos << pCreditos[i] << endl; //Guarda los créditos en un archivo seguido de un salto de línea
		cout << endl;

		// sumar las notas*creditos y los creditos
		sumCreditos += pCreditos[i]; //En cada iteración se suman los créditos usando un puntero y el valor se guarda en la variable sumCreditos
		sumPonderacion += pNotas[i] * pCreditos[i]; //En cada iteración se suma el producto de los créditos y las notas correspondientes a una materia
                                                    //en específico y el valor se guarda en la variable sumPonderacion
	} //Finaliza el ciclo for

	//Cerrar los archivos creados
	fNombres.close(); //Cierra el archivo de los nombres
	fCreditos.close(); //Cierra el archivo de los créditos
	fNotas.close(); ////Cierra el archivo de las calificaciones

	//Imprimir el resultado
	resultado(sumCreditos, sumPonderacion); //Llama a la función resultado, haciendo un paso por valor de dos parámatros. Ver la función resultado() para más información
}
//Función que imprime en pantalla el resultado
void resultado(short sumCreditos, float sumPonderacion){
    //Recibe como parámetros un short y un float los cuáles se pasan por valor y no por puntero ni referencia ya que no queremos cambiar sus valores, sólo utilizarlos
	float resultado = sumPonderacion / sumCreditos; //Se declara la variable resultado de tipo float y se inicializa con la división de los dos parámetros que recibe esta función
	cout << "Tu promedio semestral es: " << setprecision(3) << resultado << endl; //Imprime en pantalla el resultado obtenido correspondiente al promedio semestral
                                                                                //Se usa la función setprecision() para mostrar tan sólo 2 decimales
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
