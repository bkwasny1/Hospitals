#include "tabu.hpp"
#include <queue>
#include <iostream>
#include <variant>

#define NOT_IN_TABU 0
#define IN_TABU 1

#define FIRST_NEIGH 1
#define SECOND_NEIGH 2
#define THIRD_NEIGH 3
#define FOURTH_NEIGH 4

#define MAX_ITER 10000
#define CHOOSEN_NEIG 1
#define ASPIRATION 10000


double cost = 0;

std::vector<std::string> specializations = {
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

//sprawdzilem swapa, get_best_hospital i objectivefunction - dzialaja poprawnie

std::vector<std::vector<int>> city {
        {1, 2, 2, 1, 1 ,1, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 2, 3, 4, 5},
        {0, 2, 2, 1, 1 ,0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 2, 2, 1, 1 ,1, 0, 0, 1, 0 ,0, 0, 0, 1, 1 ,1, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1 ,1, 0, 0, 1, 1 ,0, 0, 0, 1, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1 ,0, 0, 0, 0, 1 ,1, 0, 0, 1, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 1, 1, 0 ,0, 1, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 1, 0, 0 ,0, 1, 1, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 3, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 3, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 1, 1, 0 ,0, 0, 0, 3, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 2, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 2, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 1, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 1, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 0, 0, 1, 0 ,0, 0, 0, 1, 0 ,0, 0, 1, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0},
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

//Funkcje
//lista wszsystkich szpitali, trzeba ja kiedys stworzyc
std::vector<Hospital*> hospital_list;

//lista wszystkich pacjentow
std::vector<Patient*> patients_list;

//lista wszystkich karetek
std::vector<Ambulance*> ambulance_list;

int apiration_usage_counter;

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
    return -1; // Brak ścieżki
}


//funckja szukajaca odpowiedniego szpitala dla pacjenta, zwraca ten szpital
//najlepszy pod wzgledem czasu

Hospital* get_best_hospital(Patient *pat){
    std::vector<Hospital*> spec_hospital;
    std::map<std::string, int> patient_injuries = pat -> get_injuries_list();

    for (auto hospital : hospital_list){
        int correct = 1;
        std::map<std::string, int> spec = hospital->get_spec_list();
        for (auto injurie : patient_injuries){
            if (spec[injurie.first] < patient_injuries[injurie.first]){
                correct = 0;
                break;
            }
        }
        if (correct == 1){
            spec_hospital.push_back(hospital);
        }
    }

    int min_time = 9999999;
    Hospital* besthospital = spec_hospital[0];

    for (auto hospital : spec_hospital){
        Point hosp_loc = Point{hospital->get_hosp_location_x(), hospital->get_hosp_location_y(), 0};
        Point patient_loc = Point{pat->get_location_x(), pat->get_location_y(), 0};
        int travel_time = BFS(city, patient_loc, hosp_loc);
        if (min_time > travel_time) {
            besthospital = hospital;
        }
    }
    return besthospital;
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

//zamienia ze soba miejsca w wektorze order na indeksach wektora
void swap(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx) {

    std::vector<Patient*> order1 = amb1.get_order();
    std::vector<Patient*> order2 = amb2.get_order();

    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;

    amb1.new_order(order1);
    amb2.new_order(order2);
}


/* Sasiedztwa  (przez dostępnych pacjentów rozumie sie ze nie ma ich w liscie tabu)
1 - wymiana zawsze pierwszych z wolnych pacjentow miedzy losowymi karetkami
2 - wymiana losowych dostępnych pacjentów między losowymi karetkami
3 - przerzucenie pacjenta
4 - losowa zamiana

*/

//funkcja celu
double ObjectiveFunction(std::vector<Ambulance*> const &solution){
    double cost;
    for (auto ambulance : solution){
        Hospital* primaty_hospital = ambulance -> get_actual_hospital();

        for (auto patient : ambulance->get_order()){
            if (patient == nullptr){
                break;
            }
//uwzglednic jeszcze czas jaki pacjent czeka
            int p_time = patient->get_time();
            Point pat_loc = {patient->get_location_x(), patient ->get_location_y(), 0};
            Point amb_loc = {ambulance->get_amb_location_x(), ambulance->get_amb_location_y(), 0};
            int amb_to_pat_time = BFS(city, amb_loc, pat_loc);
            Hospital* best_hospital = get_best_hospital(patient);
            Point hos_loc = {best_hospital->get_hosp_location_x(), best_hospital->get_hosp_location_y(), 0};
            int pat_to_hosp_time = BFS(city, pat_loc, hos_loc);
            int patient_priority = patient->get_priority();
            cost = cost + patient_priority * (p_time + amb_to_pat_time + pat_to_hosp_time);
            ambulance->change_hospital(best_hospital);
        }
        ambulance->change_hospital(primaty_hospital);
    }
    return cost;
}

//trzeba uzyc kilku sasiedztw naraz
void NeighbourSelect(TabuList Tabu, std::vector<Ambulance*> solutions, int choose_neigh){
    switch(choose_neigh) {
        case FIRST_NEIGH: {
            srand(time(nullptr));
            int swap_amp1_idx = 0;   // indeksy dla listy order_ poczatkowo rowne 0
            int swap_amp2_idx = 0;

            int ambulance_idx1 = rand() % AMBULANCE_NUMBER;  //wybor losowych karetek
            int ambulance_idx2 = rand() % AMBULANCE_NUMBER;

            while (ambulance_idx2 == ambulance_idx1){
                ambulance_idx2 = rand() % AMBULANCE_NUMBER;
            }

            std::vector<Patient*> order1 = solutions[ambulance_idx1]->get_order();
            std::vector<Patient*> order2 = solutions[ambulance_idx2]->get_order();

            int pat1_id = order1[swap_amp1_idx] -> get_patient_id();
            int pat2_id = order2[swap_amp2_idx] -> get_patient_id();

            std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat1_id}};
            std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat2_id}};

            while (Tabu.check_if_in_tabu(pair1, pair2)){
                swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], swap_amp1_idx, swap_amp2_idx);
                if (cost - ObjectiveFunction(solutions) >  ASPIRATION){
                    apiration_usage_counter++;
                    break;
                }
                else{
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], swap_amp1_idx, swap_amp2_idx);
                }
                if (order1[swap_amp1_idx + 1] != nullptr){
                    swap_amp1_idx++;
                    pat1_id = order1[swap_amp1_idx] -> get_patient_id();
                    pair1 = {{*solutions[ambulance_idx1], pat1_id}};

                }
                else if (order2[swap_amp2_idx + 1] != nullptr){
                    swap_amp2_idx++;
                    pat2_id = order2[swap_amp2_idx] -> get_patient_id();
                    pair2 = {{*solutions[ambulance_idx2], pat2_id}};
                }
            }

            swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], swap_amp1_idx, swap_amp2_idx);
            break;
        }

        case SECOND_NEIGH: {
            srand(time(nullptr));
            int ambulance_idx1;
            int ambulance_idx2;

            int numb_of_pat_idx1;  //liczba pacjentów dla wybranych losowo karetek
            int numb_of_pat_idx2;

            int pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
            int pat_idx2;

            std::map<Ambulance, int> pair1;
            std::map<Ambulance, int> pair2;

            while(true){
                ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //wybór losowych karetek
                ambulance_idx2 = rand() % AMBULANCE_NUMBER;

                while (ambulance_idx2 == ambulance_idx1) {
                    ambulance_idx2 = rand() % AMBULANCE_NUMBER;
                }

                numb_of_pat_idx1 = solutions[ambulance_idx1]->get_patient_count();  //liczba pacjentów dla wybranych losowo karetek
                numb_of_pat_idx2 = solutions[ambulance_idx2]->get_patient_count();

                pat_idx1 = rand() % numb_of_pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
                pat_idx2 = rand() % numb_of_pat_idx2;

                std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat_idx1}};
                std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat_idx2}};

                swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                if (Tabu.check_if_in_tabu(pair1, pair2) && (cost - ObjectiveFunction(solutions)) > ASPIRATION){
                    apiration_usage_counter++;
                    break;
                }
                else{
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                }
                if(!Tabu.check_if_in_tabu(pair1, pair2)){
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                    break;
                }
            }

            Tabu.update_tabu(pair1, pair2);
            break;
        }


        case THIRD_NEIGH:{
            srand(time(nullptr));
            int counter = 0;
            int ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //wybór losowej kareteki z której bedzie usuwany pacjent
            int ambulance_idx2 = rand() % AMBULANCE_NUMBER;   //wybór losowej karetki do której bedzie dodawany pacjent

            int numb_of_pat_idx1 = solutions[ambulance_idx1]->get_patient_count();  //liczba pacjentów dla wybranej losowo karetki z której będzie usuwany pacjent

            int pat_idx1 = rand() % numb_of_pat_idx1;  //losowy wybór pacjenta do usunięcia


            while (ambulance_idx2 == ambulance_idx1) {
                ambulance_idx2 = rand() % AMBULANCE_NUMBER;
                counter++;

            }

            std::vector<Patient*> order1 = solutions[ambulance_idx1]->get_order();
            std::vector<Patient*> order2 = solutions[ambulance_idx2]->get_order();

            solutions[ambulance_idx2]->add_patient(order1[pat_idx1]);

            order1.erase(order1.cbegin()+pat_idx1);

            //Trzeba wymyslic jak w tym sąsiedztwie dodawać to listy tabu  i sprawdzanie czy zabronienie jest w tabu liscie


            break;
        }
        case FOURTH_NEIGH:{
            break;
        }
        default:
            break;
    }
}

void create_first_solution(){
    int counter;
    for (auto patient : patients_list){
        ambulance_list[counter]->add_patient(patient);
        counter++;
        if (counter == AMBULANCE_NUMBER){
            counter = 0;
        }
    }
}
//algorytm tabu

std::vector<Ambulance*> TabuSearch(){
    //tworzenie tabu listy
    TabuList tabu_l = TabuList(TABU_SIZE);
    //Inicjalizowanie pierwszego rozwiązania
    create_first_solution();
    //tu trzeba bedzie sprawdzic czy kopiuje czy bedzie sie zmienial razem z ambulacne list

    std::vector<Ambulance*> solution = ambulance_list;
    std::vector<Ambulance*> global_solution;

    cost = ObjectiveFunction(global_solution);

    for (int i = 0; i < MAX_ITER; i++){
        //w tej funkcji od razu dodaje do tabu, zeby nie tworzyc kolejnych wskaznikow
        NeighbourSelect(tabu_l, solution, CHOOSEN_NEIG);

        double cost_temp = ObjectiveFunction(solution);
        if (cost_temp < cost){
            cost = cost_temp;
            global_solution = solution;
        }
    }

    return global_solution;
}
