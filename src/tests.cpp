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
  string esperado = "2 3 [(0;0;0),(0;0;0),(0;0;0),(0;0;0),(255;0;0),(0;0;0)]";
  assert (oss.str() == esperado);

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

  Imagen imagenOriginal(0,0);
  Imagen imagenOriginal2(0,0);

  Imagen imagenBlurK5(0,0);
  Imagen imagenAcuarelaK5(0,0);

  imagenOriginal.cargar(archivoOriginal);
  imagenOriginal2.cargar(archivoOriginal2);

  imagenOriginal.blur(5);
  imagenOriginal2.acuarela(5);

  imagenBlurK5.cargar(archivoBlurK5);
  imagenAcuarelaK5.cargar(archivoAcuarelaK5);

  assert (imagenOriginal == imagenBlurK5);
  assert (imagenOriginal2 == imagenAcuarelaK5);

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
  string galeriaInString  =
                "[(1 1 [(1;1;1)],5),(1 1 [(3;3;3)],3),(1 1 [(2;2;2)],2)]";
  string galeriaOutString =
                "[(1 1 [(2;2;2)],2),(1 1 [(3;3;3)],3),(1 1 [(1;1;1)],5)]";

  istringstream iss(galeriaInString.c_str());
  ostringstream oss;

  vector <Imagen> vim;
  GaleriaImagenes g;
  int i;
  g.cargar(iss);
  g.guardar(oss);
  assert (oss.str() == galeriaOutString);

  int res_t10_4[] = {4,3,2,1};
  string gist10_4 = "["
                        "(1 1 [(1;1;1)],1),"
                        "(1 1 [(4;4;4)],4),"
                        "(1 1 [(3;3;3)],3),"
                        "(1 1 [(2;2;2)],2)"
                    "]";
  int res_t10_10[] = {9,8,7,6,5,4,3,2,1,0};
  string gist10_10 = "["
                        "(1 1 [(1;1;1)],1),"
                        "(1 1 [(4;4;4)],4),"
                        "(1 1 [(3;3;3)],3),"
                        "(1 1 [(2;2;2)],2),"
                        "(1 1 [(6;6;6)],6),"
                        "(1 1 [(8;8;8)],8),"
                        "(1 1 [(9;9;9)],9),"
                        "(1 1 [(5;5;5)],5),"
                        "(1 1 [(7;7;7)],7),"
                        "(1 1 [(0;0;0)],0)"
                    "]";
  int res_t10_12[] = {500,100,9,8,7,6,5,4,3,2};
  string gist10_12 = "["
                        "(1 1 [(1;1;1)],1),"
                        "(1 1 [(4;4;4)],4),"
                        "(1 1 [(3;3;3)],3),"
                        "(1 1 [(2;2;2)],2),"
                        "(1 1 [(6;6;6)],6),"
                        "(1 1 [(8;8;8)],8),"
                        "(1 1 [(9;9;9)],9),"
                        "(1 1 [(5;5;5)],5),"
                        "(1 1 [(7;7;7)],7),"
                        "(1 1 [(0;0;0)],0),"
                        "(1 1 [(100;100;100)],100),"
                        "(1 1 [(500;500;500)],500)"
                      "]";

  istringstream iss4(gist10_4.c_str());
  g.cargar(iss4);

  vim = g.top10();
  for (i=0; i<vim.size(); i++) {
    assert(vim[i].obtenerPixel(0,0).red() == res_t10_4[i]);
  }

  istringstream iss10(gist10_10.c_str());
  g.cargar(iss10);

  vim = g.top10();
  for (i=0; i<vim.size(); i++) {
    assert(vim[i].obtenerPixel(0,0).red() == res_t10_10[i]);
  }

  istringstream iss12(gist10_12.c_str());
  g.cargar(iss12);

  vim = g.top10();
  for (i=0; i<vim.size(); i++) {
    assert(vim[i].obtenerPixel(0,0).red() == res_t10_12[i]);
  }

  //agrega imagen cuaquiera de 2x2 que no está
  string galeriaInStringa  = "[(1 1 [(1;1;1)],5),(1 1 [(3;3;3)],3),"
                              "(1 1 [(2;2;2)],2)]";

  string galeriaOutStringa =
                    "[(2 2 [(1;2;3),(123;121;31),(2;1;231),(167;161;173)],0),"
                    "(1 1 [(2;2;2)],2),(1 1 [(3;3;3)],3),(1 1 [(1;1;1)],5)]";

  istringstream issa(galeriaInStringa.c_str());
  ostringstream ossa;

  GaleriaImagenes ga;
  ga.cargar(issa);

  istringstream ihss("2 2 [(1;2;3),(123;121;31),(2;1;231),(167;161;173)]");

  Imagen nueva(0,0);
  nueva.cargar(ihss);

  ga.agregarImagen(nueva);
  ga.guardar(ossa);
  assert (ossa.str() == galeriaOutStringa);

  //mantiene la galeria porque la imagen y existia

  string galeriaInStringb  =
            "[(1 1 [(2;2;2)],2),(1 1 [(3;3;3)],3),(1 1 [(1;1;1)],5)]";
  string galeriaOutStringb =
            "[(1 1 [(2;2;2)],2),(1 1 [(3;3;3)],3),(1 1 [(1;1;1)],5)]";
  istringstream issb(galeriaInStringb.c_str());
  ostringstream ossb;


  GaleriaImagenes gb;
  gb.cargar(issb);

  istringstream inss("1 1 [(2;2;2)]");

  Imagen usada(0,0);
  usada.cargar(inss);

  gb.agregarImagen(usada);
  gb.guardar(ossb);
  assert (ossb.str() == galeriaOutStringb);

  //galeria vacia

  string galeriaInStringc  = "";
  string galeriaOutStringc = "[(1 1 [(2;2;2)],0)]";
  istringstream issc(galeriaInStringc.c_str());
  ostringstream ossc;


  GaleriaImagenes gc;
  gc.cargar(issc);

  istringstream ijss("1 1 [(2;2;2)]");

  Imagen rara(0,0);
  rara.cargar(ijss);

  gc.agregarImagen(rara);
  gc.guardar(ossc);
  assert (ossc.str() == galeriaOutStringc);

  // la más chiquita con punto blanco

  // una imagen con punto blanco
  Imagen laMasChiquita(0,0);
  galeriaInString = "[(1 1 [(0;0;0)],0),(1 1 [(255;255;255)],0)]";
  galeriaOutString = "1 1 [(255;255;255)]";
  iss.clear();
  iss.str(galeriaInString.c_str());

  g.cargar(iss);

  laMasChiquita = g.laMasChiquitaConPuntoBlanco();

  oss.str("");
  oss.clear();
  laMasChiquita.guardar(oss);
  assert (oss.str() == galeriaOutString);

  // dos imagenes con punto blanco
  galeriaInString =
        "[(1 2 [(255;255;255),(0;0;0)],0),(1 1 [(0;0;0)],0),"
        "(3 1 [(255;255;255),(0;0;0),(255;255;255)],0)]";

  galeriaOutString = "1 2 [(255;255;255),(0;0;0)]";
  iss.clear();
  iss.str(galeriaInString.c_str());

  g.cargar(iss);

  laMasChiquita = g.laMasChiquitaConPuntoBlanco();

  oss.str("");
  oss.clear();
  laMasChiquita.guardar(oss);
  assert (oss.str() == galeriaOutString);



  //votar imagen
  g.votar(laMasChiquita);
  oss.str("");
  oss.clear();
  g.guardar(oss);
  assert (oss.str() ==
    "[(1 1 [(0;0;0)],0),(3 1 [(255;255;255),(0;0;0),(255;255;255)],0),"
    "(1 2 [(255;255;255),(0;0;0)],1)]");

  //dividir y agregar
  {
    istringstream giss(
                "[(2 2 [(11;11;11),(22;22;22),(33;33;33),(44;44;44)],0)]");
                
    istringstream iiss("2 2 [(11;11;11),(22;22;22),(33;33;33),(44;44;44)]");
    ostringstream oss;
    GaleriaImagenes g;
    Imagen im(0,0);

    g.cargar(giss);
    im.cargar(iiss);

    g.dividirYAgregar(im, 2, 2);

    g.guardar(oss);

    assert (oss.str() ==
        "[(2 2 [(11;11;11),(22;22;22),(33;33;33),(44;44;44)],0),"
        "(1 1 [(11;11;11)],0),(1 1 [(22;22;22)],0),(1 1 [(33;33;33)],0),"
        "(1 1 [(44;44;44)],0)]");
  }
}
