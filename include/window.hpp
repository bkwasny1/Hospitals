#ifndef HOSPITALS_WINDOW_HPP
#define HOSPITALS_WINDOW_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

// sciezka do bazy danych
const std::string jsonPath = "../GUI/dane.json";

int wczytaj_dane();

#endif //HOSPITALS_WINDOW_HPP
