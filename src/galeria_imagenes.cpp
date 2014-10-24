#include "imagen.h"
#include "galeria_imagenes.h"
#include <vector>

void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m) {
//TODO
}

Imagen GaleriaImagenes::laMasChiquitaConPuntoBlanco() const {
//TODO
}

void GaleriaImagenes::agregarImagen(const Imagen &imagen) {
//TODO
}

void GaleriaImagenes::votar(const Imagen &imagen) {
//TODO
}

void GaleriaImagenes::eliminarMasVotada() {
  imagenes.pop_back();
  votos.pop_back();
}

vector <Imagen> GaleriaImagenes::top10() const {
//TODO
}

void GaleriaImagenes::guardar (std::ostream& os) const {

  int i = 0;
  os << '[';

  while(i < this->imagenes.size()) {

      if (i>0) {
        os << ',';
      }

      os << '(';
      this->imagenes[i].guardar(os);
      os << ',';
      os << this->votos[i];
      os << ')';
      i++;
  }

  os << ']';

}

void GaleriaImagenes::cargar (std::istream& is) {

  int kx, ky, kt;
  Imagen img(0, 0);
  int vts;
  char c;

  this->imagenes.clear();
  this->votos.clear();

  while(is >> c) { // [,]
    if (is >> c) { // (

      img.cargar(is);
      is >> c; // ,
      is >> vts;
      is >> c; // )
      this->imagenes.push_back(img);
      this->votos.push_back(vts);
    }
  }
  this->acomodar();
}

void GaleriaImagenes::acomodar() {
  Imagen ai(0,0);
  int    av;

  int i, j;
  for(i=0; i<this->votos.size(); i++) {
    for(j=0; j<this->votos.size(); j++){
      if (this->votos[i] < this->votos[j]) {
        ai = this->imagenes[i];
        av = this->votos[i];

        this->imagenes[i] = this->imagenes[j];
        this->votos[i] = this->votos[j];

        this->imagenes[j] = ai;
        this->votos[j] = av;
      }
    }
  }
}
