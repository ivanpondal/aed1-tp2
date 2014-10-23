#include "main.h"
#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int selected_action =- 1;

	while(selected_action != 0){
		cout << "ingrese el número de la acción que desea realizar:" << endl;
		cout << "0. exit" << endl;
		cout << "1. blur" << endl;
		cout << "2. acuarela" << endl;
		cout << "3. cargar galería" << endl;
		cout << "4. dividirYAgregar" << endl;
		cout << "5. posicionesMásOscuras" << endl;
		cout << "6. top 10" << endl;
		cout << "7. laMásChiquitaConPuntoBlanco" << endl;
		cout << "8. agregarImagen" << endl;
		cout << "9. votar" << endl;
		cout << "10. eliminarMásVotada" << endl;
		cout << "11. guardar galería" << endl;

		cin >> selected_action;

		switch (selected_action){
			case 1:
				doBlur();
				break;
			case 2:
				// TODO acuarela
				break;
			case 3:
				// TODO cargar galería
				break;
			case 4:
				// TODO dividirYAgregar
				break;
			case 5:
				// TODO posicionesMásOscuras
				break;
			case 6:
				// TODO top 10
				break;
			case 7:
				// TODO laMásChiquitaConPuntoBlanco
				break;
			case 8:
				// TODO agregarImagen
				break;
			case 9:
				// TODO votar
				break;
			case 10:
				// TODO eliminarMásVotada
				break;
			case 11:
				// TODO guardar galería
				break;
		}
	}
}

void doBlur(){
	int k;
	string nombreArchivoIn;
	string nombreArchivoOut;
	ifstream archivoIn;
	ofstream archivoOut;
	Imagen imagenOriginal (0,0);
	
	cout << "ingrese el nombre del archivo a modificar:" << endl;
	cin >> nombreArchivoIn;
	cout << "ingrese el nombre del archivo de salida:" << endl;
	cin >> nombreArchivoOut;
	cout << "ingrese la intensidad del filtro (k):" << endl;
	cin >> k;
	
	archivoIn.open(nombreArchivoIn.c_str());
	
	imagenOriginal.cargar(archivoIn);
	
	imagenOriginal.blur(k);
	
	archivoOut.open(nombreArchivoOut.c_str());
	
	imagenOriginal.guardar(archivoOut);
	
	cin.ignore();
}
