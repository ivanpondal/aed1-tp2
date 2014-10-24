#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

void testPixel();
void testImagen();
void testGaleria();
int main()
{
    testPixel();
    testImagen();
    testGaleria();
    cout << "Tests OK" << endl;
}

void testPixel() {

  // constructor con argumentos
  Pixel pc1 (4, 4, 4);
  assert (pc1.red()    == 4);
  assert (pc1.green()  == 4);
  assert (pc1.blue()   == 4);

  // constructor con argumentos fuera de rango va a guardar fruta
  Pixel pcfr (4, 4, 46666);
  assert (pcfr.red()    == 4);
  assert (pcfr.green()  == 4);
  assert (pcfr.blue()   == 46666);

  // igualdad
  Pixel p1, p2;
  assert (p1 == p2);

  // cambiarPixel
  p1.cambiarPixel(12, 34, 56);
  assert (p1.red()    == 12);
  assert (p1.green()  == 34);
  assert (p1.blue()   == 56);

  // desigualdad
  assert (p1 != p2);

  //guardar
  Pixel g(10,50,3);
  ostringstream oss;
  g.guardar(oss);
  assert (oss.str() == "(10;50;3)");

  //cargar
  Pixel c;
  istringstream iss ("(60;50;40)");
  c.cargar(iss);
  assert (c.red()   == 60);
  assert (c.green() == 50);
  assert (c.blue()  == 40);
}

void testImagen() {
  // constructor, alto, ancho, todanegra
  Pixel negro;
  Pixel rojo(255, 0, 0);
  Pixel p;
  Imagen i1 (2, 3);
  assert(i1.alto() == 2);
  assert(i1.ancho() == 3);

  for (int y=0; y < i1.alto(); y++) {
    for (int x=0; x < i1.ancho(); x++) {
        assert(i1.obtenerPixel(y, x) == negro);
    }
  }

  assert(i1.obtenerPixel(1,1) == negro);
  i1.modificarPixel(1,1, rojo);
  assert(i1.obtenerPixel(1,1) == rojo);

  //guardar
  ostringstream oss;
  i1.guardar(oss);
  assert (oss.str() == "2 3 [(0;0;0),(0;0;0),(0;0;0),(0;0;0),(255;0;0),(0;0;0)]");

  //cargar
  istringstream iss("2 2 [(1;2;3),(123;121;31),(2;1;231),(167;161;173)]");
  Imagen ic(0,0);
  ic.cargar(iss);
  assert (ic.obtenerPixel(0,0) == Pixel(1,    2,  3));
  assert (ic.obtenerPixel(0,1) == Pixel(123,121, 31));
  assert (ic.obtenerPixel(1,0) == Pixel(2,    1,231));
  assert (ic.obtenerPixel(1,1) == Pixel(167,161,173));

  //blur
  ifstream archivoOriginal("../res/hermione.specimg");
  ifstream archivoOriginal2("../res/hermione.specimg");

  ifstream archivoBlurK5("../res/hermione.blur.k5.specimg");
  ifstream archivoAcuarelaK5("../res/hermione.acuarela.k5.specimg");

  ofstream archivoBlurNuestroK5("../res/hermione.blurnuestro.k5.specimg");
  ofstream archivoAcuarelaNuestroK5("../res/hermione.acuarelanuestro.k5.specimg");

  Imagen imagenOriginal(0,0);
  Imagen imagenOriginal2(0,0);

  Imagen imagenBlurK5(0,0);
  Imagen imagenAcuarelaK5(0,0);

  imagenOriginal.cargar(archivoOriginal);
  imagenOriginal2.cargar(archivoOriginal2);

  imagenOriginal.blur(5);
  imagenOriginal2.acuarela(5);

  imagenOriginal.guardar(archivoBlurNuestroK5);
  imagenOriginal2.guardar(archivoAcuarelaNuestroK5);

  archivoBlurNuestroK5.close();
  archivoAcuarelaNuestroK5.close();

  imagenBlurK5.cargar(archivoBlurK5);
  imagenAcuarelaK5.cargar(archivoAcuarelaK5);

  //FIXME: las imagenes no cumplen el filtro blur, hay sombras raras en los bordes.
  //       ademas, son k6, no k5
  //
  //FIXME: hacer que esto corra o pedirle a los profes imagenes que cumplan la spec
  //assert (imagenOriginal == imagenBlurK5);
  //assert (imagenOriginal2 == imagenAcuarelaK5);

  //posicionesMasOscuras
  //ejemplo fruta
  Imagen ipmo(2,2);
  ipmo.modificarPixel(0,0, rojo);
  ipmo.modificarPixel(1,1, rojo);

  vector < pair <int, int> > pos;
  pos = ipmo.posicionesMasOscuras();

  assert(pos[0] == (pair <int, int>(0, 1)));
  assert(pos[1] == (pair <int, int>(1, 0)));

  //poder calcularlo en imagenes de verdad
  vector < pair <int, int> > hermioneBlurPosicionesMasOscuras;
  hermioneBlurPosicionesMasOscuras = imagenBlurK5.posicionesMasOscuras();


}

void testGaleria() {
  string galeriaInString  = "[(1 1 [(1;1;1)],5),(1 1 [(3;3;3)],3),(1 1 [(2;2;2)],2)]";
  string galeriaOutString = "[(1 1 [(2;2;2)],2),(1 1 [(3;3;3)],3),(1 1 [(1;1;1)],5)]";

  istringstream iss(galeriaInString.c_str());
  ostringstream oss;

  GaleriaImagenes g;
  g.cargar(iss);
  g.guardar(oss);
  assert (oss.str() == galeriaOutString);
}
