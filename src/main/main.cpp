#include "../include/pixel.h"
#include "../include/imagen.h"
#include "../include/galeria_imagenes.h"

#include <iostream>

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
				// TODO blur
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
