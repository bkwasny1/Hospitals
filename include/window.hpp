#ifndef HOSPITALS_WINDOW_HPP
#define HOSPITALS_WINDOW_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

// sciezka do bazy danych
const std::string data_file_path = "../GUI/dane.json";

//TODO: zmienne sa tu deklarowane tymczasowo, docelowo trzeba to umiescic pewnie gdzies w structures.hpp
extern int liczba_iteracji;
extern int kryterium_aspiracji;
extern int dlugosc_listy_tabu;
extern int dobor_sasiedztwa;


int wczytaj_dane();

#endif //HOSPITALS_WINDOW_HPP
