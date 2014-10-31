#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <iostream>
#include <fstream>

using namespace std;

void doFilter(int filter);
void doCargarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria);
void doDividirYAgregar(GaleriaImagenes &galeria);
void doPosicionesMasOscuras(GaleriaImagenes &galeria);
void doTop10(GaleriaImagenes &galeria);
void doLaMasChiquitaConPuntoBlanco(GaleriaImagenes &galeria);
void doAgregarImagen(GaleriaImagenes &galeria);
void doVotar(GaleriaImagenes &galeria);
void doEliminarMasVotada(GaleriaImagenes &galeria);
void doGuardarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria);

void abrirArchivoIn(string mensaje, ifstream &archivoIn);
void abrirArchivoInYpisarElNombre(string msj, ifstream &archivoIn, string& nom);
void abrirArchivoOut(string mensaje, ofstream &archivoOut);


int main()
{
	int selected_action =- 1;
	GaleriaImagenes galeria;
	string rutaArchivoGaleria;

	while(selected_action != 0){

		cout << "ingrese el número de la acción que desea realizar:\n"
		" 0. exit\n"
		" 1. blur\n"
		" 2. acuarela\n"
		" 3. cargar galería\n"
		" 4. dividirYAgregar\n"
		" 5. posicionesMásOscuras\n"
		" 6. top 10\n"
		" 7. laMásChiquitaConPuntoBlanco\n"
		" 8. agregarImagen\n"
		" 9. votar\n"
		"10. eliminarMásVotada\n"
		"11. guardar galería\n"
		;

		cin >> selected_action;

		switch (selected_action){
      case 1:  doFilter(BLUR);
               break;

      case 2:  doFilter(ACUARELA);
               break;

      case 3:  doCargarGaleria(galeria, rutaArchivoGaleria);
               break;

      case 4:  doDividirYAgregar(galeria);
               break;

      case 5:  doPosicionesMasOscuras(galeria);
               break;

      case 6:  doTop10(galeria);
               break;

      case 7:  doLaMasChiquitaConPuntoBlanco(galeria);
               break;

      case 8:  doAgregarImagen(galeria);
               break;

      case 9:  doVotar(galeria);
               break;

      case 10: doEliminarMasVotada(galeria);
               break;

      case 11: doGuardarGaleria(galeria, rutaArchivoGaleria);
               break;

		}

		if(selected_action != 0){
			cin.ignore();
			cout << "presione una tecla para continuar...\n";
			cin.ignore();
		}
	}
}

void doFilter(int filter){
	Imagen imagenOriginal (0,0);
	ifstream archivoIn;
	abrirArchivoIn("ingrese el nombre del archivo a modificar:", archivoIn);

	ofstream archivoOut;
	abrirArchivoOut("ingrese el nombre del archivo de salida:", archivoOut);

	int k;

	cout << "ingrese la intensidad del filtro (k):\n";
	cin >> k;

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

void doCargarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria){
	ifstream archivoIn;

	abrirArchivoInYpisarElNombre(
		"ingrese el nombre de la galeria que desea cargar:",
		archivoIn, rutaArchivoGaleria);

	galeria.cargar(archivoIn);
}

void doDividirYAgregar(GaleriaImagenes &galeria){
	int n, m;
	Imagen im (0,0);
	ifstream archivoIn;
	abrirArchivoIn("Nombre del archivo de la imagen (que está en la galeria)"
				   " a agregar sus divisiones?", archivoIn);
	im.cargar(archivoIn);

	cout << "Cuantas columnas? (n, debe ser multiplo del ancho de la img):\n";
 	cin >> n;

	cout << "Cuantas filas? (m, debe ser multiplo del alto de la img):\n";
	cin >> m;

	galeria.dividirYAgregar(im, n, m);
}

void doPosicionesMasOscuras(GaleriaImagenes &galeria){
	string nombreArchivoIn;
	ifstream archivoIn;
	abrirArchivoIn("ingrese el nombre del archivo a leer:", archivoIn);

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

	cout << "]\n";

	galeria.agregarImagen(imagenOriginal);

}

void doTop10(GaleriaImagenes &galeria){
	vector<Imagen> top10;
	ofstream archivoOut;
	abrirArchivoOut("ingrese el nombre del archivo de salida:", archivoOut);

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
}

void doLaMasChiquitaConPuntoBlanco(GaleriaImagenes &galeria){
	Imagen imagenFinal = galeria.laMasChiquitaConPuntoBlanco();

	if(imagenFinal.alto() != 0){
		ofstream archivoOut;
		abrirArchivoOut("ingrese el nombre para guardar la imagen más chiquita"
						" con punto blanco:", archivoOut);

		imagenFinal.guardar(archivoOut);
	}
	else{
		cout << "no se encontró ninguna imagen con punto blanco\n";
	}
}

void doAgregarImagen(GaleriaImagenes &galeria){
	ifstream archivoIn;
	abrirArchivoIn("ingrese el nombre de "
				   "la imagen que desea agregar:", archivoIn);

	Imagen imagenNueva (0,0);

	imagenNueva.cargar(archivoIn);

	galeria.agregarImagen(imagenNueva);

}

void doVotar(GaleriaImagenes &galeria){
	Imagen imagenVotada (0,0);

	ifstream archivoIn;
	abrirArchivoIn("ingrese el nombre de la imagen a votar:", archivoIn);

	imagenVotada.cargar(archivoIn);

	galeria.votar(imagenVotada);
}

void doEliminarMasVotada(GaleriaImagenes &galeria){
	galeria.eliminarMasVotada();
}

void doGuardarGaleria(GaleriaImagenes &galeria, string &rutaArchivoGaleria){

	ofstream archivoOut;
	archivoOut.open(rutaArchivoGaleria.c_str());

	galeria.guardar(archivoOut);
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

void abrirArchivoInYpisarElNombre(string mje, ifstream& archivoIn, string& nom){
	elNombre = pedirString(mje);
	archivoIn.open(nom.c_str());
}

void abrirArchivoOut(string mensaje, ofstream& archivoOut) {
	archivoOut.open(pedirString(mensaje).c_str());
}
