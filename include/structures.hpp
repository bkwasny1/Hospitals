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

#define AMBULANCE_NUMBER 5

//definicja struktur

struct Point {
    int x, y, distance;
};


enum Spec{
    Ortopedia,
    Okulistyka,
    Neurologia,
    Chirurgia,
    Kardiologia,
    Pediatria,
    Endokrynologia,
    Geriatria,
    Ginekologia,
    Urologia,
    Psychiatria,
    Oparzenia,
    Gastroenterologia
};


//zamiana z macierzy na klase reprezentujaca kazdy jeden szpital
class Hospital {
public:
    Hospital(int x, int y, std::vector<Spec> specialization, std::vector<int> spec_value)  {
        for (int i = 0; i < specialization.size(); i++){
            specialization_.insert(std::make_pair(specialization[i], spec_value[i]));
        }
        hospital_coordination_.x = x;
        hospital_coordination_.y = y;
    };

    bool doesSuppurt(Spec specialization, int needed_spec_value);
    const Point get_location() const {return hospital_coordination_;}

private:
    Point hospital_coordination_;
    std::map<Spec, int> specialization_;
};


class Patient{
public:
//injuries jako lista liczb, jesli dana specjalizacja jest potrzebna to wpisujemy jej wymagany poziom,
//jesli nie to 0,lista o stalym rozmiarze, x, y to wspolrzedne macierzy miasta
//time to czas obsługi wypadku i na sorze

    Patient(int x, int y, int time, const int injuries[INJURED_NUMBER], int priority) : time_(time), priority_(priority){
        for (int i = 0; i < INJURED_NUMBER; i++){
            injuries_[i] = injuries[i];
        }
        patient_coordination_.x = x;
        patient_coordination_.y = y;
        select_hospital();
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
    Point get_location();

//wybiera najblizszy szpital bedacy w stanie obsluzyc pacjenta
    void select_hospital();

//zwraca koszt dojazdu do szpitala
    int get_road_cost_patient_hospital();

//zwraca lokalizacje wybranego szpitala
    const Point selected_hospital_location() const { return selected_hospital_->get_location();}

private:
    Point patient_coordination_;
    int injuries_[INJURED_NUMBER]{};
    int time_;
    int priority_;
    Hospital* selected_hospital_;
};

class Ambulance{
public:
    Ambulance(int actual_hospital, int x, int y): actual_hospital_(actual_hospital){
        ambulance_coordination_.x = x;
        ambulance_coordination_.y = y;
    }

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
    Point get_patient_location(int patient_n);

//zwraca wybrany szpital
    const Hospital* get_selected_hospital(int patient_n) const;

//zwraca laczny koszt karetki
    int get_ambulance_cost();


private:
    //jeszcze nie wiem czy int, zalezy od tego jak beda reprezentowane szpitale
    int actual_hospital_;
    std::vector<Patient*> order_;
    int patient_count = 0; //przedstawia liczbe zakolejkowanych pacjentow
    Point ambulance_coordination_; // poczatkowe polozenie karetki
};


//FUNCTIONS

extern std::vector<std::vector<int>> city;

//Funkcja do znajdowania najkrotszej drogi miedzy punktami w miescie, miasto jako
//pionowe i poziome drogi (tam jakas wartosc np 1) miejsca nieosiagalne jako 0
int BFS(const Point start, const Point end, std::vector<std::vector<int>> grid = city);


//liczy koszt przejazdu na podstawie siatki znalezionej przy użyciu BFS
int get_road_cost( const Point& start, const Point& end, int step_time = 1);


#endif //HOSPITALS_STRUCTURES_HPP
