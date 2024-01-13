#include "window.hpp"
#include <iostream>
#include <tabu.hpp>
#include <cfloat>

//dane wejsciowe z GUI
int max_liczba_iteracji = 10000;
int kryterium_aspiracji;
int dlugosc_listy_tabu;
int dobor_sasiedztwa;

//dane wyjsciowe do GUI
int act_liczba_iteracji;
int liczba_uzyc_kryterium_aspiracji;
int czas_wykonania;
int iteracja_z_najlepszym_wynikiem;
double najlepszy_wynik = DBL_MAX;
int wartosci_funkcji[16];



int Patient::pat_id = 0;
int Ambulance::amb_id = 0;

void swap1(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx) {

    std::vector<Patient*> order1 = amb1.get_order();
    std::vector<Patient*> order2 = amb2.get_order();

    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;

    amb1.new_order(order1);
    amb2.new_order(order2);
}


void NeighbourSelect(Ambulance &amb1, Ambulance &amb2, std::vector<Ambulance> solutions){

    swap1(amb1, amb2, 0, 0);

}


int main(){
    std::vector<std::string> specializations= {
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

    Hospital hos_1(0,  0 , specializations, std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Hospital hos_2(1,  1 , specializations, std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Hospital hos_3(2,  2 , specializations, std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});

    hospital_list.push_back(&hos_1);
    hospital_list.push_back(&hos_2);
    hospital_list.push_back(&hos_3);

    Ambulance ambulance_1(&hos_1);
    Ambulance ambulance_2(&hos_2);
    Ambulance ambulance_3(&hos_3);

    Patient pat_1(0,6,3,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_2(1,1,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_3(0,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_4(0,3,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_5(1,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});

    patients_list.push_back(&pat_1);
    patients_list.push_back(&pat_2);
    patients_list.push_back(&pat_3);
    patients_list.push_back(&pat_4);
    patients_list.push_back(&pat_5);

    std::map<Ambulance*, int> neigh_to_swap;
    neigh_to_swap.insert(std::make_pair(&ambulance_1,1));
    neigh_to_swap.insert(std::make_pair(&ambulance_2,2));
    
    TabuSearch();
    return 0;
}