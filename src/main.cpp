#include <fstream>
#include <iostream>
#include <string>

#include "../include/tablero.hpp"

int main(void) {
  system("clear");
  int fil = 0, col = 0, heuristica, initx, inity, finalx, finaly;

  std::cout
      << "\n\t\033[1;93m¡Bienvenido al simulador de entorno del taxi!\033[0m\n";

  std::cout << "\n\033[0mIntroduzca el número de \033[96mfilas: ";
  std::cin >> fil;
  std::cout << "\n\033[0mIntroduzca el número de \033[96mcolumnas: ";
  std::cin >> col;
  Tablero tablero(
      fil,
      col);  // Creamos la tablero con las filas y columnas proporcionadas

  do {  // Obtenemos posición inicial

    std::cout << "\n\033[0mIntroduzca la posición \033[93minicial:\n\n";
    std::cout << "\t\033[0mPosición \033[96mi: ";
    std::cin >> initx;
    std::cout << "\t\033[0mPosición \033[96mj: ";
    std::cin >> inity;
    if (initx > fil || initx < 0 || inity > col || inity < 0)
      std::cout << "\t\033[91mPosición no válida, repita una nueva "
                   "posición.\033[0m\n";

  } while (initx > fil || initx < 0 || inity > col || inity < 0);

  tablero.setNodoInicial(initx, inity);

  do {  // Obtenemos posición final

    std::cout << "\n\033[0mIntroduzca la posición \033[93mfinal:\n\n";
    std::cout << "\t\033[0mPosición \033[96mi: ";
    std::cin >> finalx;
    std::cout << "\t\033[0mPosición \033[96mj: ";
    std::cin >> finaly;
    if (finalx > fil || finalx < 0 || finaly > col || finaly < 0)
      std::cout << "\t\033[91mPosición no válida, repita una nueva "
                   "posición.\033[0m\n";

  } while (finalx > fil || finalx < 0 || finaly > col || finaly < 0);

  tablero.setNodoFinal(finalx, finaly);

  // Heurística a usar
  std::cout
      << "\n\033[0mIndique la \033[96mheurística\033[0m a usar: "
         "(\033[96m1\033[0m)Manhattan, (\033[96m2\033[0m)Euclidean: \033[96m";
  std::cin >> heuristica;

  while ((heuristica != 1) && (heuristica != 2)) {
    std::cout
        << "\033[91mOpción no válida.\033[0m Inténtelo de nuevo: \033[96m";
    std::cin >> heuristica;
  }

  // Imprimimos datos por pantalla
  tablero.algoritmoAEstrella(heuristica);  // Aplicamos algoritmo A*
  // std::cout << tablero << '\n';
  tablero.salida();
  std::cout
      << "\033[1;93mEl camino amarillo muestra la ruta más óptima.\033[0m\n";
  std::cout << "\033[96mNodos explorados:\033[0m " << tablero.explorado_
            << '\n';
  std::cout << "\033[96mCamino óptimo:\033[0m " << tablero.optimo_ << '\n';
  std::cout << "\033[96mTiempo estimado:\033[0m "
            << double(tablero.tiempo_) / CLOCKS_PER_SEC << '\n';
  std::cout << "\n\t\033[1;93m!Gracias por utilizar esta simulación, sigue "
               "conduciendo con cuidado!\033[0m\n\n";

  return 0;
}
