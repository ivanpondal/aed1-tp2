#ifndef GALERIA_IMAGENES_H
#define GALERIA_IMAGENES_H

#include "imagen.h"

#include <vector>

class GaleriaImagenes {
 public:
  void dividirYAgregar(const Imagen &imagen, int n, int m);	
  Imagen laMasChiquitaConPuntoBlanco() const;
  void agregarImagen(const Imagen &imagen);
  void votar(const Imagen &imagen);
  void eliminarMasVotada();
  vector <Imagen> top10() const;
  
  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);
 private:
  std::vector<Imagen> imagenes;
  std::vector<int> votos;
};

#endif  // GALERIA_IMAGENES_H

