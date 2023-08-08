#include <iostream>
#include <string>
#include <queue>
#include <conio.h>
#include <unordered_map>
#include <fstream>
using namespace std;

//Se crea el Nodo para el Arbol
struct Nodo {
	char caracter; //El árbol leerá los caracteres introducidos
	int frecuencia; //Variable que determina la frecuencia con la que se repite el caracter
	Nodo* izquierda, * derecha; //Se recorrerá el nodo izquierdo y derecho del Nodo
};

//Conseguir un nuevo Arbol de Nodos y definir las variables necesarias para el algoritmo
Nodo* getNodo(char _caracter, int _frecuencia, Nodo* _izquierda, Nodo* _derecha) {
	Nodo* nodo = new Nodo();
	nodo->caracter = _caracter;
	nodo->frecuencia = _frecuencia;
	nodo->izquierda = _izquierda;
	nodo->derecha = _derecha;

	return nodo;
}

//Comparar la frecuencia con la que se repite la variable
struct Comparador {
	bool operator()(Nodo* I, Nodo* D) {
		return I->frecuencia > D->frecuencia;
	}
};

//Función que codifica los caracteres
void Codificar(Nodo* raiz, string str, unordered_map<char, string>& codigoHuffman) {
	if (raiz == nullptr) 
		return;

	if (!raiz->izquierda && !raiz->derecha) {
		codigoHuffman[raiz->caracter] = str;
	}

	//Reemplaza los caracteres por "0" y "1", formando así un código binario
	Codificar(raiz->izquierda, str + "0", codigoHuffman);
	Codificar(raiz->derecha, str + "1", codigoHuffman);
}

//Algoritmo Huffman y construcción del arbol
void Comprimir_Contenido(string texto) {

	unordered_map<char, int> frecuencia;
	for (char caracter : texto) {
		frecuencia[caracter]++;
	}

	priority_queue<Nodo*, vector<Nodo*>, Comparador>pq; //PQ es Priority Queue, que viene a ser Cola de Prioridad

	for (auto par : frecuencia) {
		pq.push(getNodo(par.first, par.second, nullptr, nullptr));
	}

	while (pq.size() != 1) {
		Nodo* izquierda = pq.top(); pq.pop();
		Nodo* derecha = pq.top(); pq.pop();

		int suma = izquierda->frecuencia + derecha->frecuencia;
		pq.push(getNodo('\0', suma, izquierda, derecha));
	}

	Nodo* raiz = pq.top();

	unordered_map<char, string> codigoHuffman;
	Codificar(raiz, "", codigoHuffman);

	//Mostrar el contenido codificado en el bloc de notas
	ofstream archivo;

	archivo.open("ContenidoHuffman.txt");
	for (auto par : codigoHuffman) {
		archivo << par.first << " " << par.second << '\n';
	}

	string str = "";
	for (char caracter : texto) {
		str += codigoHuffman[caracter];
	}

	archivo << '\n' << str << '\n';
}

//Descomprimir y mostrar el contenido ingresado
void Descomprimir_Contenido(string texto) {
	ofstream bloc;
	bloc.open("ContenidoHuffman.txt");
	bloc << texto << endl;
}

//MENU PRINCIPAL
int main() {

	//Variables
	string contenido;
	ofstream archivo;
	int opcion;

	cout << "-----------------------------" << endl;
	cout << "|    COMPRESION DE DATOS    |" << endl;
	cout << "-----------------------------" << endl;
	cout << "\t Bienvenido/a" << endl;
	cout << "Ingrese el contenido del archivo: "; cin >> contenido;
	system("cls");
	cout << "\t|||MENU DE OPCIONES|||" << endl;
	cout << "     1. Comprimir contenido" << endl;
	cout << "     2. Descomprimir contenido" << endl;
	cout << "     3. Salir" << endl;
	cout << "\nSeleccione una opcion: "; cin >> opcion;

	if (opcion == 1) {
		cout << "Se ha comprimido el siguiente contenido: " << contenido << endl;
		Comprimir_Contenido(contenido);
		cout << "Presione Enter para salir " << endl;
		_getch();
		return 0;
	}
	if (opcion == 2) {
		cout << "Se ha descomprimido el siguiente contenido: " << contenido << endl;
		Descomprimir_Contenido(contenido);
		cout << "Presione Enter para salir " << endl;
		_getch();
		return 0;
	}
	if (opcion == 3) {
		cout << "Se ha finalizado el programa, hasta luego" << endl;
		cout << "Presione Enter para salir " << endl;
		_getch();
		return 0;
	}
}