#ifndef IMAGEN_H
#define IMAGEN_H

#define BLUR 0
#define ACUARELA 1

#include "pixel.h"

#include <vector>

typedef std::vector<Pixel> Pixel1DContainer;
typedef std::vector<Pixel1DContainer> Pixel2DContainer;


class Imagen {
 public:
  Imagen(int alto_param, int ancho_param);
  Pixel obtenerPixel(int fila, int columna) const;
  void modificarPixel(int fila, int columna, const Pixel &pixel);
  int alto() const;
  int ancho() const;
  vector<pair<int, int> > posicionesMasOscuras() const;
  void blur(int k);
  void acuarela(int k);

  bool operator==(const Imagen &otra) const;

  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);

 private:
  Pixel2DContainer pixels;
  int sumaCanales(int x, int y) const;
  int colorMasOscuro() const;
  int maxPos(const int a[], int desde, int hasta) const;
  void upSort(int a[], int n) const;
  bool kVecinosCompletos(int k, int x, int y) const;
  void aplicarFiltro(int filtro, int k);
  Pixel pixelPromedioKVecinos(int k, int x, int y) const;
  Pixel pixelMedianaKVecinos(int k, int x, int y) const;
};

#endif  // IMAGEN_H
