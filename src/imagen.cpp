
#include "imagen.h"
#include "pixel.h"

#include <vector>

Imagen::Imagen(int alto_param, int ancho_param) {

    for (int y=0; y<alto_param; y++) {
      Pixel1DContainer fila;
      for (int x=0; x<ancho_param; x++) {
        Pixel p;
        fila.push_back(p);
      }
      pixels.push_back(fila);
    }

}

Pixel Imagen::obtenerPixel(int fila, int columna) const {
    return pixels.at(fila).at(columna);
}

void Imagen::modificarPixel(int fila, int columna, const Pixel &pixel) {
    pixels.at(fila).at(columna).cambiarPixel(
      pixel.red(), pixel.green(), pixel.blue()
    );
}

int Imagen::alto() const {
  return pixels.size();
}

int Imagen::ancho() const {
  return pixels.at(0).size();
}

//auxiliares para posicionesMasOscuras
int Imagen::sumaCanales(Pixel pixel) const {
	return pixel.red() + pixel.green() + pixel.blue();
}

Pixel Imagen::pixelMasOscuro() const {
	int x=0; int y=0; Pixel pixelMasOscuro = this->obtenerPixel(0,0);
  Pixel p;

  x=0;
	while (x < this->alto()){

    y=0;
		while (y < this->ancho()){
      p = this->obtenerPixel(x, y);
			if (sumaCanales(pixelMasOscuro) > sumaCanales(p)){
				pixelMasOscuro=p;
			}
			y++;
		}
		x++;
	}
	return pixelMasOscuro;
}

vector<pair<int, int> > Imagen::posicionesMasOscuras() const {
  vector<pair<int, int> > pixelesOscuros; int x=0; int y=0;
  int colorMasOscuro = sumaCanales(this->pixelMasOscuro());
  Pixel p;
  x=0;
  while(x<alto()){
      y=0;
    	while(y<ancho()){
        p = pixels[y][x];
    		if(sumaCanales(p)==colorMasOscuro) {
    			pixelesOscuros.push_back(pair<int, int>(x,y));
    		}
    		y++;
    	}
    	x++;
  }
  return pixelesOscuros;
}

// void Imagen::blur(int k);
// void Imagen::acuarela(int k);
//
// bool Imagen::operator==(const Imagen &otra) const;

void Imagen::guardar(std::ostream& os) const {

  os << this->alto() << ' ' << this->ancho() << ' ';

  os << '[';

  for (int y=0; y<this->alto(); y++) {
      for (int x=0; x<this->ancho(); x++) {

          if ( !(y == 0 && x == 0) )  {
              os << ',';
          }

          pixels[y][x].guardar(os);

      }
  }

  os << ']';
}

void Imagen::cargar (std::istream& is) {
    int alto, ancho;
    char c;

    pixels.clear();

    is >> alto >> ancho;

    is >> c; // [

    for (int y=0; y<alto; y++) {
      Pixel1DContainer fila;
      for (int x=0; x<ancho; x++) {
        Pixel p;
        p.cargar(is);
        fila.push_back(p);
        is >> c; // ] o ,
      }
      pixels.push_back(fila);
    }

}
