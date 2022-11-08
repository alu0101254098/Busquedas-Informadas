#include "../include/celda.hpp"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Constructor de Celda, iniciamos valores por defecto
Celda::Celda() {
  posX_ = 0;  // Fila 0
  posY_ = 0;  // Columna 0
  obstaculo_ = false;
  visitada_ = false;
  costeGlobal_ = INFINITY;
  costeLocal_ = INFINITY;
  celdaFinal_ = false;
  celdaInicial_ = false;
  caminoOptimo_ = false;
  padre_ = nullptr;
  celdasVecinas_.clear();
}

// Constructor parametrizado
Celda::Celda(int i, int j) {
  posX_ = i;
  posY_ = j;
  visitada_ = false;
  obstaculo_ = false;
  costeGlobal_ = INFINITY;
  costeLocal_ = INFINITY;
  celdaFinal_ = false;
  celdaInicial_ = false;
  caminoOptimo_ = false;
  padre_ = nullptr;
  celdasVecinas_.clear();
}

void Celda::setPosX(int i) { posX_ = i; }

int Celda::getPosX() { return posX_; }

void Celda::setPosY(int j) { posY_ = j; }

int Celda::getPosY() { return posY_; }

void Celda::setCosteGlobal(float global) { costeGlobal_ = global; }

float Celda::getCosteGlobal(void) { return costeGlobal_; }

float Celda::getCosteGlobal(void) const { return costeGlobal_; }

void Celda::setCosteLocal(float local) { costeLocal_ = local; }

float Celda::getCosteLocal(void) { return costeLocal_; }

void Celda::setLista(bool lista) { lista_ = lista; }

bool Celda::getLista(void) { return lista_; }

void Celda::setVisitada(bool visitado) { visitada_ = visitado; }

bool Celda::getVisitada(void) { return visitada_; }

void Celda::setObstaculo(bool obstaculo){ obstaculo_ = obstaculo; }

bool Celda::getObstaculo(void){ return obstaculo_; }

void Celda::setPadre(Celda *padre) { padre_ = padre; }

Celda *&Celda::getPadre(void) { return padre_; }

void Celda::setCeldaInicial(bool inicial) { celdaInicial_ = inicial; }

bool &Celda::getCeldaInicial(void) { return celdaInicial_; }

void Celda::setCeldaFinal(bool final) { celdaFinal_ = final; }

bool &Celda::getCeldaFinal(void) { return celdaFinal_; }

void Celda::setCaminoOptimo(bool camino) { caminoOptimo_ = camino; }

void Celda::setCeldasVecinas(Celda *vecinos) {
  celdasVecinas_.push_back(vecinos);
}

std::vector<Celda *> &Celda::getCeldasVecinas(void) { return celdasVecinas_; }

// Método para imprimir los distintos tipos de celdas dentro del tablero
std::ostream &Celda::imprimir(std::ostream &os) {

  if (celdaInicial_ == true) { 
    os << "\033[1;102m \033[0m"; //Verde claro
  } else if (celdaFinal_ == true) {
    os << "\033[1;101m \033[0m"; //Rojo
  } else if ((visitada_ == false) && (caminoOptimo_ != true)) { 
    os << " "; //Negro
  } else if ((visitada_ == true) && (caminoOptimo_ != true)) {
    os << "\033[1;100m \033[0m"; //Gris oscuro
  } else if (caminoOptimo_ == true){
    os << "\033[1;103m \033[0m"; //Amarillo
  }
  return os;
}

std::ostream &Celda::imprimir2(std::ostream &os) {
  if (celdaInicial_ == true) {
    os << "I";
  } else if (celdaFinal_ == true) {
    os << "F";
  } else if ((caminoOptimo_ != true)) {
    os << "#";
  } else if ((visitada_ == true) && (caminoOptimo_ != true)) {
    os << "+";
  } else if ((visitada_ == false)  && (caminoOptimo_ != true)) {
    os << "-";
  } else if (caminoOptimo_ == true) {
    os << "*";
  }
  return os;
}
