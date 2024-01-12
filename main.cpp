#include <tabu.hpp>
#include "window.hpp"

int main() {
    wczytaj_dane();

    // Wypisz odczytane dane na ekran
    std::cout << "liczba_iteracji: " << liczba_iteracji << std::endl;
    std::cout << "kryterium_aspiracji: " << kryterium_aspiracji << std::endl;
    std::cout << "dlugosc_listy_tabu: " << dlugosc_listy_tabu << std::endl;
    std::cout << "dobor_sasiedztwa: " << dobor_sasiedztwa << std::endl;
    return 0;
}
