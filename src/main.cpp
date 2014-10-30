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
void doLaMasChiquitaConPuntoBlanco(GaleriaImagenes &galeria);
void doEliminarMasVotada(GaleriaImagenes &galeria);
void doVotar(GaleriaImagenes &galeria);
void doTop10(GaleriaImagenes &galeria);

void abrirArchivoIn(string mensaje, ifstream &archivoIn);
void abrirArchivoOut(string mensaje, ofstream &archivoOut);


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
				doTop10(galeria);
				break;
			case 7:
				doLaMasChiquitaConPuntoBlanco(galeria);
				break;
			case 8:
				doAgregarImagen(galeria);
				break;
			case 9:
				doVotar(galeria);
				break;
			case 10:
				doEliminarMasVotada(galeria);
				break;
			case 11:
				doGuardarGaleria(galeria, rutaArchivoGaleria);
				break;
			default:
				cin.ignore();
				break;
		}

		if(selected_action != 0){
			cout << "presione una tecla para continuar..." << endl;
			cin.ignore();
		}
	}
}

void doFilter(int filter){
	Imagen imagenOriginal (0,0);
	ifstream archivoIn;  abrirArchivoIn("ingrese el nombre del archivo a modificar:", archivoIn);
	ofstream archivoOut; abrirArchivoOut("ingrese el nombre del archivo de salida:", archivoOut);
	int k;

	cout << "ingrese la intensidad del filtro (k):" << endl;
	cin >> k;
	cin.ignore();

	imagenOriginal.cargar(archivoIn);
	switch(filter){
		case BLUR:
			imagenOriginal.blur(k);
			break;
		case ACUARELA:
			imagenOriginal.acuarela(k);
			break;
	}

	imagenOriginal.guardar(archivoOut);
}

void doPosicionesMasOscuras(GaleriaImagenes &galeria){
	string nombreArchivoIn;
	ifstream archivoIn; abrirArchivoIn("ingrese el nombre del archivo a leer:", archivoIn);
	Imagen imagenOriginal (0,0);

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

	cout << "]" << endl;

	galeria.agregarImagen(imagenOriginal);

}

void doAgregarImagen(GaleriaImagenes &galeria){
	ifstream archivoIn; abrirArchivoIn("ingrese el nombre de la imagen que desea agregar:", archivoIn);
	Imagen imagenNueva (0,0);

	imagenNueva.cargar(archivoIn);

	galeria.agregarImagen(imagenNueva);

}

void doCargarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria){
	ifstream archivoIn; abrirArchivoIn("ingrese el nombre de la galeria que desea cargar:", archivoIn);

	galeria.cargar(archivoIn);
}

void doGuardarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria){

	ofstream archivoOut;
	//TODO: acá no se pide el nombre del archivo y SIEMPRE se guarda sobre la misma galeria, está bien?
	archivoOut.open(rutaArchivoGaleria.c_str());

	galeria.guardar(archivoOut);

	cin.ignore();
}

void doLaMasChiquitaConPuntoBlanco(GaleriaImagenes &galeria){
	Imagen imagenFinal = galeria.laMasChiquitaConPuntoBlanco();

	if(imagenFinal.alto() != 0){
		ofstream archivoOut;
		abrirArchivoOut("ingrese el nombre para guardar la imagen más chiquita con punto blanco:", archivoOut);

		imagenFinal.guardar(archivoOut);
	}
	else{
		cout << "no se encontró ninguna imagen con punto blanco" << endl;
	}

	cin.ignore();
}

void doEliminarMasVotada(GaleriaImagenes &galeria){
	// FIXME: el requiere dice que aca tiene que haber al menos una imagen y no esta chequeandose eso.
	galeria.eliminarMasVotada();
	cin.ignore();
}

void doVotar(GaleriaImagenes &galeria){
	Imagen imagenVotada (0,0);

	ifstream archivoIn; abrirArchivoIn("ingrese el nombre de la imagen que desea votar:", archivoIn);

	imagenVotada.cargar(archivoIn);

	galeria.votar(imagenVotada);

	cin.ignore();

}

void doTop10(GaleriaImagenes &galeria){
	vector<Imagen> top10;
	ofstream archivoOut; abrirArchivoOut("ingrese el nombre del archivo de salida:", archivoOut);

	top10 = galeria.top10();

	int i = 0;

	archivoOut << '[';

	while(i < top10.size()) {
	    if (i>0 && i < top10.size()) {
			archivoOut << ',';
	    }
	    top10[i].guardar(archivoOut);
	    i++;
	}

	archivoOut << ']';

	cin.ignore();
}

string pedirString(string mensaje) {
	string str;

	cout << mensaje << '\n';
	cin  >> str;

	return str;
}

void abrirArchivoIn(string mensaje, ifstream& archivoIn) {
	archivoIn.open(pedirString(mensaje).c_str());
}

void abrirArchivoOut(string mensaje, ofstream& archivoOut) {
	archivoOut.open(pedirString(mensaje).c_str());
}
