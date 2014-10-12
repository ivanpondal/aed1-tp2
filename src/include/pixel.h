#ifndef PIXEL_H
#define PIXEL_H

#include <string>
#include <iostream>

using namespace std;

class Pixel {
 public:
  Pixel(int red, int green, int blue);
  Pixel();
  void cambiarPixel(int red, int green, int blue);
  int red() const;
  int green() const;
  int blue() const;
  bool operator==(const Pixel &otro) const;

  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);
 private:
  int intensidades[3];
};

#endif  // PIXEL_H
