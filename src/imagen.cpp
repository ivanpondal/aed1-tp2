
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
      this->pixels.push_back(fila);
    }

}

Pixel Imagen::obtenerPixel(int fila, int columna) const {
    return this->pixels.at(fila).at(columna);
}

void Imagen::modificarPixel(int fila, int columna, const Pixel &pixel) {
    this->pixels.at(fila).at(columna).cambiarPixel(
      pixel.red(), pixel.green(), pixel.blue()
    );
}

int Imagen::alto() const {
  return this->pixels.size();
}

int Imagen::ancho() const {
  return this->pixels.at(0).size();
}

//auxiliares para posicionesMasOscuras
int Imagen::sumaCanales(int x, int y) const {
    Pixel p = this->pixels[y][x];
	return p.red() + p.green() + p.blue();
}

int Imagen::colorMasOscuro() const {
	int x=0; int y=0; 
	int colorMasOscuro = this->sumaCanales(0,0);

	while (x < this->alto()){
    y=0;
		while (y < this->ancho()){
			if (colorMasOscuro > this->sumaCanales(x,y)){
				colorMasOscuro = this->sumaCanales(x,y);
			}
			y++;
		}
		x++;
	}
	return colorMasOscuro;
}

vector<pair<int, int> > Imagen::posicionesMasOscuras() const {
  vector<pair<int, int> > pixelesOscuros;
  int x=0; int y=0;
  int colorMasOscuro = this->colorMasOscuro();

  while(x < this->alto()){
      y=0;
    	while(y < this->ancho()){
    		if(this->sumaCanales(x,y) == colorMasOscuro) {
    			pixelesOscuros.push_back(pair<int, int>(x,y));
    		}
    		y++;
    	}
    	x++;
  }
  return pixelesOscuros;
}

// auxiliares para blur

bool Imagen::kVecinosCompletos(int k, int x, int y) const {
	return (x-k+1)>=0 && (x+k-1)<this->ancho() && (y-k+1)>=0 && (y+k-1)<this->alto();
}

Pixel1DContainer Imagen::kVecinos(int k, int x, int y) const {
	Pixel1DContainer kVecinos;
	int xi=x-k+1;
	int yi=y-k+1;
	
	while(yi < y+k){
		while(xi < x+k){
			kVecinos.push_back(this->obtenerPixel(yi,xi));
			xi++;
		}
		xi=x-k+1;
		yi++;
	}
	return kVecinos;
}

Pixel Imagen::pixelPromedioKVecinos(Pixel1DContainer kVecinos) const {
	int r=0; int g=0; int b=0;int i=0;
	int totalKVecinos=kVecinos.size();
	
	Pixel pixelPromedio;
	
	while(i < totalKVecinos){
		r += kVecinos.at(i).red();
		g += kVecinos.at(i).green();
		b += kVecinos.at(i).blue();
		i++;
	}
	
	r /= totalKVecinos;
	g /= totalKVecinos;
	b /= totalKVecinos;
	
	pixelPromedio.cambiarPixel(r,g,b);
	
	return pixelPromedio;
}

void Imagen::blur(int k){
	Pixel2DContainer pixelsBlur;
	int x=0; int y=0;
	Pixel pixelNegro(0,0,0);
	
	while (y < this->alto()){
		Pixel1DContainer fila;
		while(x < this->ancho()){
			if(this->kVecinosCompletos(k,x,y)){
				fila.push_back(pixelPromedioKVecinos(this->kVecinos(k,x,y)));
			}
			else{
				fila.push_back(pixelNegro);
			}
			x++;
		}
		pixelsBlur.push_back(fila);
		x=0;
		y++;
	}

	this->pixels.clear();
	this->pixels = pixelsBlur;

}

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

          this->pixels[y][x].guardar(os);

      }
  }

  os << ']';
}

void Imagen::cargar (std::istream& is) {
    int alto, ancho;
    char c;

    this->pixels.clear();

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
      this->pixels.push_back(fila);
    }

}
