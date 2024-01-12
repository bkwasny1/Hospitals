#include "window.hpp"

int wczytaj_dane(){

    // Strumień do odczytu pliku JSON
    std::ifstream plik(jsonPath);

    // Sprawdź, czy plik został otwarty poprawnie
    if (!plik.is_open()) {
    std::cerr << "Nie mozna otworzyc pliku " << jsonPath << std::endl;
    return 1; // Zwróć kod błędu
    }

    // Parsuj dane z pliku JSON
    nlohmann::json dane;
    plik >> dane;

    // Wyciągnij dane i zapisz do zmiennych
    std::string imie = dane["imie"];
    int wiek = dane["wiek"];

    // Wypisz odczytane dane na ekran
    std::cout << "Imie: " << imie << std::endl;
    std::cout << "Wiek: " << wiek << " lat" << std::endl;

    // Zamknij plik
    plik.close();

    return 0;
}