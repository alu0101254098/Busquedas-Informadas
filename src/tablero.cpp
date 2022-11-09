#include "../include/tablero.hpp"

#include <chrono>
#include <thread>
// Constructor de Tablero, iniciamos valores por defecto
Tablero::Tablero() {
  filas_ = 0;
  columnas_ = 0;
  nodos_ = vector<vector<Celda *>>((columnas_), vector<Celda *>(filas_));
  // nodos_ = new Celda[(filas_) * (columnas_)];
  for (int i = 0; i < filas_; i++) {
    for (int j = 0; j < columnas_; j++) {
      // A cada nodo le damos sus propias coordenadas
      nodos_[i][j]->setPosX(i);
      nodos_[i][j]->setPosY(j);
      nodos_[i][j]->setPadre(nullptr);
      nodos_[i][j]->setVisitada(false);
      nodos_[i][j]->setCeldaInicial(false);
      nodos_[i][j]->setCeldaFinal(false);
      nodos_[i][j]->setCaminoOptimo(false);
      nodoFinal_ = nullptr;
      nodoInicial_ = nullptr;
    }
  }
}

// Constructor de Tablero parametrizado
Tablero::Tablero(int fil, int col) {
  filas_ = fil;
  columnas_ = col;
  // nodos_ = new Celda[(filas_) * (columnas_)];
  nodos_ = vector<vector<Celda *>>(filas_, vector<Celda *>(columnas_));

  for (int i = 0; i < filas_; i++) {
    for (int j = 0; j < columnas_; j++) {
      nodos_[i][j] = new Celda{};
      // A cada nodo le damos sus propias coordenadas
      nodos_[i][j]->setPosX(i);
      nodos_[i][j]->setPosY(j);
      nodos_[i][j]->setPadre(nullptr);
      nodos_[i][j]->setVisitada(false);
      nodos_[i][j]->setCeldaInicial(false);
      nodos_[i][j]->setCeldaFinal(false);
      nodos_[i][j]->setCaminoOptimo(false);
      nodoFinal_ = nullptr;
      nodoInicial_ = nullptr;
    }
  }
}

// Funcion que muestra por la terminal el progreso del camino optimo
// en caso de ser mayor a 50x50 se mostrara el progreso en un fichero
// llamado salida.txt
void Tablero::salida() {
  vector<Celda *> coordenadas_optimas;
  for (int i = 0; i < filas_; i++) {
    for (int j = 0; j < columnas_; j++) {
      if (nodos_[i][j]->EsParteDelCAmino()) {
        coordenadas_optimas.emplace_back(nodos_[i][j]);
      }
    }
  }

  Tablero tablero_salida{filas_, columnas_};

  if (filas_ > 50 or columnas_ > 50) {
    ofstream fichero_salida;
    fichero_salida.open("salida.txt", fstream::out | std::fstream::trunc);
    tablero_salida.tt = true;

    for (size_t i = 0; i < coordenadas_optimas.size(); i++) {
      tablero_salida[coordenadas_optimas[i]->getPosX()]
                    [coordenadas_optimas[i]->getPosY()] =
                        coordenadas_optimas[i];
      this_thread::sleep_for(chrono::milliseconds(100));
      fichero_salida.open("salida.txt", fstream::out | std::fstream::trunc);
      fichero_salida << tablero_salida;
      fichero_salida.close();
    }
    fichero_salida.close();
  } else {
    for (size_t i = 0; i < coordenadas_optimas.size(); i++) {
      tablero_salida[coordenadas_optimas[i]->getPosX()]
                    [coordenadas_optimas[i]->getPosY()] =
                        coordenadas_optimas[i];
      sleep(1);
      system("clear");
      cout << tablero_salida;
    }
  }
}

// Destructor de Tablero
Tablero::~Tablero() {
  // delete[] nodos_;
}

// Método para convertir una celda libre a posición inicial
void Tablero::setNodoInicial(int i, int j) {
  nodoInicial_ = nodos_[i][j];
  nodos_[i][j]->setCeldaInicial(true);
}

// Método para convertir una celda libre a posición final
void Tablero::setNodoFinal(int i, int j) {
  nodoFinal_ = nodos_[i][j];
  nodos_[i][j]->setCeldaFinal(true);
}

// Método que nos permite asignar los vecinos más próximos disponibles de la
// celda en la que nos encontramos
void Tablero::establecerConexiones(int i, int j, Celda *nodoactual) {
  // NORTE
  if ((i > 0)) {
    nodoactual->setCeldasVecinas(nodos_[i - 1][j + 0]);
  }

  // SUR
  if ((i < filas_ - 1)) {
    nodoactual->setCeldasVecinas(nodos_[i + 1][j + 0]);
  }

  // OESTE
  if ((j > 0)) {
    nodoactual->setCeldasVecinas(nodos_[i + 0][j - 1]);
  }

  // ESTE
  if ((j < columnas_ - 1)) {
    nodoactual->setCeldasVecinas(nodos_[i + 0][j + 1]);
  }
}

