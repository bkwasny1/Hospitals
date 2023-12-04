#include "tabu.hpp"
#include "structures.hpp"


/* Sasiedztwa  (przez dostępnych pacjentów rozumie sie ze nie ma ich w liscie tabu)
1 - wymiana zawsze pierwszych wolnych pacjentow miedzy looswymi karetkami
2 - wymiana losowych dostępnych pacjentów między losowymi karetkami
3 - losowa zamiana każdego pacjenta między karetkami
4 - wzięcie najlepszego dostępnego rozwiązania
5 - co n-ta iteracje wziecie najgorszego rozwiazania
*/

void NeighbourSelect(int Tabu___List, std::vector<Ambulance*> solutions){
    srand(time(NULL));
    int ambulance_idx1 = rand() % AMBULANCE_NUMBER;
    int ambulacne_idx2 = rand() % AMBULANCE_NUMBER;
    while(ambulacne_idx2 == ambulance_idx1){
        ambulacne_idx2 = rand() % AMBULANCE_NUMBER;
    }
}



void UpdateTabu(){

}

void TabuSearch(){

}