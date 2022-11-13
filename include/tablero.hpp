#pragma once
#include <math.h>
#include <unistd.h>

#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#include "celda.hpp"
using namespace std;

class Tablero {
 private:
  int filas_;
  int columnas_;
  vector<vector<Celda *>> nodos_{};
  Celda *nodoInicial_ = nullptr;
  Celda *nodoFinal_ = nullptr;

 public:
  Tablero();
  Tablero(int fil, int col);
  ~Tablero();
  void establecerConexiones(int i, int j, Celda *nodoactual);
  void setNodoInicial(int i, int j);
  void setNodoFinal(int i, int j);
  void algoritmoAEstrella(int heuristica);
  void algoritmoPrimero(int heuristica);
  float heuristicaManhattan(Celda *a, Celda *b);
  float heuristicaEuclides(Celda *a, Celda *b);
  friend std::ostream &operator<<(std::ostream &os, const Tablero &Tablero);
  vector<Celda *> &operator[](int x) { return nodos_[x]; }
  int explorado_ = 0;
  int optimo_ = 0;
  clock_t tiempo_;

  void salida();
  bool tt = false;
  int col() { return columnas_; }
  int fil() { return filas_; }
};

std::ostream &operator<<(std::ostream &os, Tablero &Tablero);