// Método que calcula la estimación del coste mínimo para alcanzar el objetivo
// desde la Celda a, hasta la Celda b, mediante Manhattan
float Tablero::heuristicaManhattan(Celda *a, Celda *b) {
  return (abs((a->getPosX()) - (b->getPosX())) +
          abs((a->getPosY()) - (b->getPosY())));
}

// Método que calcula la estimación del coste mínimo para alcanzar el objetivo
// desde la Celda a, hasta la Celda b, mediante Euclidean
float Tablero::heuristicaEuclides(Celda *a, Celda *b) {
  return sqrtf(pow(((a->getPosX()) - (b->getPosX())), 2) +
               pow(((a->getPosY()) - (b->getPosY())), 2));
}

// Método que halla el camino óptimo usando el algoritmo A*, y una heurística,
// que puede ser Manhattan o Euclidean
void Tablero::algoritmoAEstrella(int heuristica) {
  // Empezamos desde el nodo elegido como inicial y asignamos el costo local a 0
  Celda *nodoactual = nodoInicial_;
  nodoactual->setCosteLocal(0.0);

  // Decidimos que heurística usar
  if (heuristica == 1)
    nodoactual->setCosteGlobal(heuristicaManhattan(nodoactual, nodoFinal_));

  if (heuristica == 2)
    nodoactual->setCosteGlobal(heuristicaEuclides(nodoactual, nodoFinal_));

  tiempo_ = clock();
  std::list<Celda *> lista;  // Creamos lista abierta

  // Insertamos en la lista abierta
  lista.push_back(nodoactual);
  nodoactual->setLista(true);

  while (!lista.empty()) {
    lista.sort([](const Celda *a, const Celda *b) {
      return a->getCosteGlobal() < b->getCosteGlobal();
    });  // Ordenamos de menor a mayor coste global la lista abierta

    nodoactual = lista.front();  // Cogemos el de menor coste

    if (nodoactual ==
        nodoFinal_) {  // Entrará cuando haya encontrado el camino óptimo
      tiempo_ = clock() - tiempo_;

      while (nodoactual != NULL) {
        nodoactual->setCaminoOptimo(true);  // Forma parte del camino óptimo
        optimo_++;
        nodoactual = nodoactual->getPadre();  // El nodoactual pasa a ocupar los
                                              // valores de su nodo padre
      }
      std::cout << "\033[1;93m¡Se ha encontrado una solución óptima!\033[0m"
                << std::endl;
      optimo_ = optimo_ - 1;
      return;
    }

    lista.pop_front();  // Lo eliminamos de la lista abierta ya que lo vamos a
                        // explorar
    nodoactual->setVisitada(true);  // Lo ponemos a visitado, que indica que
                                    // está en la lista cerrada
    nodoactual->setLista(
        false);  // Indicamos que no se encuentra en la lista abierta
    explorado_++;
    establecerConexiones(nodoactual->getPosX(), nodoactual->getPosY(),
                         nodoactual);  // Creamos conexiones del nodoactual

    for (int w = 0; w < nodoactual->getCeldasVecinas().size(); w++) {
      Celda *vecino = nodoactual->getCeldasVecinas().at(
          w);  // En cada iteración cogemos un vecino distinto del nodo actual
      float costelocal =
          nodoactual->getCosteLocal() +
          1.0;  // Al desplazarse a la celda vecina, aumentamos su coste en 1

      if (vecino->getVisitada() == false) {  // Si no está en la lista cerrada
        if (vecino->getLista() == false) {   // Ni en la lista abierta
          lista.push_back(vecino);           // Lo colocamos en la lista abierta
          vecino->setLista(true);
        }
        if (costelocal < vecino->getCosteLocal()) {
          vecino->setPadre(
              nodoactual);  // Pasará a tener como predecesor el nodoactual

          // Actualizamos costes
          vecino->setCosteLocal(costelocal);
          if (heuristica == 1) {
            vecino->setCosteGlobal(costelocal +
                                   heuristicaManhattan(vecino, nodoFinal_));
          }
          if (heuristica == 2) {
            vecino->setCosteGlobal(costelocal +
                                   heuristicaEuclides(vecino, nodoFinal_));
          }
        }
      } else {  // Si está visitado (en la lista cerrada)
        if (costelocal < vecino->getCosteLocal()) {
          vecino->setVisitada(false);  // Lo quitamos de la lista cerrada(bool
                                       // de visitado a falso)
          lista.push_back(vecino);  // Insertamos el vecino en la lista abierta
          vecino->setLista(true);
          vecino->setPadre(nodoactual);
          vecino->setCosteLocal(costelocal);  // Actualizamos costes
          if (heuristica == 1) {
            vecino->setCosteGlobal(costelocal +
                                   heuristicaManhattan(vecino, nodoFinal_));
          }
          if (heuristica == 2) {
            vecino->setCosteGlobal(costelocal +
                                   heuristicaEuclides(vecino, nodoFinal_));
          }
        }
      }
    }
  }
  tiempo_ = clock() - tiempo_;
  std::cout << "\033[91m¡No hay solución óptima!\033[0m\n";
}

