#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <iostream>
#include <fstream>

using namespace std;

void doFilter(int filter);
void doPosicionesMasOscuras(GaleriaImagenes &galeria);
void doAgregarImagen(GaleriaImagenes &galeria);
void doCargarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria);
void doGuardarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria);

int main()
{
	int selected_action =- 1;
	GaleriaImagenes galeria;
	string rutaArchivoGaleria;

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
				doFilter(BLUR);
				break;
			case 2:
				doFilter(ACUARELA);
				break;
			case 3:
				doCargarGaleria(galeria, rutaArchivoGaleria);
				break;
			case 4:
				// TODO dividirYAgregar
				break;
			case 5:
				doPosicionesMasOscuras(galeria);
				break;
			case 6:
				// TODO top 10
				break;
			case 7:
				// TODO laMásChiquitaConPuntoBlanco
				break;
			case 8:
				doAgregarImagen(galeria);
				break;
			case 9:
				// TODO votar
				break;
			case 10:
				// TODO eliminarMásVotada
				break;
			case 11:
				doGuardarGaleria(galeria, rutaArchivoGaleria);
				break;
		}
	}
}

void doFilter(int filter){
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
	switch(filter){
		case BLUR:
			imagenOriginal.blur(k);
			break;
		case ACUARELA:
			imagenOriginal.acuarela(k);
			break;
	}
	
	archivoOut.open(nombreArchivoOut.c_str());
	
	imagenOriginal.guardar(archivoOut);
}

void doPosicionesMasOscuras(GaleriaImagenes &galeria){
	string nombreArchivoIn;
	ifstream archivoIn;
	Imagen imagenOriginal (0,0);

	cout << "ingrese el nombre del archivo a leer:" << endl;

	cin >> nombreArchivoIn;

	archivoIn.open(nombreArchivoIn.c_str());

	imagenOriginal.cargar(archivoIn);

	vector < pair <int, int> > pos;
	pos = imagenOriginal.posicionesMasOscuras();

	int i;

	cout << "[";

	for(i=0; i<pos.size() ; i++){
		if(i == pos.size()-1){
			cout << "(" << pos[i].first << "," << pos[i].second << ")";
		}else{
			cout << "(" << pos[i].first << "," << pos[i].second << "),";
		}
	}

	cout << "]";

	galeria.agregarImagen(imagenOriginal);

}

void doAgregarImagen(GaleriaImagenes &galeria){
	string nombreArchivoIn;
	ifstream archivoIn;
	Imagen imagenNueva (0,0);

	cout << "ingrese el nombre de la imagen que desea agregar:" << endl;

	cin >> nombreArchivoIn;

	archivoIn.open(nombreArchivoIn.c_str());

	imagenNueva.cargar(archivoIn);

	galeria.agregarImagen(imagenNueva);

}

void doCargarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria){
	string nombreArchivoIn;
	ifstream archivoIn;

	cout << "ingrese el nombre de la galeria que desea cargar:" << endl;

	cin >> rutaArchivoGaleria;

	archivoIn.open(nombreArchivoIn.c_str());

	galeria.cargar(archivoIn);

}

void doGuardarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria){

	ofstream archivoOut;
	
	archivoOut.open(rutaArchivoGaleria.c_str());
	
	galeria.guardar(archivoOut);
}
