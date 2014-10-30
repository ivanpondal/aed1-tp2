#include "pixel.h"

//TODO ordenar esto como estaba el .h original
//TODO unificar el uso de this-> (ponerlo siempre)

Pixel::Pixel(int red, int green, int blue) {
  this->cambiarPixel(red, green, blue);
}

Pixel::Pixel () {
  this->cambiarPixel(0, 0, 0);
}

void Pixel::cambiarPixel(int red, int green, int blue) {
    intensidades[0] = red;
    intensidades[1] = green;
    intensidades[2] = blue;
}

int Pixel::red() const {
  return intensidades[0];
}

int Pixel::green() const {
  return intensidades[1];
}

int Pixel::blue() const {
  return intensidades[2];
}

bool Pixel::operator==(const Pixel &p) const {
   return (
            (intensidades[0] == p.red()) &&
            (intensidades[1] == p.green()) &&
            (intensidades[2] == p.blue())
          );
}

bool Pixel::operator!=(const Pixel &p) const {
   return (
            (intensidades[0] != p.red()) ||
            (intensidades[1] != p.green()) ||
            (intensidades[2] != p.blue())
          );
}

void Pixel::guardar(std::ostream& os) const {
  os  << '('
      << intensidades[0]
      << ';'
      << intensidades[1]
      << ';'
      << intensidades[2]
      << ')';
}


void Pixel::cargar(std::istream& is) {
  char c;
  int r, g, b;

  is >> c; // (

  is >> r;

  is >> c; // ;

  is >> g;

  is >> c; // ;

  is >> b;

  is >> c; // )

  this->cambiarPixel(r,g,b);
}