void Tablero::algoritmoPrimero(int heuristica) {
  // Empezamos desde el nodo elegido como inicial y asignamos el costo local a 0
  Celda *nodoactual = nodoInicial_;
  nodoactual->setCosteLocal(0.0);

  // Decidimos que heurística usar
  if (heuristica == 1)
    nodoactual->setCosteGlobal(heuristicaManhattan(nodoactual, nodoFinal_));

  if (heuristica == 2)
    nodoactual->setCosteGlobal(heuristicaEuclides(nodoactual, nodoFinal_));

  tiempo_ = clock();
  std::list<Celda *> lista;  // Creamos lista abierta

  // Insertamos en la lista abierta
  lista.push_back(nodoactual);
  nodoactual->setLista(true);

  while (!lista.empty()) {
    
    lista.sort([](const Celda *a, const Celda *b) {
      return a->getCosteGlobal() < b->getCosteGlobal();
    });  // Ordenamos de menor a mayor coste global la lista abierta

    nodoactual = lista.front();  // Cogemos el de menor coste

    if (nodoactual ==
        nodoFinal_) {  // Entrará cuando haya encontrado el camino óptimo
      tiempo_ = clock() - tiempo_;

      while (nodoactual != NULL) {
        nodoactual->setCaminoOptimo(true);  // Forma parte del camino óptimo
        optimo_++;
        nodoactual = nodoactual->getPadre();  // El nodoactual pasa a ocupar los
                                              // valores de su nodo padre
      }
      std::cout << "\033[1;93m¡Se ha encontrado una solución óptima!\033[0m"
                << std::endl;
      optimo_ = optimo_ - 1;
      return;
        }
    lista.pop_front();  // Lo eliminamos de la lista abierta ya que lo vamos a
                        // explorar
    nodoactual->setVisitada(true);  // Lo ponemos a visitado, que indica que
                                    // está en la lista cerrada
    nodoactual->setLista(
        false);  // Indicamos que no se encuentra en la lista abierta
    explorado_++;
    establecerConexiones(nodoactual->getPosX(), nodoactual->getPosY(),
                         nodoactual);  // Creamos conexiones del nodoactual

    lista.pop_front();  // Lo eliminamos de la lista abierta ya que lo vamos a
                        // explorar
    nodoactual->setVisitada(true);  // Lo ponemos a visitado, que indica que
                                    // está en la lista cerrada
    nodoactual->setLista(
        false);  // Indicamos que no se encuentra en la lista abierta
    explorado_++;
    establecerConexiones(nodoactual->getPosX(), nodoactual->getPosY(),
                         nodoactual);  // Creamos conexiones del nodoactual
  }
  tiempo_ = clock() - tiempo_;
  std::cout << "\033[91m¡No hay solución óptima!\033[0m\n";
}

// Método sobrecarga para imprimir el tablero
std::ostream &operator<<(std::ostream &os, Tablero &Tablero) {
  if (Tablero.tt) {
    for (size_t i = 0; i < Tablero.fil(); i++) {
      for (size_t j = 0; j < Tablero.col(); j++) {
        Tablero[i][j]->imprimir2(os);
      }
      os << endl;
    }
    return os;
  }

  int aux = 0;
  while (aux < Tablero.col() + 2) {
    os << "\033[1;34m▄\033[0m";
    aux++;
  }

  os << '\n';

  for (int i = 0; i < Tablero.fil(); i++) {
    os << "\033[1;104m \033[0m";

    for (int j = 0; j < Tablero.col(); j++) {
      Tablero[i][j]->imprimir(os);
    }

    os << "\033[1;104m \033[0m\n";
  }

  aux = 0;

  while (aux < Tablero.col() + 2) {
    os << "\033[1;34m▀\033[0m";
    aux++;
  }

  os << '\n';
  return os;
}
