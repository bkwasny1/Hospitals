import json
import tkinter as tk
from tkinter import ttk

class GUI(tk.Tk):
    def __init__(self):
        self.data_to_save = {"liczba_iteracji": None,
                             "kryterium_aspiracji": None,
                             "dlugosc_listy_tabu": None,
                             "dobor_sasiedztwa": None} #dane zapisywane w .json

        self.input_data = {"liczba_iteracji": None,
                           "liczba_uzyc_kryteriow_aspiracji": None,
                           "czas_obliczen": None,
                           "iteracja_znalazla_wynik": None,
                           "optymalne_rozwiazanie": None,
                           "kolejne_wartosci_funkcji": None}

        #frontend
        super().__init__()
        self.title("Algorytm TS") # Ustawienie tytułu okna
        self.geometry("1000x800") # Ustawienie rozmiarów okna

        # Utwórz zakładki
        self.notebook = ttk.Notebook(self, padding=10)
        self.utworz_zakladke_zapisu_danych()
        self.utworz_zakladke_wyniku()

        # Wyświetl zakładki w pełnej szerokości i wysokości okna
        self.notebook.grid(row=0, column=0, sticky="nsew")
        # Ustaw wagi dla kolumn i wierszy
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)


    def utworz_zakladke_zapisu_danych(self):
        self.karta1 = tk.Frame(self.notebook)
        self.dodaj_pola_karty1()
        self.notebook.add(self.karta1, text="Dane do algorytmu")


    def dodaj_pola_karty1(self):
        # liczba iteracji
        self.label_liczba_iteracji = tk.Label(self.karta1, text="liczba iteracji")
        self.label_liczba_iteracji.grid(row=0, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_liczba_iteracji = tk.Entry(self.karta1)
        self.entry_liczba_iteracji.grid(row=0, column=0, padx=10, pady=10)

        # dlugosc listy tabu
        self.label_dlugosc_listy_tabu = tk.Label(self.karta1, text="dlugosc listy tabu")
        self.label_dlugosc_listy_tabu.grid(row=1, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_dlugosc_listy_tabu = tk.Entry(self.karta1)
        self.entry_dlugosc_listy_tabu.grid(row=1, column=0, padx=10, pady=10)

        # kryterium aspiracji
        self.label_kryterium_aspiracji = tk.Label(self.karta1, text="kryterium aspiracji")
        self.label_kryterium_aspiracji.grid(row=2, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_kryterium_aspiracji = tk.Entry(self.karta1)
        self.entry_kryterium_aspiracji.grid(row=2, column=0, padx=10, pady=10)

        # wybierz dobor sasiedztwa
        self.label_dobor_sasiedztwa = tk.Label(self.karta1, text="wybierz dobor sasiedztwa")
        self.label_dobor_sasiedztwa.grid(row=4, column=1)  # Przesunięcie napisu
        self.combobox_dobor_sasiedztwa = ttk.Combobox(self.karta1, values=["sasiedztwo1", "sasiedztwo2", "sasiedztwo3"])
        self.combobox_dobor_sasiedztwa.set("sasiedztwo1")  # Domyślna wartość
        self.combobox_dobor_sasiedztwa.grid(row=4, column=0, padx=10, pady=10)


        self.przycisk_karta1 = tk.Button(self.karta1, text="Zapisz", command=self.zapisz_wartosci_GUI)
        self.przycisk_karta1.grid(row=50, column=0, padx=10, pady=10)


    def zapisz_wartosci_GUI(self):
        self.data_to_save["liczba_iteracji"] = self.entry_liczba_iteracji.get()
        self.data_to_save["kryterium_aspiracji"] = self.entry_kryterium_aspiracji.get()
        self.data_to_save["dlugosc_listy_tabu"] = self.entry_dlugosc_listy_tabu.get()
        self.data_to_save["dobor_sasiedztwa"] = self.wybierz_sasiedztwo()

        print(self.data_to_save)
        self.save_data()


    def wybierz_sasiedztwo(self):
        sasiedztwo = self.combobox_dobor_sasiedztwa.get()
        if sasiedztwo == "sasiedztwo1":
            return 1
        elif sasiedztwo == "sasiedztwo2":
            return 2
        elif sasiedztwo == "sasiedztwo3":
            return 3


    def save_data(self):
        # Zapis do pliku JSON
        with open("dane.json", "w") as file:
            json.dump(self.data_to_save, file)


    def utworz_zakladke_wyniku(self):
        self.karta2 = tk.Frame(self.notebook)

        # Utwórz zmienną do przechowywania wartości wprowadzonej przez użytkownika
        self.wartosc_var = tk.StringVar()

        # Dodaj pole tekstowe
        # Etykieta do wyświetlania wartości
        self.etykieta_wartosci = tk.Label(self.karta2, text="123")
        self.etykieta_wartosci.pack(padx=10, pady=10)

        # Dodaj przycisk do wywołania funkcji po naciśnięciu
        self.przycisk_wyswietlania = tk.Button(self.karta2, text="Wyswietl Wartosc", command=self.wyswietl_wyniki_algorytmu)
        self.przycisk_wyswietlania.pack(padx=10, pady=10)

        self.notebook.add(self.karta2, text="wyniki")


    def wyswietl_wyniki_algorytmu(self):
        try:
            # Wczytaj dane z pliku JSON
            with open('wynik.json', 'r') as plik_json:
                dane = json.load(plik_json)

            # random_zmienna = 1
            # # Wyświetl wartość w etykiecie
            # self.etykieta_wartosci.config(text="Wprowadzona wartość: {}".format(random_zmienna))

        except Exception as e:
            # Wyświetl wartość w etykiecie
            self.etykieta_wartosci.config(text="Algorytm nie zostal uruchomiony (nie udalo sie odczytac wyniku)")



if __name__ == "__main__":
    app = GUI()
    app.mainloop()