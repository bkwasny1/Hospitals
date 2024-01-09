#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "tabu.hpp"

int Patient::pat_id = 1;
int Ambulance::amb_id = 1;

void swap1(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx) {
    std::vector<Patient*> order1 = amb1.get_order_try();
    std::vector<Patient*> order2 = amb2.get_order_try();
    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;
    amb1.new_order(order1);
}

int main() {

    std::vector<std::string> specializations {
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

    std::vector<int> abc1 {8, 4, 5, 6, 1, 7, 9, 1, 5, 6, 8, 9, 7};
    std::vector<int> abc2 {6, 7, 1, 3, 7, 7, 9, 5, 5, 7, 8, 5, 1};
    std::vector<int> abc3 {8, 6, 1, 7, 9, 6, 9, 4, 6, 1, 7, 4, 9};

    Hospital H1(0, 0, specializations, abc1);
    Hospital H2(0, 0, specializations, abc2);
    Hospital H3(0, 0, specializations, abc3);

    std::vector<int> value1 {0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 4, 0};
    std::vector<int> value2 {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> value3 {2, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0};

    Patient P1(0, 0, 10, specializations, value1, 9);
    Patient P2(0, 0, 8, specializations, value2, 5);
    Patient P3(0, 0, 2, specializations, value3, 2);

    Ambulance A1(&H1);
    Ambulance A2(&H2);
    Ambulance A3(&H3);

    A1.add_patient(&P1);
    A2.add_patient(&P2);
    A3.add_patient(&P3);



    swap1(A1,  A2, 1, 1);

    std::cout << 1;

    return 0;
}
