
#include "imagen.h"
#include "pixel.h"

#include <algorithm>
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

// auxiliares para blur y acuarela

bool Imagen::kVecinosCompletos(int k, int x, int y) const {
	return (x-k+1)>=0 && (x+k-1)<this->ancho() && (y-k+1)>=0 && (y+k-1)<this->alto();
}

Pixel1DContainer Imagen::kVecinos(int k, int x, int y) const {
  Pixel1DContainer kv;

  int yi, xi;
  for(yi = y-k+1; yi < y+k; yi++){
  for(xi = x-k+1; xi < x+k; xi++){
      kv.push_back(this->obtenerPixel(yi, xi));

  }}

  return kv;
}

Pixel Imagen::pixelPromedioKVecinos(int k, int x, int y) const {
	int r=0; int g=0; int b=0;
	int i;

  Pixel1DContainer kv = this->kVecinos(k, x, y);

  for(i=0; i<kv.size(); i++) {
      Pixel p = kv[i];
      r += p.red();
      g += p.green();
      b += p.blue();
  }

	r /= kv.size();
	g /= kv.size();
	b /= kv.size();

	return Pixel(r, g, b);
}

void Imagen::blur(int k) {
	Pixel2DContainer pixelsBlur;
	int x=0; int y=0;

  for(y = 0; y < this->alto(); y++) {
    Pixel1DContainer fila;

    for(x = 0; x < this->ancho(); x++) {
        Pixel p;
        if(this->kVecinosCompletos(k,x,y)){
            p = this->pixelPromedioKVecinos(k,x,y);
        }

        fila.push_back(p);
    }

    pixelsBlur.push_back(fila);
  }

	this->pixels = pixelsBlur;

}

Pixel Imagen::pixelMedianaKVecinos(int k, int x, int y) const {
  vector<int> red, green, blue;
  int i;

  Pixel1DContainer kv = this->kVecinos(k, x, y);

  for(i=0; i<kv.size(); i++) {
      Pixel p = kv[i];
        red.push_back( p.red()   );
      green.push_back( p.green() );
       blue.push_back( p.blue()  );
  }

	sort(  red.begin(),   red.end());
	sort(green.begin(), green.end());
	sort( blue.begin(),  blue.end());

  int pos = (kv.size()/2);

	return Pixel(red[pos], green[pos], blue[pos]);
}

void Imagen::acuarela(int k) {
  Pixel2DContainer pixelsAcuarela;
  int x=0; int y=0;

  for(y = 0; y < this->alto(); y++) {
    Pixel1DContainer fila;

    for(x = 0; x < this->ancho(); x++) {
        Pixel p;
        if(this->kVecinosCompletos(k,x,y)){
            p = this->pixelMedianaKVecinos(k,x,y);
        }

        fila.push_back(p);
    }

    pixelsAcuarela.push_back(fila);
  }

  this->pixels = pixelsAcuarela;

}

bool Imagen::operator==(const Imagen &otra) const{
	bool equals=true;
	if(this->ancho() == otra.ancho() && this->alto()== otra.alto()){
		int x=0; int y=0;
		while (y < this->alto() && equals){
			while(x < this->ancho() && equals){
				if(this->pixels[y][x] != otra.obtenerPixel(y,x)){
					equals=false;
				}
				x++;
			}
			x=0;
			y++;
		}
	}
	else{
		equals=false;
	}
	return equals;
}

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
