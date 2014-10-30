
#include "imagen.h"
#include "pixel.h"

#include <algorithm>
#include <vector>

//TODO ordenar esto como estaba el .h original
//TODO unificar el uso de this-> (ponerlo siempre)
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
	while (x < this->ancho()){
    y=0;
		while (y < this->alto()){
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
  while(x < this->ancho()){
      y=0;
    	while(y < this->alto()){
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

int Imagen::maxPos(const int a[], int desde, int hasta) const{
	int maxPos = desde;
	int i = desde + 1;
	while (i <= hasta) {
		if (a[i] > a[maxPos]) maxPos = i;
		i++;
	}
	return maxPos;
}

void Imagen::upSort(int a[], int n) const{
	int pos; int valorActual; int actual = n - 1;
	while (actual > 0) {
		pos = maxPos(a ,0 ,actual);
		valorActual = a[actual];
		a[actual] = a[pos];
		a[pos] = valorActual;
		actual--;
	}
}

bool Imagen::kVecinosCompletos(int k, int x, int y) const {
	return (x-k+1)>=0 && (x+k-1)<this->ancho() && (y-k+1)>=0 && (y+k-1)<this->alto();
}

void Imagen::aplicarFiltro(int filtro, int k) {
	Pixel2DContainer pixelsFiltro;
	int x=0; int y=0;
	Pixel pixel(0,0,0);

	while (y < this->alto()){
		Pixel1DContainer fila;
		while(x < this->ancho()){
			if(this->kVecinosCompletos(k,x,y)){
				switch(filtro){
					case BLUR:
						pixel = this->pixelPromedioKVecinos(k,x,y);
						break;
					case ACUARELA:
						pixel = this->pixelMedianaKVecinos(k,x,y);
						break;
				}
			}
			fila.push_back(pixel);
			pixel.cambiarPixel(0,0,0);
			x++;
		}
		pixelsFiltro.push_back(fila);
		x=0;
		y++;
	}

	this->pixels.clear();
	this->pixels = pixelsFiltro;
}

Pixel Imagen::pixelPromedioKVecinos(int k, int x, int y) const {
	int r=0; int g=0; int b=0;
	int totalKVecinos=(2*k-1)*(2*k-1);
	int xi=x-k+1;
	int yi=y-k+1;

	Pixel pixelPromedio;

	while(yi < y+k){
		Pixel p;
		while(xi < x+k){
			p = this->obtenerPixel(yi,xi);
			r += p.red();
			g += p.green();
			b += p.blue();
			xi++;
		}
		xi=x-k+1;
		yi++;
	}

	r /= totalKVecinos;
	g /= totalKVecinos;
	b /= totalKVecinos;

	pixelPromedio.cambiarPixel(r,g,b);

	return pixelPromedio;
}

Pixel Imagen::pixelMedianaKVecinos(int k, int x, int y) const {
  int xi = x-k+1;
  int yi = y-k+1;
  int sizeKVecinos = (2*k-1)*(2*k-1);
  int middleKVecinos = sizeKVecinos/2;
  int* red = new int[sizeKVecinos];
  int* green = new int[sizeKVecinos];
  int* blue = new int[sizeKVecinos];
  int i = 0;

  Pixel pixelMediana;

  while(yi < y+k){
    Pixel p;
    while(xi < x+k){
      p = this->obtenerPixel(yi,xi);
      red[i] = p.red();
      green[i] = p.green();
      blue[i] = p.blue();

      i++;
      xi++;
    }
    xi=x-k+1;
    yi++;
  }

  upSort(red, sizeKVecinos);
  upSort(green, sizeKVecinos);
  upSort(blue, sizeKVecinos);

  pixelMediana.cambiarPixel(red[middleKVecinos], green[middleKVecinos], blue[middleKVecinos]);
  return pixelMediana;
}

void Imagen::blur(int k){
	this->aplicarFiltro(BLUR, k);
}

void Imagen::acuarela(int k){
	this->aplicarFiltro(ACUARELA, k);
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
