#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void testPixel();
void testImagen();

int main()
{
    testPixel();
    testImagen();
    cout << "Tests OK" << endl;
}

void testPixel() {

  // constructor con argumentos
  Pixel pc1 (4, 4, 4);
  assert (pc1.red()    == 4);
  assert (pc1.green()  == 4);
  assert (pc1.blue()   == 4);

  // constructor con argumentos fuera de rango deja en 0
  Pixel pcfr (4, 4, 46666);
  assert (pcfr.red()    == 0);
  assert (pcfr.green()  == 0);
  assert (pcfr.blue()   == 0);

  // constructor simple
  Pixel pc2;
  assert (pc2.red()    == 0);
  assert (pc2.green()  == 0);
  assert (pc2.blue()   == 0);

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

  // cambiarPixel fuera de rango no hace nada
  int prer, preg, preb;
  prer = p1.red();
  preg = p1.green();
  preb = p1.blue();
  p1.cambiarPixel(500,-100, 40);
  assert (p1.red()    == prer);
  assert (p1.green()  == preg);
  assert (p1.blue()   == preb);

  // constructor con argumentos fuera de rango deja en 0
  Pixel tonto(-4, 600, 503404);
  assert (tonto.red()    == 0);
  assert (tonto.green()  == 0);
  assert (tonto.blue()   == 0);

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

  //cargar fuera de rango no hace nada
  Pixel c2;
  istringstream iss2 ("(60;50;600)");
  c2.cargar(iss2);
  assert (c2.red()    == 0);
  assert (c2.green()  == 0);
  assert (c2.blue()   == 0);
}

void testImagen() {
  // constructor, alto, ancho, todanegra
  Pixel negro;
  Pixel rojo(255, 0, 0);
  Pixel p;
  Imagen i1 (20, 30);
  assert(i1.alto() == 20);
  assert(i1.ancho() == 30);
  for (int y=0; y < i1.alto(); y++) {
    for (int x=0; x < i1.ancho(); x++) {
        assert(i1.obtenerPixel(y, x) == negro);
    }
  }
  assert(i1.obtenerPixel(2,3) == negro);
  i1.modificarPixel(2,3, rojo);
  assert(i1.obtenerPixel(2,3) == rojo);

}
