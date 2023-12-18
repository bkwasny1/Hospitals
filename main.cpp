#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <structures.hpp>

int main() {

    std::vector<Spec> specialization = { Ortopedia,
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
                                        Gastroenterologia};
    std::vector<int> spec_value = { 5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5,
                                    5};

    Hospital szpital1(3, 3, specialization, spec_value);

    Point test_point = {1, 3};
    std::cout << BFS(szpital1.get_location(), test_point) << std::endl;


    std::cout << szpital1.doesSuppurt(Ortopedia, 3) << std::endl;
    std::cout << szpital1.get_location().x << std::endl;
    return 0;
}
