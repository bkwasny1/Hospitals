#ifndef HOSPITALS_STRUCTURES_HPP
#define HOSPITALS_STRUCTURES_HPP
#include <vector>
#include <iostream>
#include <map>
#include <utility>

//rowne ilosci specjalizacji
#define INJURED_NUMBER 14

//do okreslenia jeszcze co do liczby   length jako ROWS
#define CITY_LENGTH 25
#define CITY_HEIGTH 50


//definicja struktur

struct Point {
    int x, y, distance;
};


class Patient{
public:
//injuries jako lista liczb, jesli dana specjalizacja jest potrzebna to wpisujemy jej wymagany poziom,
//jesli nie to 0,lista o stalym rozmiarze, x, y to wspolrzedne macierzy miasta
//time to czas obsługi wypadku i na sorze

    Patient(int x, int y, int time, const int injuries[INJURED_NUMBER], int priority) : x_(x), y_(y), time_(time), priority_(priority){
        for (int i = 0; i < INJURED_NUMBER; i++){
            injuries_[i] = injuries[i];
        }
    }

//zwraca priorytet
    int get_priority(){return priority_;}

//zwraca urazy w postaci stringow
    std::vector<std::string> get_injuries();

//zwraca stopien zaawansowania urazow
    std::vector<int> get_difficulty();

//zwraca indeksy specjalizacji
    std::vector<int> get_spec_idx();

//zwraca czas obsługi
    int get_time(){return time_;}

//zwraca wspolrzedne
    int* get_location();


private:
    int x_;
    int y_;
    int injuries_[INJURED_NUMBER]{};
    int time_;
    int priority_;
};

class Ambulance{
public:
    Ambulance(int actual_hospital): actual_hospital_(actual_hospital){}

    int number_of_patients() {return patient_count;}
//dodaje pacjenta do karetki
    void add_patient(Patient* patient);

//w kazdej funkcji mozna wybrac o ktorego pacjenta chodzi
//zwraca priorytet pacjenta
    int get_patient_priority(int patient_n);

//zwraca urazy w postaci stringow
    std::vector<std::string> get_patient_injuries(int patient_n);

//zwraca stopien zaawansowania urazow pacjenta
    std::vector<int> get_patient_difficulty(int patient_n);

//zwraca indeksy specjalizacji pacjenta
    std::vector<int> get_patient_spec_idx(int patient_n);

//zwraca czas obsługi pacjenta
    int get_patient_time(int patient_n);

//zwraca wspolrzedne pacjenta
    int* get_patient_location(int patient_n);


private:
    //jeszcze nie wiem czy int, zalezy od tego jak beda reprezentowane szpitale
    int actual_hospital_;
    std::vector<Patient*> order_;
    //przedstawia liczbe zakolejkowanych pacjentow
    int patient_count = 0;
};

//zamiana z macierzy na klase reprezentujaca kazdy jeden szpital

class Hospital {
public:
    Hospital(int x, int y, std::vector<std::string> specialization, std::vector<int> value) : x_(x), y_(y) {
        for (int i = 0; i < specialization.size(); i++){
            specialization_.insert(std::make_pair(specialization[i], value[i]));
        }
    };

private:
    int x_;
    int y_;
    std::map<std::string, int> specialization_;
};

#endif //HOSPITALS_STRUCTURES_HPP
