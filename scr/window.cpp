#include "window.hpp"

int liczba_iteracji;
int kryterium_aspiracji;
int dlugosc_listy_tabu;
int dobor_sasiedztwa;


int wczytaj_dane(){

    // Strumień do odczytu pliku JSON
    std::ifstream plik(data_file_path);

    // Sprawdź, czy plik został otwarty poprawnie
    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku " << data_file_path << std::endl;
        return 1;
    }

    // Parsuj dane z pliku JSON
    nlohmann::json dane;
    plik >> dane;

    // Wyciągnij dane i zapisz do zmiennych
    liczba_iteracji = dane["liczba_iteracji"];
    kryterium_aspiracji = dane["kryterium_aspiracji"];
    dlugosc_listy_tabu = dane["dlugosc_listy_tabu"];
    dobor_sasiedztwa = dane["dobor_sasiedztwa"];

    // Zamknij plik
    plik.close();

    return 0;
}