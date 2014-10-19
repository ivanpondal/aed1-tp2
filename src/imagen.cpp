
#include "imagen.h"
#include "pixel.h"
bool enRango(int min, int max, int v);

#include <vector>

Imagen::Imagen(int alto_param, int ancho_param) {
  if (alto_param > 0 && ancho_param > 0) {

    for (int y=0; y<alto_param; y++) {
      Pixel1DContainer fila;
      for (int x=0; x<ancho_param; x++) {
        Pixel p;
        fila.push_back(p);
      }
      pixels.push_back(fila);
    }

  }
}

Pixel Imagen::obtenerPixel(int fila, int columna) const {
  if (enRango(0, this->alto()  - 1, fila) &&
      enRango(0, this->ancho() - 1, columna)) {

        Pixel p = pixels.at(fila).at(columna);
        return p;

  }
}
void Imagen::modificarPixel(int fila, int columna, const Pixel &pixel) {
  if (enRango(0, this->alto()  - 1, fila) &&
      enRango(0, this->ancho() - 1, columna)) {

        pixels.at(fila).at(columna).cambiarPixel(
          pixel.red(), pixel.green(), pixel.blue()
        );
  }
}

int Imagen::alto() const {
  return pixels.size();
}

int Imagen::ancho() const {
  return pixels.at(0).size();
}

// vector<pair<int, int> > Imagen::posicionesMasOscuras() const;
// void Imagen::blur(int k);
// void Imagen::acuarela(int k);
//
// bool Imagen::operator==(const Imagen &otra) const;
//
// void Imagen::guardar(std::ostream& os) const;
// void Imagen::cargar (std::istream& is);
