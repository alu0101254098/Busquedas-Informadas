#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Celda {
 private:
  int posX_;           // Posición en el eje x
  int posY_;           // Posición en el eje y
  bool celdaInicial_;  // Booleano para saber si es la celda inicial
  bool celdaFinal_;    // Booleano para saber si es la celda final
  bool visitada_;      // Booleano para saber si es una celda visitada o no
  bool lista_;         // Booleano para saber si pertenece a la lista abierta
  bool caminoOptimo_;  // Booleano para saber si es camino óptimo
  bool obstaculo_;     // Booleano para saber si es un obstáculo o no
  Celda *padre_;       // Contendrá la celda predecesora
  std::vector<Celda *>
      celdasVecinas_;  // Contendrá todas las celdas vecinas del nodo
  float costeGlobal_;  // Coste global
  float costeLocal_;   // Coste local

 public:
  Celda();
  Celda(int i, int j);
  ~Celda(){};
  void setPosX(int i);
  int getPosX();
  void setPosY(int j);
  int getPosY();
  void setCeldaInicial(bool inicial);
  bool &getCeldaInicial(void);
  void setCeldaFinal(bool final);
  bool &getCeldaFinal(void);
  void setVisitada(bool visitado);
  bool getVisitada(void);
  void setObstaculo(bool obstaculo);
  bool getObstaculo(void);
  void setLista(bool lista);
  bool getLista(void);
  void setCaminoOptimo(bool camino);
  void setPadre(Celda *padre);
  Celda *&getPadre(void);
  void setCeldasVecinas(Celda *vecinos);
  std::vector<Celda *> &getCeldasVecinas(void);
  void setCosteGlobal(float global);
  float getCosteGlobal(void);
  float getCosteGlobal(void) const;
  void setCosteLocal(float local);
  float getCosteLocal(void);
  std::ostream &imprimir(std::ostream &os);
  std::ostream &imprimir2(std::ostream &os);

  bool EsParteDelCAmino() { return caminoOptimo_; }
};