#include "Sistema.h"
#include <iostream>

int main() {
    Sistema s("exercicios.txt", "fichas.txt", "historico.txt");
    s.iniciar();
    std::cout << "Programa finalizado.\n";
    return 0;
}