#include "imagen.h"
#include "galeria_imagenes.h"
#include <vector>
//TODO ordenar esto como estaba el .h original

void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m) {
  int d, i, j, x, y, k, an, al;
  vector<Imagen> divisiones;

  if ( this->existeImagen(imagen)
    && (n > 0)
    && (m > 0)
    && (n % imagen.ancho() == 0)
    && (m % imagen.alto() == 0)
  ) {

    k = n*m;
    an = imagen.ancho() / n;
    al = imagen.alto() / m;

    for(d=0; d<k; d++) {
      divisiones.push_back(Imagen(an, al));
    }

    for(x=0; x<n; x++) {
      for(y=0; y<m; y++) {
        d = x*m + y;

        for (j=0; j<an; j++) {
          for (i=0; i<al; i++) {
            Pixel p = imagen.obtenerPixel(x*an + j, y*al + i);
            divisiones[d].modificarPixel(j, i, p);
          }
        }

      }
    }

    for(d=0; d<k; d++) {
      this->agregarImagen(divisiones[d]);
    }

  }
}

Imagen GaleriaImagenes::laMasChiquitaConPuntoBlanco() const {
  int x; int y;
  int an; int al;
  int area;
  bool imgTieneBlanco = false;

  int minArea = -1;
  Pixel pixelBlanco (255, 255, 255);
  Imagen laMasChiquitaConPuntoBlanco (0, 0);
  Imagen img (0, 0);

  // recorro todas las imágenes buscando si tienen al menos un punto blanco
  for(int i=0; i < this->imagenes.size(); i++) {
    img = this->imagenes[i];
    imgTieneBlanco = false;

    an = img.ancho();
    al = img.alto();
    area = an * al;

    y = 0;
    while(y < al && !imgTieneBlanco) {
      x=0;
      while(x < an && !imgTieneBlanco) {

        // en el caso de que tengan punto blanco me fijo si es más chica la imagen que la anterior que tuviese
        if(img.obtenerPixel(y, x) == pixelBlanco) {
          imgTieneBlanco = true;
          // si todavia no habia guardado ninguna con punto blanco o el area que tengo es mas grande que esta, la guardo
          if ((minArea == -1) || (minArea > area)) {
              minArea = area;
              laMasChiquitaConPuntoBlanco = img;
          }
        }

        x++;
      }

      y++;
    }

  }

  return laMasChiquitaConPuntoBlanco;
}

bool GaleriaImagenes::existeImagen(const Imagen &imagen) {
  int i=0;
  bool res=false;
  while(i<this->imagenes.size() && res==false){
    if(imagen == this->imagenes[i]){
      res=true;
    }
    i++;
  }
  return res;
}

void GaleriaImagenes::agregarImagen(const Imagen &imagen) {

  if(!this->existeImagen(imagen)){
    this->imagenes.push_back(imagen);
    this->votos.push_back(0);
    this->acomodar();
  }
}

void GaleriaImagenes::votar(const Imagen &imagen) {
  int posImg;
  int k=0;
  while(k<this->imagenes.size()){
    if(this->imagenes[k]==imagen){
      posImg=k;
    }
    k++;
  }
  this->votos[posImg]++;
  this->acomodar();
}

void GaleriaImagenes::eliminarMasVotada() {
  this->imagenes.pop_back();
  this->votos.pop_back();
}

vector <Imagen> GaleriaImagenes::top10() const {
    int k = this->imagenes.size() - 1;
    int i;
    vector <Imagen> res;

    i = k;
    while ((i > k-10) && (i >= 0)) {
        res.push_back(this->imagenes[i]);
        i--;
    }

    return res;
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
    for(j=i+1; j<this->votos.size(); j++){

      if (this->votos[i] > this->votos[j]) {
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
