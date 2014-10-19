#include "pixel.h"

Pixel::Pixel(int red, int green, int blue) {
  this->cambiarPixel(red, green, blue);
}

Pixel::Pixel () {
  this->cambiarPixel(0,0,0);
}

void Pixel::cambiarPixel(int red, int green, int blue) {
  red   = max(0, min(red, 255));
  green = max(0, min(green, 255));
  blue  = max(0, min(blue, 255));

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
            (intensidades[0] == p.intensidades[0]) &&
            (intensidades[1] == p.intensidades[1]) &&
            (intensidades[2] == p.intensidades[2])
          );
}

bool Pixel::operator!=(const Pixel &p) const {
   return (
            (intensidades[0] != p.intensidades[0]) ||
            (intensidades[1] != p.intensidades[1]) ||
            (intensidades[2] != p.intensidades[2])
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
  bool valido;

  valido = true;

  is >> c;
  if (c != '(') valido = false;
  is >> r;
  is >> c;
  if (c != ';') valido = false;
  is >> g;
  is >> c;
  if (c != ';') valido = false;
  is >> b;
  is >> c;
  if (c != ')') valido = false;

  if (valido) this->cambiarPixel(r,g,b);
}
