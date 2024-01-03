#ifndef HOSPITALS_TABU_HPP
#define HOSPITALS_TABU_HPP

#define Neigbour_mode 1
#define SIZE_ 5

#include "structures.hpp"
#include <map>
#include <utility>
#include <vector>

//pewnie jako tablica o ograniczonej pojemnosci
class TabuList{
public:
    TabuList(int size): size_(size * 2){}

//zmienic inta na zamiane
    void insert_t(std::map<Ambulance, int> pair1, std::map<Ambulance, int> pair2);

    int check_if_in_tabu(int);

private:
    int size_;
    std::vector<std::map<Ambulance, int>> tabu_l;
    int save_index = 0;
};

//na razie voidy

void UpdateTabu();

//tabu bedzie takiego typu jak rozwiazanie
void TabuSearch();

void ObjectiveFunction();

#endif //HOSPITALS_TABU_HPP



