#include "tabu.hpp"
#include "structures.hpp"
#include "queue"

#define NOT_IN_TABU 0
#define IN_TABU 1

//Funkcje
//lista wszsystkich szpitali, trzeba ja kiedys stworzyc
std::vector<Hospital*> hospital_list;


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


//funckja szukajaca odpowiedniego szpitala dla pacjenta, zwraca ten szpital
//najlepszy pod wzgledem czasu

Hospital* get_best_hospital(Patient *pat){
    std::vector<Hospital*> spec_hospital;
    std::map<std::string, int> patient_injuries = pat -> get_injuries_list();
    for (auto hospital : hospital_list){
        std::map<std::string, int> spec = hospital->get_spec_list();
        for (auto injurie : patient_injuries){
            //dokonczyc
            if (spec[injurie.first] < patient_injuries[injurie.first]){
                break;
            }
        }
        //trzeba dodac szpital jesli przejdzie cala petle
    }
}

//Tabulist

void TabuList::update_tabu(std::map<Ambulance, int> const &pair1, std::map<Ambulance, int> const &pair2){
    if (size_ >= save_index){
        tabu_l.push_back(pair1);
        tabu_l.push_back(pair2);
        save_index = save_index + 2;
    }
    else{
        int index = save_index % size_;
        tabu_l[index] = pair1;
        tabu_l[index + 1] = pair2;
        save_index = save_index + 2;
    }
};

//dla parzystych indeksow sprawdza sasiada z prawej, dla nieparzystych z lewej
//

int TabuList::check_if_in_tabu(std::map<Ambulance, int> const &pair1, std::map<Ambulance, int> const &pair2){
    if (size_ >= save_index && save_index == 0){
        return NOT_IN_TABU;
    }
    else{
        int i = 0;
        for(auto &pair_in_tabu : tabu_l){
            if(pair_in_tabu == pair1){
                if (i % 2 == 1){
                    if (tabu_l[i - 1] == pair2) {
                        return IN_TABU;
                    }
                }
                if (i % 2 == 0){
                    if (tabu_l[i + 1] == pair2){
                        return IN_TABU;
                    }
                }
            }
            i++;
        }
        return NOT_IN_TABU;
    }
}

/* Sasiedztwa  (przez dostępnych pacjentów rozumie sie ze nie ma ich w liscie tabu)
1 - wymiana zawsze pierwszych wolnych pacjentow miedzy looswymi karetkami
2 - wymiana losowych dostępnych pacjentów między losowymi karetkami
3 - losowa zamiana każdego pacjenta między karetkami
4 - wzięcie najlepszego dostępnego rozwiązania
5 - co n-ta iteracje wziecie najgorszego rozwiazania
*/

void swap(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx){
    std::map<Ambulance, int> pair1 {{amb1, patient1_idx}};
    std::map<Ambulance, int> pair2 {{amb2, patient2_idx}};

    std::vector<Patient*> order1 = *amb1.get_order();
    std::vector<Patient*> order2 = *amb2.get_order();
    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;

    // Ustaw zaktualizowane wektory pacjentów z powrotem w odpowiednich
/*    ambulance1.get_order() = &patients1;
    ambulance2.get_order() = &patients2;*/
}

//dodac TabuListe w implementacji
void NeighbourSelect(int Tabu___List, std::vector<Ambulance*> solutions){
    srand(time(NULL));
    int ambulance_idx1 = rand() % AMBULANCE_NUMBER;
    int ambulacne_idx2 = rand() % AMBULANCE_NUMBER;
    while(ambulacne_idx2 == ambulance_idx1){
        ambulacne_idx2 = rand() % AMBULANCE_NUMBER;
    }

    swap(*solutions[ambulance_idx1], *solutions[ambulacne_idx2], 1, 1);
}

//funckaj celu
double ObjectiveFunction(std::vector<Ambulance*> const &solution){
    double cost;
    for (auto ambulance : solution){
        for (auto patient : *ambulance->get_order()){
            int p_time = patient->get_time();
            Point pat_loc = {patient->get_location_x(), patient ->get_location_y(), 0};
            Point amb_loc = {ambulance->get_amb_location_x(), ambulance->get_amb_location_y(), 0};
            int amb_to_pat_time = BFS(city, amb_loc, pat_loc);
        }
    }
}

//algorytm tabu
std::vector<Ambulance*> TabuSearch(){

}