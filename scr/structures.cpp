#include "structures.hpp"
#include <vector>
#include <string>
#include <queue>

//implementacja struktur

int Hospitals_spec = 0;

std::vector<std::vector<int>> city = {
        {1, 2, 2, 1, 1 ,1, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 2, 3, 4, 5},
        {0, 2, 2, 1, 1 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 2, 2, 1, 1 ,1, 0, 0, 1, 0 ,0, 0, 0, 1, 1 ,1, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1 ,1, 0, 0, 1, 1 ,0, 0, 0, 1, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1 ,0, 0, 0, 0, 1 ,1, 0, 0, 1, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 1, 1, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 1, 0, 0 ,0, 1, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 1, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 1, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1},
};


//jako permutacja dla kazdej karetki z doborem pacjenta/pacjentow,
//moze klasa a moze slownik
int solution = 0;

int emergency = 0;


//te dwie to tak wstępnie, albo enum albo zwykła lista cos sie moze przyda

std::string specializations[INJURED_NUMBER] = {
        "Ortopedia",
        "Okulistyka",
        "Neurologia",
        "Chirurgia",
        "Kardiologia",
        "Pediatria",
        "Endokrynologia",
        "Geriatria",
        "Ginekologia",
        "Urologia",
        "Psychiatria",
        "Oparzenia",
        "Gastroenterologia"};

enum class Spec{
    Ortopedia,
    Okulistyka,
    Neurologia,
    Chirurgia,
    Kardiologia,
    Pediatria,
    Endokrynologia,
    Geriatria,
    Ginekologia,
    Urologia,
    Psychiatria,
    Oparzenia,
    Gastroenterologia
};


//PATIENT

std::vector<std::string> Patient::get_injuries(){
    std::vector<std::string> patient_injuries;
    for (int i = 0; i < INJURED_NUMBER; i++){
        if (injuries_[i] != 0){
            patient_injuries.push_back(specializations[i]);
        }
    }
    return patient_injuries;
};

std::vector<int> Patient::get_difficulty() {
    std::vector<int> priority;
    for (int i = 0; i < INJURED_NUMBER; i++){
        if (injuries_[i] != 0){
            priority.push_back(injuries_[i]);
        }
    }
    return priority;
}

std::vector<int> Patient::get_spec_idx(){
    std::vector<int> priority;
    for (int i = 0; i < INJURED_NUMBER; i++){
        if (injuries_[i] != 0){
            priority.push_back(i);
        }
    }
    return priority;
}

int* Patient::get_location(){
    int loc[2] = {x_, y_};
    int * loc_return = loc;
    return loc_return;
}


//AMBULACE

void Ambulance::add_patient(Patient* patient) {
    Patient *patient_pointer = patient;
    order_.push_back(patient_pointer);
    patient_count++;
}

//zwraca priorytet pacjenta
int Ambulance::get_patient_priority(int patient_n){
    return order_[patient_n] -> get_priority();
};

//zwraca urazy w postaci stringow
std::vector<std::string> Ambulance::get_patient_injuries(int patient_n){
    return order_[patient_n] -> get_injuries();
};

//zwraca stopien zaawansowania urazow pacjenta
std::vector<int> Ambulance::get_patient_difficulty(int patient_n){
    return order_[patient_n] -> get_difficulty();
};

//zwraca indeksy specjalizacji pacjenta
std::vector<int> Ambulance::get_patient_spec_idx(int patient_n){
    return order_[patient_n] -> get_spec_idx();
};

//zwraca czas obsługi pacjenta
int Ambulance::get_patient_time(int patient_n){
    return order_[patient_n] -> get_time();
};

//zwraca wspolrzedne pacjenta
int* Ambulance::get_patient_location(int patient_n){
    return order_[patient_n] -> get_location();
};



//Funkcje

bool isValid(int x, int y, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited) {
    return (x >= 0 && x < CITY_LENGTH && y >= 0 && y < CITY_HEIGTH && grid[x][y] && !visited[x][y]);
}


//Funkcja do znajdowania najkrotszej drogi miedzy punktami w miescie, miasto jako
//pionowe i poziome drogi (tam jakas wartosc np 1) miejsca nieosiagalne jako 0
int BFS(std::vector<std::vector<int>>& grid, const Point& start, const Point& end) {
    std::vector<std::vector<bool>> visited(CITY_LENGTH, std::vector<bool>(CITY_HEIGTH, false));
    std::queue<Point> q;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    q.push(start);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) {
            std::cout << "Znaleziono cel!" << std::endl;
            return current.distance; // Zwraca ilość kroków do celu
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, grid, visited)) {
                visited[newX][newY] = true;
                q.push({newX, newY, current.distance + grid[newX][newY]});
            }
        }
    }

    std::cout << "Nie znaleziono ścieżki!" << std::endl;
    return -1; // Brak ścieżki
}