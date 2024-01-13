#include <tabu.hpp>
#include "window.hpp"

//dane wejsciowe z GUI
int max_liczba_iteracji;
int kryterium_aspiracji;
int dlugosc_listy_tabu;
int dobor_sasiedztwa;

//dane wyjsciowe do GUI
int act_liczba_iteracji;
int liczba_uzyc_kryterium_aspiracji;
int czas_wykonania;
int iteracja_z_najlepszym_wynikiem;
int wartosci_funkcji[16];

int main() {
    act_liczba_iteracji = 5;
    liczba_uzyc_kryterium_aspiracji = 6;
    czas_wykonania = 7;
    iteracja_z_najlepszym_wynikiem = 8;

    wartosci_funkcji[1] = 5;
    wartosci_funkcji[3] = 2;
    zapisz_dane();


    wczytaj_dane();

    // Wypisz odczytane dane na ekran
    std::cout << "max_liczba_iteracji: " << max_liczba_iteracji << std::endl;
    std::cout << "kryterium_aspiracji: " << kryterium_aspiracji << std::endl;
    std::cout << "dlugosc_listy_tabu: " << dlugosc_listy_tabu << std::endl;
    std::cout << "dobor_sasiedztwa: " << dobor_sasiedztwa << std::endl;
    return 0;
}
