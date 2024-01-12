#include "structures.hpp"
#include <vector>
#include <string>

//implementacja struktur

//te dwie to tak wstępnie, albo enum albo zwykła lista cos sie moze przyda




//AMBULACE

void Ambulance::add_patient(Patient* patient) {
    order_[patient_count] = patient;
    patient_count++;
}



