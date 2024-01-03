#include "tabu.hpp"
#include "structures.hpp"


/* Sasiedztwa  (przez dostępnych pacjentów rozumie sie ze nie ma ich w liscie tabu)
1 - wymiana zawsze pierwszych wolnych pacjentow miedzy looswymi karetkami
2 - wymiana losowych dostępnych pacjentów między losowymi karetkami
3 - losowa zamiana każdego pacjenta między karetkami
4 - wzięcie najlepszego dostępnego rozwiązania
5 - co n-ta iteracje wziecie najgorszego rozwiazania
*/
void swap(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx){
    std::vector<Patient*> order1 = *amb1.get_order();
    std::vector<Patient*> order2 = *amb2.get_order();
    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;


    // Ustaw zaktualizowane wektory pacjentów z powrotem w odpowiednich
/*    ambulance1.get_order() = &patients1;
    ambulance2.get_order() = &patients2;*/
}


void NeighbourSelect(int Tabu___List, std::vector<Ambulance*> solutions){
    srand(time(NULL));
    int ambulance_idx1 = rand() % AMBULANCE_NUMBER;
    int ambulacne_idx2 = rand() % AMBULANCE_NUMBER;
    while(ambulacne_idx2 == ambulance_idx1){
        ambulacne_idx2 = rand() % AMBULANCE_NUMBER;
    }

    swap(*solutions[ambulance_idx1], *solutions[ambulacne_idx2], 1, 1);
}





void UpdateTabu(){

}

void TabuSearch(){

}