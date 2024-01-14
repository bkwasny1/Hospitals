#include "window.hpp"
#include <iostream>
#include <tabu.hpp>
#include <cfloat>
#include <chrono>

//pamietac o zmianie AMBULANCE_NUMBER

//dane wejsciowe z GUI
int max_liczba_iteracji;
int kryterium_aspiracji;
int dlugosc_listy_tabu;
std::vector<int> dobor_sasiedztwa;

//dane wyjsciowe do GUI
int act_liczba_iteracji = 0;
int liczba_uzyc_kryterium_aspiracji = 0;
int czas_wykonania = 0;
int iteracja_z_najlepszym_wynikiem;
double najlepszy_wynik = DBL_MAX;
int wartosci_funkcji[10000];


int Patient::pat_id = 0;
int Ambulance::amb_id = 0;


int main(){
    wczytaj_dane();

    // Początkowy czas
    auto start = std::chrono::high_resolution_clock::now();


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
    Hospital hos_4(0,  0 , specializations, std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Hospital hos_5(1,  1 , specializations, std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Hospital hos_6(2,  2 , specializations, std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});

    hospital_list.push_back(&hos_1);
    hospital_list.push_back(&hos_2);
    hospital_list.push_back(&hos_3);
    hospital_list.push_back(&hos_4);
    hospital_list.push_back(&hos_5);
    hospital_list.push_back(&hos_6);

    Ambulance ambulance_1(&hos_1);
    Ambulance ambulance_2(&hos_2);
    Ambulance ambulance_3(&hos_3);
    Ambulance ambulance_4(&hos_1);
    Ambulance ambulance_5(&hos_2);
    Ambulance ambulance_6(&hos_3);
    Ambulance ambulance_7(&hos_1);
    Ambulance ambulance_8(&hos_2);

    Patient pat_1(0,6,3,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_2(1,1,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_3(0,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_4(0,3,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_5(1,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_6(0,6,3,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_7(1,1,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_8(0,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_9(0,3,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_10(1,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_11(0,6,3,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_12(1,1,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_13(0,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_14(0,3,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_15(1,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_16(0,6,3,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_17(1,1,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_18(0,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_19(0,3,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_20(1,4,1,1, specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,0});

    patients_list.push_back(&pat_1);
    patients_list.push_back(&pat_2);
    patients_list.push_back(&pat_3);
    patients_list.push_back(&pat_4);
    patients_list.push_back(&pat_5);

    std::map<Ambulance*, int> neigh_to_swap;
    neigh_to_swap.insert(std::make_pair(&ambulance_1,1));
    neigh_to_swap.insert(std::make_pair(&ambulance_2,2));

    std::vector<Ambulance*> wynik = TabuSearch();

    int index_ambulansu = 1;
    for(auto karetka: wynik){
        for(auto pacjent: karetka->get_order()){
            if (pacjent == nullptr){
                break;
            }
            std::cout << "Ambulans " << index_ambulansu << " Pacjent: " << pacjent->get_patient_id() << std::endl;
        }
        index_ambulansu++;
    }

    // Końcowy czas
    auto end = std::chrono::high_resolution_clock::now();
    // Obliczenie różnicy czasu
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    czas_wykonania = (int)duration.count();

    zapisz_dane();

    return 0;
}