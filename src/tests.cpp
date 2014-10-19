#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void testPixel();

int main()
{
    testPixel();

    cout << "Tests OK" << endl;
}

void testPixel() {

  // constructor con argumentos
  Pixel pc1 (4,4,4);
  assert (pc1.red()    == 4);
  assert (pc1.green()  == 4);
  assert (pc1.blue()   == 4);

  // constructor simple
  Pixel pc2;
  assert (pc2.red()    == 0);
  assert (pc2.green()  == 0);
  assert (pc2.blue()   == 0);

  // igualdad
  Pixel p1, p2;
  assert (p1 == p2);

  // cambiarPixel
  p1.cambiarPixel(1, 0, 0);
  assert (p1.red()    == 1);
  assert (p1.green()  == 0);
  assert (p1.blue()   == 0);

  // desigualdad
  assert (p1 != p2);

  // cambiarPixel fuera de rango
  p1.cambiarPixel(500,-100, 40);
  assert (p1.red()    == 255);
  assert (p1.green()  == 0);
  assert (p1.blue()   == 40);

  // constructor con argumentos fuera de rango
  Pixel tonto(-4, 600, 503404);
  assert (tonto.red()    == 0);
  assert (tonto.green()  == 255);
  assert (tonto.blue()   == 255);

  //guardar
  Pixel g(10,500,3);
  ostringstream oss;
  g.guardar(oss);
  assert (oss.str() == "(10;255;3)");

  //cargar
  Pixel c;
  istringstream iss ("(60;50;40)");
  c.cargar(iss);
  assert (c.red() == 60);
  assert (c.green() == 50);
  assert (c.blue() == 40);
}
