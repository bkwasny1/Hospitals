#ifndef HOSPITALS_STRUCTURES_HPP
#define HOSPITALS_STRUCTURES_HPP
#include <vector>
#include <iostream>
#include <map>
#include <utility>

//rowne ilosci specjalizacji
#define INJURED_NUMBER 13

//do okreslenia jeszcze co do liczby   length jako ROWS
#define CITY_LENGTH 25
#define CITY_HEIGTH 50

#define AMBULANCE_NUMBER 5

//definicja struktur


struct Point {
    int x, y, distance;
};

class Hospital {
public:
    Hospital(int x, int y, std::vector<std::string> specialization, std::vector<int> value) : x_(x), y_(y) {
        for (int i = 0; i < specialization.size(); i++){
            specialization_.insert(std::make_pair(specialization[i], value[i]));
        }
    };

    int get_hosp_location_x(){return x_;}

    int get_hosp_location_y(){return y_;}

    std::map<std::string, int> get_spec_list(){return specialization_;}

private:
    int x_;
    int y_;
    std::map<std::string, int> specialization_;
};



class Patient{
public:
    int static pat_id;
//injuries jako lista liczb, jesli dana specjalizacja jest potrzebna to wpisujemy jej wymagany poziom,
//jesli nie to 0,lista o stalym rozmiarze, x, y to wspolrzedne macierzy miasta
//time to czas obsługi wypadku i na sorze

    Patient(int x, int y, int time, std::vector<std::string> specialization, std::vector<int> value, int priority) : x_(x), y_(y), time_(time), priority_(priority), id_(pat_id){
        for (int i = 0; i < INJURED_NUMBER; i++){
            patient_injuries_.insert({specialization[i], value[i]});
        }
        pat_id++;
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

    int get_location_x(){return x_;}

    int get_location_y(){return y_;}

    std::map<std::string, int> get_injuries_list(){return patient_injuries_;}

private:
    int id_;
    int x_;
    int y_;
    int injuries_[INJURED_NUMBER]{};
    int time_;
    int priority_;
    std::map<std::string, int> patient_injuries_;
};

class Ambulance{
public:
    //unikalne id identyfikujace karetke
    static int amb_id;

    Ambulance(Hospital *actual_hospital): actual_hospital_(actual_hospital), id(amb_id){
        amb_id++;
    }

    //dodanie operatorow porownania
    bool operator==(const Ambulance& other)const{
        return id == other.id;
    }
    bool operator<(const Ambulance& other)const{
        return id < other.id;
    }
    bool operator>(const Ambulance& other)const{
        return id > other.id;
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
    int* get_patient_location(int patient_n);

    std::vector<Patient*>* get_order(){return &order_;}

    std::vector<Patient*> get_order_try(){return order_;};

    void new_order(std::vector<Patient*> ord){order_ = ord;}

    Patient* get_patient(int patient_idx){return order_[patient_idx - 1];}

    int get_amb_location_x(){return actual_hospital_ -> get_hosp_location_x();}
    int get_amb_location_y(){return actual_hospital_ -> get_hosp_location_y();}

    void change_hospital(Hospital* new_hospital) {
        actual_hospital_ = new_hospital;
    }

private:
    //jeszcze nie wiem czy int, zalezy od tego jak beda reprezentowane szpitale
    Hospital* actual_hospital_;
    int id;
    std::vector<Patient*> order_;
    //przedstawia liczbe zakolejkowanych pacjentow
    int patient_count = 0;
};



#endif //HOSPITALS_STRUCTURES_HPP
